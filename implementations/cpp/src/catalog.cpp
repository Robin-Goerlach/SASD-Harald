#include <harald/catalog.hpp>

#include <cctype>
#include <stdexcept>
#include <unordered_set>

namespace harald {
namespace {
/** ASCII whitespace removal is enough for this first validated CLI slice.
 * Unicode normalization and ISBN checksum validation remain explicit future
 * requirements; silently pretending to do either would corrupt expectations.
 */
std::string trim(std::string_view value) {
    auto begin = value.find_first_not_of(" \t\r\n");
    if (begin == std::string_view::npos) return {};
    auto end = value.find_last_not_of(" \t\r\n");
    return std::string(value.substr(begin, end - begin + 1));
}
} // namespace

Id CatalogService::createBook(const BookDraft& draft) {
    BookDraft clean = draft;
    clean.title = trim(draft.title);
    clean.creator = trim(draft.creator);
    clean.edition_label = trim(draft.edition_label);
    clean.isbn = trim(draft.isbn);

    if (clean.title.empty() || clean.creator.empty() || clean.edition_label.empty()) {
        throw std::invalid_argument("title, creator and edition label are required");
    }
    if (clean.copies.empty()) {
        throw std::invalid_argument("at least one physical copy is required for this slice");
    }

    // Check duplicates before entering a transaction; SQL UNIQUE remains the
    // final authority for conflicts with copies already stored in the catalog.
    std::unordered_set<std::string> inventory_codes;
    for (auto& copy : clean.copies) {
        copy.inventory_code = trim(copy.inventory_code);
        copy.location = trim(copy.location);
        if (copy.inventory_code.empty() || copy.location.empty()) {
            throw std::invalid_argument("copy inventory code and location are required");
        }
        if (!inventory_codes.insert(copy.inventory_code).second) {
            throw std::invalid_argument("duplicate inventory code within the new book");
        }
    }
    return repository_.insertBook(clean);
}

std::vector<BookSummary> CatalogService::search(std::string_view term) const {
    return repository_.searchBooks(term);
}

std::optional<BookDetails> CatalogService::details(Id edition_id) const {
    if (edition_id <= 0) throw std::invalid_argument("edition id must be positive");
    return repository_.findBook(edition_id);
}
} // namespace harald
