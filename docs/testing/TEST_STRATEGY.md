# HARALD — Test Strategy and Acceptance Evidence

> Document: HARALD-TEST-001  
> Status: Proposed quality plan, 2026-10-17. **The first real SQLite integration-test executable and Linux CI workflow definition exist as of 2026-10-26.** The original local tests passed. On 2026-10-28, GitHub Actions also verified Linux GCC/Clang Debug/Release CTest and an installed SASD UI Toolkit 0.2 headless consumer. Non-Linux and graphical tests remain unverified. The full release test suite remains planned.  
> Related: [Roadmap](../../ROADMAP.md), [Requirements](../requirements/README.md), [Architecture](../architecture/ARCHITECTURE.md), [Agent instructions](../../AGENTS.md).

## 1. Purpose

HARALD manages catalog identities, individually inventoried objects, active loans, personal membership information and potentially valuable or sensitive digital assets. The test strategy must prove **data integrity and authorizations under realistic failures**, not merely that user interface actions look correct.

Test requirements should be mapped to the stable IDs in the original functional specification (CAT-*, CIR-*, DIG-*, SEC-*, NFR-*, AT-001–AT-024). R0/R1/R2/R3 scope is tracked in the roadmap. All tools and commands remain **TBD until the stack is accepted**.

## Current execution evidence (2026-10-26)

[The initial C++/SQLite test](../../implementations/cpp/tests/catalog_tests.cpp) exercises actual database persistence rather than mocks: one Work/Edition/two distinct copies, reopen, literal-search metacharacters, blank/duplicate validation, and atomic rollback on duplicate inventory codes. CTest passed locally with GCC Debug/Release and Clang Debug. GitHub Actions additionally verified a Linux compiler/build-type matrix and the projection/selection preview. Circulation concurrency, JSON, export/restore, security, graphical UI and non-Linux builds remain **untested and/or unimplemented**.

## 2. Principles

1. Verify user-observable behavior, domain invariants and security properties.
2. Start with deterministic unit tests, then adapter/integration tests, then end-to-end flows.
3. Use realistic but **synthetic** catalog/person/media fixture data.
4. Test unhappy paths: invalid identifiers, duplicate copies, concurrent loans, denied exports, broken files, missing components and interrupted imports.
5. Treat persistent schema, public API, export and plugin protocol compatibility as independently versioned contracts.
6. Use test databases and temporary asset stores isolated from production.
7. Never add a test that passes vacuously or only checks a mock's implementation.
8. Keep reference fixtures committed and reviewable if legally permissible.
9. No performance, security or OS-support claim without results on specified versions.
10. Document failures and environmental limits explicitly.

## 3. Layers of verification

| Layer | Targets | Example outcomes |
| --- | --- | --- |
| Static validation | Formatting, lint, type/null analysis, licenses, secrets, docs | Reproducible command and CI result |
| Architecture test | Dependency direction, module ownership, no database/UI in domain | Invalid dependency is rejected |
| Unit | ISBN/EAN checksums, media fields, circulation rules, permission predicates | Exact positive and negative cases |
| Integration | Database constraints, transactions, migrations, asset store, metadata adapters | Commit/rollback integrity and error isolation |
| Contract | API DTO/schema versions, export formats, events, plugin messages | Consumer-compatible fixture comparisons |
| End-to-end | Catalog creation, physical lending, return, inventory, import/export | Real completed user workflow |
| Concurrency / fault | Double checkout, restart during write, idempotent retry | No duplicate loan or inconsistent state |
| Security | Unauthorized access, file traversal, malicious metadata/upload, privilege boundaries | Fail closed and no data leakage |
| Portability | OS/compiler/runtime install/uninstall/restore | Clean reproducible build/run on **claimed** platform |
| Performance | Catalog scale, search response, concurrent operations | Measured targets with environment documented |
| Accessibility / i18n | Keyboard, screen-reader semantics, languages, Unicode | Recorded manual + automated checks |

## 4. Golden sample data

Use original synthetic or public-domain-safe sample records; do **not** commit third-party cover images, commercial e-books or real member details.

Minimum synthetic catalog fixture set:

