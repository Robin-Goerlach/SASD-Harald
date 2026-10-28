#pragma once

#include <harald/catalog.hpp>

#include <cstddef>
#include <optional>
#include <string>
#include <vector>

namespace harald::presentation {

/**
 * An owned, toolkit-independent snapshot of one catalog search result.
 *
 * The UI Toolkit identifies selected cells by a positional row/column pair.
 * Such a position becomes invalid after searching, filtering or reordering.
 * This projection deliberately keeps the authoritative edition ID alongside
 * each displayed row so a presentation adapter never has to parse a visible
 * table cell or use a row number as a database key.
 *
 * Copying the summaries severs the projection's lifetime from repository
 * cursors, temporary service results, and individual toolkit widgets.
 * A new search creates a new projection; consumers must capture the selected
 * edition ID before replacing their table model, then use rowForEdition() to
 * restore selection if that edition still appears in the new result.
 *
 * Current IDs are local SQLite prototype IDs, NOT portable cross-backend IDs.
 */
class CatalogTableProjection final {
public:
    /**
     * Takes ownership of a completed application-layer search result.
     *
     * A non-positive or repeated edition ID is rejected. Allowing either
     * would make identity-based selection ambiguous and could display details
     * of a different book after a refresh. No persistence is modified.
     */
    explicit CatalogTableProjection(std::vector<BookSummary> summaries);

    [[nodiscard]] std::size_t rowCount() const noexcept { return summaries_.size(); }

    /**
     * Creates an owned rectangular five-column snapshot for StringTableModel.
     * Text is passed through unchanged, including valid UTF-8; the toolkit
     * owns a separate copy after construction and may outlive this projection.
     */
    [[nodiscard]] std::vector<std::vector<std::string>> tableRows() const;

    /** Returns no ID for an out-of-range model row, including stale selection. */
    [[nodiscard]] std::optional<Id> editionIdAt(std::size_t row) const noexcept;

    /** Finds the current model row by domain ID, or returns no row if filtered out. */
    [[nodiscard]] std::optional<std::size_t> rowForEdition(Id edition_id) const noexcept;

private:
    std::vector<BookSummary> summaries_;
};

} // namespace harald::presentation
