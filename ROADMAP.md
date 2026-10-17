# HARALD — Development Roadmap

> **Document:** HARALD-ROADMAP-001  
> **Version:** 1.0 — planning baseline  
> **Last reviewed:** 2026-10-17  
> **Status:** Proposed; not a promise of release dates or completed functionality  
> **Repository:** [Robin-Goerlach/SASD-Harald](https://github.com/Robin-Goerlach/SASD-Harald)  
> **Architecture:** [docs/architecture/ARCHITECTURE.md](docs/architecture/ARCHITECTURE.md)  
> **Requirements:** [docs/requirements/README.md](docs/requirements/README.md)  
> **Testing:** [docs/testing/TEST_STRATEGY.md](docs/testing/TEST_STRATEGY.md)

HARALD is intended to become a free, open-source, offline-capable library and multimedia collection manager for physical and digital media. This roadmap turns the earlier requirements into **small, verifiable steps**. It does not imply that source code or releases already exist.

**Present reality (October 2026):** A public repository, MIT license, README, conceptual UI screenshot, and an architecture proposal exist. Technology choices, product implementation, installation packages, and CI are not yet established. The items checked below refer to actual repository evidence rather than aspirations.

## 1. How to read this roadmap

- **R0 — Foundation:** create a maintainable, runnable vertical slice. It is not a release for everyday library work.
- **R1 — First useful product:** users can catalog, inventory, find, lend, export, back up, and recover a mixed collection.
- **R2 — Enhanced experience:** metadata providers, public discovery, reader/player, optional adapters, and convenience features.
- **R3 — Institutional features:** selected professional standards and deployments, only after real user demand.
- **M0–M17:** proposed delivery milestones that can be tracked as GitHub milestones/issues when the project organization is established.
- **P00–P17:** work-package references from the German specification; mapping below is not a new competing requirements system.
- **AT-001–AT-024:** acceptance-test references in the requirements draft. Do not claim a test passed unless an executable test and its output exist.

**Priority policy:** An R1 MUST requirement cannot be silently deferred to R2 merely to declare R1 finished. A scope change needs a documented requirements change, test update, and explicit approval.

**Progress policy:** Check a task only when there is a merged commit plus the evidence requested by its completion check. Documentation alone is not executable evidence.

## 2. Goals, boundaries, and constraints

### Required product properties

1. Support printed books, comics, periodicals, DVDs, Blu-rays, UHD Blu-rays, CDs, vinyl, audio dramas, audiobooks, e-books, and appropriately stored digital files using media-specific fields.
2. Distinguish creative **Work**, publication **Edition**, individual **Physical Item**, **Component**, **Digital Asset**, and its permissions.
3. Support reliable **inventory, locations, circulation, and search** without requiring an external cloud account.
4. Offer machine-readable **import/export** and demonstrable **backup/restore**.
5. Keep domain code independent of persistence, HTTP, UI, and third-party metadata services.
6. Make later clients, media profiles, and integrations possible through versioned contracts instead of bypassing business rules.
7. Protect personal data and digital rights, including unauthenticated or misconfigured deployments.
8. Test the operating systems and runtime prerequisites actually claimed as supported.

### Explicit non-goals for R1

- No feature parity promise with Koha, FOLIO, or Evergreen.
- No commercial DRM bypass, protected-disc ripping, or unauthorized digital distribution.
- No mandatory cloud, Kubernetes, external identity provider, or AI service.
- No arbitrary native plugin code executing with full core-process privileges.
- No distributed multi-master offline synchronization or complex multitenancy.
- No unsupported claims of FreeBSD/OpenBSD compatibility; portability remains a target to **validate**.

### Working assumptions, subject to ADRs

The architecture proposes a **modular monolith**, a small/self-hosted operating profile, isolated domain/application layers, and a possible SQLite-first implementation. These are design directions, **not declarations that a stack has been selected**. Platform/runtime costs, native packaging, and optional future SASD component integration require an explicit decision and proof of concept.

## 3. Status dashboard

| Area | Actual status | Next evidence |
| --- | --- | --- |
| Name HARALD and GitHub repository | Complete | Existing repository |
| MIT license | Complete | LICENSE |
| Introductory project README | Complete | README.md |
| Conceptual interface image | Complete | docs/images/harald-ui-concept.webp |
| Architecture proposal | Complete as **draft** | docs/architecture/ARCHITECTURE.md; review and ADRs still outstanding |
| Functional requirements | Drafted; review/approval outstanding | docs/requirements |
| Stack and supported-platform decision | Open | Accepted ADR + proof-of-concept builds |
| Source tree/build system | Not implemented | Reproducible fresh build |
| Automated CI/testing | Not implemented | Real workflows and passing logs |
| Working application | Not implemented | Demonstrable R0 vertical slice |
| Alpha/beta/stable release | None | Tagged release artifacts and acceptance evidence |

## 4. Milestone dependency overview

~~~mermaid
flowchart LR
    M0[M0 Documentation baseline] --> M1[M1 Stack and platform ADR]
    M1 --> M2[M2 Build and CI foundation]
    M2 --> M3[M3 First vertical slice]
    M3 --> M4[M4 Catalog domain]
    M4 --> M5[M5 Media profiles and inventory]
    M3 --> M6[M6 Identity and security]
    M5 --> M7[M7 Circulation]
    M6 --> M7
    M6 --> M8[M8 Digital assets]
    M4 --> M9[M9 Import and export]
    M5 --> M10[M10 Stocktaking]
    M4 --> M11[M11 Search and user experience]
    M7 --> M12[M12 R1 hardening and acceptance]
    M8 --> M12
    M9 --> M12
    M10 --> M12
    M11 --> M12
    M12 --> M13[M13 Metadata providers]
    M12 --> M14[M14 OPAC, personal lists]
    M12 --> M15[M15 Reader, player and OPDS]
    M13 --> M16[M16 Extension contracts and R2 acceptance]
    M14 --> M16
    M15 --> M16
    M16 --> M17[M17+ Institutional features]
~~~

This is a **dependency illustration**. Parallel development is possible where invariants and published module contracts permit it.

## 5. R0 — Foundation

### M0 — Documentation and governance baseline (P00)

**Purpose:** establish one understandable direction before introducing frameworks or package conventions.

**Deliverables**
- [x] GitHub repository, MIT license, README, and visual concept.
- [x] Architecture proposal with module boundaries and extension directions.
- [ ] Approved functional scope for R1 and named open decisions.
- [ ] Roadmap, developer/agent instructions, contribution and security policies (documents must be reviewed after creation).
- [ ] Documented ADR process and initial open stack ADR.
- [ ] Agreed initial coding language/style/build/test commands once selected.

**Completion check:** No planned functionality is described as shipped. Links between README, architecture, requirement sources, roadmap, and policies work; names and licensing are consistent. The maintainer explicitly accepts the R1 boundary.

### M1 — Platform and technology decision (P00; ARCH-GATE-01)

**Purpose:** resolve what must be known to build and support HARALD without sacrificing future extension options.

**Evaluate**
- C#/.NET, C++/Qt, and any credible alternative against developer productivity, maintainability, dependency burden, packaging, security, tooling, licensing, and ecosystem.
- Windows and Linux baseline; proof-of-concept work on FreeBSD/OpenBSD as **evaluation**, not a support claim.
- Desktop vs local service/web UI vs hybrid; headless operation and API access.
- SQLite-first and future PostgreSQL feasibility; explicit transaction/locking semantics.
- Self-contained packaging/runtime dependencies (especially Windows); no untested promise of zero external runtimes.

**Deliverables**
- [ ] Proposed ADR-0001 replaced by an **Accepted** decision with rationale.
- [ ] Small reproducible build on each claimed initial platform.
- [ ] Measured startup, packaging, basic database access, and local API or CLI viability.
- [ ] List of accepted and rejected alternatives and costs of changing later.
- [ ] Source format, dependency policy, minimum OS/compiler/runtime requirements.

**Completion check:** Another developer can reproduce the proof of concept from documented commands, and the accepted ADR explicitly distinguishes **supported**, **tested experimentally**, and **unverified** platforms.

### M2 — Build, repository, and quality foundation (P00)

**Deliverables**
- [ ] Compile a minimal domain module with **no** ORM/UI/network imports.
- [ ] Define application-use-case interfaces and persistence/storage ports.
- [ ] Establish deterministic formatting, lint/static analysis, and test commands.
- [ ] Create automated CI jobs for the actually supported stack.
- [ ] Set up project configuration with secret handling and safe defaults.
- [ ] Establish database migrations, test fixtures, logging conventions, and baseline security scans.
- [ ] Document local development and clean installation instructions.
- [ ] Introduce contract/architecture tests detecting forbidden layer references.
- [ ] Set up release versioning and a repeatable (not yet production-ready) package build.

**Completion check:** A clean checkout builds and tests without modifying generated files manually. CI reruns the documented commands and fails for a deliberate forbidden dependency.

### M3 — First executable vertical slice (P01/P02)

**Scope:**
- [ ] Create one work (e.g., a novel).
- [ ] Attach one publication edition with creator and external identifiers.
- [ ] Create **two physical copies** with different inventory IDs, states, and shelf locations.
- [ ] Persist and reload through the selected database and a versioned migration.
- [ ] Exercise the same application use case through a minimal UI or CLI and a documented transport boundary where appropriate.
- [ ] Reject duplicate inventory barcodes without a partially committed entity.
- [ ] Demonstrate full round-trip export for the sample model.
- [ ] Demonstrate initial backup/restore of the slice.
- [ ] Test non-ASCII titles and identifiers.

**Completion check:** An automated or reproducible demo builds a fresh database, creates the model, restarts the service/process, verifies both copies independently, exports data, restores to a clean instance, and compares relationships. **M3 is not R1.**

## 6. R1 — A usable multimedia library

R1 must stand alone as a useful small-library product; all R1 MUST requirements from the specification are release blockers unless explicitly changed.

### M4 — Complete catalog, identities, and relationships (P01)

- [ ] Work, edition/release, contributors and contributor roles.
- [ ] Internal stable IDs independent of ISBN/EAN/UPC.
- [ ] Edition-specific publication data, language, publisher/label, formats.
- [ ] Series, translations, adaptations, and related works.
- [ ] Support for multiple external identifiers with validation and conflict handling.
- [ ] Consistent create/read/update/archival operations with authorization boundaries.
- [ ] Duplicate candidates shown for review; no destructive auto-merge.
- [ ] Searchable localized text and Unicode-preserving persistence.

**Gate:** Two editions of a work are distinguishable, all relationships survive restart and export, deleting an in-use record is rejected or safely archived.

### M5 — Media profiles, inventory, and physical structure (P02–P04)

- [ ] Book and comic-specific fields.
- [ ] DVD, Blu-ray and UHD Blu-ray release metadata.
- [ ] Music CDs, vinyl, tracks, albums, credits and labels.
- [ ] Audio CDs and multi-disc audiobook sets with narrators and components.
- [ ] Configurable yet validated media descriptors; typed core fields remain authoritative.
- [ ] Locations, copy conditions, availability, ownership, acquisitions.
- [ ] Explicit copy-level barcodes and identification.
- [ ] Multi-part set completeness checks.

**Gate:** A DVD, Blu-ray, printed book, music CD, and six-disc audiobook all coexist in the same catalog; item and edition metadata do not leak into each other.

### M6 — Accounts, roles, and authorization (P05)

- [ ] Single-user bootstrap with a safe path to multiple users.
- [ ] Local account authentication (if selected) with secure credential storage.
- [ ] Role/action/resource authorization for cataloging, lending, members and administration.
- [ ] Membership/person data segregated from public catalog information.
- [ ] Audit events and configurable retention/deletion rules.
- [ ] No privilege escalation through API, search, export, or guessed identifiers.
- [ ] Authorized administrative recovery procedures.

**Gate:** Default-deny security tests pass across all exposed transports. No user can query a forbidden resource using another ID.

### M7 — Circulation and holds (P06)

- [ ] Checkout/return/renewal with due-date calculation and policies.
- [ ] Borrower records and role-aware workflows.
- [ ] Simple holds/reservations and non-lendable item states.
- [ ] Missing/damaged/lost item and incomplete-set handling.
- [ ] Idempotent or safely retryable requests where appropriate.
- [ ] Database constraints and transaction boundaries guarding state changes.
- [ ] Clearly documented history and privacy retention policies.

**Gate:** Two simultaneous checkout attempts for **the same physical copy** produce at most one active loan; rollback on failure preserves correct availability.

### M8 — Digital storage and rights (P07)

- [ ] Store metadata and approved digital content separately.
- [ ] Upload quarantine, type and size validation, checksum/integrity checks.
- [ ] Edition-to-asset references and duplicate-file detection.
- [ ] Permission-controlled downloads/access, no public filesystem exposure.
- [ ] Explicit rights/license notes; uploading does **not** grant redistribution rights.
- [ ] Backup includes assets, manifests, and applicable configuration.
- [ ] Failure recovery for an interrupted upload or asset write.

**Gate:** Unauthorized asset retrieval fails, restored assets match hashes, and interrupted uploads leave no falsely “ready” asset.

### M9 — Bulk import, export, and interoperability baseline (P09)

- [ ] CSV/UTF-8 import/export with field mapping.
- [ ] Versioned JSON catalog export/import preserving relational identities.
- [ ] Validation previews, dry run and error reporting.
- [ ] Source ID provenance and controlled duplicate matching.
- [ ] Fault handling with no silent partial-loss success reports.
- [ ] Import/export only information permitted by user permissions.
- [ ] Regression sample data covering all core media types.

**Gate:** Clean-install JSON round trip produces equivalent records, relationships, copy IDs, Unicode, and authorized asset references. Sensitive fields remain protected.

### M10 — Stocktaking, locations, and reporting (P10)

- [ ] Barcode-driven inventory sessions, discrepancies, and reconciliation.
- [ ] Moves and changes of item condition with history.
- [ ] Missing/damaged component reporting for sets.
- [ ] Summaries by medium, location, availability and circulation.
- [ ] Exportable reports with appropriate access filtering.

**Gate:** Inventory can detect a missing copy and unexpected barcode without silently deleting either.

### M11 — Search, operations UI, and accessibility (P08)

- [ ] Global title/creator/identifier search across media.
- [ ] Faceted filtering by type, format, language, location, and loan status.
- [ ] Practical create/edit/detail views and copy-level actions.
- [ ] Scanner-friendly keyboard workflows and meaningful errors.
- [ ] Paging, sorting, and repeatable search results.
- [ ] Localization-ready interface with at least one tested language.
- [ ] Baseline keyboard navigation and accessibility checks.
- [ ] Documentation matching the actual implementation.

**Gate:** Users can complete catalog → locate → lend → return through the real UI, and automated authorization tests cover corresponding API/query paths.

### M12 — R1 release hardening and acceptance (P11)

**Required production evidence**
- [ ] All R1 MUST items from the approved specification reviewed and traced to tests.
- [ ] Acceptance scenarios **AT-001–AT-021** evaluated; outcomes logged.
- [ ] Integrity, concurrency, authorization, upload, and negative-input tests green.
- [ ] Complete database and asset backup restored to a clean supported machine.
- [ ] Update/migration and documented recovery procedure tested.
- [ ] Supported OS installation/packages built and validated.
- [ ] No unresolved known exploitable critical/high release-blocking vulnerabilities.
- [ ] Dependences/licenses/attributions audited.
- [ ] Install, user, administrator, security and troubleshooting documentation complete.
- [ ] Release artifacts, checksums, version number, changelog and known limitations published.

**Gate:** A collector or small library can install and operate HARALD without cloud accounts or R2-only modules. Formal release decision recorded.

## 7. R2 — Digital experience and integrations

R2 work may be reordered according to real user feedback, but **must not weaken R1 security or data portability**.

### M13 — Metadata providers (P12)

- [ ] Replaceable provider ports and adapters.
- [ ] Book, film, and music provider evaluation under their published license/API terms.
- [ ] Explicit user approval before overwriting locally curated metadata.
- [ ] Attribution, provenance, caching, throttling and outage handling.
- [ ] Zero-provider offline fallback and protected provider credentials.

**Gate:** Disabling every provider leaves manual cataloging functional; provider outage does not corrupt local records.

### M14 — Discovery and personal experience (P13)

- [ ] Public OPAC with explicit public-data projection.
- [ ] Personal lists, saved searches, configurable visibility.
- [ ] Improved holds and member-facing circulation views.
- [ ] Optional notification channels subject to consent/permissions.

**Gate:** Guests can see only approved public metadata; copying an internal URL or changing an item ID never exposes private records.

### M15 — Digital reader, player and protocols (P14/P15)

- [ ] EPUB/PDF reader architecture and supported-format checks.
- [ ] Digital-audio playback, chapter metadata, bookmarks, reading/listening progress.
- [ ] OPDS or comparable open-client support when justified.
- [ ] Rights-aware access and no implicit redistribution or DRM circumvention.
- [ ] Accessibility and device/client compatibility evaluation.

**Gate:** Relevant **AT-022–AT-024** scenarios pass for supported non-DRM formats; private media is never accessible anonymously.

### M16 — Extensibility and R2 acceptance (P16)

- [ ] Stable extension contracts for metadata providers, importers/exporters and UI clients.
- [ ] Capability permissions, isolation, timeouts and observable failure handling.
- [ ] Example adapter developed outside the domain layer with integration tests.
- [ ] Public API documented and compatible with declared versioning policy.
- [ ] R2 security, performance, migration and regression report.
- [ ] Third-party module policy including signing/distribution and trust boundaries if in-process plugins are ever introduced.

**Gate:** A replaceable extension can be added/disabled without editing the domain model or bypassing authorization.

## 8. R3 — Institutional and specialist functionality

### M17+ — Select only after user-driven requirements (P17)

Candidate epics include:
- Bibliographic interoperability: MARC21/MARCXML, SRU, Z39.50, authority data.
- Serial publications and acquisition workflows.
- LDAP/OIDC, richer role boundaries and location policies.
- PostgreSQL-backed server operation and validated higher concurrency.
- Label and borrower-card printing; optional RFID/SIP2 hardware adapters.
- Multi-site transfers and, only if needed, securely isolated multitenancy.
- Advanced migration adapters from existing library products.
- Device-oriented integrations, optional external media servers, and specialty catalog formats.

**Entry criterion:** A concrete use case, ownership, security model, acceptance criteria, maintainability plan and supported deployment target exist. R3 is not an obligation to implement every candidate.

## 9. Work-package / requirement traceability

| Roadmap milestone | Earlier work packages | Main requirement families / gates |
| --- | --- | --- |
| M0–M2 | P00 | Architecture, NFR, SEC, docs/CI |
| M3–M4 | P01 | CAT, GATE-02/03 |
| M5 | P02–P04 | LOC, VID, MUS, AUD |
| M6 | P05 | IAM, SEC |
| M7 | P06 | CIR, concurrency gates |
| M8 | P07 | DIG, asset/rights gates |
| M9 | P09 | IMP, round-trip gates |
| M10 | P10 | INV, reporting |
| M11 | P08 | SEA, UI |
| M12 | P11 | R1 acceptance, AT-001–AT-021 |
| M13 | P12 | provider/IMP enhancements |
| M14 | P13 | OPAC/SEA, user lists |
| M15 | P14–P15 | DIG, AT-022–AT-024 |
| M16 | P16 | NFR extension, public contracts |
| M17+ | P17 | ADV and institutional requirements |

The German functional specification remains the detailed source of requirement IDs. A milestone does **not** supersede those IDs; issues and tests should refer to both.

## 10. Continuous workstreams

These are not optional "end-of-project" tasks. Each implementation milestone must consider:

| Workstream | Required evidence |
| --- | --- |
| Tests and regression | Unit/integration/e2e tests appropriate to changed behavior |
| Architecture | Boundary tests and ADR for public contract, data model, or dependency changes |
| Security/privacy | Permission checks, threat analysis for newly exposed input/data |
| Data migration | Forward migration, compatibility assessment, failure recovery |
| Portability | Builds on claimed OS targets, no unverified runtime promises |
| Documentation | README/docs updated with **actual**, not imagined, behavior |
| Accessibility/localization | Keyboard, meaningful labels, UI resource strings |
| Licensing | Dependency, artwork, metadata and API terms |
| Operations | Logs, health, backups, upgrade/rollback implications |
| Release bookkeeping | Changelog, breaking-change notes, known limitations |

## 11. Work item template

~~~markdown
### Goal
What user-facing or architectural problem is solved?

### Scope / out of scope
Which media, users, and interactions change?

### Requirements
CAT-..., CIR-..., SEC-..., AT-..., M...

### Architecture
Module owner, public ports/contracts, migrations, ADR impact.

### Security and data ownership
Permissions, personal data, digital rights, exports and backups.

### Acceptance
- [ ] Concrete successful flow
- [ ] Concrete error/negative flow
- [ ] Automated test and command
- [ ] Documentation and schema update
- [ ] Supported-platform verification

### Dependencies
Blocked by M...
~~~

## 12. Definition of Done

A milestone is **done** only if:
1. Its implementation is committed and reviewable (not just specified).
2. Documented test commands run and required tests pass on the stated platform(s).
3. Data invariants, role checks, and backup/export implications have been tested.
4. API/schema changes have contracts and migration notes.
5. Important behavior and non-obvious implementation choices are commented.
6. Public documentation matches current capabilities; unfinished features remain marked planned.
7. Open limitations and risks are recorded honestly.

## 13. Managing change without closing future options

When a new media type, integration, client, or deployment request arrives:

1. Write the concrete use case before selecting a technology.
2. Classify it as core domain capability, optional media profile, external adapter, UI client, or operational concern.
3. Confirm the Work/Edition/Item/Asset distinctions remain valid.
4. Assess whether any accepted contract or security boundary would need to change.
5. Prefer a versioned adapter or new bounded module over modifying unrelated modules.
6. Record a significant cross-cutting choice as an ADR and update tests/roadmap.
7. Defer speculative generic frameworks until at least two genuine use cases justify them.

**Open architecture is not unlimited configuration.** It means reliable identities, clear ownership, reversible decisions, and stable interfaces that make later work less risky.

## 14. Decisions that must be made before R0 implementation

| Decision | Why it matters | Record |
| --- | --- | --- |
| Language/runtime/toolchain | Packaging, contributor accessibility, BSD feasibility | ADR-0001 (proposed) |
| First executable UI | Desktop packaging versus local service/web model | Follow-up ADR |
| Storage and concurrency | SQLite deployment correctness, migration to PostgreSQL | Follow-up ADR |
| Public API approach | Stable external clients and errors | Follow-up ADR |
| Media profile extensibility | Typed fields versus custom values | Follow-up ADR |
| Plugin trust and isolation | Local process permissions and hostile inputs | Follow-up ADR |
| Windows runtime distribution | Installer size, dependencies, self-contained option | Proof-of-concept and ADR |
| R1 platform list | Honest support claims and CI matrix | Accepted ADR |
| Digital access rights | Privacy and lawful asset sharing | Security review |

Do not freeze all these decisions simultaneously. Resolve the ones blocking **M1–M3**, document assumptions for the rest, and keep the domain independent of them.

## 15. Project documents

- [README — current status and vision](README.md)
- [Architecture proposal (German)](docs/architecture/ARCHITECTURE.md)
- [Requirements baseline (German originals)](docs/requirements/README.md)
- [Research and reference program inventory](docs/research/README.md)
- [ADR register](docs/architecture/adr/README.md)
- [Agent/developer instructions](AGENTS.md)
- [Contribution guide](CONTRIBUTING.md)
- [Security policy](SECURITY.md)
- [Test strategy](docs/testing/TEST_STRATEGY.md)
- [Operations design](docs/operations/OPERATIONS.md)
- [Changelog](CHANGELOG.md)

---

**HARALD — One library. Many media. Your data.**

*Roadmap revisions must preserve traceability, document changed priorities, and avoid treating unimplemented plans as finished work.*
