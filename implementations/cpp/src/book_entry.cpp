#include <harald/presentation/book_entry.hpp>

#include <algorithm>
#include <utility>

namespace harald::presentation {

void BookCopyEditor::editCurrent(CopyDraft draft) {
    // Build an owned draft from the UI. Assigning this row never validates,
    // trims or inserts a record; those operations belong to CatalogService.
    copies_[selected_] = std::move(draft);
}

bool BookCopyEditor::select(std::size_t index) noexcept {
    if (index >= copies_.size()) return false;
    selected_ = index;
    return true;
}

void BookCopyEditor::append() {
    // Only update the current index AFTER push_back succeeds. If allocation
    // fails, the old editor selection remains usable.
    copies_.emplace_back();
    selected_ = copies_.size() - 1;
}

bool BookCopyEditor::removeCurrent() {
    if (copies_.size() == 1) return false;

    copies_.erase(copies_.begin() +
                  static_cast<std::vector<CopyDraft>::difference_type>(selected_));
    // Deleting the final item selects the new final item; deleting a middle
    // row selects the copy that shifted into the vacated position.
    selected_ = std::min(selected_, copies_.size() - 1);
    return true;
}

void BookCopyEditor::reset() {
    // Construct before replacing existing rows to keep the old draft intact
    // if memory allocation fails.
    std::vector<CopyDraft> clean(1);
    copies_.swap(clean);
    selected_ = 0;
}

Id BookEntryController::create(const BookEntryFields& fields) {
    // The vector is passed through as ONE aggregate: no per-row inserts are
    // performed in the UI. CatalogService checks emptiness, normalization and
    // duplicates BEFORE calling CatalogRepository::insertBook().
    BookDraft draft{
        fields.title,
        fields.creator,
        fields.edition_label,
        fields.isbn,
        fields.copies,
    };
    return service_.createBook(draft);
}

} // namespace harald::presentation
