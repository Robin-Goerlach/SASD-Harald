# HARALD — API and Integration Contract Plan

> **Status:** Design guidance only. There is **no implemented or stable public API** as of October 2026. The examples below are concepts, not endpoints available for use.

## Purpose

HARALD should support optional alternative interfaces: web frontend, native desktop application, CLI, barcode workstation, read-only public catalog, metadata importers, digital readers and external automation. These clients must not need direct database access.

The actual transport (local in-process calls, HTTP API, process protocol) will be chosen by an accepted ADR. Public contracts should be explicitly versioned independently from internal database schemas.

## Proposed contract principles

1. **One application-use-case boundary:** every client uses authorized catalog, inventory, circulation and asset use cases.
2. **Stable internal IDs:** ISBN, EAN and other external IDs are queryable attributes, not canonical object identifiers.
3. **Typed DTOs:** do not serialize database entities or unrestricted domain objects to clients.
4. **Resource-level access:** the API authenticates and authorizes the actual actor for commands and queries, including bulk exports.
5. **Safe errors:** machine-readable failure category, non-sensitive details, correlation ID and retry guidance when relevant.
6. **Versioned schemas:** request, response, export, public events and plugin protocols have explicit compatibility rules.
7. **Predictable writes:** concurrency controls, transaction scope, optimistic preconditions and idempotency for retried requests where appropriate.
8. **Non-leaking reads:** public search and administrative data use different projections; unauthorized data is never included in a response.
9. **No provider bypass:** importer adapters use validated application interfaces, not raw writes to the database.
10. **Documented pagination/filtering:** stable ordering and bounded page sizes for large catalogs.
11. **Portability:** command/business rules should not depend on a web framework or client language.
12. **Offline-capable:** external providers remain optional; local use cases work without Internet.

## Conceptual use-case families

| Family | Responsibilities |
| --- | --- |
| Catalog | Work/Edition lookup and management; contributors, identifiers and relationships |
| Media profiles | Book/film/music/audiobook-specific verified fields |
| Inventory | Physical items, components, location and condition |
| Circulation | Checkout, renew, return, reservations, circulation rules |
| Members and access | Approved member views, roles, authentication and permissions |
| Digital assets | Protected ingest, checksum checks, authorized retrieval |
| Discovery | Permission-filtered catalog search and later OPAC projection |
| Exchange | Validated CSV/JSON import/export, manifest/version negotiation |
| Operations | Health, migrations, audit and backup with administrative permissions |
| Providers | Replaceable metadata lookup, clear provenance and rate controls |

No actual HTTP paths are specified here because the chosen technology and API design remain open.

## Open decisions

- Public HTTP API versus in-process API as the initial supported contract.
- Authentication model for local/remote automation.
- API versioning and deprecation window.
- Conflict semantics for editing a work or checking out a copy.
- Event delivery format/ordering and failure strategy.
- Search/OPAC projection and caching.
- Digital asset download links, token lifetime and revocation.
- SDK/plugin isolation and capability security.
- Documentation generator (OpenAPI or equivalent if HTTP is chosen).

Decisions that affect callers, security, or long-lived data should be recorded in an [ADR](../architecture/adr/README.md).

## Acceptance before first stable API

- [ ] Endpoint or method implementation exists with integration tests.
- [ ] Requests/responses have a published versioned machine-readable contract.
- [ ] Authorization and negative access tests are included.
- [ ] Errors, pagination, sorting, concurrency and idempotency are defined.
- [ ] A non-primary client can complete a representative end-to-end catalog workflow.
- [ ] Contract change has a migration/deprecation plan.
- [ ] Real examples correspond to a released version.

See [architecture](../architecture/ARCHITECTURE.md) for full conceptual contracts and module boundaries.
