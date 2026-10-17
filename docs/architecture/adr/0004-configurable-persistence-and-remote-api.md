# ADR-0004 — Configurable Persistence Profiles and Remote Application API

- **Status:** Proposed — architecture requirement recorded, details/phase still OPEN
- **Date:** 2026-10-17
- **Owner/approver:** Repository maintainer
- **Requirements:** User-requested selectable local JSON/SQLite, remote MySQL/PostgreSQL/Oracle, and remote REST data access with UI/file configuration
- **Related:** [Storage Provider Architecture (German)](../STORAGE_PROVIDERS.md), [Architecture](../ARCHITECTURE.md), [Roadmap](../../../ROADMAP.md)
- **Supersedes:** None

## Context

The user explicitly requests an intermediate layer between HARALD's user interface and persistent data. This layer should choose and configure the data location through **the UI or a configuration file**. Planned choices include local JSON, local SQLite, remote MySQL, PostgreSQL and Oracle databases, and remote REST API access. HARALD must support future adapters without rewriting domain logic or assuming all backends offer identical reliability.

The existing architecture already favors Ports & Adapters and domain isolation, but previously emphasized SQLite as the R1 example and postponed PostgreSQL. A dedicated, selectable backend strategy and the distinction between **SQL storage** and **remote application services** were not detailed enough.

## Decision drivers

- A user can inspect and configure the active backend **without changing source code**.
- Business operations behave consistently across supported backends.
- Local/offline installation remains possible.
- Data integrity, transactional circulation and authorization are mandatory.
- Browser applications must never receive database credentials.
- The configuration supports both an administrative UI and a versioned file.
- Safe transitions: switching backend is not automatically migrating data.
- Versions and capabilities are negotiated/validated before writes.
- Real adapter-specific conformance tests establish support.

## Proposed decision

**A. One interface for the UI:** Expose a transport-agnostic application facade, not raw database tables or generic remote CRUD.

**B. Backend selection:** Use a validated `BackendProfileManager` and `BackendResolver` to select either:

1. **Local/server-side Use Cases + Persistence Ports** backed by JSON, SQLite, MySQL, PostgreSQL or Oracle adapters.
2. **Remote HARALD Application Client** speaking a versioned, authenticated REST protocol to a remote server, where the server owns transactions and rights.

**C. Configurable named profiles:** UI and versioned config file operate on the same validated model; secure operator overrides may lock specific settings. Store credentials via secret references rather than browser-visible connection strings.

**D. One authoritative writer per catalog:** No cross-process unsynchronized writes to JSON/SQLite, no multiple applications writing each other's database schemas and no transparent dual-master replication.

**E. Separate migration flow:** Editing/activating a profile never implicitly copies a library. Migration requires backup, export/import, schema negotiation and verification.

**F. Provider truthfulness:** A provider appears as usable in the UI only after it is actually implemented, tested and its limitations are documented. Architecture targets are not shipping features.

**This ADR is a proposal, not an Accepted decision.** The user confirmed the goal of configurable backends, not every listed implementation detail or release assignment.

## Proposed options considered

| Option | Benefit | Limitations |
| --- | --- | --- |
| UI directly calls each backend | Small initial layer | Exposes SQL/filesystem details and risks inconsistent rules; rejected as direction |
| One app facade + persistence adapters | Stable domain, reuse of use cases | Requires transaction and conformance testing per provider; proposed |
| Remote REST treated as another repository | Superficially uniform CRUD | Risks client-side business decisions and server transaction bypass; not recommended |
| Remote REST as application-service transport | Central policy, idempotent commands and backend-agnostic clients | Requires versioned API/auth and robust network handling; proposed |
| Always use a single HARALD server | Uniform safety and simple clients | Adds mandatory service even for a personal local/offline library; deferred |
| JSON only as import/export | Least production-storage work | Would not meet user's local JSON backend option; can remain fallback if provider complexity proves excessive |

## Suggested release approach (not decided)

- **R0:** Interface design, configuration contract, resolver, at least one verified local adapter (SQLite candidate).
- **R1:** UI/file profile editing and safe storage choice; local JSON adapter if tested and product priority confirmed.
- **R1/R2:** HARALD REST client/server integration, depending on the desired earliest multiuser model.
- **R2/R3:** SQL server adapter expansion (PostgreSQL/MySQL/MariaDB), each tested on real servers.
- **R3/optional:** Oracle adapter after demand, dependency/license and CI environment review.

**Owner decision required:** Which of these options must work in V1 rather than remaining architecturally prepared?

## Consequences

- Config profiles become security-sensitive, versioned operational entities.
- Persistence ports must be granular enough to test across SQL and JSON without leaking vendor dialects.
- REST calls expose authorized application commands/queries, not internal persistence interfaces.
- Asset storage remains separately configured, with private access checks and migration.
- No unsupported claim that file writes and relational DB transactions have identical guarantees.
- Direct remote SQL requires a trusted HARALD host or qualified native client; never browser credentials.
- Tests must include crash consistency, permissions, retries, migrations and negative-path failures.

## Acceptance before marking Accepted

- [ ] Explicit V1 provider scope selected.
- [ ] Reference backend and operating profile selected.
- [ ] Capability contract and stable application facade reviewed.
- [ ] Single-writer/transactional guarantees documented per provider.
- [ ] JSON crash-safe design chosen and validated if planned for R1.
- [ ] SQL version/support/license matrix established.
- [ ] REST version/auth/idempotency and server authority model approved.
- [ ] UI/file config precedence, encryption/secret provider and change validation approved.
- [ ] Backend switch versus data migration UX reviewed.
- [ ] Example conformance test suite built and at least one provider executed.
- [ ] Backup/restore and adapter-failure plan approved.

## Decision log

- **2026-10-17:** Proposed in response to explicit user request. Support goals documented; exact sequencing and technical choices await review.
