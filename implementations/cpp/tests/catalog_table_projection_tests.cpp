#include <harald/presentation/catalog_table_projection.hpp>

#include <cstddef>
#include <iostream>
#include <limits>
#include <stdexcept>
#include <string>
#include <utility>
#include <vector>

namespace {
void check(bool condition, const char* description) {
    if (!condition) throw std::runtime_error(description);
}
#define CHECK(condition) check(static_cast<bool>(condition), #condition)

harald::BookSummary book(harald::Id edition_id, std::string title, std::size_t copies) {
    return {edition_id, edition_id + 1000, std::move(title), "Author", "First", "", copies};
}

void testEmptyAndOutOfRange() {
    const harald::presentation::CatalogTableProjection empty{{}};
    CHECK(empty.rowCount() == 0);
    CHECK(empty.tableRows().empty());
    CHECK(!empty.editionIdAt(0));
    CHECK(!empty.editionIdAt(std::numeric_limits<std::size_t>::max()));
    CHECK(!empty.rowForEdition(1));
    CHECK(!empty.rowForEdition(0));
}

void testOwnedRowsAndUnicode() {
    const harald::presentation::CatalogTableProjection projection{{
        book(42, "Über die Bücher", 2), book(7, "日本語の本", 0)}};
    CHECK(projection.rowCount() == 2);
    auto rows = projection.tableRows();
    CHECK(rows.size() == 2);
    CHECK(rows[0].size() == 5);
    CHECK(rows[0][0] == "42");
    CHECK(rows[0][1] == "Über die Bücher");
    CHECK(rows[0][4] == "2");
    CHECK(rows[1][1] == "日本語の本");
    CHECK(rows[1][4] == "0");
    CHECK(projection.editionIdAt(0) == 42);
    CHECK(projection.editionIdAt(1) == 7);
    CHECK(!projection.editionIdAt(2));
    rows[0][0] = "not an ID";
    CHECK(projection.editionIdAt(0) == 42); // Identity is not parsed from formatted text.
    CHECK(projection.tableRows()[0][0] == "42");
}

void testSelectionAcrossReorderAndFilter() {
    const harald::presentation::CatalogTableProjection before{{book(42, "Zeta", 1),
                                                                  book(7, "Alpha", 2)}};
    const auto selected_id = before.editionIdAt(0);
    CHECK(selected_id == 42);
    const harald::presentation::CatalogTableProjection reordered{{book(7, "Alpha", 2),
                                                                     book(42, "Zeta", 1)}};
    CHECK(reordered.rowForEdition(*selected_id) == 1);
    CHECK(reordered.editionIdAt(0) == 7);
    const harald::presentation::CatalogTableProjection filtered{{book(7, "Alpha", 2)}};
    CHECK(!filtered.rowForEdition(*selected_id));
    CHECK(filtered.rowForEdition(7) == 0);
}

void testBadIdentityFailsClosed() {
    bool rejected = false;
    try {
        (void)harald::presentation::CatalogTableProjection{{book(0, "Bad", 0)}};
    } catch (const std::invalid_argument&) { rejected = true; }
    CHECK(rejected);
    rejected = false;
    try {
        (void)harald::presentation::CatalogTableProjection{{book(9, "First", 1),
                                                               book(9, "Duplicate", 1)}};
    } catch (const std::invalid_argument&) { rejected = true; }
    CHECK(rejected);
}
} // namespace

int main() {
    try {
        testEmptyAndOutOfRange();
        testOwnedRowsAndUnicode();
        testSelectionAcrossReorderAndFilter();
        testBadIdentityFailsClosed();
        std::cout << "HARALD catalog table projection tests passed\n";
        return 0;
    } catch (const std::exception& e) {
        std::cerr << "HARALD catalog table projection tests failed: " << e.what() << '\n';
        return 1;
    }
}
