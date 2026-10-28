#include <harald/presentation/book_entry.hpp>

#include <chrono>
#include <filesystem>
#include <iostream>
#include <stdexcept>
#include <string>

namespace {
namespace fs = std::filesystem;

void check(bool valid, const char* expression) {
    if (!valid) throw std::runtime_error(expression);
}
#define CHECK(expr) check(static_cast<bool>(expr), #expr)

template <typename Error, typename Operation>
bool rejected(Operation&& operation) {
    try {
        operation();
    } catch (const Error&) {
        return true;
    }
    return false;
}

/** Exercise real SQLite rather than an in-memory mock: failed inserts must
 * never persist half a Work/Edition/Copy aggregate. An isolated temporary DB
 * prevents the tests from modifying any user's library. */
void testBookEntryAndRollback() {
    const fs::path path = fs::temp_directory_path() /
        ("harald-entry-" + std::to_string(
            std::chrono::steady_clock::now().time_since_epoch().count()) + ".sqlite");
    try {
        harald::Id first_id{};
        {
            harald::SqliteCatalog storage{path.string()};
            harald::CatalogService service{storage};
            harald::presentation::BookEntryController entry{service};

            CHECK(rejected<std::invalid_argument>([&] {
                (void)entry.create({"  ", "Author", "Edition", "", "BAR-1", "Shelf"});
            }));
            CHECK(service.search("").empty());

            first_id = entry.create({
                "  Über Bücher  ", " Ada Lovelace ", " First ", "",
                " INV-01 ", " Library / Shelf A "});
            CHECK(first_id > 0);
            auto record = service.details(first_id);
            CHECK(record.has_value());
            CHECK(record->book.title == "Über Bücher");
            CHECK(record->book.creator == "Ada Lovelace");
            CHECK(record->copies.size() == 1);
            CHECK(record->copies[0].inventory_code == "INV-01");
            CHECK(record->copies[0].location == "Library / Shelf A");

            // The second form attempts a barcode that is already persisted.
            // SQLite UNIQUE rejects it and the repository rolls back both
            // freshly inserted Work and Edition, not just the physical copy.
            CHECK(rejected<std::runtime_error>([&] {
                (void)entry.create({"Never persist", "Someone", "Second", "",
                                    "INV-01", "Shelf B"});
            }));
            CHECK(service.search("Never persist").empty());
            CHECK(service.search("").size() == 1);

            CHECK(rejected<std::invalid_argument>([&] {
                (void)entry.create({"Missing location", "Author", "Edition", "",
                                    "INV-02", "  "});
            }));
            CHECK(service.search("").size() == 1);
        }

        // The controller does not cache any data: reopening SQLite confirms
        // durability and that no failed entry remains in persistent storage.
        {
            harald::SqliteCatalog storage{path.string()};
            harald::CatalogService service{storage};
            CHECK(service.details(first_id)->copies.size() == 1);
            CHECK(service.search("").size() == 1);
        }
    } catch (...) {
        fs::remove(path);
        throw;
    }
    fs::remove(path);
}
} // namespace

int main() {
    try {
        testBookEntryAndRollback();
        std::cout << "HARALD book entry integration tests passed\n";
        return 0;
    } catch (const std::exception& problem) {
        std::cerr << "HARALD book entry tests failed: " << problem.what() << '\n';
        return 1;
    }
}
