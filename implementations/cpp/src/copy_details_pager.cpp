#include <harald/presentation/copy_details_pager.hpp>

#include <algorithm>

namespace harald::presentation {

std::size_t CopyDetailsPager::pageCount(std::size_t item_count) const noexcept {
    // Divide first to avoid potential overflow of item_count + page_size.
    // One empty display page is useful for editions that may someday have no
    // physical items (digital-only records are a separate domain change).
    if (item_count == 0) return 1;
    return item_count / kPageSize + (item_count % kPageSize != 0 ? 1 : 0);
}

void CopyDetailsPager::clamp(std::size_t item_count) noexcept {
    page_ = std::min(page_, pageCount(item_count) - 1);
}

bool CopyDetailsPager::previous() noexcept {
    if (page_ == 0) return false;
    --page_;
    return true;
}

bool CopyDetailsPager::next(std::size_t item_count) noexcept {
    clamp(item_count);
    if (page_ + 1 >= pageCount(item_count)) return false;
    ++page_;
    return true;
}

} // namespace harald::presentation
