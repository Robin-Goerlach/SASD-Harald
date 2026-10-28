# HARALD — First C++20 catalog implementation slice

> **Status: experimental, not HARALD V1.0.** This directory contains real, tested source code for a small SQLite-backed catalog. It does **not** yet implement circulation, media profiles, configurable JSON backends, acquisitions, export/backup, security, or a graphical desktop application. The optional SASD UI Toolkit target is a **headless model/view preview**, not the finished screen shown in the repository README.

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

A separately installed SASD UI Toolkit CMake package version 0.2 or later is required; this optional target has **not** been built in the current execution environment, because that package is not installed there.

```sh
cmake -S implementations/cpp -B implementations/cpp/build-ui \
  -DCMAKE_BUILD_TYPE=Debug \
  -DHARALD_WITH_SASD_UI=ON \
  -DCMAKE_PREFIX_PATH=/path/to/installed/sasd-ui-toolkit
cmake --build implementations/cpp/build-ui --parallel
./implementations/cpp/build-ui/harald_ui_preview /tmp/harald-demo.sqlite
```

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
- [`src/catalog_table_projection.cpp`](src/catalog_table_projection.cpp): toolkit-independent, owned table/edition-ID projection with negative and Unicode tests.\n- [`src/ui_preview.cpp`](src/ui_preview.cpp): optional SASD UI Toolkit table-model consumer, now with selection-driven details lookup.
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
- The optional toolkit preview is not yet a graphical catalog window and is not verified in the local environment.

## Next increment

Implement a genuine desktop host on a tested SASD UI Toolkit package. Reuse the same `CatalogService` and add a search box, `TableView`, selection-driven detail display and a new-book dialog without putting SQL calls in any widget. Expand automated tests to include UI model adapter behavior, Windows build verification, Unicode and domain error categories. **Do not mark the full M3 milestone complete until export/restore, UI and platform validation are proven.**

### Catalog selection bridge (experimental, 28 October 2026)

`HARALD::CatalogPresentation` adds `CatalogTableProjection`: an owned, five-column snapshot of `CatalogService::search()` results, independent of SQLite and SASD UI. The projection validates that edition IDs are positive and unique; `editionIdAt(row)` converts a selected table row into an authoritative application ID, and `rowForEdition(id)` can restore selection after filtering/reordering. A stale row returns no ID, not an unrelated record. This does **not** create globally portable IDs; that requires a separate design/migration step.

The headless `harald_catalog_table_projection_tests` is enabled by the default CTest configuration and exercises Unicode, selection after reorder/filter, owned snapshot values, invalid/duplicate IDs, and stale rows. The optional `harald_ui_preview` is still **not verified** against an installed UI Toolkit in this development environment, and remains a console demo. A real SDL/native desktop host and interactive search remain future work.
