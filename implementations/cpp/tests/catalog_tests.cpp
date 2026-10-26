#include <harald/catalog.hpp>

#include <cstdlib>
#include <chrono>
#include <filesystem>
#include <iostream>
#include <stdexcept>
#include <string>

namespace fs = std::filesystem;

/** Unlike CHECK(), CHECK is active in Release builds as well as Debug. */
void check(bool condition, const char* message) {
    if (!condition) throw std::runtime_error(message);
}
#define CHECK(condition) check(static_cast<bool>(condition), #condition)

// These tests intentionally exercise the real SQLite adapter instead of a mock.
// A fake would not catch missing transaction boundaries or uniqueness rules.
void testCatalog() {
    const std::string filename = (fs::temp_directory_path() /
        ("harald-integration-" + std::to_string(
             std::chrono::steady_clock::now().time_since_epoch().count()) + ".sqlite")).string();
    fs::remove(filename);
    try {
        harald::Id created{};
        {
            harald::SqliteCatalog repo(filename);
            harald::CatalogService app(repo);
            CHECK(app.search("").empty());
            created = app.createBook({"  Example 100%_!  ", " Ada Lovelace ",
                                      " Paperback ", "1234567890",
                                      {{"A-001", "Shelf 1"}, {"A-002", "Shelf 2"}}});
            CHECK(created > 0);
            auto full = app.details(created);
            CHECK(full && full->copies.size() == 2);
            CHECK(full->book.title == "Example 100%_!");
            CHECK(full->copies[0].inventory_code == "A-001");
            CHECK(full->copies[1].inventory_code == "A-002");
            CHECK(full->copies[0].id != full->copies[1].id);
            CHECK(app.search("100%_!").size() == 1); // %/_/! are literal
            CHECK(app.search("not present").empty());
            CHECK(!app.details(created + 100));
            // Duplicates in the proposed batch fail before writing anything.
            bool rejected = false;
            try {
                app.createBook({"Should not exist", "Author", "Ed", "",
                                {{"DUP", "A"}, {"DUP", "B"}}});
            } catch (const std::invalid_argument&) { rejected = true; }
            CHECK(rejected);
            CHECK(app.search("Should not exist").empty());
            // A duplicate against an existing copy fails during the SQL
            // transaction; work and edition must both roll back.
            rejected = false;
            try {
                app.createBook({"Rollback me", "Author", "Ed", "",
                                {{"UNIQUE-NEW", "A"}, {"A-001", "B"}}});
            } catch (const std::runtime_error&) { rejected = true; }
            CHECK(rejected);
            CHECK(app.search("Rollback me").empty());
            rejected = false;
            try {
                app.createBook({"  ", "Author", "Ed", "", {{"NEW", "A"}}});
            } catch (const std::invalid_argument&) { rejected = true; }
            CHECK(rejected);
            CHECK(app.search("").size() == 1);
        }
        // Reopen the file: data must really be persistent, not just cached.
        {
            harald::SqliteCatalog repo(filename);
            harald::CatalogService app(repo);
            auto book = app.details(created);
            CHECK(book && book->copies.size() == 2);
            CHECK(book->book.creator == "Ada Lovelace");
            CHECK(app.search("%_").size() == 1);
        }
    } catch (...) {
        fs::remove(filename);
        throw;
    }
    fs::remove(filename);
}

int main() {
    try {
        testCatalog();
        std::cout << "HARALD integration tests passed\n";
        return 0;
    } catch (const std::exception& e) {
        std::cerr << "HARALD tests failed: " << e.what() << '\n';
        return 1;
    }
}
