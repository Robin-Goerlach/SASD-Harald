#include <harald/catalog.hpp>
#include <harald/presentation/catalog_browser.hpp>
#include <harald/presentation/book_entry.hpp>

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
#include <array>
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
int run(const std::string& database_path, bool smoke_test) {
    harald::SqliteCatalog repository{database_path};
    harald::CatalogService service{repository};
    harald::presentation::CatalogBrowser browser{service};
    harald::presentation::BookEntryController entry{service};
    harald::presentation::BookCopyEditor copy_editor;

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
    auto& new_book = window.emplace<Button>("New book");
    auto& list_label = window.emplace<Label>("Catalog (select a row to view copies)");
    auto& table = window.emplace<TableView>();
    auto& details_title = window.emplace<Label>("No book selected");
    auto& details_edition = window.emplace<Label>("");
    auto& details_isbn = window.emplace<Label>("");
    auto& details_copies = window.emplace<Label>("");
    auto& copy_line_1 = window.emplace<Label>("");
    auto& copy_line_2 = window.emplace<Label>("");
    auto& copy_line_3 = window.emplace<Label>("");
    auto& details_previous = window.emplace<Button>("< Copies");
    auto& details_page = window.emplace<Label>("");
    auto& details_next = window.emplace<Button>("Copies >");

    // The detail view is a PAGE over BookDetails::copies, never a truncated
    // list. Every copy remains reachable without SQL or native widgets here.
    std::size_t details_copy_page = 0;
    constexpr std::size_t kCopiesPerPage = 3;
    auto& status = window.emplace<Label>("Ready");

    /*
     * Editor controls belong to HARALD, not the generic toolkit. We reuse
     * normal semantic TextFields, Buttons and Labels; there are no SQL calls
     * and no second, platform-specific widget hierarchy.
     *
     * The first book-entry use case intentionally creates ONE physical copy.
     * A variable-length copy editor will be a separate, tested milestone.
     */
    auto& form_heading = window.emplace<Label>("New book with physical copies");
    auto& title_label = window.emplace<Label>("Title *");
    auto& title_input = window.emplace<TextField>();
    auto& creator_label = window.emplace<Label>("Author / creator *");
    auto& creator_input = window.emplace<TextField>();
    auto& edition_label = window.emplace<Label>("Edition *");
    auto& edition_input = window.emplace<TextField>();
    auto& isbn_label = window.emplace<Label>("ISBN (optional)");
    auto& isbn_input = window.emplace<TextField>();
    auto& copy_position = window.emplace<Label>("Copy 1 / 1");
    auto& inventory_label = window.emplace<Label>("Inventory code *");
    auto& inventory_input = window.emplace<TextField>();
    auto& location_label = window.emplace<Label>("Location *");
    auto& location_input = window.emplace<TextField>();
    auto& copy_previous = window.emplace<Button>("< Previous");
    auto& copy_next = window.emplace<Button>("Next >");
    auto& copy_add = window.emplace<Button>("Add copy");
    auto& copy_remove = window.emplace<Button>("Remove copy");
    auto& save_button = window.emplace<Button>("Save book");
    auto& cancel_button = window.emplace<Button>("Cancel");

    const std::array<Widget*, 16> browsing_controls{
        &search_label, &search, &search_button, &new_book, &list_label, &table,
        &details_title, &details_edition, &details_isbn, &details_copies,
        &copy_line_1, &copy_line_2, &copy_line_3,
        &details_previous, &details_page, &details_next};
    const std::array<Widget*, 20> editing_controls{
        &form_heading, &title_label, &title_input, &creator_label, &creator_input,
        &edition_label, &edition_input, &isbn_label, &isbn_input,
        &copy_position, &inventory_label, &inventory_input,
        &location_label, &location_input, &copy_previous, &copy_next,
        &copy_add, &copy_remove, &save_button, &cancel_button};
    bool editing = false;
    for (Widget* control : editing_controls) control->setVisible(false);

    table.setModel(&table_model);
    table.setSelectionModel(&selection);
    table.setViewport(0, 10, 0, headers.size());

    // Fixed logical positions are an explicit prototype limitation, not
    // HARALD's final responsive form system. Resize recomputes the table's
    // visible range and never lets negative geometry reach Widget::arrange().
    const auto arrange = [&](Size size) {
        const Coordinate w = std::max<Coordinate>(0, size.width);
        const Coordinate h = std::max<Coordinate>(0, size.height);
        // Reserve a full detail pager beneath the table, including a
        // persistent status line. Three physical copies are shown per page.
        const Coordinate table_height = std::max<Coordinate>(0, h - 398);
        window.arrange({0, 0, w, h});
        heading.arrange({16, 12, std::max<Coordinate>(0, w - 32), 30});
        search_label.arrange({16, 60, 80, 30});
        search.arrange({98, 53, std::max<Coordinate>(0, w - 240), 36});
        search_button.arrange({std::max<Coordinate>(0, w - 126), 53, 110, 36});
        new_book.arrange({16, 99, 112, 32});
        list_label.arrange({144, 103, std::max<Coordinate>(0, w - 160), 26});
        table.arrange({16, 137, std::max<Coordinate>(0, w - 32), table_height});
        const Coordinate detail_y = 153 + table_height;
        details_title.arrange({16, detail_y, std::max<Coordinate>(0, w - 32), 27});
        details_edition.arrange({16, detail_y + 27, std::max<Coordinate>(0, w - 32), 25});
        details_isbn.arrange({16, detail_y + 52, std::max<Coordinate>(0, w - 32), 25});
        details_copies.arrange({16, detail_y + 77, std::max<Coordinate>(0, w - 32), 25});
        copy_line_1.arrange({25, detail_y + 104, std::max<Coordinate>(0, w - 50), 25});
        copy_line_2.arrange({25, detail_y + 129, std::max<Coordinate>(0, w - 50), 25});
        copy_line_3.arrange({25, detail_y + 154, std::max<Coordinate>(0, w - 50), 25});
        details_previous.arrange({16, detail_y + 188, 126, 32});
        details_page.arrange({158, detail_y + 188, 150, 28});
        details_next.arrange({318, detail_y + 188, 126, 32});
        /*
         * Compact responsive editor layout: a single active copy uses the
         * same two fields regardless of how many CopyDrafts exist. The list
         * itself is stored in BookCopyEditor, NOT by creating Widget children
         * for every copy. This avoids hard-coded upper copy limits.
         *
         * Smaller windows compress the vertical rhythm to 32px. Extremely
         * tiny windows (< ~450px) still need a future ScrollView/FormLayout.
         */
        const Coordinate field_step = std::clamp<Coordinate>((h - 350) / 6, 32, 52);
        const Coordinate y_first = 103;
        form_heading.arrange({16, 58, std::max<Coordinate>(0, w - 32), 30});
        const std::array<Label*, 6> form_labels{&title_label, &creator_label,
            &edition_label, &isbn_label, &inventory_label, &location_label};
        const std::array<TextField*, 6> form_inputs{&title_input, &creator_input,
            &edition_input, &isbn_input, &inventory_input, &location_input};
        for (std::size_t i = 0; i < form_labels.size(); ++i) {
            const Coordinate y = i < 4
                ? y_first + static_cast<Coordinate>(i) * field_step
                : y_first + static_cast<Coordinate>(i) * field_step + 27;
            form_labels[i]->arrange({16, y, 170, 30});
            form_inputs[i]->arrange({195, y,
                                    std::max<Coordinate>(0, w - 216), 33});
        }
        const Coordinate copy_heading_y = y_first + 4 * field_step;
        copy_position.arrange({16, copy_heading_y, std::max<Coordinate>(0, w - 32), 23});

        // Copy commands reflow into two rows when horizontal space is scarce.
        // The editor remains explicitly limited to readable-sized windows.
        const Coordinate nav_y = y_first + 6 * field_step + 33;
        const Coordinate nav_width = std::min<Coordinate>(
            132, std::max<Coordinate>(0, (w - 58) / 4));
        copy_previous.arrange({16, nav_y, nav_width, 32});
        copy_next.arrange({22 + nav_width, nav_y, nav_width, 32});
        copy_add.arrange({28 + 2 * nav_width, nav_y, nav_width, 32});
        copy_remove.arrange({34 + 3 * nav_width, nav_y, nav_width, 32});
        save_button.arrange({16, nav_y + 44, 150, 36});
        cancel_button.arrange({176, nav_y + 44, 150, 36});
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
            details_page.setText("");
            return;
        }
        const auto& book = details->book;
        details_title.setText(book.title + "  |  " + book.creator);
        details_edition.setText("Edition: " + book.edition_label +
                                "  (ID " + std::to_string(book.edition_id) + ")");
        details_isbn.setText("ISBN: " + (book.isbn.empty() ? "(not specified)" : book.isbn));
        details_copies.setText("Physical copies: " + std::to_string(details->copies.size()));

        /*
         * A fixed set of three read-only labels represents a paged window
         * over ALL owned physical copies. The previous prototype discarded
         * the third visible copy to show "...more"; this one never hides a
         * persisted copy. Page state is re-clamped after every refresh.
         */
        const std::size_t pages = std::max<std::size_t>(
            1, (details->copies.size() + kCopiesPerPage - 1) / kCopiesPerPage);
        details_copy_page = std::min(details_copy_page, pages - 1);
        const std::size_t offset = details_copy_page * kCopiesPerPage;
        Label* lines[]{&copy_line_1, &copy_line_2, &copy_line_3};
        for (std::size_t i = 0; i < kCopiesPerPage; ++i) {
            if (offset + i < details->copies.size()) {
                const auto& item = details->copies[offset + i];
                lines[i]->setText(item.inventory_code + "  |  " + item.location);
            } else {
                lines[i]->setText("");
            }
        }
        details_page.setText("Page " + std::to_string(details_copy_page + 1) +
                             " / " + std::to_string(pages));
    };

    details_previous.setOnActivated([&] {
        if (details_copy_page > 0) {
            --details_copy_page;
            updateDetails();
        }
    });
    details_next.setOnActivated([&] {
        if (const auto& details = browser.selectedDetails()) {
            const auto pages = (details->copies.size() + kCopiesPerPage - 1) /
                               kCopiesPerPage;
            if (details_copy_page + 1 < pages) {
                ++details_copy_page;
                updateDetails();
            }
        }
    });

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
        details_copy_page = 0;
        updateDetails();
    });
    (void)subscription;

    const auto refresh = [&]() -> bool {
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
            details_copy_page = 0;
            updateDetails();
            status.setText(std::to_string(browser.projection().rowCount()) +
                           " edition(s) found; filter: " + std::string(browser.filter()));
            return true;
        } catch (const std::exception& failure) {
            // Keep the previous result on a repository error. Never claim
            // success or silently switch a storage profile here.
            status.setText(std::string{"Catalog search failed: "} + failure.what());
            return false;
        }
    };
    search_button.setOnActivated([&] { (void)refresh(); });
    (void)refresh();

    FocusManager focus;
    PointerRouter pointer_router;
    (void)focus.requestFocus(search);
    arrange(backend.windowSize());

    /*
     * The copy navigator saves its currently edited fields BEFORE switching
     * rows. No database operation happens during Add/Next/Previous/Remove.
     * A validation error at Save leaves every draft and the active row intact.
     */
    const auto saveVisibleCopy = [&] {
        copy_editor.editCurrent({std::string{inventory_input.text()},
                                 std::string{location_input.text()}});
    };
    const auto showVisibleCopy = [&] {
        inventory_input.setText(copy_editor.current().inventory_code);
        location_input.setText(copy_editor.current().location);
        copy_position.setText("Physical copy " +
                              std::to_string(copy_editor.selectedIndex() + 1) +
                              " / " + std::to_string(copy_editor.size()));
    };
    copy_previous.setOnActivated([&] {
        saveVisibleCopy();
        if (copy_editor.selectedIndex() > 0) {
            (void)copy_editor.select(copy_editor.selectedIndex() - 1);
            showVisibleCopy();
        }
    });
    copy_next.setOnActivated([&] {
        saveVisibleCopy();
        if (copy_editor.select(copy_editor.selectedIndex() + 1)) {
            showVisibleCopy();
        }
    });
    copy_add.setOnActivated([&] {
        saveVisibleCopy();
        copy_editor.append();
        showVisibleCopy();
        (void)focus.requestFocus(inventory_input);
        status.setText("New blank copy added to the draft (not saved yet).");
    });
    copy_remove.setOnActivated([&] {
        if (!copy_editor.removeCurrent()) {
            status.setText("At least one physical copy is required.");
            return;
        }
        showVisibleCopy();
        status.setText("Draft copy removed; no database change.");
    });

    /**
     * Switching the visible view is strictly a presentation operation.
     * No transaction starts when the editor is opened or cancelled. Toolkit
     * visibility clears hidden-widget focus, so we focus an eligible control.
     */
    const auto showEditor = [&](bool open) {
        editing = open;
        for (Widget* control : browsing_controls) control->setVisible(!open);
        for (Widget* control : editing_controls) control->setVisible(open);
        (void)focus.requestFocus(open ? static_cast<Widget&>(title_input)
                                      : static_cast<Widget&>(search));
        arrange(backend.windowSize());
    };

    new_book.setOnActivated([&] {
        // Opening starts a NEW form. A cancelled form must not accidentally
        // resurrect unsaved copies from the previous editing session.
        copy_editor.reset();
        title_input.setText("");
        creator_input.setText("");
        edition_input.setText("");
        isbn_input.setText("");
        showVisibleCopy();
        showEditor(true);
        status.setText("Fields marked * are required. Save or Cancel.");
    });
    cancel_button.setOnActivated([&] {
        // Cancel is a presentation-only action; the untouched persisted
        // catalog will be shown. The next New book resets the draft.
        showEditor(false);
        status.setText("Book entry cancelled; no data was written.");
    });

    save_button.setOnActivated([&] {
        try {
            // Make owned UTF-8 copies before passing any values to the
            // application layer. A rejected write leaves all fields intact.
            saveVisibleCopy();
            const harald::presentation::BookEntryFields fields{
                std::string{title_input.text()}, std::string{creator_input.text()},
                std::string{edition_input.text()}, std::string{isbn_input.text()},
                copy_editor.copies(),
            };
            const harald::Id edition_id = entry.create(fields);

            // Once COMMIT succeeded, clear the search filter so the new book
            // will be visible even when the old query excluded its title.
            search.setText("");
            showEditor(false);
            if (refresh()) {
                if (const auto row = browser.projection().rowForEdition(edition_id)) {
                    (void)selection.select(*row, 0);
                }
                status.setText("Book saved (edition " + std::to_string(edition_id) + ").");
            } else {
                status.setText("Book saved (edition " + std::to_string(edition_id) +
                               "), but the catalog refresh failed.");
            }

            // Only reset after persistence. A storage error must NEVER erase
            // a partially entered form or imply that the write succeeded.
            title_input.setText("");
            creator_input.setText("");
            edition_input.setText("");
            isbn_input.setText("");
            copy_editor.reset();
            showVisibleCopy();
        } catch (const std::exception& problem) {
            status.setText(std::string{"Book not saved: "} + problem.what());
        }
    });

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

    if (smoke_test) {
        /*
         * Under Xvfb this verifies the actual GTK/native host initializes,
         * queries SQLite and accepts a rendered frame. It does not establish
         * interactive mouse, keyboard, IME or visual accessibility quality.
         */
        std::cout << "HARALD native desktop startup smoke passed\n";
        return EXIT_SUCCESS;
    }

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
                        (void)refresh();
                    } else if (key->key == Key::escape && editing) {
                        showEditor(false);
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
        if (argc != 2 && !(argc == 3 && std::string{argv[2]} == "--smoke")) {
            std::cerr << "Usage: harald_desktop PATH_TO_SQLITE_DB [--smoke]\n";
            return EXIT_FAILURE;
        }
        return run(argv[1], argc == 3);
    } catch (const std::exception& failure) {
        std::cerr << "HARALD desktop error: " << failure.what() << '\n';
        return EXIT_FAILURE;
    }
}
