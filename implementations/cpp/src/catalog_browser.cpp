#include <harald/presentation/catalog_browser.hpp>

#include <utility>

namespace harald::presentation {

void CatalogBrowser::refresh(std::string filter) {
    // Do potentially failing repository work before changing any visible
    // state. A malformed/duplicate ID likewise fails in the projection's
    // constructor rather than entering the toolkit as an ambiguous row.
    CatalogTableProjection next{catalog_.search(filter)};
    std::optional<Id> next_id;
    std::optional<BookDetails> next_details;

    if (selected_id_ && next.rowForEdition(*selected_id_)) {
        next_details = catalog_.details(*selected_id_);
        if (next_details) {
            next_id = *selected_id_;
        }
    }

    // Moving std::string, vector-backed projection and optional value data
    // cannot fail with their standard allocators. Commit only a coherent
    // search/selection/details triple, never a half-refreshed screen.
    filter_ = std::move(filter);
    projection_ = std::move(next);
    selected_id_ = next_id;
    selected_details_ = std::move(next_details);
}

bool CatalogBrowser::selectRow(std::size_t row) {
    const auto id = projection_.editionIdAt(row);
    if (!id) {
        clearSelection();
        return false;
    }

    auto details = catalog_.details(*id);
    if (!details) {
        // The library may have changed since the result was fetched. Do not
        // show another book's details under a now-invalid selection.
        clearSelection();
        return false;
    }

    selected_id_ = *id;
    selected_details_ = std::move(details);
    return true;
}

void CatalogBrowser::clearSelection() noexcept {
    selected_details_.reset();
    selected_id_.reset();
}

} // namespace harald::presentation
