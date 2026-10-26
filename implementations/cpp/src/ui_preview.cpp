#include <harald/catalog.hpp>

#include <sasd/ui/table_model.hpp>
#include <sasd/ui/table_selection_model.hpp>
#include <sasd/ui/table_view.hpp>

#include <cstdlib>
#include <exception>
#include <iostream>
#include <string>
#include <vector>

/**
 * Optional SASD UI Toolkit integration: a real TableModel and virtualized
 * TableView consume HARALD application data without knowing SQLite or the
 * persistence adapter. The preview prints visible rows to stdout for now;
 * it is NOT yet a native graphical desktop window.
 *
 * The corresponding desktop host will be a separate presentation adapter;
 * starting with an independently testable model allows its backend (Win32,
 * SDL3, GTK, ...) to change without changing catalogue use cases.
 */
int main(int argc, char** argv) {
    try {
        if (argc < 2) {
            std::cerr << "Usage: harald_ui_preview PATH_TO_SQLITE_DB [FILTER]\n";
            return EXIT_FAILURE;
        }
        harald::SqliteCatalog repository(argv[1]);
        harald::CatalogService catalog(repository);
        const auto books = catalog.search(argc >= 3 ? argv[2] : "");
        std::vector<std::vector<std::string>> rows;
        rows.reserve(books.size());
        for (const auto& book : books) {
            rows.push_back({std::to_string(book.edition_id), book.title, book.creator,
                            book.edition_label, std::to_string(book.copy_count)});
        }
        sasd::ui::StringTableModel model({"ID", "Title", "Creator", "Edition", "Copies"},
                                          std::move(rows));
        sasd::ui::TableSelectionModel selection;
        selection.setModel(&model);
        sasd::ui::TableView view;
        view.setModel(&model);
        view.setSelectionModel(&selection);
        view.setViewport(0, 20, 0, 5);
        for (auto const& row : view.visibleRows()) {
            std::cout << row.cells.at(0) << " | " << row.cells.at(1) << " | "
                      << row.cells.at(2) << " | " << row.cells.at(3) << " | "
                      << row.cells.at(4) << " copies\n";
        }
        return EXIT_SUCCESS;
    } catch (const std::exception& e) {
        std::cerr << "HARALD UI preview error: " << e.what() << '\n';
        return EXIT_FAILURE;
    }
}
