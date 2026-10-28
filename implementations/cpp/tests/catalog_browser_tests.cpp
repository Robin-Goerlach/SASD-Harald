#include <harald/presentation/catalog_browser.hpp>

#include <algorithm>
#include <cstddef>
#include <iostream>
#include <stdexcept>
#include <string>
#include <string_view>
#include <utility>
#include <vector>

namespace {

void check(bool value, const char* expression) {
    if (!value) throw std::runtime_error(expression);
}
#define CHECK(expression) check(static_cast<bool>(expression), #expression)

/**
 * A deterministic repository fake at the existing DOMAIN PORT, not at the
 * browser level. These tests exercise the real CatalogService and projection.
 * SQLite integration is already covered by harald_catalog_tests; using a fake
 * here allows deleted data, reorder, and injected failures to be reproducible.
 */
class FakeRepository final : public harald::CatalogRepository {
public:
    std::vector<harald::BookSummary> books;
    bool fail_search{false};
    bool fail_details{false};
    bool missing_details{false};

    harald::Id insertBook(const harald::BookDraft&) override {
        throw std::runtime_error("not a write test");
    }

    std::vector<harald::BookSummary> searchBooks(std::string_view term) const override {
        if (fail_search) throw std::runtime_error("synthetic search failure");
        std::vector<harald::BookSummary> matches;
        for (const auto& book : books) {
            if (term.empty() || book.title.find(term) != std::string::npos) {
                matches.push_back(book);
            }
        }
        return matches;
    }

    std::optional<harald::BookDetails> findBook(harald::Id id) const override {
        if (fail_details) throw std::runtime_error("synthetic details failure");
        if (missing_details) return std::nullopt;
        const auto it = std::find_if(books.begin(), books.end(),
            [id](const auto& book) { return book.edition_id == id; });
        if (it == books.end()) return std::nullopt;
        return harald::BookDetails{*it, {{100 + id, id, "INV-" + std::to_string(id), "Shelf A"}}};
    }
};

harald::BookSummary example(harald::Id id, std::string title) {
    return {id, id + 100, std::move(title), "Creator", "Hardcover", "", 1};
}

template <typename Operation>
bool throwsRuntimeError(Operation&& operation) {
    try {
        operation();
    } catch (const std::runtime_error&) {
        return true;
    }
    return false;
}

void testSearchSelectionAndUnicode() {
    FakeRepository data;
    data.books = {example(2, "Über Bücher"), example(7, "日本語の本")};
    harald::CatalogService catalog{data};
    harald::presentation::CatalogBrowser browser{catalog};

    CHECK(browser.projection().rowCount() == 0);
    CHECK(!browser.selectRow(0));
    browser.refresh("");
    CHECK(browser.filter().empty());
    CHECK(browser.projection().rowCount() == 2);
    CHECK(browser.tableRows()[1][1] == "日本語の本");
    CHECK(browser.selectRow(1));
    CHECK(browser.selectedEditionId() == 7);
    CHECK(browser.selectedRow() == 1);
    CHECK(browser.selectedDetails()->copies[0].inventory_code == "INV-7");
    CHECK(!browser.selectRow(200)); // Never reuse an unrelated prior detail.
    CHECK(!browser.selectedEditionId());
    CHECK(!browser.selectedDetails());
}

void testIdentitySurvivesReorderAndFilter() {
    FakeRepository data;
    data.books = {example(8, "Alpha"), example(5, "Beta")};
    harald::CatalogService catalog{data};
    harald::presentation::CatalogBrowser browser{catalog};

    browser.refresh("");
    CHECK(browser.selectRow(1));
    CHECK(browser.selectedEditionId() == 5);
    std::swap(data.books[0], data.books[1]);
    browser.refresh("");
    CHECK(browser.selectedRow() == 0);
    CHECK(browser.selectedEditionId() == 5);
    CHECK(browser.selectedDetails()->book.title == "Beta");

    browser.refresh("Alpha");
    CHECK(browser.projection().rowCount() == 1);
    CHECK(!browser.selectedEditionId());
    CHECK(!browser.selectedDetails());
    CHECK(browser.filter() == "Alpha");

    CHECK(browser.selectRow(0));
    data.missing_details = true; // A deletion between search and details.
    CHECK(!browser.selectRow(0));
    CHECK(!browser.selectedDetails());
}

void testFailureDoesNotDestroyLastGoodView() {
    FakeRepository data;
    data.books = {example(3, "First")};
    harald::CatalogService catalog{data};
    harald::presentation::CatalogBrowser browser{catalog};

    browser.refresh("");
    CHECK(browser.selectRow(0));

    data.fail_search = true;
    CHECK(throwsRuntimeError([&] { browser.refresh("bad"); }));
    data.fail_search = false;
    CHECK(browser.filter().empty());
    CHECK(browser.projection().rowCount() == 1);
    CHECK(browser.selectedEditionId() == 3);

    data.books = {example(3, "First updated")};
    data.fail_details = true;
    CHECK(throwsRuntimeError([&] { browser.refresh("First"); }));
    CHECK(throwsRuntimeError([&] { (void)browser.selectRow(0); }));
    data.fail_details = false;
    CHECK(browser.filter().empty());
    CHECK(browser.selectedEditionId() == 3);
    CHECK(browser.selectedDetails()->book.title == "First");

    browser.refresh("");
    CHECK(browser.selectedDetails()->book.title == "First updated");

    data.books.clear();
    browser.refresh("");
    CHECK(browser.projection().rowCount() == 0);
    CHECK(!browser.selectedEditionId());
}

void testRejectAmbiguousDomainIdentity() {
    FakeRepository data;
    data.books = {example(10, "Valid")};
    harald::CatalogService catalog{data};
    harald::presentation::CatalogBrowser browser{catalog};
    browser.refresh("");
    CHECK(browser.selectRow(0));

    data.books = {example(10, "Old"), example(10, "Duplicate")};
    bool rejected = false;
    try {
        browser.refresh("");
    } catch (const std::invalid_argument&) {
        rejected = true;
    }
    CHECK(rejected);
    CHECK(browser.projection().rowCount() == 1);
    CHECK(browser.selectedEditionId() == 10);
}

} // namespace

int main() {
    try {
        testSearchSelectionAndUnicode();
        testIdentitySurvivesReorderAndFilter();
        testFailureDoesNotDestroyLastGoodView();
        testRejectAmbiguousDomainIdentity();
        std::cout << "HARALD catalog browser tests passed\n";
        return 0;
    } catch (const std::exception& failure) {
        std::cerr << "HARALD catalog browser tests failed: " << failure.what() << '\n';
        return 1;
    }
}
