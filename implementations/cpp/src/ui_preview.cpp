#include <harald/catalog.hpp>
#include <harald/presentation/catalog_browser.hpp>

#include <sasd/ui/table_model.hpp>
#include <sasd/ui/table_selection_model.hpp>
#include <sasd/ui/table_view.hpp>

#include <cstdlib>
#include <exception>
#include <iostream>
#include <optional>
#include <stdexcept>
#include <string>

/**
 * Optional, headless SASD UI Toolkit integration.
 *
 * CatalogBrowser owns the application-layer search snapshot and keeps
 * typed edition IDs independent of positional TableView rows. StringTableModel
 * takes a separate owned copy of the display cells. Selection and TableView
 * borrow the model but are destroyed first (reverse declaration order).
 *
 * The first row is selected programmatically to demonstrate a selection-driven
 * details query through CatalogService. No SQL, SQLite handle or database key
 * parsing occurs in a widget. This is NOT a graphical desktop host.
 */
int main(int argc, char** argv) {
    try {
        if (argc < 2) {
            std::cerr << "Usage: harald_ui_preview PATH_TO_SQLITE_DB [FILTER]\n";
            return EXIT_FAILURE;
        }

        harald::SqliteCatalog repository(argv[1]);
        harald::CatalogService catalog(repository);
        harald::presentation::CatalogBrowser browser{catalog};
        browser.refresh(argc >= 3 ? argv[2] : "");

        sasd::ui::StringTableModel model(
            {"ID", "Title", "Creator", "Edition", "Copies"}, browser.tableRows());
        sasd::ui::TableSelectionModel selection;
        selection.setModel(&model);
        sasd::ui::TableView view;
        view.setModel(&model);
        view.setSelectionModel(&selection);
        view.setViewport(0, 20, 0, 5);

        for (const auto& row : view.visibleRows()) {
            std::cout << row.cells.at(0) << " | " << row.cells.at(1) << " | "
                      << row.cells.at(2) << " | " << row.cells.at(3) << " | "
                      << row.cells.at(4) << " copies\n";
        }

        if (browser.projection().rowCount() != 0) {
            if (!selection.select(0, 0)) {
                throw std::runtime_error("Cannot select the first catalog row");
            }
            const auto selected_cell = selection.selectedCell();
            // Selected positions are ephemeral; only the projection's typed ID
            // is allowed to cross into a domain details lookup.
            const bool available = selected_cell && browser.selectRow(selected_cell->row);
            const auto edition_id = available ? browser.selectedEditionId() : std::nullopt;
            if (!edition_id) {
                throw std::runtime_error("Selected catalog row is no longer available");
            }
            const auto& details = browser.selectedDetails();
            if (!details) {
                throw std::runtime_error("Selected edition was removed from the catalog");
            }

            std::cout << "Selected edition " << *edition_id << ": "
                      << details->book.title << '\n';
            for (const auto& copy : details->copies) {
                std::cout << "  Copy " << copy.id << " | " << copy.inventory_code
                          << " | " << copy.location << '\n';
            }
        }
        return EXIT_SUCCESS;
    } catch (const std::exception& e) {
        std::cerr << "HARALD UI preview error: " << e.what() << '\n';
        return EXIT_FAILURE;
    }
}
