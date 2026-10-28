#include <harald/catalog.hpp>
#include <harald/presentation/catalog_browser.hpp>

#if defined(_WIN32)
#  include <sasd/ui/native/win32_backend.hpp>
#else
#  include <sasd/ui/native/gtk_backend.hpp>
#endif

#include <sasd/ui/application.hpp>
#include <sasd/ui/button.hpp>
#include <sasd/ui/events/event.hpp>
#include <sasd/ui/focus_manager.hpp>
#include <sasd/ui/focus_traversal.hpp>
#include <sasd/ui/hit_test.hpp>
#include <sasd/ui/label.hpp>
#include <sasd/ui/pointer_router.hpp>
#include <sasd/ui/presentation/presentation_coordinator.hpp>
#include <sasd/ui/rendered/display_list.hpp>
#include <sasd/ui/rendered/rendered_presentation_sink.hpp>
#include <sasd/ui/rendered/rendered_text_field_pointer_selection.hpp>
#include <sasd/ui/rendered/table_view_presentation.hpp>
#include <sasd/ui/table_model.hpp>
#include <sasd/ui/table_selection_model.hpp>
#include <sasd/ui/table_view.hpp>
#include <sasd/ui/text_field.hpp>
#include <sasd/ui/window.hpp>

#include <algorithm>
#include <chrono>
#include <cstdlib>
#include <exception>
#include <iostream>
#include <string>
#include <thread>
#include <utility>
#include <variant>

