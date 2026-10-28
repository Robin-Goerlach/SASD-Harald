#include <harald/presentation/catalog_table_projection.hpp>

#include <stdexcept>
#include <unordered_set>
#include <utility>

namespace harald::presentation {

CatalogTableProjection::CatalogTableProjection(std::vector<BookSummary> summaries)
    : summaries_(std::move(summaries)) {
    std::unordered_set<Id> seen;
    for (const auto& summary : summaries_) {
        // The application's search contract returns one row per Edition.
        // Refuse broken repository data instead of making selection ambiguous.
        if (summary.edition_id <= 0 || !seen.insert(summary.edition_id).second) {
            throw std::invalid_argument("catalog projection requires unique positive edition IDs");
        }
    }
}

std::vector<std::vector<std::string>> CatalogTableProjection::tableRows() const {
    std::vector<std::vector<std::string>> rows;
    rows.reserve(summaries_.size());
    for (const auto& summary : summaries_) {
        // Formatting is a presentation concern, never a persistence key. The
        // original numeric ID remains available separately via editionIdAt().
        rows.push_back({std::to_string(summary.edition_id), summary.title,
                        summary.creator, summary.edition_label,
                        std::to_string(summary.copy_count)});
    }
    return rows;
}

std::optional<Id> CatalogTableProjection::editionIdAt(std::size_t row) const noexcept {
    if (row >= summaries_.size()) return std::nullopt;
    return summaries_[row].edition_id;
}

std::optional<std::size_t> CatalogTableProjection::rowForEdition(Id edition_id) const noexcept {
    if (edition_id <= 0) return std::nullopt;
    for (std::size_t row = 0; row < summaries_.size(); ++row) {
        if (summaries_[row].edition_id == edition_id) return row;
    }
    return std::nullopt;
}

} // namespace harald::presentation
