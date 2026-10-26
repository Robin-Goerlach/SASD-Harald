# Changelog

All notable changes to HARALD are intended to be recorded here.

This file follows the spirit of [Keep a Changelog](https://keepachangelog.com/en/1.1.0/) and considers [Semantic Versioning](https://semver.org/) when a public API and releases eventually exist.

> **Status:** Planning/pre-alpha. HARALD has **no published application release**, no production feature set, and no promised release date. Do not invent a version or change entry implying otherwise.

## [Unreleased]

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
- Catalog, inventory, lending, accounts, protected asset management, UI, import/export and API are **not yet implemented**.
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
