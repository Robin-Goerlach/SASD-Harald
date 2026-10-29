# HARALD — First C++20 catalog implementation slice

> **Status: experimental, not HARALD V1.0.** This directory contains real, tested source code for a small SQLite-backed catalog. It does **not** yet implement circulation, media profiles, configurable JSON backends, acquisitions, export/backup, security, or a finished graphical desktop application. An **experimental optional native Windows/GTK4 catalog window with first book-entry form** now exists alongside the headless TableView preview; it is not the finished screen shown in the repository README.

This is the **M2/M3 exploratory vertical slice**. The main project remains in planning; an accepted stack ADR and a complete supported-OS matrix are still pending.

## Build on Linux (verified)

Prerequisites: CMake 3.20+, a C++20 compiler and SQLite3 development headers/library (e.g. `libsqlite3-dev`).

```sh
cmake -S implementations/cpp -B implementations/cpp/build -DCMAKE_BUILD_TYPE=Debug
cmake --build implementations/cpp/build --parallel
ctest --test-dir implementations/cpp/build --output-on-failure
```

Run from the **repository root**. The compiled program is at `implementations/cpp/build/harald_cli` on typical Linux single-configuration generators.

```sh
./implementations/cpp/build/harald_cli --db /tmp/harald-demo.sqlite init
./implementations/cpp/build/harald_cli --db /tmp/harald-demo.sqlite seed
./implementations/cpp/build/harald_cli --db /tmp/harald-demo.sqlite list
./implementations/cpp/build/harald_cli --db /tmp/harald-demo.sqlite list Example
./implementations/cpp/build/harald_cli --db /tmp/harald-demo.sqlite show 1
```

**CAUTION:** `seed` inserts one sample record only when the catalog contains no editions. Do not use a production database for experiments or assume the program makes backups. `init` creates a database if missing. Choosing a different database path opens a different collection; it does **not** migrate data.

Create a book and two copies explicitly:

```sh
./implementations/cpp/build/harald_cli --db /tmp/harald-demo.sqlite \
  add-book 'My first book' 'Example Author' 'Paperback' '' \
  'INV-101' 'Study / Shelf A' 'INV-102' 'Study / Shelf B'
```

The `add-book` demonstration is intentionally limited to **exactly two copies**. The underlying application service accepts one or more copies and rejects duplicate inventory codes.

### Optional SASD UI Toolkit model/view preview

This small **opt-in** target integrates `StringTableModel`, `TableSelectionModel` and `TableView` with real HARALD catalog data. It prints visible table rows, selects the first result and displays its physical copies through `CatalogService::details()`; it **does not** create a graphical window. It is deliberately kept separate until the desired desktop host and toolkit version are validated.

A separately installed SASD UI Toolkit CMake package version 0.2 is required. The **pinned package consumer is exercised in GitHub Actions on Linux**; this does not imply manual visual testing.

```sh
cmake -S implementations/cpp -B implementations/cpp/build-ui \
  -DCMAKE_BUILD_TYPE=Debug \
  -DHARALD_WITH_SASD_UI=ON \
  -DCMAKE_PREFIX_PATH=/path/to/installed/sasd-ui-toolkit
cmake --build implementations/cpp/build-ui --parallel
./implementations/cpp/build-ui/harald_ui_preview /tmp/harald-demo.sqlite
```

### Optional native desktop catalog window (experimental, 28 October 2026)

`harald_desktop` uses the **public** SASD UI Toolkit 0.2 interfaces for a native window, search field, search button, virtualized TableView, selection, read-only detail pane and a multi-copy book-entry form with Previous/Next/Add/Remove navigation. The view calls the new toolkit-neutral `CatalogBrowser`, which calls `CatalogService`; no SQL crosses the UI boundary. This is a catalog **browse/search/create prototype**, not a full create/edit/delete UI. The detail pane paginates all stored copies three at a time; manual keyboard/mouse accessibility acceptance is still open.

On **Windows**, install a compatible SASD UI Toolkit 0.2 **Debug** CMake package with its Win32 native target (the published toolkit CMake build does this on Windows). Use the same x64 MSVC toolchain/triplet and configure **Debug only**: the 0.2 export does not provide a Release library when it was installed from a Debug-only build. Do not mix Debug and Release MSVC runtimes. Then run:

```powershell
cmake -S implementations/cpp -B build-harald-desktop -A x64 -DCMAKE_CONFIGURATION_TYPES=Debug -DHARALD_WITH_DESKTOP=ON -DCMAKE_PREFIX_PATH="C:/path/to/sasd-ui-install"
cmake --build build-harald-desktop --config Debug
ctest --test-dir build-harald-desktop -C Debug --output-on-failure
.\build-harald-desktop\Debug\harald_cli.exe --db "$env:TEMP\harald-demo.sqlite" seed
.\build-harald-desktop\Debug\harald_desktop.exe "$env:TEMP\harald-demo.sqlite"
```

