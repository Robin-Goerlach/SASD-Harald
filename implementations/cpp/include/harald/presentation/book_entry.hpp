#pragma once

#include <harald/catalog.hpp>

#include <string>

namespace harald::presentation {

/**
 * One editable book form, independent of SASD UI controls and SQL.
 *
 * All fields are owned UTF-8 strings. The entry form's first increment
 * deliberately captures exactly ONE physical copy: creating a bare edition
 * without inventory is not permitted by the existing R0 CatalogService.
 * Additional copies and digital-only editions need separate future use cases.
 */
struct BookEntryFields final {
    std::string title;
    std::string creator;
    std::string edition_label;
    std::string isbn;
    std::string inventory_code;
    std::string location;
};

/**
 * Presentation-facing command that adapts form fields to the existing use case.
 *
 * The controller deliberately does NOT duplicate mandatory-field validation,
 * trimming, uniqueness checks or transaction logic. CatalogService owns those
 * business rules; its CatalogRepository port enforces atomic persistence.
 *
 * The caller owns CatalogService for the lifetime of this controller.
 * Exceptions are propagated so the UI can preserve entered text and report
 * the failure without pretending a transaction succeeded.
 */
class BookEntryController final {
public:
    explicit BookEntryController(CatalogService& service) noexcept : service_{service} {}

    /**
     * Creates a work, edition and one physical copy as one atomic use case.
     *
     * @param fields Owned user input from the desktop form.
     * @returns Persisted edition identity for post-save selection.
     * @throws std::invalid_argument On invalid bibliographic/copy data.
     * @throws std::runtime_error On storage failure (e.g. duplicate barcode).
     */
    [[nodiscard]] Id create(const BookEntryFields& fields);

private:
    CatalogService& service_;
};

} // namespace harald::presentation
