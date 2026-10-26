# AGENTS.md — Instructions for AI Coding Agents and Contributors

> Applies throughout this repository unless a narrower AGENTS.md exists.  
> Project status: planning/pre-alpha (2026-10-17).  
> **Never mistake planned functionality, conceptual diagrams, or example code for a working application.**

HARALD is an MIT-licensed project for an open, offline-capable and modular library and multimedia catalog. The primary priorities are **data integrity, security, testability, understandable code, long-term maintainability, and portability**. This file is also suitable as an engineering checklist for humans.

## 1. Read first and verify reality

Before modifying the project, read:

1. [README.md](README.md) — actual implementation status and goals.
2. [ROADMAP.md](ROADMAP.md) — stage, milestone, acceptance checks and dependency order.
3. [Architecture document](docs/architecture/ARCHITECTURE.md) — domain model, ports, module boundaries, extension and security architecture.
4. [Requirements](docs/requirements/README.md) — original functional specification with CAT-*, CIR-*, IAM-*, DIG-*, SEC-*, NFR-* and AT-* identifiers.
5. [ADR register](docs/architecture/adr/README.md) — accepted decisions, proposals and unresolved questions.
6. [Test strategy](docs/testing/TEST_STRATEGY.md), [security policy](SECURITY.md), [contribution guide](CONTRIBUTING.md) as applicable.

Inspect the **current branch, files, latest commit, available toolchain and CI** before claiming that a command exists. Verify actual behavior and tests rather than trusting prior chat summaries.

**Precedence:** repository LICENSE is authoritative for license; approved requirements and accepted ADRs govern behavior/decisions; implemented tests and source establish what works. Architecture and roadmap documents describe proposed direction until ratified. On conflict, report exactly what contradicts what—do not silently choose.

## 2. Current stage: no selected implementation stack

As of 2026-10-26 there is **no released application or accepted final stack**, but an **experimental C++20/SQLite core, CLI, CMake build, and real integration tests** exist. See [the C++ README](implementations/cpp/README.md) for verified Linux commands. The graphical UI, Toolkit package integration, production backups and non-Linux builds remain unverified.

- Do **not** introduce a production C#, C++, Java, Python, JavaScript, Qt, .NET, Electron or web stack without an accepted stack ADR or an explicitly requested scoped proof of concept.
- No speculative dependency locks, Docker compose files, API specifications presented as stable, package badges or empty "all tests pass" workflows.
- Windows/Linux are intended early targets; FreeBSD/OpenBSD are portability evaluation targets, **not proven support**. Runtime-free Windows distribution is a topic for measured ADR evaluation, not a guarantee.
- A prototype must be labeled experimental. Do not permanently constrain architecture by choosing whichever framework happens to be easiest to scaffold.
- Start with a small, executable work/edition/item vertical slice. Do not start with generic plugin infrastructure, an OPAC or a multimedia streaming engine.

**Repository state:** `implementations/cpp/` now contains **actual C++ code, CMake, CLI, SQLite adapter and tests**, plus a **not-yet-compiled optional SASD UI Toolkit preview**. C# and Java remain placeholders. `shared/contracts/`, `shared/fixtures/`, and `shared/conformance/` have only guidance, not published protocols or passing tests. Read [MULTI_LANGUAGE.md](docs/architecture/MULTI_LANGUAGE.md) before adding language-specific code. Language folders do **not** approve multiple production backends or shared database writes.

After the stack is accepted, update AGENTS.md with **real commands**, version requirements and source directories.

## 3. Never confuse catalog identities

| Domain concept | Required interpretation |
| --- | --- |
| Work | Creative/intellectual content (novel, film, album, recording) |
| Edition / Release | A particular publication, language, format or issue |
| Physical Item / Copy | A uniquely inventoried owned copy or lendable set |
| Component | Disc, booklet, volume or accessory belonging to a physical item |
| Digital Asset | Actual file with integrity, storage and access metadata |
| Rights / Entitlement | Whether a subject may view, download or otherwise access content |
| Identifier | Typed and scoped external or local code (ISBN, EAN, UPC, inventory barcode, etc.) |
| Loan | Transactional assignment of an eligible physical item to a borrower |
| Location | Physical hierarchy; separate from thematic collections |
| Collection | Logical list/group; not a physical storage location |

