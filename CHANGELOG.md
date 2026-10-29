# Changelog

All notable changes to HARALD are intended to be recorded here.

This file follows the spirit of [Keep a Changelog](https://keepachangelog.com/en/1.1.0/) and considers [Semantic Versioning](https://semver.org/) when a public API and releases eventually exist.

> **Status:** Planning/pre-alpha. HARALD has **no published application release**, no production feature set, and no promised release date. Do not invent a version or change entry implying otherwise.

## [Unreleased]

### Documentation — consolidated HARALD morning requirements (2026-10-29)
- Created [HARALD-LH-001 Lastenheft](docs/requirements/Lastenheft_HARALD_2026.md) with traceable user-needs IDs LH-EX/LH-SS/LH-MI/LH-Q for individual item condition and withdrawal, later self-service checkout/check-in and foreign-library migration. Cross-referenced the Lastenheft in the historical German Pflichtenheft as labeled, non-approved HARALD addenda; aligned Roadmap, architecture, migration plan, testing strategy, user/admin outlines and documentation indexes. **Documentation only; no feature or release claim.**


### Proposed requirements — migration from other library systems (2026-10-29)
- Added [HARALD-REQ-ADD-003](docs/requirements/MIGRATION_FROM_OTHER_SYSTEMS.md) describing a safe CSV-first migration process and future source-specific adapters (MIG-001–012, MIG-AT-01–12). It preserves Work/Edition/per-copy identities, source provenance, status, reviewable conflicts, private circulation data, rollback and cutover evidence. Clarified M9 and the test strategy; **documentation only, no importer code or supported source-system claim**.


### Proposed requirements — self-service borrowing and return (2026-10-29)
- Added [HARALD-REQ-ADD-002](docs/requirements/SELF_SERVICE_CIRCULATION.md) for member-operated kiosk/mobile checkout, secure intake and return workflows, with SSC-001–SSC-012 and negative acceptance scenarios. Return announcement is distinct from verified physical receipt/condition inspection; a remote barcode alone does not authorize borrowing. Roadmap and tests record dependency on M6/M7 and provisional R2 priority. **Documentation only; no self-service or circulation runtime exists yet.**


### Clarified — per-copy condition, return inspection and withdrawal (2026-10-29)
- Made the existing R1 requirements (BOK-005, LOC-001/002/005/009 and CIR-005/008/009) explicit: physical condition and withdrawal attach to each inventoried copy, not its book title or edition. Added multi-copy return, damage, withdrawal, rollback and authorization acceptance scenarios to the requirements, test strategy and roadmap. **Documentation only; no condition/status/return code is claimed.**


### Added — multiple physical copies and details paging (2026-10-29)
- Toolkit-independent `BookCopyEditor` tracks arbitrary unsaved copies, valid active indexes, Add/Remove navigation and reset without SQL or UI dependencies.
- Native new-book form now saves any positive number of copies atomically using the existing service. Read-only detail pages cover every persisted copy (three per page) using a separately unit-tested toolkit-neutral `CopyDetailsPager`.
- SQLite/CTest regression coverage for 12-copy persistence, Unicode, duplicate inventory codes, rollback after a late conflicting copy and draft navigation. Small-window and real interactive GUI acceptance remain open.


### Added — initial book entry and native-host verification (2026-10-28)
- Toolkit-independent `BookEntryController` reuses `CatalogService::createBook()` for a one-copy native book-entry panel, preserving form values on failure.
- Real SQLite create/reopen/rollback integration tests through the new presentation command adapter.
- Optional native desktop `--smoke` startup mode, Linux Xvfb launch check, and Windows MSVC/Win32 build plus CTest workflow. Manual UI interaction and accessibility have not been verified.


### Added — experimental native catalog browser (2026-10-28)
- Toolkit-neutral `CatalogBrowser` presentation state and CTest scenarios for refresh, selection ID stability, Unicode, stale/deleted results, duplicate identities and exception-safe search.
- Opt-in native Win32/GTK4 desktop catalog prototype with search field/button, TableView, selection-driven read-only details and status/error feedback. This is **not a stable GUI release** and has not been manually smoke-tested.
- Linux CI GTK4 build-tree consumer compile path plus existing installed-toolkit console preview. Windows GUI runtime and installer validation remain open.


### Added — catalog presentation selection bridge (2026-10-28)
- New toolkit-neutral `HARALD::CatalogPresentation` C++ target; owned book-table projection stores edition identities separately from display rows and rejects invalid/duplicate identities.
- Standalone CTest coverage for Unicode rows, stale selection, reorder/filter identity preservation and independent display-string ownership.
- Optional console UI preview uses TableSelectionModel to request copy details through the application service by typed edition ID. Linux CI also builds the installed UI Toolkit 0.2 consumer; **no graphical host is claimed.**

### Added — experimental catalog slice (2026-10-26)
- First **C++20 Work → Edition → Physical Copy** implementation under `implementations/cpp/`.
- Framework-independent `CatalogService` and `CatalogRepository` port; SQLite schema v1 with foreign keys and unique inventory barcodes.
- Atomic insert-and-rollback, bound SQL parameters, literal book search, persisted records and a working `harald_cli`.
- Integration tests against actual SQLite, compiled locally with GCC 14.2 Debug/Release and Clang Debug.
- Optional SASD UI Toolkit TableModel/TableView **console preview source**, not a tested graphical app.
- CMake build instructions, dedicated architecture note and Linux CI workflow definition (GitHub job execution unverified).


### Documentation
- Added the user-requested configurable backend architecture with local JSON/SQLite, remote MySQL/MariaDB/PostgreSQL/Oracle and remote HARALD REST options; specified profile settings via UI/file, security constraints and migration checks. Introduced ADR-0004 as **Proposed**; no backend support was implemented.
- Added draft requirements for tracking books intended for purchase and separate Dewey-compatible classification/shelfmark information, with acceptance cases and licensing notes. No runtime functionality has been added.
- Prepared independent C#, C++, and Java directory tracks with documented empty source/test/example areas; added shared contract/fixture/conformance folders and a multilingual architecture note. **No executable implementations were introduced.**
- Created an English introductory README describing the proposed catalog and multimedia-management platform.
- Added a conceptual user-interface image to the repository and README, explicitly labeled a design mockup.
- Added an extensive German architecture proposal documenting module boundaries, data identities, extensibility and open design choices.
- Added an implementation roadmap, agent guidance, contribution guide, security policy, test strategy, operations design and ADR process.
- Imported the prior German functional specification and 24-program research catalog as historical **draft planning references**, accompanied by status and naming notes.

### Planning
- Clarified initial storage rollout: local JSON and SQLite first; MySQL/MariaDB, PostgreSQL, Oracle and remote REST are architectural targets rather than V1 release obligations. No provider has been implemented.
- Established HARALD as the project name.
- Confirmed the repository already uses the MIT license.
- Identified stack/platform selection, accepted ADRs, source implementation, test automation and runnable installation as **future tasks**.

### Not yet available
- Full cataloging workflows, lending, accounts, protected asset management, graphical UI, import/export and API are **not yet implemented**. The working experimental catalog CLI and headless table preview do not constitute a completed product.
- No installable binaries, containers, tagged releases or verified runtime commands exist.

<!-- For future real releases:
## [1.0.0] - YYYY-MM-DD
### Added
### Changed
### Deprecated
### Removed
### Fixed
### Security
Only create a release heading after a real corresponding tag and artifact exists.
-->