On **Linux**, GTK4 is *not* installed/exported by the pinned toolkit 0.2 CMake package. Its public native GTK target is currently **build-tree-only**. Install `libsqlite3-dev`, `libgtk-4-dev`, `pkg-config` and a C++20 toolchain; check out the toolkit separately and provide its source directory explicitly:

```sh
cmake -S implementations/cpp -B build-harald-desktop -DCMAKE_BUILD_TYPE=Debug \
  -DHARALD_WITH_DESKTOP=ON \
  -DHARALD_SASD_UI_SOURCE_DIR=/path/to/SASD-UI-Toolkit
cmake --build build-harald-desktop --parallel 2
ctest --test-dir build-harald-desktop --output-on-failure
./build-harald-desktop/harald_cli --db /tmp/harald-desktop.sqlite seed
./build-harald-desktop/harald_desktop /tmp/harald-desktop.sqlite
```

Use a **throwaway SQLite file** for the first interactive run. A GUI smoke test on a physical Windows/Linux session is still required; automated headless compilation alone does not prove native events, resizing and international text entry.

### Tests performed (26 October 2026, local environment)

- GCC 14.2 Debug build and CTest — passed.
- GCC 14.2 Release build and CTest — passed.
- Clang/LLVM Debug build and CTest — passed.
- Manual CLI `init`, `seed`, `list`, `show` — passed on Linux with SQLite 3.46.1.
- Not tested: Windows/MSVC, macOS, FreeBSD/OpenBSD, real SASD UI package integration, graphical desktop host, sanitizer run, multiple concurrent writers.

## Architecture

```text
CLI (now) / SASD UI Adapter (optional) / future REST/UI clients
                         │
                 CatalogService
                         │
                CatalogRepository   ← port, no sqlite3 types
                         │
                 SqliteCatalog      ← implementation adapter
                         │
                SQLite schema v1
```

- [`include/harald/catalog.hpp`](include/harald/catalog.hpp): portable domain types and the repository contract.
- [`src/catalog.cpp`](src/catalog.cpp): independent validation and application use cases.
- [`src/sqlite_catalog.cpp`](src/sqlite_catalog.cpp): concrete SQLite access, migration and transactions.
- [`src/main.cpp`](src/main.cpp): minimal command-line host.
- [`src/catalog_table_projection.cpp`](src/catalog_table_projection.cpp): toolkit-independent, owned table/edition-ID projection with negative and Unicode tests.
- [`src/catalog_browser.cpp`](src/catalog_browser.cpp): UI-independent search/selection/details controller with typed IDs, refresh identity preservation and failure atomicity.\n- [`tests/catalog_browser_tests.cpp`](tests/catalog_browser_tests.cpp): deterministic tests for Unicode, filter/reorder, deletion, stale selection and repository failure.\n- [`src/ui_preview.cpp`](src/ui_preview.cpp): optional SASD UI Toolkit console consumer bound through CatalogBrowser.\n- [`src/desktop_main.cpp`](src/desktop_main.cpp): optional native Win32/GTK4 interactive catalog browser.
- [`tests/catalog_tests.cpp`](tests/catalog_tests.cpp): integration tests using real SQLite.
- [`docs/ARCHITECTURE_SLICE.md`](docs/ARCHITECTURE_SLICE.md): implementation boundaries, deliberate limitations and next increment.

The first schema distinguishes **Work**, **Edition** and **Copy**; it is deliberately simpler than the final multimedia catalog. SQLite `FOREIGN KEY`, `UNIQUE` and `CHECK` constraints complement application validation. The whole new-book operation uses `BEGIN IMMEDIATE` and commits Work, Edition and all copies **atomically**. Prepared statements protect user values. Migration version 1 is recorded using `PRAGMA user_version` and rejects databases with a newer schema version.

A SQLite file in this prototype is not a general cross-language interchange contract. JSON remains a planned **storage adapter**, not an implemented feature. The REST server is likewise future work; it must own server-side use cases and permissions.

## Known limitations

- No update/delete, transactions across external asset stores, lending, authentication or availability states yet.
- Search is literal substring matching in SQLite `LIKE`; SQLite's built-in case folding is limited for non-ASCII Unicode. Full-text search and language-aware collation are future concerns.
- The domain currently represents only book editions with creator and an optional raw ISBN; formal ISBN validation and multi-creator/format-specific profiles remain undone.
- IDs are SQLite-generated integers in this proof-of-concept; stable cross-backend IDs and migration policy remain an ADR decision.
- No portable backup/restore or JSON migration exists; this prototype is **not suitable for irreplaceable library data**.
- Concurrency and schema upgrades beyond v1 still need design and testing.
- The console preview remains headless. The native window supports a variable number of new physical copies and read-only paged copy details, but has no edition edit/delete, accessible keyboard/IME acceptance or general-purpose responsive form scrolling.