**Invariant examples:**

1. At most one active loan for a physical copy, enforced transactionally and under concurrency—not only by the UI.
2. External identifiers such as ISBN are **not** canonical internal primary keys and may be absent/duplicated.
3. Multiple copies of an edition have independent barcodes, conditions, locations and status.
4. An edition may have physical items and/or assets; a digital file is not a physical lendable item.
5. A six-disc audiobook box must be checked for all recorded components when returned.
6. Uploading a digital asset does **not** grant legal rights to redistribute it.
7. Queries, commands, exports, search indexes, background jobs and clients are equally authorization-sensitive.
8. Imports never silently destroy verified local data or discard unknown fields without a report.
9. Backups/restores preserve catalog relationships, rights, asset checksums and consistent loan state.
10. Manual cataloging functions when external providers are disabled or unreachable.

Treat invariants as executable test assertions.

## 4. Architecture and ownership rules

HARALD prefers a **modular monolith with hexagonal boundaries** unless a specific accepted ADR changes that direction.

~~~text
Browser / Desktop / CLI / API clients
                |
      Application / Use cases
                |
              Domain
                ^
        Ports / Contracts
                ^
DB, files, metadata, external services (adapters)
~~~

- Domain types must **not** import UI, HTTP, an ORM, an external provider SDK or platform-specific filesystem/networking APIs.
- Application code owns use-case orchestration and applies authorization, transactions and audit context.
- Infrastructure implements replaceable ports; it must not own business rules.
- Modules own their write state and invariants. No other module may update their private tables.
- UI/transport may not bypass application commands to write SQL directly.
- Events do not replace atomic transactions for loans or permissions.
- Exports and public API DTOs may not expose ORM entities or private model fields.
- API/schema/plugin contracts require explicit versioning once made public.
- New clients should use the same use cases; do not hardwire business behavior into a particular UI toolkit.
- Do not introduce dependencies on other SASD projects unless explicitly approved; any optional UI integration must remain an adapter.
- Do not introduce microservices, unbounded reflection or a universal generic framework without measured need.

**Conceptual modules:** Catalog, Media Profiles, Inventory, Circulation, Identity/Authorization, Digital Assets, Search/Discovery, Data Exchange, Integrations, Operations. They are boundaries first, not claims that code packages already exist.

### Adding a new medium or feature

1. State the concrete use case and media type.
2. Classify changes to Work, Edition, Physical Item, Component, Digital Asset, Rights, Identifier and relationships.
3. Prefer new validated media profile fields or a replaceable adapter rather than modifications to unrelated modules.
4. Define input validation, search mapping, exports, permissions, and upgrade compatibility.
5. Add representative golden samples and negative, round-trip and migration tests.
6. Document impacts on privacy, licensing, storage and backup.
7. Discuss a public-contract or cross-cutting change in an ADR.

An extension point is valuable only if it has a concrete consumer. Avoid elaborate plugin SDKs before the catalog works.

### Storage and backend mediation requirement

A new user request explicitly requires **storage-location selection through UI or configuration file**, supporting local JSON, local SQLite, remote MySQL/MariaDB, PostgreSQL, Oracle and HARALD-compatible remote REST as **possible adapters**.

Read [STORAGE_PROVIDERS.md](docs/architecture/STORAGE_PROVIDERS.md) and [ADR-0004](docs/architecture/adr/0004-configurable-persistence-and-remote-api.md). Do not pretend these connectors are already implemented.

