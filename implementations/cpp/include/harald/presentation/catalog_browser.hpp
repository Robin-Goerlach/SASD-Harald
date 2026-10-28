#pragma once

#include <harald/catalog.hpp>
#include <harald/presentation/catalog_table_projection.hpp>

#include <cstddef>
#include <optional>
#include <string>
#include <string_view>
#include <vector>

namespace harald::presentation {

/**
 * Toolkit-neutral state for the first interactive catalog browser.
 *
 * CatalogService is the ONLY path to book data. In particular, neither this
 * coordinator nor a widget opens SQLite, interprets visible table text as an
 * identifier, or caches a repository cursor.
 *
 * The caller owns CatalogService (and its repository) for this object's entire
 * lifetime. Each successful refresh replaces a value-owned search snapshot.
 * The selected edition is tracked by domain ID, never by a transient row.
 *
 * Service exceptions propagate without replacing the previously displayed
 * snapshot or selection. Presentation code may catch them to show an error
 * while retaining the last coherent screen state.
 */
class CatalogBrowser final {
public:
    explicit CatalogBrowser(const CatalogService& catalog) noexcept : catalog_(catalog) {}

    /** Current successfully applied filter; not the text currently being edited. */
    [[nodiscard]] std::string_view filter() const noexcept { return filter_; }

    /** A stable view of the current result; invalidated by the next refresh. */
    [[nodiscard]] const CatalogTableProjection& projection() const noexcept {
        return projection_;
    }

    /** An owned display-only table; no persistence identities need be parsed. */
    [[nodiscard]] std::vector<std::vector<std::string>> tableRows() const {
        return projection_.tableRows();
    }

    /**
     * Search anew and restore the selected edition only if it still exists.
     *
     * A filtered-out or deleted edition clears its detail view. The next
     * projection and its details are fully prepared BEFORE changing the current
     * state, giving callers the strong exception guarantee on lookup failure.
     */
    void refresh(std::string filter);

    /**
     * Select the edition at a visible model row, then load its full details.
     *
     * Invalid/stale rows and deleted editions clear selection and return false.
     * A repository exception leaves the prior selection intact and propagates.
     */
    [[nodiscard]] bool selectRow(std::size_t row);

    /** Explicit deselection (e.g. after the toolkit clears its selection). */
    void clearSelection() noexcept;

    [[nodiscard]] std::optional<Id> selectedEditionId() const noexcept {
        return selected_id_;
    }

    [[nodiscard]] std::optional<std::size_t> selectedRow() const noexcept {
        return selected_id_ ? projection_.rowForEdition(*selected_id_) : std::nullopt;
    }

    /** Borrowed; invalidated by refresh, selectRow or clearSelection. */
    [[nodiscard]] const std::optional<BookDetails>& selectedDetails() const noexcept {
        return selected_details_;
    }

private:
    const CatalogService& catalog_;
    std::string filter_;
    CatalogTableProjection projection_{{}};
    std::optional<Id> selected_id_;
    std::optional<BookDetails> selected_details_;
};

} // namespace harald::presentation
