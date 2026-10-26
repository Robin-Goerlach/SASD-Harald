# HARALD C++ R0 — Architecture implementation note

**Status:** First executable catalog experiment. A stable stack ADR, product model and V1 release have **not** been finalized.

## Scope deliberately limited

The working increment implements a small slice of the larger domain: creating one **Work**, one **Edition**, and **two individual Physical Items** with distinct inventory codes and locations; finding editions; displaying their physical copies; and persisting/reopening the catalog via SQLite. A command-line host is available. A SASD UI Toolkit `TableModel`/`TableView` consumer is present as an optional build target but is **not yet a graphical application**.

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

A real window requires an appropriate Toolkit host/backend, layout and event loop integration, selection and query update handling, and additional UI components. None should leak into the domain/application library.

The UI Toolkit remains a **versioned, optional dependency**; HARALD core builds and tests without it.

## Next architectural hardening

1. Verify the optional SASD UI integration against a checked-out and installed version of the toolkit, including Windows/Linux runtime presentation.
2. Add editor/search flows and a detail panel, keeping all data mutations in application commands.
3. Provide stable cross-storage record identities, a v2 schema plan, migration and roll-back tests.
4. Add secure JSON persistence and compare adapter conformance against SQLite.
5. Introduce concurrency-safe circulation as a separate bounded context (not by adding a nullable `borrower` field to `copies`).
6. Add safe backup/restore **before real collections are migrated**.
7. Expand CI to actual Windows/macOS targets only after prerequisites and results are verified.