| Fixture | Coverage |
| --- | --- |
| NOVEL-A | Work, two editions (one translation), multiple contributors and identifiers |
| ITEM-A1/A2 | Two copies of an edition with different inventory barcodes, location and condition |
| MOVIE-DVD / MOVIE-BD | One film work with independent DVD and Blu-ray edition details |
| ALBUM-CD | Music album with performers, label and track positions |
| AUDIOBOX-6 | Audiobook physical set with six named components and optional booklet |
| EBOOK-EPUB | Legally generated synthetic digital book file linked to an edition |
| AUDIO-M4B | Synthetic audiobook-like asset and chapter metadata if parser supports it |
| COMIC-SERIES | Issue/volume relationships and non-ASCII titles |
| BORROWER-1/2 | Synthetic members with different permissions and loan eligibility |
| PUBLIC/PRIVATE | Records suitable for security/public search projection tests |

All fixture identifiers must be stable within a test run, and test data should be easy to regenerate. If file formats are used, keep very small artificial samples with explicit license notices.

## 5. Domain invariants and required negative tests

### Catalog and identities
- Work, Edition, Physical Item and Asset are separate identities.
- An ISBN or EAN cannot replace an inventory barcode as the item primary identifier.
- Two copies share an edition but preserve distinct attributes and status.
- Same film in DVD and Blu-ray remains distinct at edition level.
- Duplicate external identifiers generate reviewable conflicts, not silent destructive merges.
- Deleting a work with active referenced records is rejected or safely archived.
- Unicode and multiline descriptions round-trip without data loss.
- A newly introduced profile does not modify unrelated edition fields.

### Inventory and physical sets
- Three copies of one edition retain **independent physical condition and availability**; a return inspection of barcode B must not change A or C.
- A damaged returned copy is blocked before it can be reloaned; an unchanged healthy sibling remains lendable.
- An authorized, reasoned withdrawal of worn copy C affects only C; its identity/audit history remains, the edition and other copies survive, and available-copy counts exclude C.
- A failed return-with-condition transaction rolls back loan closure, condition and availability together. An unauthorized withdrawal has no effects.
- Condition history records timestamp, action, actor and reason without disclosing private inspection notes to public readers.
- A six-disc set can be checked out as the intended unit.
- Returns can record a missing disc without lying about complete inventory.
- Location moves preserve history and do not change unrelated loan state.
- Scanning an unknown barcode reports it without creating a phantom item.
- Stocktaking does not silently delete expected-but-missing copies.

### Circulation and concurrency
- One physical item has **at most one active loan** under simultaneous requests.
- A rollback on storage error leaves availability unchanged.
- Due dates respect calendar/timezone configuration and media/member policy.
- An already-returned loan is not silently returned twice with conflicting history.
- Renewals honor holds, limits and non-renewable item states.
- Duplicate/retried commands use explicit idempotency or conflict semantics.
- Unauthorized staff/member can neither override a loan nor view unrelated borrower history.

### Proposed self-service circulation (SSC-001–SSC-012; not implemented)
- Authenticated kiosk/mobile borrower can check out only to their own eligible account and only when the deployment's handover policy is satisfied; knowing a barcode remotely is not sufficient.
- Staff and self-service clients racing for the same inventory item produce at most one active loan, including on retry after timeout.
- Clicking "returned" online without trusted physical receipt does **not** complete a loan, make the item lendable, or falsify a return date.
- Confirmed intake with outstanding condition inspection remains non-lendable; completion reconciles loan, condition and holds without disturbing sibling copies.
- Disconnected kiosks may only queue non-authoritative requests; eventual server validation must still detect conflicts.
- Kiosk timeout must clear prior member data; no unauthorized lookup, member impersonation, duplicated return, or untrusted client-clock backdating succeeds.
- See [SSC-AT-01–SSC-AT-10](../requirements/SELF_SERVICE_CIRCULATION.md) for explicit future tests. These are not counted as passing or R1 blockers until approved.

### Digital files and rights
- No upload becomes publicly accessible by default.
- Invalid type, disallowed size, path traversal and corrupt files fail safely.
- A partially written upload cannot reach the "ready" state.
- Stored checksums are verified during restore and relevant workflows.
- Digital asset retrieval checks authorization and rights **on each request**.
- Thumbnails/derived files and temporary data have the same privacy boundary.
- File-system and database failures do not leave a silently inconsistent success state.

