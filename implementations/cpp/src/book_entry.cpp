#include <harald/presentation/book_entry.hpp>

namespace harald::presentation {

Id BookEntryController::create(const BookEntryFields& fields) {
    // Keep the mapping transparent and small. R0 CatalogService will trim and
    // validate its OWN BookDraft copy before calling the repository. The same
    // operation is already used by the CLI and can be reused by later clients.
    BookDraft draft{
        fields.title,
        fields.creator,
        fields.edition_label,
        fields.isbn,
        {{fields.inventory_code, fields.location}},
    };
    return service_.createBook(draft);
}

} // namespace harald::presentation