- UI calls a unified application facade, not SQL tables or direct local JSON files.
- For JSON/SQLite/SQL, the local or trusted HARALD application layer enforces business invariants; persistence remains a port.
- For remote REST, the **remote HARALD server** owns auth, authorization and transactions. Do not present REST as an untrusted generic SQL repository.
- Config profile edit/activate/migrate must be distinct and protected against unauthorized changes.
- Never deliver DB credentials to a browser; use secret references and TLS validation.
- An implemented provider must pass persistence, loan-concurrency, negative security, migration and backup/restore tests before advertising it.

## 5. Workflow for substantial tasks

**Inspect → plan → implement → verify → document → report.**

1. Inspect repository files and recent commits; identify what already exists.
2. Link the change to a roadmap milestone and requirement IDs where applicable.
3. Define the **smallest useful increment** with explicit scope and non-goals.
4. Map ownership (domain/application/adapter/UI), data changes, permission checks, and interface changes.
5. Ask for / record a decision if blocked by an open major ADR. Do not guess the long-term stack.
6. Implement clear, comprehensible code in focused changes, with meaningful comments for non-obvious invariants and concurrency.
7. Cover success, validation failure, unauthorized access, integrity, and crash/retry paths.
8. Run actual formatting, build, test and migration checks available for the current stack.
9. Update relevant documents: README, ROADMAP, CHANGELOG, architecture, ADRs, tests, operations.
10. Report which checks **ran** versus which were **not run**, and why.

**Branch handling:** Respect explicit user directions and repository protection. Direct main commits are acceptable when specifically requested and authorized. Do not force-push, rewrite public history, delete branches or modify unrelated repositories without direction. Community contributions should normally be focused PRs.

## 6. Implementation style (once code exists)

- Prefer readable, moderately sized functions and explicit variable names over clever or premature performance optimization.
- Use clear terminology across modules; preserve distinctions such as Edition vs Copy and Member vs User Account.
- **Comment why**, especially invariant checks, security decisions, migrations, transaction boundaries and non-obvious algorithms.
- Do not fill code with trivial commentary or obscure generated abstractions.
- Favor deterministic tests with injected clock, ID generation, external HTTP and filesystem fakes where suitable.
- Define domain-specific errors separately from storage/network errors; surface actionable failures.
- Do not swallow errors or convert incomplete updates into apparent success.
- Validate untrusted strings, paths, files and metadata. Handle Unicode, long titles, multiple creators, language tags, edge-case identifiers.
- Secrets belong in protected configuration; never commit keys/tokens, private catalogs, borrower data, or copyrighted media fixtures.
- Third-party libraries must be licensed compatibly and regularly assessed for vulnerabilities.
- Use versioned schema migrations; no undocumented destructive database scripts.
- Avoid unrelated mass formatting, dependency upgrades and sweeping refactors.
- Do not copy external proprietary code or protected cover art from referenced library projects.

## 7. Evidence and testing standards

See [TEST_STRATEGY.md](docs/testing/TEST_STRATEGY.md).

| Test family | Why it is required |
| --- | --- |
| Unit | Identifiers, profiles, rules, invariants |
| Integration | Persistence, migrations, assets, adapters |
| Concurrency | Simultaneous checkout and idempotent retries |
| Contract | API/DTO/export schemas and compatibility |
| Security | Authorization, private files, path traversal, role escalation |
| E2E | Catalog → physical copy → checkout → return → backup/restore |
| Portability | Real clean builds on claimed supported OS targets |
| Performance | Measurements on representative data, never unproven marketing numbers |

Critical negative scenarios include: duplicate barcode; invalid ISBN; unauthorized member lookup; unauthorized asset download; corrupted asset upload; missing disc in a set; failed metadata provider; conflicting edits; mid-import interruption; backup with missing files; upgrade failure and clean restore.

If a command is unavailable, state **not run**. If a test is failing, do not falsely report the milestone complete. If a platform has not been tested, do not call it supported.

## 8. External APIs and extensions

