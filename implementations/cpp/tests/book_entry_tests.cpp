#include <harald/presentation/book_entry.hpp>
#include <harald/presentation/copy_details_pager.hpp>

#include <chrono>
#include <filesystem>
#include <iostream>
#include <stdexcept>
#include <string>
#include <utility>

namespace {
namespace fs = std::filesystem;
namespace view = harald::presentation;

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

/** Verify that the copy editor handles arbitrarily many rows without native
 * widgets and cannot lose its selection or underflow when rows are deleted. */
void testDetailsPaging() {
    view::CopyDetailsPager pager;
    CHECK(pager.pageCount(0) == 1);
    CHECK(pager.pageCount(1) == 1);
    CHECK(pager.pageCount(3) == 1);
    CHECK(pager.pageCount(4) == 2);
    CHECK(pager.pageCount(7) == 3);
    CHECK(!pager.previous());
    CHECK(!pager.next(0));
    CHECK(!pager.next(3));
    CHECK(pager.next(7));
    CHECK(pager.page() == 1);
    CHECK(pager.firstIndex() == 3);
    CHECK(pager.next(7));
    CHECK(pager.page() == 2);
    CHECK(pager.firstIndex() == 6);
    CHECK(!pager.next(7));
    pager.clamp(4);
    CHECK(pager.page() == 1);
    CHECK(pager.firstIndex() == 3);
    pager.clamp(0);
    CHECK(pager.page() == 0);
    CHECK(pager.previous() == false);
    CHECK(pager.next(12));
    pager.reset();
    CHECK(pager.page() == 0);
}

void testCopyEditorNavigation() {
    view::BookCopyEditor editor;
    CHECK(editor.size() == 1);
    CHECK(editor.selectedIndex() == 0);
    CHECK(!editor.removeCurrent());
    CHECK(!editor.select(1));

    editor.editCurrent({" INV-001 ", "Shelf A"});
    editor.append();
    CHECK(editor.size() == 2);
    CHECK(editor.selectedIndex() == 1);
    CHECK(editor.current().inventory_code.empty());
    editor.editCurrent({"INV-002", "Shelf B"});
    CHECK(editor.select(0));
    CHECK(editor.current().inventory_code == " INV-001 ");
    CHECK(editor.select(1));
    CHECK(editor.current().location == "Shelf B");

    for (int i = 0; i < 17; ++i) {
        editor.append();
        editor.editCurrent({"EXTRA-" + std::to_string(i), "Room / Shelf"});
    }
    CHECK(editor.size() == 19);
    CHECK(!editor.select(19));
    CHECK(editor.selectedIndex() == 18);

    // Removing the end keeps the index valid and exposes its predecessor.
    CHECK(editor.removeCurrent());
    CHECK(editor.size() == 18);
    CHECK(editor.selectedIndex() == 17);
    CHECK(editor.current().inventory_code == "EXTRA-15");

    // Removing the FIRST row shifts the next copy into its position.
    CHECK(editor.select(0));
    CHECK(editor.removeCurrent());
    CHECK(editor.current().inventory_code == "INV-002");

    editor.reset();
    CHECK(editor.size() == 1);
    CHECK(editor.selectedIndex() == 0);
    CHECK(editor.current().inventory_code.empty());
    CHECK(!editor.removeCurrent());
    CHECK(!editor.select(5));
}

/**
 * Execute the SAME form adapter as the desktop against real SQLite.
 *
 * All failed operations must leave the three-table Work/Edition/Copy
 * aggregate untouched, including conflicts that occur after several
 * otherwise valid copies have already been tentatively inserted.
 */
void testBookEntryAndRollback() {
    const fs::path path = fs::temp_directory_path() /
        ("harald-entry-" + std::to_string(
            std::chrono::steady_clock::now().time_since_epoch().count()) + ".sqlite");
    try {
        harald::Id first_id{};
        harald::Id many_id{};
        {
            harald::SqliteCatalog storage{path.string()};
            harald::CatalogService service{storage};
            view::BookEntryController entry{service};

            CHECK(rejected<std::invalid_argument>([&] {
                (void)entry.create({"  ", "Author", "Edition", "",
                                    {{"BAR-1", "Shelf"}}});
            }));
            CHECK(rejected<std::invalid_argument>([&] {
                (void)entry.create({"No copies", "Author", "Edition", "", {}});
            }));
            CHECK(service.search("").empty());

            first_id = entry.create({
                "  Über Bücher  ", " Ada Lovelace ", " First ", "",
                {{" INV-01 ", " Library / Shelf A "}}});
            CHECK(first_id > 0);
            const auto one = service.details(first_id);
            CHECK(one.has_value());
            CHECK(one->book.title == "Über Bücher");
            CHECK(one->book.creator == "Ada Lovelace");
            CHECK(one->copies.size() == 1);
            CHECK(one->copies[0].inventory_code == "INV-01");
            CHECK(one->copies[0].location == "Library / Shelf A");

            // A multi-copy form includes far more than the old three-line
            // detail preview. Every row is preserved and retains its order.
            view::BookCopyEditor editor;
            editor.editCurrent({"  MANY-001 ", " Shelf 1 "});
            for (int n = 2; n <= 12; ++n) {
                editor.append();
                editor.editCurrent({"MANY-" + std::to_string(1000 + n).substr(1),
                                    "Shelf " + std::to_string(n)});
            }
            CHECK(editor.size() == 12);
            many_id = entry.create({"  Kunst und Wissenschaft ", "Research Team",
                                    "Third edition", "", editor.copies()});
            CHECK(many_id > first_id);
            const auto many = service.details(many_id);
            CHECK(many.has_value());
            CHECK(many->book.title == "Kunst und Wissenschaft");
            CHECK(many->book.copy_count == 12);
            CHECK(many->copies.size() == 12);
            CHECK(many->copies[0].inventory_code == "MANY-001");
            CHECK(many->copies[11].inventory_code == "MANY-012");
            CHECK(many->copies[11].location == "Shelf 12");

            // A duplicate inside a single form must be caught by the domain
            // service before any transaction is started (even after trim).
            CHECK(rejected<std::invalid_argument>([&] {
                (void)entry.create({"Internal duplicate", "Author", "Edition", "",
                                    {{" DUP-1 ", "Shelf"},
                                     {"DUP-2", "Shelf"},
                                     {"DUP-1", "Other shelf"}}});
            }));
            CHECK(service.search("Internal duplicate").empty());

            // The very LAST copy collides with an inventory code in an
            // existing edition. SQLite must roll back the entire aggregate,
            // not leave the Work, Edition or first two Copies behind.
            CHECK(rejected<std::runtime_error>([&] {
                (void)entry.create({"Never persist", "Someone", "Second", "",
                                    {{"NEW-01", "Shelf A"},
                                     {"NEW-02", "Shelf B"},
                                     {"INV-01", "Shelf C"}}});
            }));
            CHECK(service.search("Never persist").empty());

            CHECK(rejected<std::invalid_argument>([&] {
                (void)entry.create({"Missing location", "Author", "Edition", "",
                                    {{"GOOD-1", "Shelf"}, {"GOOD-2", "  "}}});
            }));
            CHECK(service.search("").size() == 2);
        }

        // Closing and reopening the database proves commits are durable and
        // rejected drafts did not escape the SQL transaction rollback.
        {
            harald::SqliteCatalog storage{path.string()};
            harald::CatalogService service{storage};
            const auto one = service.details(first_id);
            const auto many = service.details(many_id);
            CHECK(one.has_value());
            CHECK(many.has_value());
            CHECK(one->copies.size() == 1);
            CHECK(many->copies.size() == 12);
            CHECK(service.search("").size() == 2);
            CHECK(service.search("Never persist").empty());
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
        testCopyEditorNavigation();
        testDetailsPaging();
        testBookEntryAndRollback();
        std::cout << "HARALD multi-copy editor and SQLite integration tests passed\n";
        return 0;
    } catch (const std::exception& problem) {
        std::cerr << "HARALD book entry tests failed: " << problem.what() << '\n';
        return 1;
    }
}