### Import/export
- CSV/JSON reject invalid foreign keys or report them explicitly.
- Dry run has no persistent side effect.
- Repeating a correctly configured import follows documented duplicate behavior.
- Unknown extension fields are preserved when the schema contract says so; otherwise report loss.
- Import never overwrites verified local values without an explicit policy/confirmation.
- Round-trip export → clean install → import preserves relationships, identities and Unicode.
- Unauthorized user export omits unauthorized borrower/asset data.

### Moving from a foreign library management system (proposed MIG-001–012)
- Import multiple physically identical editions/copies with independent item IDs, barcodes, conditions and locations; never collapse them by title or ISBN.
- Keep source IDs origin-qualified and source-to-target mapping stable across reruns; the second identical import creates no additional copies.
- Distinguish wrong edition matching, duplicate barcodes from different libraries, unknown fields and missing parent/item/borrower references; report all conflicts without destructive auto-merges.
- An initial dry run has **zero persistent effects** and provides a loss/conflict report. A failed transactional batch leaves no partial work/edition/copy tree and a resumed job uses actual committed checkpoints.
- Non-ASCII characters, newline/quote escapes, encoding errors, file limits and malformed paths are either preserved through documented decoding or rejected safely.
- Import of members and active loans is a separate **authorized** scenario. Missing item/borrower mappings, duplicated active loans and status conflicts must fail closed.
- Returnable, blocked, lost and withdrawn copies retain correct availability; import must not accidentally make damaged physical items lendable.
- Verify final source/target counts, relationships and a protected cutover/rollback procedure; do not claim support for a named source system until tested against its real export/version.
- See [MIG-AT-01–MIG-AT-12](../requirements/MIGRATION_FROM_OTHER_SYSTEMS.md); these are proposals, **not executed tests**.

### Search and external providers
- Search never leaks restricted fields, titles or asset URLs to anonymous users.
- Disabling all network providers does not block manual local catalog entry.
- Provider timeouts and malformed metadata do not corrupt local records.
- Search indexes converge after documented mutation/restore processes.

### Requirements from the 2026-10-29 HARALD Lastenheft (proposal)

| User need | Verification baseline | Current evidence |
| --- | --- | --- |
| [LH-EX-01–05](../requirements/Lastenheft_HARALD_2026.md) | Individual copy IDs, state/condition separation, return check, withdrawal, audit and transaction rollback on a three-copy edition | Basic multiple-copy SQLite persistence exists; **condition/return/withdrawal remains unimplemented** |
| [LH-SS-01–05](../requirements/Lastenheft_HARALD_2026.md) | [SSC-AT-01–10](../requirements/SELF_SERVICE_CIRCULATION.md): ownership/hand-over checks, pending return, double checkout, kiosk privacy | **Not implemented; R2 candidate** |
| [LH-MI-01–07](../requirements/Lastenheft_HARALD_2026.md) | [MIG-AT-01–12](../requirements/MIGRATION_FROM_OTHER_SYSTEMS.md): full item-identity mapping, dry-run, rerun, conflict/loss report, allowed borrowers, safe cutover | **Not implemented** (neither importer nor migration suite) |
| [LH-Q-01–06](../requirements/Lastenheft_HARALD_2026.md) | Authorization, security, data integrity, usability and roundtrip evidence per milestone | **No blanket compliance claim** |

A proposed requirement is not a passed test. Release-gate checks remain those of the **previous approved/currently proposed release plan** until an explicit scope decision changes them. Future tests should record the Lastenheft ID, linked Pflichtenheft/addendum ID, fixture, command, environment and actual result.

## 6. Acceptance-test mapping

The original requirements document names AT-001–AT-024. Its test descriptions are the **source of truth**, not the approximate grouping below.

| Phase | Tests | Meaning |
| --- | --- | --- |
| R0 | Proof-of-concept checks (not substitutes for AT scenarios) | Build/migration, Work–Edition–two Items, simple round trip |
| R1 | **AT-001 through AT-021** | Core catalog, media, lending, rights, search, inventory, backup and restoration |
| R2 | **AT-022 through AT-024** | Reader/player and more advanced digital workflows |
| R3 | New acceptance IDs in separately approved requirements | Institutional protocols and optional services |

