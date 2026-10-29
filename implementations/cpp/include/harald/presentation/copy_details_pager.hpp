#pragma once

#include <cstddef>

namespace harald::presentation {

/**
 * Toolkit-independent paging state for read-only physical-copy details.
 *
 * The catalog browser owns the complete BookDetails aggregate; the desktop
 * renders a small view of it. This class prevents widget callbacks from
 * reimplementing and accidentally diverging on page bounds and row offsets.
 *
 * Zero copies still represents one EMPTY page; rendering code may show its
 * normal "no copies" state. Counts are calculated without size_t addition
 * overflow (unlike a naive (n + page_size - 1) / page_size).
 */
class CopyDetailsPager final {
public:
    static constexpr std::size_t kPageSize = 3;

    [[nodiscard]] std::size_t page() const noexcept { return page_; }

    [[nodiscard]] std::size_t pageCount(std::size_t item_count) const noexcept;

    /** First item of the currently selected page (after caller clamps). */
    [[nodiscard]] std::size_t firstIndex() const noexcept {
        return page_ * kPageSize;
    }

    /** Rebound the page after details are refreshed or the count shrinks. */
    void clamp(std::size_t item_count) noexcept;

    /** Move only within a valid page range; neither function reads storage. */
    [[nodiscard]] bool previous() noexcept;
    [[nodiscard]] bool next(std::size_t item_count) noexcept;

    /** New edition selection starts at the first copy, regardless of history. */
    void reset() noexcept { page_ = 0; }

private:
    std::size_t page_ = 0;
};

} // namespace harald::presentation
