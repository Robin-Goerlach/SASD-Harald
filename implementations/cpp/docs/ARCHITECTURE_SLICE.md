# HARALD C++ R0 — Architecture implementation note

**Status:** First executable catalog experiment. A stable stack ADR, product model and V1 release have **not** been finalized.

## Scope deliberately limited

The working increment implements a small slice of the larger domain: creating one **Work**, one **Edition**, and **two individual Physical Items** with distinct inventory codes and locations; finding editions; displaying their physical copies; and persisting/reopening the catalog via SQLite. A command-line host is available. The optional SASD UI Toolkit consumer now has a **console preview** and an **experimental native Win32/GTK4 window** for search, selection, details and one-copy book creation; neither is a stable release.

This slice verifies layer boundaries before adding borrowing, media-specific metadata, procurement, classification or remote backends.

## Logical dependency direction

```text
CLI ──────────────┐
                  ├──> CatalogService ──> CatalogRepository (port)
Toolkit adapter ──┘                              ^
                                                │
                                           SqliteCatalog
                                                │
                                              sqlite3
```

The **domain/application boundary** declares `CatalogRepository`, and SQLite *implements* it. Thus `catalog.hpp` does not include `sqlite3.h`, and `CatalogService` can be exercised with a replacement repository. The CLI and future UI must call the application service rather than issuing SQL directly.

The initial `BookDraft` groups Work/Edition/Copy input for **one atomic use case**, not as an assertion that all later book metadata belongs in one persisted table. In a future version, creator relations, multilingual editions, ISBN validation and media profiles may require new entities.

## Key invariants and their enforcement

| Invariant | Application layer | SQL layer |
| --- | --- | --- |
| Work title/creator and edition label nonempty | Trims ASCII whitespace, validates | CHECK NOT NULL and nonblank |
| Physical copy has distinct inventory barcode | Rejects duplicates in command | UNIQUE across catalog |
| Copy has physical location | Rejects empty location | NOT NULL + CHECK |
| Edition references an existing work | Persist together | FOREIGN KEY |
| Copy references an existing edition | Persist together | FOREIGN KEY |
| All records inserted together | One application use case | BEGIN IMMEDIATE / COMMIT / ROLLBACK |
| Reopening catalog returns the same records | Integration test | Persistent SQLite file |

**Separate ISBN and inventory code:** An ISBN identifies a publication/edition; it can appear on many separately owned copies. The SQLite schema does **not** make ISBN unique, but each individual copy's barcode is unique.

## Exception and failure semantics

Invalid user input raises `std::invalid_argument` before persistence. SQLite errors raise `std::runtime_error` and cause an immediate transaction rollback. The CLI returns nonzero and writes an error message. Future work should introduce typed domain and storage error categories, localization and safe diagnostics rather than exposing SQL details to normal users.

No exception from a failed rollback is allowed to replace the original failure. SQLite `sqlite3_prepare_v2`/`sqlite3_finalize` are wrapped in a small RAII class, ensuring resources are released on every early return.

The implementation is **not yet proven safe for general concurrent access**, nor does it provide a robust backup/restore workflow. Do not use real private or irreplaceable library data in the prototype.

## Backend strategy

The existing [storage architecture](../../../docs/architecture/STORAGE_PROVIDERS.md) specifies local JSON/SQLite plus optional remote SQL and REST. This experiment implements **SQLite only**. `CatalogRepository` is the first port; it intentionally does not claim that arbitrary SQL and REST adapters share identical semantics.

A future JSON adapter must provide crash-consistent storage and a safe single-writer strategy. A remote REST client belongs behind an **application-level** facade and delegates authoritative transactions and rights checking to a remote HARALD server. A remote SQL adapter stays inside a trusted application process.

The eventual switch between named backend profiles, schema version negotiation and data migration are out of scope for this first slice.

## Model/View integration plan