For every implemented acceptance test, record: requirement ID, code commit, build/OS, fixture IDs, execution command, actual result, status, issue reference and relevant logs.

## 7. Database and migration matrix

When persistence is implemented, tests should cover:
- Empty database initialization and schema version recording.
- Upgrade from each officially supported schema version to the current version.
- No schema downgrade without a tested documented method.
- Uniqueness and referential integrity under racing transactions.
- Corrupt/incomplete input detection and safe abort.
- Import into an empty DB and an existing catalog with conflicts.
- Transaction rollback after injected failure between item/loan changes.
- Backup while writes are occurring, using an approved snapshot mechanism.
- Restore onto a new installation with matching data and checksums.
- Recovery from missing/partial assets and indexes without false success.
- Where SQLite is chosen: appropriate WAL/backup API usage and local-filesystem constraints, measured lock behavior and clear operator guidance.
- If PostgreSQL is later supported: the same semantic contract tests against that adapter.

## 8. Security test categories

- Authentication, session/token expiry and secret storage.
- Role/resource access matrix with all sensitive operations and read paths.
- OWASP-style web/API issues only where a web or API surface actually exists.
- Broken object-level authorization, mass assignment, injection, CSRF, SSRF, XSS, upload limits, directory traversal and arbitrary download.
- Untrusted provider data and potentially malicious plugin manifests.
- Safe error details and log redaction.
- Backup/export authorization and private data retention.
- Public OPAC projection when actually implemented.

Use a threat-model review to determine concrete exploit cases, rather than automatically adding every security scanner imaginable.

## 9. Performance and scalability evidence

Numbers from the original requirements (e.g., 100,000 works; 200,000 editions; 300,000 physical items; 100,000 digital-asset metadata records; 50 logged-in users) are **planning targets**, not verified operating capacities. A small SQLite installation assumes substantially lower simultaneous write concurrency and must be tested.

For each benchmark report:
- Hardware/CPU/RAM/storage and exact OS.
- Build/runtime/database engine versions.
- Fixture generator and record counts.
- Index/search configuration, warm/cold cache behavior.
- Concurrent readers/writers and network conditions.
- Median/p95/p99 query/transaction latency and error/timeout counts.
- Repeatability, bottlenecks and whether a goal was met.

Do not put benchmark numbers in README until reproduced.

## 10. CI and developer commands

**Not established yet.** After accepting the stack ADR, a PR should introduce a single documented command (or clear equivalent) to run:
- Formatting/lint and static analysis.
- Unit/integration/contract tests.
- Security and dependency checks.
- Architecture-boundary tests.
- Build artifacts for supported platforms.
- Markdown links/lint and documentation quality checks.

CI must not report success based on placeholders or silently skip failed tests. Long-running end-to-end/performance checks may be separately gated but must be visible in release criteria.

## 11. Failure and recovery experiments

Prior to R1 release, deliberately exercise:
1. Kill the process during a loan update and restart.
2. Interrupt file upload after bytes are written but before DB commit.
3. Stop metadata provider responses mid-request.
4. Corrupt a copied backup and verify detection.
5. Restore assets and catalog on a fresh machine.
6. Retry previously processed commands.
7. Apply an incompatible schema or export package and observe a safe rejection.
8. Revocation of access during an active asset request.
9. Concurrently modify an item and attempt checkout.
10. Return an incomplete multi-disc item.

Document any assumptions (e.g., file atomicity, database locking or token revocation delay) as explicit behavior or open ADRs.

## 12. Release evidence and sign-off

An R1 candidate is acceptable only after:
- All approved R1 MUST requirements map to passing tests.
- AT-001–AT-021 are run and their outcomes recorded.
- Supported-platform installation, authorization, backup/restore, migration, and concurrency checks pass.
- No unaddressed high-impact data-loss/privacy/security blocker remains.
- Release documentation, LICENSE/dependencies, change log and reproducible build artifacts match.

This strategy will be revised when code, real test frameworks, and CI exist. **It is deliberately not a substitute for test execution.**
