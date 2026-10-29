#pragma once

#include <harald/catalog.hpp>

#include <cstddef>
#include <string>
#include <vector>

namespace harald::presentation {

/**
 * Owned values entered in the "New book" desktop form.
 *
 * This DTO deliberately does not depend on a Widget, SQLite or the native
 * window. An Edition may have any POSITIVE number of physical copies. Each
 * CopyDraft has its own globally unique inventory code and a location.
 * CatalogService remains the sole authority for validation and transactions.
 */
struct BookEntryFields final {
    std::string title;
    std::string creator;
    std::string edition_label;
    std::string isbn;
    std::vector<CopyDraft> copies;
};

/**
 * Toolkit-independent editor for a variable-length set of physical copies.
 *
 * Instead of constructing unbounded native widgets, the desktop presents one
 * copy at a time and pages through this owned collection. The UI first saves
 * its two visible TextField values using editCurrent(), then changes the
 * selection and loads current() into the same controls.
 *
 * Invariants:
 * - exactly one copy is selected at all times;
 * - at least one draft row always exists (it may still be empty);
 * - navigation/add/remove do NOT write to the database;
 * - Save validates ALL drafts together through CatalogService.
 *
 * Removal of the last row is disallowed so the view can never dereference an
 * empty collection. A newly opened form should call reset() to discard edits.
 */
class BookCopyEditor final {
public:
    BookCopyEditor() : copies_(1) {}

    [[nodiscard]] std::size_t size() const noexcept { return copies_.size(); }
    [[nodiscard]] std::size_t selectedIndex() const noexcept { return selected_; }
    [[nodiscard]] const CopyDraft& current() const noexcept {
        return copies_[selected_];
    }
    [[nodiscard]] const std::vector<CopyDraft>& copies() const noexcept {
        return copies_;
    }

    /** Replace one draft; database validation occurs only at Save. */
    void editCurrent(CopyDraft draft);

    /** Select an existing row; invalid indexes do not change the state. */
    [[nodiscard]] bool select(std::size_t index) noexcept;

    /** Append a BLANK physical copy and make it the visible row. */
    void append();

    /** Remove the selected row unless it is the only remaining row. */
    [[nodiscard]] bool removeCurrent();

    /** Start an entirely fresh entry; no persistence operation is performed. */
    void reset();

private:
    std::vector<CopyDraft> copies_;
    std::size_t selected_ = 0;
};

/**
 * Form command adapter. Input is copied to a domain BookDraft and forwarded to
 * the existing service. It MUST NOT maintain a parallel validation rule set.
 * The service normalizes fields and enforces duplicate-code checks; SQLite
 * inserts Work, Edition and every Copy within one transaction.
 *
 * The caller owns CatalogService longer than the adapter.
 */
class BookEntryController final {
public:
    explicit BookEntryController(CatalogService& service) noexcept : service_{service} {}

    /**
     * @returns Persisted edition ID, only after the transaction succeeded.
     * @throws std::invalid_argument Invalid title/edition/copy input.
     * @throws std::runtime_error Storage or uniqueness failure.
     *
     * The input DTO stays unchanged on failure, so a caller can show its
     * previous form values and allow the user to correct them.
     */
    [[nodiscard]] Id create(const BookEntryFields& fields);

private:
    CatalogService& service_;
};

} // namespace harald::presentation