namespace {

using namespace sasd::ui;

#if defined(_WIN32)
using DesktopBackend = native::win32::Win32WindowBackend;
using DesktopConfig = native::win32::Win32WindowBackendConfig;
#else
using DesktopBackend = native::gtk::GtkWindowBackend;
using DesktopConfig = native::gtk::GtkWindowBackendConfig;
#endif

/**
 * The first HARALD desktop host intentionally uses toolkit-native window
 * backends and the shared Rendered presentation surface, not platform-specific
 * controls. All SQL remains in SqliteCatalog; the window only knows the
 * CatalogBrowser application-facing projection and typed edition selections.
 *
 * Native window creation, semantic Widgets, table hit-testing and frame replay
 * follow the public SASD UI Toolkit 0.2 API. No SDL source or private toolkit
 * implementation headers are included here.
 */
int run(const std::string& database_path) {
    harald::SqliteCatalog repository{database_path};
    harald::CatalogService service{repository};
    harald::presentation::CatalogBrowser browser{service};

    DesktopConfig config{};
    config.title = "HARALD - Catalog (experimental)";
    config.initial_size = {960, 680};
    config.background_color = Color::black;
    DesktopBackend backend{std::move(config)};
    Application application{backend}; // Owns backend initialize/shutdown via RAII.

    // Table model and selection outlive the TableView (which observes them).
    // Replacing table cells never changes the stable edition IDs in browser.
    const std::vector<std::string> headers{"ID", "Title", "Creator", "Edition", "Copies"};
    StringTableModel table_model{headers, {}};
    TableSelectionModel selection;
    selection.setModel(&table_model);

    Window window;
    auto& heading = window.emplace<Label>("HARALD - Library & multimedia catalog");
    auto& search_label = window.emplace<Label>("Search:");
    auto& search = window.emplace<TextField>();
    auto& search_button = window.emplace<Button>("Search");
    auto& list_label = window.emplace<Label>("Catalog (select a row to view copies)");
    auto& table = window.emplace<TableView>();
    auto& details_title = window.emplace<Label>("No book selected");
    auto& details_edition = window.emplace<Label>("");
    auto& details_isbn = window.emplace<Label>("");
    auto& details_copies = window.emplace<Label>("");
    auto& copy_line_1 = window.emplace<Label>("");
    auto& copy_line_2 = window.emplace<Label>("");
    auto& copy_line_3 = window.emplace<Label>("");
    auto& status = window.emplace<Label>("Ready");

    table.setModel(&table_model);
    table.setSelectionModel(&selection);
    table.setViewport(0, 10, 0, headers.size());

    // Fixed logical positions are an explicit prototype limitation, not
    // HARALD's final responsive form system. Resize recomputes the table's
    // visible range and never lets negative geometry reach Widget::arrange().
    const auto arrange = [&](Size size) {
        const Coordinate w = std::max<Coordinate>(0, size.width);
        const Coordinate h = std::max<Coordinate>(0, size.height);
        const Coordinate table_height = std::max<Coordinate>(0, h - 350);
        window.arrange({0, 0, w, h});
        heading.arrange({16, 12, std::max<Coordinate>(0, w - 32), 30});
        search_label.arrange({16, 60, 80, 30});
        search.arrange({98, 53, std::max<Coordinate>(0, w - 240), 36});
        search_button.arrange({std::max<Coordinate>(0, w - 126), 53, 110, 36});
        list_label.arrange({16, 103, std::max<Coordinate>(0, w - 32), 26});
        table.arrange({16, 137, std::max<Coordinate>(0, w - 32), table_height});
        const Coordinate detail_y = 153 + table_height;
        details_title.arrange({16, detail_y, std::max<Coordinate>(0, w - 32), 27});
        details_edition.arrange({16, detail_y + 27, std::max<Coordinate>(0, w - 32), 25});
        details_isbn.arrange({16, detail_y + 52, std::max<Coordinate>(0, w - 32), 25});
        details_copies.arrange({16, detail_y + 77, std::max<Coordinate>(0, w - 32), 25});
        copy_line_1.arrange({25, detail_y + 104, std::max<Coordinate>(0, w - 50), 25});
        copy_line_2.arrange({25, detail_y + 129, std::max<Coordinate>(0, w - 50), 25});
        copy_line_3.arrange({25, detail_y + 154, std::max<Coordinate>(0, w - 50), 25});
        status.arrange({16, std::max<Coordinate>(0, h - 32),
                        std::max<Coordinate>(0, w - 32), 26});

        const Coordinate line_height = std::max<Coordinate>(1, backend.lineHeight());
        const auto visible_rows = static_cast<std::size_t>(
            std::max<Coordinate>(1, table_height / line_height - 1));
        table.setViewport(table.firstVisibleRow(), visible_rows, 0, headers.size());
    };

    const auto updateDetails = [&] {
        const auto& details = browser.selectedDetails();
        if (!details) {
            details_title.setText("No book selected");
            details_edition.setText("");
            details_isbn.setText("");
            details_copies.setText("");
            copy_line_1.setText("");
            copy_line_2.setText("");
            copy_line_3.setText("");
            return;
        }
        const auto& book = details->book;
        details_title.setText(book.title + "  |  " + book.creator);
        details_edition.setText("Edition: " + book.edition_label +
                                "  (ID " + std::to_string(book.edition_id) + ")");
        details_isbn.setText("ISBN: " + (book.isbn.empty() ? "(not specified)" : book.isbn));
        details_copies.setText("Physical copies: " + std::to_string(details->copies.size()));

        // This intentionally limited read-only detail pane displays the first
        // three items. The controller retains ALL copies; later scrolling and
        // a dedicated copy TableView can expose the rest without new SQL here.
        Label* lines[]{&copy_line_1, &copy_line_2, &copy_line_3};
        for (std::size_t i = 0; i < 3; ++i) {
            if (i < details->copies.size()) {
                const auto& item = details->copies[i];
                lines[i]->setText(item.inventory_code + "  |  " + item.location);
            } else {
                lines[i]->setText("");
            }
        }
        if (details->copies.size() > 3) {
            copy_line_3.setText("... more copies (detail scrolling not yet implemented)");
        }
    };

    // Toolkit reset notifications clear positional selection. Suppress only
    // that transient notification while replacing the table; then reselect by
    // the persistent domain ID preserved by CatalogBrowser::refresh().
    bool resetting_table = false;
    const auto subscription = selection.observe([&](const TableSelectionChange& change) {
        if (resetting_table) return;
        if (change.current) {
            if (!browser.selectRow(change.current->row)) {
                status.setText("Selected edition is no longer available.");
            }
        } else {
            browser.clearSelection();
        }
        updateDetails();
    });
    (void)subscription;

    const auto refresh = [&] {
        try {
            browser.refresh(std::string{search.text()});
            auto new_rows = browser.tableRows();
            resetting_table = true;
            try {
                table_model.reset(headers, std::move(new_rows));
            } catch (...) {
                resetting_table = false;
                throw;
            }
            resetting_table = false;
            if (const auto selected = browser.selectedRow()) {
                (void)selection.select(*selected, 0);
            }
            updateDetails();
            status.setText(std::to_string(browser.projection().rowCount()) +
                           " edition(s) found; filter: " + std::string(browser.filter()));
        } catch (const std::exception& failure) {
            // Keep the previous result on a repository error. Never claim
            // success or silently switch a storage profile here.
            status.setText(std::string{"Catalog search failed: "} + failure.what());
        }
    };
    search_button.setOnActivated(refresh);
    refresh();

    FocusManager focus;
    PointerRouter pointer_router;
    (void)focus.requestFocus(search);
    arrange(backend.windowSize());

    rendered::DisplayList frame;
    rendered::RenderedPresentationSink sink{frame, backend, Color::black};
    const auto present = [&] {
        if (backend.windowSize().isEmpty()) return;
        frame.clear();
        const auto result = PresentationCoordinator::replay(window, sink);
        if (!result.complete()) {
            throw std::runtime_error{"SASD UI rendered presentation was incomplete"};
        }
        (void)backend.presentFrame(frame);
    };
    present();

    while (!application.exitRequested()) {
        application.processRoutedEvents(
            [&](const Event& event) -> Widget* {
                if (std::holds_alternative<KeyEvent>(event) ||
                    std::holds_alternative<TextInputEvent>(event)) {
                    return focus.focusedWidget();
                }
                // PointerRouter owns capture and table pointer selection.
                return nullptr;
            },
            [&](const Event& event) {
                if (const auto* pointer = std::get_if<PointerEvent>(&event)) {
                    if (pointer->action == PointerAction::press &&
                        pointer->button == PointerButton::primary) {
                        Widget* hit = HitTest::deepestAt(window, pointer->position);
                        if (hit != nullptr && hit->canReceiveFocus()) {
                            (void)focus.requestFocus(*hit);
                        }
                        if (hit == &table) {
                            const auto snapshot = rendered::RenderedTableViewPresentation::snapshot(
                                table, table.bounds(), backend);
                            if (snapshot) {
                                (void)rendered::RenderedTableViewPresentation::selectAt(
                                    *snapshot, pointer->position, selection);
                            }
                            pointer_router.leaveRoot();
                            return;
                        }
                    }
                    (void)rendered::RenderedTextFieldPointerSelection::route(
                        window, pointer_router, *pointer, backend);
                } else if (const auto* surface = std::get_if<PointerSurfaceEvent>(&event)) {
                    if (surface->action == PointerSurfaceAction::left) {
                        pointer_router.leaveRoot();
                    }
                } else if (const auto* resize = std::get_if<ResizeEvent>(&event)) {
                    arrange(resize->size);
                } else if (const auto* key = std::get_if<KeyEvent>(&event)) {
                    if (FocusTraversal::handleEvent(focus, window, event) ==
                        EventResult::handled) {
                        return;
                    }
                    if (!key->pressed) return;
                    if (key->key == Key::enter && focus.focusedWidget() == &search) {
                        refresh();
                    } else if (key->key == Key::escape) {
                        application.requestExit();
                    }
                }
            });

        if (window.isVisualUpdatePending() || backend.presentationRequested()) {
            present();
        }
        std::this_thread::sleep_for(std::chrono::milliseconds{16});
    }
    return EXIT_SUCCESS;
}

} // namespace

int main(int argc, char** argv) {
    try {
        if (argc != 2) {
            std::cerr << "Usage: harald_desktop PATH_TO_SQLITE_DB\n";
            return EXIT_FAILURE;
        }
        return run(argv[1]);
    } catch (const std::exception& failure) {
        std::cerr << "HARALD desktop error: " << failure.what() << '\n';
        return EXIT_FAILURE;
    }
}