The optional [`ui_preview.cpp`](../src/ui_preview.cpp) uses `StringTableModel`, `TableSelectionModel` and a virtualized `TableView` from the separately maintained [SASD UI Toolkit](https://github.com/Robin-Goerlach/SASD-UI-Toolkit). It exposes *snapshot strings*, not database handles, to the presentation widgets. It currently prints the visible rows as a contract demonstration.

The experimental real window now uses Toolkit 0.2 Win32/GTK4 hosts, a rendered event loop and an inline creation form. It still needs manual keyboard/IME, mouse, accessibility and responsive-layout acceptance; these host details must remain outside the domain/application library.

The UI Toolkit remains a **versioned, optional dependency**; HARALD core builds and tests without it.

## Next architectural hardening

1. Complete physical Windows/Linux manual interactive smoke testing of the optional native host; CI now covers Linux Xvfb startup, Windows compile and headless application tests.
2. Add editor/search flows and a detail panel, keeping all data mutations in application commands.
3. Provide stable cross-storage record identities, a v2 schema plan, migration and roll-back tests.
4. Add secure JSON persistence and compare adapter conformance against SQLite.
5. Introduce concurrency-safe circulation as a separate bounded context (not by adding a nullable `borrower` field to `copies`).
6. Add safe backup/restore **before real collections are migrated**.
7. Expand CI to actual Windows/macOS targets only after prerequisites and results are verified.

## Selection identity bridge (2026-10-28, experimental)

`HARALD::CatalogPresentation` contains `CatalogTableProjection`, an owned presentation-layer snapshot. It depends on the existing application DTO `BookSummary`, **not** SQLite or `sasd::ui`. Its five display cells are transient values, while each row's edition identity remains an `Id` in the snapshot. UI adapters should obtain an ID using `editionIdAt()` before calling `CatalogService::details()`; on refresh, keep the ID rather than the old table position and use `rowForEdition()` to reselect it. Stale rows, non-positive IDs and duplicate IDs fail closed.

The optional UI preview now programmatically selects the first cell and requests copy details through `CatalogService`. This is a testable intermediate binding, **not a user-interactive desktop window**. The UI Toolkit 0.2 package and a concrete native/SDL host are deliberately not bundled with HARALD.

## First native catalog host and search coordinator (2026-10-28)

The new `CatalogBrowser` is an application-facing **presentation coordinator**, not a repository and not a widget. It prepares a validated, value-owned `CatalogTableProjection` from `CatalogService::search()` and loads details by ID through `CatalogService::details()`. This allows mock-repository headless tests (reorder, invalid ID, deletion, exceptions) without linking any toolkit. Both optional UI consumers share this coordinator.

```text
Win32/GTK4 host -> SASD UI widgets -> HARALD CatalogBrowser
                                             |
                                       CatalogService
                                             |
                                       CatalogRepository
                                             ^
                                        SqliteCatalog
```

The optional native desktop uses SASD UI 0.2 `Window`, `TextField`, `Button`, `TableView`, `TableSelectionModel`, `RenderedPresentationSink`, and the public native Win32/GTK4 backends. It does not use a private toolkit header. Win32 is exported as an installed CMake target; GTK4 currently requires building toolkit sources in an explicitly named sibling directory. Neither enters the default build. Native input and layout still require physical desktop smoke testing; Linux CI will only compile this target and exercise headless tests.

The first detail pane is read-only and intentionally limited to three copy lines, while the coordinator retains all `BookDetails` data. Do not mark full catalog UI, pagination, data migration or authorization as implemented.


## Native book-create form and host startup verification (2026-10-28)

`BookEntryController` is a tiny presentation-facing command adapter, with no SASD UI or SQLite includes. It converts owned `BookEntryFields` into the existing `BookDraft`, then delegates mandatory fields, whitespace normalization, duplicate inventory checks and persistence to `CatalogService::createBook()`. The existing SQLite transaction remains the single authority for atomic Work/Edition/Copy creation and uniqueness of inventory codes.

`desktop_main.cpp` switches between catalog browsing and an inline book-create form by changing visibility of semantic SASD UI widgets. Save commits data before the form fields are cleared, then searches without a filter and selects the returned edition by ID; Cancel never calls the application layer. Failure retains all entered text, prevents a false success notification and preserves the existing catalog snapshot where possible. This design intentionally avoids a second validation rule set inside the UI.

The first form has exactly one physical copy. It does **not** implement edits, deletion, a variable number of copies, zero-copy/digital items, ISBN checksum validation, or permissions. The normal catalog build stays toolkit-independent.

`--smoke` starts the native desktop host, builds the initial table and renders one frame, then exits. Linux CI runs this under Xvfb; the new Windows CI job builds with MSVC and runs headless SQLite tests. Neither proves interactive mouse, keyboard, IME, accessiblity or visual appearance. A real desktop smoke checklist remains necessary.
