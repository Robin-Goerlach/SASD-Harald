#include <harald/catalog.hpp>

#include <sqlite3.h>

#include <stdexcept>
#include <string>
#include <utility>

namespace harald {
namespace {
/**
 * A statement is a short-lived resource. Closing it in the destructor is
 * important: outstanding SQLite statements can prevent a DB handle from
 * closing, especially after exceptions or early returns.
 */
class Statement final {
public:
    Statement(sqlite3* db, const char* sql) : db_(db) {
        if (sqlite3_prepare_v2(db, sql, -1, &stmt_, nullptr) != SQLITE_OK) {
            throw std::runtime_error(std::string("SQLite prepare: ") + sqlite3_errmsg(db));
        }
    }
    ~Statement() { sqlite3_finalize(stmt_); }
    Statement(const Statement&) = delete;
    Statement& operator=(const Statement&) = delete;

    void text(int index, std::string_view value) {
        // SQLITE_TRANSIENT copies the bytes: the binder does not have to keep
        // the caller's buffer alive until sqlite3_step() finishes.
        if (sqlite3_bind_text(stmt_, index, value.data(), static_cast<int>(value.size()),
                              SQLITE_TRANSIENT) != SQLITE_OK) fail("bind text");
    }
    void number(int index, Id value) {
        if (sqlite3_bind_int64(stmt_, index, value) != SQLITE_OK) fail("bind integer");
    }
    bool step() {
        int result = sqlite3_step(stmt_);
        if (result == SQLITE_ROW) return true;
        if (result == SQLITE_DONE) return false;
        fail("execute statement");
        return false;
    }
    void execute() {
        if (step()) throw std::runtime_error("SQLite: unexpected result row");
    }
    [[nodiscard]] Id id(int column) const { return sqlite3_column_int64(stmt_, column); }
    [[nodiscard]] std::string str(int column) const {
        const unsigned char* value = sqlite3_column_text(stmt_, column);
        return value ? reinterpret_cast<const char*>(value) : std::string{};
    }

private:
    [[noreturn]] void fail(const char* action) const {
        throw std::runtime_error(std::string("SQLite ") + action + ": " + sqlite3_errmsg(db_));
    }
    sqlite3* db_{};
    sqlite3_stmt* stmt_{};
};

void exec(sqlite3* db, const char* sql) {
    char* error = nullptr;
    int rc = sqlite3_exec(db, sql, nullptr, nullptr, &error);
    if (rc != SQLITE_OK) {
        std::string message = error ? error : sqlite3_errmsg(db);
        sqlite3_free(error);
        throw std::runtime_error("SQLite: " + message);
    }
}

/**
 * Escape LIKE metacharacters for a *literal* user-entered search term.
 * Without this, an underscore or percent sign unexpectedly matches many
 * unrelated books. Parameters still protect the SQL statement itself.
 */
std::string literalSearch(std::string_view term) {
    std::string value = "%";
    for (char c : term) {
        if (c == '%' || c == '_' || c == '!') value += '!';
        value += c;
    }
    return value + '%';
}
} // namespace

struct SqliteCatalog::Impl {
    sqlite3* db{};
    explicit Impl(const std::string& database_path) {
        int rc = sqlite3_open_v2(database_path.c_str(), &db,
                                 SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE, nullptr);
        if (rc != SQLITE_OK) {
            std::string why = db ? sqlite3_errmsg(db) : "out of memory";
            sqlite3_close(db);
            db = nullptr;
            throw std::runtime_error("Cannot open catalog: " + why);
        }
        try {
            // Foreign keys must be enabled *per connection*; merely declaring
            // REFERENCES in CREATE TABLE is insufficient for SQLite.
            exec(db, "PRAGMA foreign_keys = ON;");
            sqlite3_busy_timeout(db, 3000);

            Statement version(db, "PRAGMA user_version;");
            if (!version.step()) throw std::runtime_error("Missing SQLite schema version");
            const Id current = version.id(0);
            if (current > 1) throw std::runtime_error("Database schema is newer than HARALD");
            if (current == 0) {
                // Entire first migration is transactional; a failed schema
                // change leaves the catalog unmodified and retryable.
                exec(db, "BEGIN IMMEDIATE;");
                try {
                    exec(db, R"sql(
                        CREATE TABLE works (
                          id INTEGER PRIMARY KEY,
                          title TEXT NOT NULL CHECK(length(trim(title)) > 0),
                          creator TEXT NOT NULL CHECK(length(trim(creator)) > 0)
                        );
                        CREATE TABLE editions (
                          id INTEGER PRIMARY KEY,
                          work_id INTEGER NOT NULL REFERENCES works(id) ON DELETE RESTRICT,
                          edition_label TEXT NOT NULL CHECK(length(trim(edition_label)) > 0),
                          isbn TEXT NOT NULL DEFAULT ''
                        );
                        CREATE TABLE copies (
                          id INTEGER PRIMARY KEY,
                          edition_id INTEGER NOT NULL REFERENCES editions(id) ON DELETE RESTRICT,
                          inventory_code TEXT NOT NULL UNIQUE CHECK(length(trim(inventory_code)) > 0),
                          location TEXT NOT NULL CHECK(length(trim(location)) > 0)
                        );
                        CREATE INDEX idx_editions_work ON editions(work_id);
                        CREATE INDEX idx_copies_edition ON copies(edition_id);
                        PRAGMA user_version = 1;
                    )sql");
                    exec(db, "COMMIT;");
                } catch (...) {
                    // Rollback must not mask the original failure.
                    sqlite3_exec(db, "ROLLBACK;", nullptr, nullptr, nullptr);
                    throw;
                }
            }
        } catch (...) {
            sqlite3_close(db);
            db = nullptr;
            throw;
        }
    }
    ~Impl() { if (db) sqlite3_close(db); }
};

SqliteCatalog::SqliteCatalog(const std::string& path) : impl_(std::make_unique<Impl>(path)) {}
SqliteCatalog::~SqliteCatalog() = default;

Id SqliteCatalog::insertBook(const BookDraft& book) {
    sqlite3* db = impl_->db;
    // This aggregate operation is atomic. No partial Work/Edition/Copy tree
    // remains if, for example, a barcode collides with an existing item.
    exec(db, "BEGIN IMMEDIATE;");
    try {
        Statement work(db, "INSERT INTO works(title,creator) VALUES(?1,?2);");
        work.text(1, book.title);
        work.text(2, book.creator);
        work.execute();
        Id work_id = sqlite3_last_insert_rowid(db);

        Statement edition(db, "INSERT INTO editions(work_id,edition_label,isbn) VALUES(?1,?2,?3);");
        edition.number(1, work_id);
        edition.text(2, book.edition_label);
        edition.text(3, book.isbn);
        edition.execute();
        Id edition_id = sqlite3_last_insert_rowid(db);

        for (const CopyDraft& copy : book.copies) {
            Statement item(db, "INSERT INTO copies(edition_id,inventory_code,location) VALUES(?1,?2,?3);");
            item.number(1, edition_id);
            item.text(2, copy.inventory_code);
            item.text(3, copy.location);
            item.execute();
        }
        exec(db, "COMMIT;");
        return edition_id;
    } catch (...) {
        sqlite3_exec(db, "ROLLBACK;", nullptr, nullptr, nullptr);
        throw;
    }
}

std::vector<BookSummary> SqliteCatalog::searchBooks(std::string_view term) const {
    Statement query(impl_->db, R"sql(
        SELECT e.id, w.id, w.title, w.creator, e.edition_label, e.isbn,
               (SELECT count(*) FROM copies c WHERE c.edition_id = e.id)
          FROM editions e JOIN works w ON w.id = e.work_id
         WHERE w.title LIKE ?1 ESCAPE '!'
            OR w.creator LIKE ?1 ESCAPE '!'
            OR e.isbn LIKE ?1 ESCAPE '!'
         ORDER BY w.title COLLATE NOCASE, e.id;
    )sql");
    query.text(1, literalSearch(term));
    std::vector<BookSummary> result;
    while (query.step()) {
        result.push_back({query.id(0), query.id(1), query.str(2), query.str(3),
                          query.str(4), query.str(5), static_cast<std::size_t>(query.id(6))});
    }
    return result;
}

std::optional<BookDetails> SqliteCatalog::findBook(Id edition_id) const {
    Statement detail(impl_->db, R"sql(
        SELECT e.id, w.id, w.title, w.creator, e.edition_label, e.isbn,
               (SELECT count(*) FROM copies c WHERE c.edition_id = e.id)
          FROM editions e JOIN works w ON w.id = e.work_id WHERE e.id = ?1;
    )sql");
    detail.number(1, edition_id);
    if (!detail.step()) return std::nullopt;
    BookDetails result{{detail.id(0), detail.id(1), detail.str(2), detail.str(3),
                        detail.str(4), detail.str(5), static_cast<std::size_t>(detail.id(6))}, {}};
    Statement copies(impl_->db, "SELECT id,edition_id,inventory_code,location FROM copies WHERE edition_id=?1 ORDER BY id;");
    copies.number(1, edition_id);
    while (copies.step()) {
        result.copies.push_back({copies.id(0), copies.id(1), copies.str(2), copies.str(3)});
    }
    return result;
}
} // namespace harald