## Next increment

Manually smoke-test search, book creation, keyboard focus/text input and pointer selection on real Windows/Linux desktops. Then improve layout/resizing and add a edition editing/deletion, domain error categories and a scrollable responsive form. Automated Windows compile/CTest and Linux Xvfb startup checks are configured in GitHub Actions, but they cannot replace manual accessibility/IME tests. **Do not mark the full M3 milestone complete until export/restore, UI and platform validation are proven.**

### Catalog selection bridge (experimental, 28 October 2026)

`HARALD::CatalogPresentation` adds `CatalogTableProjection`: an owned, five-column snapshot of `CatalogService::search()` results, independent of SQLite and SASD UI. The projection validates that edition IDs are positive and unique; `editionIdAt(row)` converts a selected table row into an authoritative application ID, and `rowForEdition(id)` can restore selection after filtering/reordering. A stale row returns no ID, not an unrelated record. This does **not** create globally portable IDs; that requires a separate design/migration step.

The headless `harald_catalog_table_projection_tests` is enabled by the default CTest configuration and exercises Unicode, selection after reorder/filter, owned snapshot values, invalid/duplicate IDs, and stale rows. An additional Linux CI job builds the pinned SASD UI Toolkit (commit `2dd0b6f`, 0.2.0) as an installed package and compiles/runs the optional headless preview. Its actual outcome must be checked in GitHub Actions; the preview remains a console demo, not a graphical application. A real SDL/native desktop host and interactive search remain future work.

### Native catalog browser coordinator (experimental, 28 October 2026)

`CatalogBrowser` retains an owned `CatalogTableProjection`, applied filter, selected **Edition ID** and optional owned `BookDetails`. Selecting a table row is translated into the stable edition ID before querying the service. After search the selected ID survives **reorder** but not filtering/removal. Repository exceptions leave the prior visible snapshot intact. `StringTableModel::reset()` invalidates toolkit positional selection; the desktop adapter deliberately suppresses transient deselection notifications and then reselects by the preserved ID. These behaviors are covered by a new default-build CTest. Neither `HARALD::Catalog` nor `HARALD::CatalogPresentation` depends on SASD UI.


### New book form and native smoke test (experimental, 28 October 2026)

Click **New book** and enter title, author/creator, edition, optional ISBN, inventory code and physical location. For any number of physical copies, enter an inventory code and location, then click **Add copy** to enter another. **Previous** and **Next** navigate the locally edited copies; **Remove copy** drops only the currently selected unsaved draft. The first copy cannot be removed, but it can be edited. A successful **Save book** calls the same `CatalogService::createBook()` used by the CLI and commits Work/Edition/**all** Copies atomically, returns to the catalog, clears the search filter and attempts to select the new edition by typed ID. **Cancel** makes no database changes. On a validation/storage error, the editor remains open with its entered text intact. The form requires **at least one physical copy**; zero-copy/digital-only editions require separate business requirements.

Automated `harald_book_entry_tests` invokes the real SQLite adapter, including multi-copy persistence after reopen and rollback on a duplicate inventory code in the **last** submitted copy. A separate toolkit-free `BookCopyEditor` model is tested for Add/Previous/Next/Remove behavior. Linux CI also uses `xvfb-run` to start GTK4 and render an initial frame. This checks only native startup and renderer integration, **not interactive behavior**.

Use a disposable test database for smoke tests:

```sh
./build-harald-desktop/harald_cli --db /tmp/harald-smoke.sqlite seed
xvfb-run -a ./build-harald-desktop/harald_desktop /tmp/harald-smoke.sqlite --smoke
```

Windows CI compiles the native Win32 target against a pinned installed Toolkit 0.2 package, with SQLite supplied through vcpkg, and executes the same four headless CTests. Successful CI does not imply that a person has verified the visual UI. **MSVC and Windows CI results should be checked for each commit before a merge.**

### Copy paging and entry model (29 October 2026)

The native window now supports **arbitrarily many** physical copies per new
edition without allocating a variable number of SASD UI controls. The
`BookCopyEditor` state model stores all unsaved `CopyDraft` values and the
selected copy index. Before changing the index, the window copies the two
currently visible text field values into the state model; switching back
restores the previously entered values. **Add**, **Previous**, **Next** and
**Remove** do not perform SQL or create incomplete editions. The final
**Save book** calls the existing validated service once with the entire
aggregate. On failure, the form and its current unsaved copy remain available
for correction.

The read-only catalog detail pane uses the toolkit-neutral `CopyDetailsPager`
to show physical copies in **pages of three** with **< Copies** and **Copies >** navigation. No persisted copy is
silently hidden by a truncation indicator.

The form uses a compact, partially responsive layout and still needs manual
acceptance at narrow window sizes and with assistive technologies. Automated
CI proves compilation, SQLite integration and native initial-frame startup,
not that a real user can interact reliably with every widget.
