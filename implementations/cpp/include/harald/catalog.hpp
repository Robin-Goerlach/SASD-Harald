#pragma once

#include <cstdint>
#include <memory>
#include <optional>
#include <string>
#include <string_view>
#include <vector>

namespace harald {

using Id = std::int64_t;

/**
 * A physical copy belongs to an edition, never directly to a creative work.
 * Its inventory code identifies that *individual copy* (not an ISBN/product).
 */
struct CopyDraft {
    std::string inventory_code;
    std::string location;
};

/**
 * Input for the first vertical slice. Creating one Work, Edition and its Copies
 * is a single business operation: either all records are stored or none are.
 * Future formats will have their own validated edition/media profiles.
 */
struct BookDraft {
    std::string title;
    std::string creator;
    std::string edition_label;
    std::string isbn; // Optional bibliographic identifier; NOT a copy's inventory code.
    std::vector<CopyDraft> copies;
};

struct Copy {
    Id id{};
    Id edition_id{};
    std::string inventory_code;
    std::string location;
};

struct BookSummary {
    Id edition_id{};
    Id work_id{};
    std::string title;
    std::string creator;
    std::string edition_label;
    std::string isbn;
    std::size_t copy_count{};
};

struct BookDetails {
    BookSummary book;
    std::vector<Copy> copies;
};

/**
 * Repository port: the application cannot depend on SQLite (or later JSON).
 * Use cases use domain-oriented operations rather than passing SQL strings.
 */
class CatalogRepository {
public:
    virtual ~CatalogRepository() = default;
    virtual Id insertBook(const BookDraft& book) = 0;
    virtual std::vector<BookSummary> searchBooks(std::string_view term) const = 0;
    virtual std::optional<BookDetails> findBook(Id edition_id) const = 0;
};

/**
 * Single authority for input rules in the first HARALD use cases. Validation
 * is independent of the persistence adapter and therefore reusable by JSON,
 * REST, or a future desktop/web frontend.
 */
class CatalogService final {
public:
    explicit CatalogService(CatalogRepository& repository) : repository_(repository) {}
    Id createBook(const BookDraft& draft);
    [[nodiscard]] std::vector<BookSummary> search(std::string_view term) const;
    [[nodiscard]] std::optional<BookDetails> details(Id edition_id) const;

private:
    CatalogRepository& repository_;
};

/** SQLite adapter. The implementation hides sqlite3 and owns its connection. */
class SqliteCatalog final : public CatalogRepository {
public:
    explicit SqliteCatalog(const std::string& database_path);
    ~SqliteCatalog() override;
    SqliteCatalog(const SqliteCatalog&) = delete;
    SqliteCatalog& operator=(const SqliteCatalog&) = delete;

    Id insertBook(const BookDraft& book) override;
    [[nodiscard]] std::vector<BookSummary> searchBooks(std::string_view term) const override;
    [[nodiscard]] std::optional<BookDetails> findBook(Id edition_id) const override;

private:
    struct Impl;
    std::unique_ptr<Impl> impl_;
};

} // namespace harald
