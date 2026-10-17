# HARALD

**Open-source library and multimedia collection management**

> **Project status: Planning / pre-alpha.** HARALD is a new project. The features described below are a **product vision and development plan**, not functionality already available in a released application. As of October 2026, this repository contains the project introduction and its MIT license; there is no downloadable application, installer, or supported build procedure yet.

HARALD aims to provide a **free, self-hostable, offline-capable, and extensible system** for cataloging, organizing, finding, inventorying, and lending physical and digital media. Rather than requiring separate applications for books, film collections, audio recordings, and e-books, HARALD is designed around a consistent model that can describe all of them without losing their differences.

**Repository:** [Robin-Goerlach/SASD-Harald](https://github.com/Robin-Goerlach/SASD-Harald)  
**License:** [MIT](LICENSE)  
**Current stage:** Requirements and architecture planning  
**Primary audience:** Private collectors, households, clubs, small libraries, school libraries, and self-hosting enthusiasts

## Contents

- [Why HARALD?](#why-harald)
- [Current status](#current-status)
- [Goals and design principles](#goals-and-design-principles)
- [Supported media: target scope](#supported-media-target-scope)
- [Planned functionality](#planned-functionality)
- [How the catalog model works](#how-the-catalog-model-works)
- [Example workflows](#example-workflows)
- [Architecture direction](#architecture-direction)
- [Security, privacy, and data ownership](#security-privacy-and-data-ownership)
- [Import, export, and interoperability](#import-export-and-interoperability)
- [Roadmap](#roadmap)
- [Installation and development](#installation-and-development)
- [Planned repository structure](#planned-repository-structure)
- [Quality and testing](#quality-and-testing)
- [Contributing](#contributing)
- [Project governance and decisions](#project-governance-and-decisions)
- [License and third-party content](#license-and-third-party-content)
- [Name and inspiration](#name-and-inspiration)

## Why HARALD?

Managing a collection becomes difficult when its contents extend beyond ordinary printed books. A single household or small library may own:

- Printed books in several editions, languages, and physical conditions.
- DVDs, Blu-rays, 4K Ultra HD Blu-rays, and multi-disc film collections.
- Music CDs, vinyl records, audio cassettes, and digital audio.
- Audiobook and audio drama CDs, including multi-disc box sets.
- E-books, PDF publications, digital audiobooks, and comics.
- Magazines, journals, reference materials, and personal documents.

These items share important properties—titles, creators, identifiers, collections, locations, and ownership—but they also need specialized metadata. A film may have directors, region codes, subtitles, and audio tracks. A record may have artists, release labels, and track lists. An audiobook may need narrators, duration, abridgment information, and a list of discs.

HARALD's central idea is **one catalog with media-specific detail**, rather than one inflexible form for everything or separate databases that cannot work together.

A second motivation is **long-term independence**: users should be able to run HARALD on their own hardware, maintain backups, export their catalog, and migrate to other software without having to depend on a particular cloud service.

## Current status

HARALD is **not yet a working library application**.

| Area | Status |
| --- | --- |
| Project name and public repository | Established |
| Open-source license | MIT license present |
| Product scope and feature planning | Drafted; subject to refinement |
| Implementation language and UI framework | Not selected |
| Database implementation and schema migrations | Not implemented |
| Catalog, inventory, lending, and search | Planned |
| Web interface, desktop interface, and public catalog | Planned / under evaluation |
| Installers, containers, downloadable binaries | Not available |
| Automated tests and CI pipeline | Not yet established |
| Stable API, plugin SDK, and data exchange schema | Not yet published |
| Public release | None |

**Please do not interpret feature descriptions, example workflows, API concepts, or the roadmap below as promises of currently shipping behavior.** Progress will be documented in commits, GitHub issues, release notes, and eventually versioned technical documentation.

## Goals and design principles

HARALD is intended to follow these principles:

1. **Free and open source.** The project is distributed under the MIT license already included in this repository.
2. **Media-neutral core.** Books, films, music, and other collections share catalog concepts while preserving their own fields.
3. **Edition-aware cataloging.** A creative work, a specific published edition, and an individual physical copy must not be confused.
4. **Offline-first core operations.** Core cataloging, inventory, and lending should remain usable without Internet access; optional external metadata services are separate.
5. **No mandatory cloud account.** Users retain control of their database, assets, and backups.
6. **Open, portable data.** Documented exports and migrations should prevent avoidable vendor lock-in.
7. **Modular architecture.** Domain rules should not depend directly on UI widgets, a specific metadata provider, or a single database engine.
8. **Practical operation.** Small installations should be simple to deploy and maintain.
9. **Security by design.** Access control, digital-asset permissions, auditability, and safe input processing are fundamental requirements.
10. **Incremental development.** Each milestone should produce tested, documented, reviewable functionality rather than accumulate unverified features.
11. **Interoperability.** Standards-based integration should be possible without making sophisticated library protocols mandatory for every user.
12. **Accessibility and internationalization.** Keyboard accessibility, clear interaction flows, and translation-ready interfaces are development goals.

### Initial target users

- **Individual collectors:** Maintain a personal catalog with shelves, conditions, editions, and wish lists.
- **Families and shared households:** Organize a shared library and optionally record who borrowed an item.
- **Clubs and community libraries:** Manage members, barcodes, circulation, and basic stocktaking.
- **Small school or specialist libraries:** Manage a collection with locations, simple policies, and accountable user roles.
- **System administrators and self-hosters:** Install, back up, upgrade, and integrate the software locally.
- **Developers:** Create clients, importers, and future extensions against documented contracts.

Large university consortia, commercial digital-rights marketplaces, and enterprise resource management are **not initial-release targets**.

## Supported media: target scope

The following table describes the **planned cataloging scope**, not implemented format support.

| Media group | Examples | Media-specific information to capture |
| --- | --- | --- |
| Printed books | Hardcover, paperback, textbooks, reference books | ISBN, authors, translators, publisher, edition, pages, language, series |
| Comics and graphic novels | Single issues, volumes, omnibus editions | Series, volume/issue, creators, format, publisher |
| Periodicals | Magazines, journals, annuals | ISSN, volume, issue, publication date, frequency |
| Film and video | DVD, Blu-ray, UHD Blu-ray, video media | Director, cast, year, runtime, languages, subtitles, region, discs, rating |
| Music | Audio CD, vinyl, cassette, digital music | Artist, composer, album, label, release, track list, duration |
| Audiobooks and audio dramas | Audio CD, MP3 CD, boxed sets, digital audio | Author, narrator, cast, abridged/unabridged, chapters, discs, duration |
| E-books | EPUB, PDF | Author, publication metadata, format, language, files, access rights |
| Digital audio | MP3, M4B and other evaluated formats | Encoding, duration, chapters, files, rights |
| Digital comics and documents | CBZ and compatible documents | Series, creators, file format, page data, rights |
| Other physical or digital items | Maps, manuals, archival material, special collections | Configurable or extensible descriptive fields |

**Important distinctions:**

- **Cataloging a disc** does not imply that HARALD can play the disc or bypass copy protection.
- **Registering a digital file** does not automatically authorize sharing or lending that file.
- **Storing metadata for a format** is different from providing a built-in reader, player, or conversion tool.
- The initial release prioritizes catalog management; richer reading and playback experiences belong to later milestones.

## Planned functionality

All functionality in this section is **proposed** unless explicitly identified as implemented in the [status table](#current-status).

### 1. Unified catalog and bibliographic records

- Create, edit, validate, archive, and find catalog entries.
- Keep shared creative-work data separate from edition-specific publication details.
- Associate contributors with roles such as author, editor, translator, director, performer, composer, narrator, or illustrator.
- Maintain multilingual titles, alternative titles, descriptions, genres, subjects, tags, notes, and series.
- Record publishers, labels, publication dates, languages, countries, dimensions, and media-specific attributes where appropriate.
- Store multiple identifiers per edition, such as ISBN-10/13, ISSN, EAN, UPC, and external catalog IDs.
- Validate supported identifiers; do not assume an ISBN or product barcode uniquely identifies an individual physical item.
- Detect possible duplicates without silently merging different editions or overriding manual corrections.
- Connect related works and editions, including adaptations, translations, reissues, film versions, sequels, and accompanying media.
- Support personal ratings, favorites, condition notes, private annotations, and optional custom fields.
- Treat deletion and deaccessioning carefully where active loans or other references exist.

### 2. Physical copies and inventory

- Record **zero, one, or multiple physical copies** of an edition.
- Assign each physical copy its own permanent internal identity and inventory barcode.
- Distinguish an edition's product barcode from a library copy's inventory barcode.
- Maintain copy-specific condition, acquisition information, ownership, storage location, and availability.
- Define hierarchical physical locations: site → room → shelf → section/slot.
- Move copies between locations with an auditable history where needed.
- Manage multi-part items such as film box sets, multi-disc audiobooks, and books with inserts.
- Track expected components and highlight incomplete returns or damaged components.
- Support inventory counting using keyboard input or barcode scanners that behave like keyboards.
- Produce discrepancy lists for missing, unexpected, damaged, or misplaced items.
- Provide basic collection and inventory summaries; more sophisticated reports can follow.

### 3. Lending, returns, and reservations

- Create borrowers or members with appropriate permissions and privacy controls.
- Lend an eligible physical copy to a member and calculate a due date from configured policies.
- Return an item, renew a loan when permitted, and record overdue items.
- Maintain availability and loan state consistently, including when two users act at the same time.
- Prevent one physical copy from having two active loans simultaneously.
- Support simple holds/reservations and configurable borrowing restrictions.
- Allow different circulation rules for different media or member categories.
- Record damaged, lost, incomplete, reference-only, or unavailable copies explicitly.
- Preserve an auditable event trail without retaining personal loan histories indefinitely.
- Plan for more sophisticated queues, notifications, and multi-site workflows in later releases.

**Digital licensing is a separate problem.** Physical-copy circulation rules must not be applied automatically to DRM-protected or licensed electronic content.

### 4. Search, browsing, and discovery

- Search across titles, creators, identifiers, genres, subjects, tags, and descriptions.
- Filter by media type, format, collection, location, language, publication year, and availability.
- Sort and paginate results with predictable behavior for large catalogs.
- Show detail pages connecting works, editions, copies, relationships, and available assets.
- Provide a clear distinction between a bibliographic match and an available physical copy.
- Support saved searches, favorites, and personal lists in a later iteration.
- Develop an optional **OPAC** (Online Public Access Catalog) for controlled public discovery.
- Ensure public searches and indexes never expose private accounts, unauthorized assets, or confidential records.

### 5. Digital assets and controlled access

- Associate digital files with the correct editions without conflating files and physical copies.
- Store format, size, checksums, storage identifiers, and access permissions.
- Validate uploads and inspect supported file types instead of trusting extensions alone.
- Detect identical files and warn about duplicate or conflicting metadata.
- Keep source files in protected storage and manage previews separately from originals.
- Support backups that include the database, file manifest, and all required digital assets.
- Record whether content may be viewed, downloaded, or otherwise accessed.
- Add an integrated EPUB/PDF reader and digital-audio player only after safe storage and authorization foundations exist.
- Consider reading progress, bookmarks, audiobook chapters, and standards-based client access as future features.

HARALD is **not intended to circumvent DRM, rip protected DVDs/Blu-rays, or distribute copyrighted material without permission**.

### 6. Metadata retrieval and enrichment

- Allow complete manual data entry without online dependencies.
- Import metadata from appropriately licensed providers in a future milestone.
- Investigate book/ISBN sources and optional film or music services such as TMDb and MusicBrainz, subject to their API terms.
- Show proposed changes before accepting external metadata.
- Preserve field provenance and explicitly chosen local corrections.
- Handle provider failures, timeouts, throttling, and missing API credentials gracefully.
- Keep integration adapters replaceable so a discontinued service does not break the catalog.
- Observe license, attribution, and privacy requirements for cover art and external content.

### 7. Import, export, and migration

- Import from common tabular and structured data sources, initially **CSV and JSON**.
- Map source fields to catalog attributes with a preview before committing changes.
- Validate identifiers, relations, field types, and required values.
- Identify duplicates and report rejected or ambiguous rows.
- Support dry runs and resumable or recoverable bulk-import processes where feasible.
- Export a **versioned, machine-readable catalog package** with relationship-preserving identifiers and a manifest.
- Offer UTF-8 CSV views for ordinary catalog and inventory reports.
- Distinguish catalog-only exports from authorized exports of personal borrowing data.
- Provide a tested round-trip path: export → clean installation → import → verify records and relationships.
- Evaluate import adapters for existing solutions such as Calibre, Koha, and Tellico as later work.

### 8. Members, accounts, and permissions

- Support a private single-user scenario and appropriately constrained multi-user installations.
- Define clear roles for system administration, collection management, cataloging, circulation, readers, and guests.
- Apply **role-based access control** (RBAC) consistently through UI, API, search, and exports.
- Limit access to personal member details and loan history.
- Record important changes in an audit log that does not expose passwords, tokens, or file contents.
- Plan localized account management first; external identity providers may be added later.
- Separate system administration rights from content-access permissions where feasible.

### 9. User interface and everyday usability

- Provide a coherent catalog view with media filters, collections, search, and item detail panels.
- Favor keyboard-friendly forms, helpful validation, and rapid item entry.
- Make scanning a barcode a short and reliable workflow.
- Show copy availability and current lending status clearly.
- Provide understandable feedback for duplicates, missing components, invalid fields, and permission errors.
- Use layouts that remain practical across different screen sizes.
- Allow localization from the beginning, with English and German as sensible initial candidates.
- Evaluate web-first administration and an optional native desktop client without forcing the core to depend on either UI framework.
- Treat any early UI mockups as **visual concepts**, not proof of implemented functionality.

### 10. Administration, reporting, and operations

- Configure library identity, collections, locations, circulation policies, and basic account roles.
- Provide basic inventory, lending, and collection statistics.
- Make backups and **testable restore procedures** part of the first production-ready release.
- Use versioned database migrations and document how upgrades affect stored data.
- Make optional jobs such as indexing, integrity checks, and metadata synchronization observable.
- Produce actionable logs while avoiding disclosure of secrets or personal information.
- Document deployment, configuration, maintenance, and failure recovery for supported platforms.
- Make application health and storage integrity visible to authorized administrators.

### 11. Future professional-library capabilities

The following are potential **later-stage integrations**, not requirements for the first usable release:

- MARC21/MARCXML, SRU, and Z39.50 catalog interoperability.
- Authority records and normdata integrations.
- More advanced serials and periodical management.
- Basic acquisitions workflows and institutional reporting.
- LDAP/OIDC authentication and enhanced multi-location policies.
- PostgreSQL-backed deployment for more demanding installations.
- Printing labels and barcodes; optional SIP2/RFID or specialist hardware integration.
- Carefully isolated third-party plugins and extended public catalog features.

## How the catalog model works

A core architectural decision under consideration is a **work → edition → item/asset** model:

| Concept | Meaning | Example |
| --- | --- | --- |
| **Work** | The underlying creative or intellectual content | The novel *Dune* |
| **Edition** | A particular publication or release of that work | A specific English paperback edition |
| **Physical item / copy** | An individual owned copy with its own barcode and state | Copy #2, shelved in the office |
| **Digital asset** | An actual file linked to an edition with access rules | A legally obtained EPUB file |
| **Component** | Part of a physical set | Disc 3 of a six-disc audiobook |
| **Collection** | A logical user-defined grouping | Science fiction favorites |
| **Location** | Where a physical item is stored | Home → Library → Shelf A3 |
| **Loan** | A temporary assignment of an eligible physical copy | Copy #2 lent to a member |
| **Identifier** | An externally or internally scoped reference | ISBN, EAN, inventory barcode |
| **Relationship** | A link among works or editions | Novel adapted into a film |

### Conceptual domain diagram

~~~mermaid
flowchart TD
    W[Work] -->|has editions| E[Edition]
    E -->|has physical copies| I[Physical item]
    E -->|has digital files| A[Digital asset]
    I -->|contains| C[Components]
    I -->|stored at| L[Location]
    I -->|can be assigned to| LO[Loan]
    LO -->|borrowed by| U[Member]
    E -->|identified by| ID[Identifier]
    W <-->|related works| RW[Work relationships]
    E -->|grouped in| CO[Collections]
~~~

**Why this matters:** Two copies of the same paperback should share bibliographic data but have **different inventory IDs, locations, conditions, and loan states**. A DVD and a Blu-ray of the same film may be related at the work level but remain different editions. An EPUB file is not itself the same thing as a lendable disc or a physical copy.

The diagram is **conceptual**, not a finalized database schema. Cardinalities, constraints, and persistence formats will be specified and tested during implementation.

## Example workflows

These describe the **intended** user experience, not actions available in the repository today.

### Catalog a book with multiple copies

1. Search for the title or enter an ISBN.
2. Check for an existing work or edition.
3. Create or select the matching edition.
4. Add two physical copies with different inventory barcodes.
5. Assign each copy its own location and condition.
6. Confirm that lending one copy leaves the other available.

### Record a film in multiple formats

1. Create or find the film work.
2. Create a DVD edition and a Blu-ray edition.
3. Store format-specific product IDs, languages, regions, and other details.
4. Add any owned physical copies.
5. Find both editions from the same work entry, without merging their inventories.

### Lend a multi-disc audiobook

1. Select the audiobook edition and the inventory item representing the complete set.
2. Review the expected discs and accessories.
3. Scan or select the borrowing member.
4. Apply the appropriate loan policy and create the loan.
5. On return, verify the components and record any missing or damaged parts.

### Import an e-book

1. Select an appropriately obtained file.
2. Validate the type, size, integrity, and duplicate status.
3. Assign the file to the appropriate edition.
4. Store the file with restrictive default permissions.
5. Include it in authorized export and backup workflows.

### Restore a library

1. Create a consistent backup of catalog data and protected files.
2. Install HARALD on another supported machine.
3. Restore the database, file manifest, and assets.
4. Verify checksums and references.
5. Confirm that users, catalog entries, locations, and item states are intact.

## Architecture direction

**The implementation stack has not been selected.** The following principles are architectural targets to guide that decision.

### Modular core

A **modular monolith** is the preferred starting design: one manageable application with well-defined internal boundaries, rather than premature distributed microservices.

~~~text
+-----------------------------------------------------+
| User interfaces                                     |
| Administration UI / future desktop or OPAC clients  |
+-----------------------------+-----------------------+
                              |
+-----------------------------v-----------------------+
| Versioned application API and use cases             |
| Catalog / Inventory / Circulation / Import / Access |
+-----------------------------+-----------------------+
                              |
+-----------------------------v-----------------------+
| Domain model and business rules                     |
| Works / Editions / Copies / Assets / Members / Loans|
+-----------------------------+-----------------------+
                              |
+-----------------------------v-----------------------+
| Ports and adapters                                  |
| Database / Files / Search / Metadata / Notifications|
+-----------------------------------------------------+
~~~

The core business model should **not** import UI classes or rely on a metadata provider's internal model. Future UI implementations and integrations should depend on well-defined application contracts.

### Storage direction

- **Initial planning option:** SQLite for straightforward local deployments, subject to performance and concurrency tests.
- **Later option:** PostgreSQL for installations needing more sophisticated multi-user operation.
- **Digital files:** Protected local storage with stable IDs, hashes, and controlled delivery.
- **Search:** An interchangeable indexing strategy appropriate for offline and larger deployments.
- **Migrations:** Explicit schema versions and tested upgrades, including failure recovery.

These choices remain **proposals**, not installed or supported production configurations.

### Platform direction

The initial planning targets are **Windows and Linux**. FreeBSD and OpenBSD are relevant portability goals, but support must be established through actual builds and test runs before being advertised. The final runtime, packaging strategy, and potential dependency requirements will be decided and documented in architecture decision records (ADRs).

### Interface boundaries

Potential contracts include catalog repositories, item repositories, loan services, a digital-asset store, metadata providers, search services, backup services, a clock abstraction, and audit sinks. Their final signatures and public compatibility guarantees have **not** yet been defined.

## Security, privacy, and data ownership

HARALD's intended deployment model gives users control of their own information. It also makes secure defaults essential, especially when operating on a local network or exposing a catalog through a browser.

Planned safeguards include:

- **Least privilege:** Users and integrations receive only the capabilities they need.
- **Authentication and authorization:** Every sensitive operation checks permissions, including background tasks and bulk exports.
- **No implicit digital sharing:** Uploading an e-book does not make it publicly downloadable.
- **Protected file paths:** Storage identifiers rather than untrusted user paths; defense against traversal and unsafe upload handling.
- **Password and secret hygiene:** Appropriate password hashing, protected configuration, and no credentials in logs.
- **Private circulation records:** Member information and borrowing history should not appear in public searches.
- **Safe metadata ingestion:** External providers and imported files are treated as untrusted inputs.
- **Integrity:** Checksums, consistent transactional updates, and reliable backup verification.
- **Auditability:** Changes to inventory, access, and lending can be traced without collecting unnecessary personal data.
- **Data minimization:** Avoid retaining personal information longer than needed; provide appropriate deletion and export paths.
- **No mandatory telemetry or cloud dependency** as a product design goal.

Public networking, remote access, authentication-provider integrations, and plugin execution will require explicit threat modeling before release.

## Import, export, and interoperability

**Data portability is a product requirement**, not an optional convenience.

The initial goal is a documented catalog exchange format that preserves work/edition relationships, physical-copy identities, components, collections, locations, and permitted references. An export should identify its schema and application versions.

| Integration category | Initial direction | Later direction |
| --- | --- | --- |
| Manual entry | Core requirement | Improved assistance and batch workflows |
| CSV | Import/export with documented mapping | More source-specific mappings |
| JSON | Versioned, relationship-preserving exchange | Stable migration compatibility |
| ISBN and product identifiers | Validation and local search | Optional metadata retrieval |
| Music and film metadata | Manual or imported records | Replaceable external provider adapters |
| Calibre / Tellico / Koha migration | Not initially guaranteed | Evaluated adapters and field-mapping reports |
| OPDS | Not required for initial release | Optional e-book client interoperability |
| MARC21 / SRU / Z39.50 | Out of initial scope | Professional-library integration phase |
| REST-style API | Architectural goal | Published and versioned contract |

**No public API endpoints, import schema, or plugin interfaces should be considered stable until they are actually implemented, documented, and versioned.**

## Roadmap

This is a **planning roadmap**. It indicates intended sequencing, not delivery dates.

| Stage | Objective | Main deliverables |
| --- | --- | --- |
| **R0 — Foundation** | Establish a maintainable development base | Architecture decisions, repository layout, CI, tests, migrations, initial domain model, first vertical slice |
| **R1 — Usable multimedia library** | Make a complete small-library workflow possible | Catalog, editions, copies, locations, lending, basic holds, members, search, inventory, protected assets, CSV/JSON, backup/restore |
| **R2 — Digital experience and integrations** | Improve everyday use and discovery | Provider adapters, enhanced search, OPAC, wish lists, reader/player, OPDS, notifications, extensibility |
| **R3 — Institutional capabilities** | Serve more demanding libraries | Bibliographic protocols, authority data, periodicals, acquisitions, external identity, PostgreSQL, multi-location and device features |

### Suggested implementation work packages

| Package | Proposed focus |
| --- | --- |
| P00 | Repository foundation, standards, CI, licensing, and build decisions |
| P01 | Work/edition model, contributors, identifiers, and relationships |
| P02 | Physical copies, inventory IDs, locations, and components |
| P03 | Book and film-specific metadata |
| P04 | Music and audiobook-specific metadata |
| P05 | User accounts, roles, authentication, and audit |
| P06 | Lending, returns, renewals, simple reservations, and concurrency |
| P07 | Digital-asset storage, validation, and permissions |
| P08 | Core UI, catalog search, filters, and barcode workflows |
| P09 | CSV/JSON import, export, validation, and round trips |
| P10 | Stocktaking, reports, and basic collection statistics |
| P11 | R1 deployment, recovery, security review, documentation, acceptance tests |
| P12–P16 | R2 metadata, OPAC, readers, playback, OPDS, notifications, adapters |
| P17+ | R3 institutional workflows and specialist integrations |

**Suggested first executable milestone:** Create one work, one edition, and two independently inventoried physical copies; persist them through a tested database migration; expose a minimal UI/API; verify backup and restore. This tests the most important model before implementing an entire interface.

### Release readiness

A production-ready R1 should not be declared complete until:

- Catalog, inventory, circulation, and permission requirements have automated tests.
- A physical item cannot be loaned twice under concurrent requests.
- Media-specific example records can be created and found.
- Import/export preserves relationships and international text.
- Protected assets remain inaccessible without permission.
- A full backup is restored successfully on a clean installation.
- Supported OS builds and deployment instructions have been verified.
- License notices, dependency information, and security documentation are in place.
- Known critical or high-severity exploitable defects have been addressed.
- The documentation distinguishes delivered capabilities from deferred work.

## Installation and development

**There is currently no installation command, development server, binary release, or package to run.**

The repository contains a license and this planning-oriented README. Once the technology stack is selected and source code is introduced, this section will be updated with **tested**, version-specific steps for:

1. Supported operating systems and prerequisites.
2. Obtaining or cloning the source.
3. Installing required toolchains and dependencies.
4. Building and running the application.
5. Creating and migrating the local database.
6. Running automated tests.
7. Configuring storage, accounts, and optional integrations.
8. Building distributable packages and restoring backups.

You can already clone the repository to follow development:

~~~shell
git clone https://github.com/Robin-Goerlach/SASD-Harald.git
cd SASD-Harald
~~~

Cloning the repository **does not install a usable HARALD application** at this stage.

## Planned repository structure

The following tree is a **proposal**, not a claim that these directories already exist:

~~~text
SASD-Harald/
├── README.md
├── LICENSE
├── CHANGELOG.md                 # planned
├── CONTRIBUTING.md              # planned
├── SECURITY.md                  # planned
├── docs/                        # planned
│   ├── requirements/
│   ├── architecture/
│   │   └── adr/
│   ├── api/
│   ├── user-guide/
│   ├── admin-guide/
│   ├── migration/
│   └── testing/
├── src/                         # planned
│   ├── domain/
│   ├── application/
│   ├── infrastructure/
│   ├── api/
│   ├── ui/
│   └── adapters/
├── tests/                       # planned
│   ├── unit/
│   ├── integration/
│   ├── contracts/
│   ├── end-to-end/
│   ├── security/
│   └── performance/
├── tools/                       # planned
└── .github/
    └── workflows/               # planned
~~~

The actual naming and folder layout may change once implementation language and packaging are agreed.

## Quality and testing

Development should be driven by small, independently verifiable changes. Planned quality practices include:

- **Unit tests** for identifier validation, catalog rules, and inventory state transitions.
- **Integration tests** for persistence, migrations, external adapters, and storage behavior.
- **Concurrency tests** for lending and reservations.
- **Contract tests** for API request/response behavior and schema versions.
- **End-to-end tests** for essential cataloging, circulation, and restoration workflows.
- **Security tests** for unauthorized access, unsafe files, path traversal, and data leaks.
- **Performance tests** based on representative large catalogs rather than unsupported marketing claims.
- **Cross-platform build tests** for systems officially supported by each release.
- **Accessibility and localization checks** for important UI journeys.

Each accepted feature should have clear acceptance criteria, meaningful source comments for complex rules, updated documentation, and a passing automated test suite. No CI or coverage badge is shown until a real pipeline exists.

## Contributing

HARALD is intended to grow as an open-source project. Ideas, bug reports, architecture feedback, documentation improvements, and future code contributions are welcome.

A practical way to get involved now is to:

1. Check the [GitHub issues](https://github.com/Robin-Goerlach/SASD-Harald/issues) for existing discussions.
2. Open an issue describing a problem, use case, feature suggestion, or interoperability need.
3. Explain which media types and workflows are affected.
4. Include examples and acceptance criteria when proposing a change.
5. For substantial architecture changes, discuss the approach before preparing an implementation.
6. When a development setup exists, submit focused pull requests with tests and documentation.

Please avoid adding unrelated frameworks or creating dependencies on proprietary hosted services without prior discussion. Prefer portable interfaces, explicit business rules, small diffs, readable code, and comments that explain non-obvious decisions.

Formal contribution and security-reporting guides are planned. Until a private vulnerability-reporting channel is established, **do not publish exploit details or private data in a public issue**; use an available private contact or disclosure mechanism if one is provided on the repository profile.

### Reporting useful issues

For reproducible defects in future releases, include:

- HARALD version or Git commit.
- Operating system and deployment mode.
- Steps to reproduce and expected versus actual behavior.
- Relevant logs with personal information and secrets removed.
- Whether the issue affects data integrity, circulation, permissions, or backup/restore.

For feature suggestions, explain the motivating use case and why existing planned concepts would not already address it.

## Project governance and decisions

The project currently resides at **[Robin-Goerlach/SASD-Harald](https://github.com/Robin-Goerlach/SASD-Harald)**. It is in early planning; formal governance, maintainership processes, and release policy may evolve.

Major architecture decisions should be recorded as short **Architecture Decision Records (ADRs)** describing context, alternatives, selected approach, consequences, and date.

Initial decisions to document include:

- Application language and runtime (for example, C#/.NET versus C++/Qt or another suitable stack).
- Primary user interface and optional desktop strategy.
- Database and supported concurrent-user profiles.
- Installation and packaging across Windows, Linux, and possible BSD targets.
- Public API compatibility and plugin isolation model.
- Digital-asset storage and default access permissions.
- Supported metadata providers and third-party license obligations.
- The formal definition of R1 acceptance and release guarantees.

The **MIT license is already selected** in this repository; references in earlier requirements drafts to an undecided license should be read as superseded by the repository's actual license file.

## License and third-party content

HARALD is licensed under the **MIT License**. See [LICENSE](LICENSE) for the full terms.

Copyright (c) 2026 Robin Goerlach (SASD-GmbH), as specified in the existing license notice.

The MIT license applies to the project's own material as distributed under that notice; it **does not automatically grant rights** to third-party book covers, film artwork, artist photographs, imported metadata, e-books, audio recordings, or commercial media.

Users and contributors must respect relevant copyrights, database rights, API conditions, attribution requirements, and local law. Third-party dependency licenses and external provider policies should be documented as integrations are introduced.

## Name and inspiration

**HARALD** is a friendly project name inspired by **Harold Finch**, the fictional character whose library-based workspace appears in *Person of Interest*. It is an informal nod to the idea that books, information, and computers belong together.

HARALD is an independent open-source software project. It is **not affiliated with or endorsed by the creators or rights holders of *Person of Interest***.

---

**HARALD — One library. Many media. Your data.**

*This README describes the intended direction of an early-stage project and will be updated as real functionality becomes available.*