- Define source-agnostic metadata provider ports; network access is opt-in.
- Preserve provider provenance, terms, rate limits and attribution.
- External metadata should be previewed; avoid overriding local changes automatically.
- Do not grant arbitrary third-party plugins raw DB access, full filesystem access, secrets or borrower histories.
- Prefer documented process boundaries/capabilities to loading untrusted native modules.
- Extension failure must not corrupt the catalog or block offline core operations.
- A published extension contract needs compatibility tests, lifecycle rules, versioning and disable/removal behavior.
- Never allow an external adapter to bypass use-case authorization by writing directly to storage.
- Treat plugin manifests, URLs, binaries and provider responses as untrusted data.

## 9. Privacy, security, and legal boundaries

- **Default deny.** Grant least privilege per action and resource.
- Keep member identities, circulation records, login information and audit details out of public views and unsecured logs.
- Digital asset storage must not sit under a public static-file root.
- Do not build DRM circumvention, protected-disc ripping or unauthorized redistribution of books, music, films or audiobooks.
- No automatic cloud upload, undisclosed telemetry, or external provider calls without configuration/consent.
- Plan configurable data retention and safe export/deletion flows; avoid unsupported assertions of automatic legal compliance.
- Review artwork, metadata databases, and service API license obligations; MIT does not license third-party content.
- Security incidents require a **private** disclosure path. Public issues must not contain exploitable proof-of-concept details or secrets.

## 10. Definition of Done

A code change is done when all applicable criteria are met:

- [ ] Requested acceptance behavior exists in tested code.
- [ ] No domain/UI/ORM cross-layer imports or unauthorized DB writes.
- [ ] Security, storage and data-migration effects assessed.
- [ ] Positive and important negative paths tested; tests genuinely executed.
- [ ] Relevant docs and roadmap state reflect current reality.
- [ ] Significant new architectural choice recorded or linked to an ADR.
- [ ] Supported-platform statements backed by builds.
- [ ] No credentials, PII or unlicensed external assets committed.
- [ ] Code comments explain complex behavior, not syntax.
- [ ] Diff is focused and commit message accurately describes it.

Suggested completion report:

~~~text
Milestone and requirements:
Changed files:
Behavior and design decisions:
Tests run (exact commands / results):
Tests not run and why:
Migration / compatibility:
Security and license review:
Documentation updated:
Known limitations / open questions:
Commit / PR:
~~~

## 11. Documentation and versioning responsibilities

- **README.md:** truthful product status and real installation instructions once verified.
- **ROADMAP.md:** planned work, acceptance gates and genuine evidence-based checkboxes.
- **CHANGELOG.md:** real changes, released versions only when tags/artifacts exist.
- **docs/architecture/ARCHITECTURE.md:** durable boundaries and design rationale.
- **docs/architecture/adr/:** explicit accepted, proposed or superseded decisions.
- **docs/requirements/:** traceable source requirements and changes.
- **docs/testing/:** evidence and test strategy.
- **docs/operations/:** tested deployment, recovery and upgrade procedures.
- **SECURITY.md / CONTRIBUTING.md:** disclosure and collaboration policies.

Use honest labels: *planned*, *proposed*, *experimental*, *implemented but not verified*, *verified*, and *out of scope*. A diagram or example route is not an implemented API.

## 12. Initial task recommendation

After accepting ADR-0001 (stack and platforms), implement a single vertical slice:

1. Work → Edition → two physical copies with different inventory barcodes.
2. Domain validations and transactional persistent storage.
3. Minimal use-case API/CLI/UI access, with no business rules in controllers.
4. A schema migration and repeatable clean build.
5. Automated domain, persistence and duplicate ID/barcode tests.
6. Round-trip export and a demonstrated initial backup/restore.
7. CI, clear code comments, and updated developer instructions with **actual commands**.

This establishes the architecture without prematurely building full video playback, an institutional OPAC, or a speculative plugin ecosystem.

---

**North star:** HARALD should remain easy to extend precisely because its small, working core stays stable, secure and understandable.
