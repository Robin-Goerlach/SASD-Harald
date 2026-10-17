# ADR-0002 — Modular Monolith and Enforced Module Boundaries

- **Status:** Proposed — acceptance pending
- **Date:** 2026-10-17
- **Approver:** Repository maintainer
- **Milestone:** M1–M2
- **References:** [Architecture](../ARCHITECTURE.md), [Roadmap](../../../ROADMAP.md)

## Context

HARALD has many potential future extensions but begins with a small number of contributors and a small deployment. A monolith without boundaries becomes difficult to extend; distributed microservices would introduce networking, deployments, data consistency and operational costs long before they are justified.

## Options

1. **Modular monolith with domain/application/adapter boundaries (preferred proposal):** Single controllable deployment, explicit module ownership, internal interfaces, shared transaction coordination. Easier testing and evolution; requires boundary discipline.
2. **Single unstructured application:** Fast to scaffold but prone to catalog/UI/database coupling, schema leakage, and brittle additions.
3. **Microservices from day one:** Separation by process at the cost of distributed transactions, observability, deployment and networked failure modes.
4. **Independent media applications with data synchronization:** Each medium can be specialized; costly duplication and inconsistent identity/search/loans.

## Proposed decision

Begin with a **modular monolith**, partitioned conceptually into catalog, media profiles, inventory, circulation, identity/authorization, digital assets, search, data exchange, integrations and operations. These names describe responsibilities, not mandatory code directories or processes.

Rules:
- Domain depends on no UI, database, ORM, HTTP or platform-specific framework.
- Application use cases coordinate domain rules, authorization and transactions.
- Each module owns its write model; other modules access an explicit contract.
- Adapters implement ports; UIs/CLI/HTTP are transport clients.
- No direct SQL writes into another module's tables.
- Out-of-process plugins and microservices are **future decisions**, not implied by modularity.

## Verification before acceptance

- [ ] Architecture tests reject forbidden dependencies.
- [ ] A domain test executes without a real database or UI.
- [ ] Work/Edition/Item vertical slice uses at least one replaceable persistence port.
- [ ] Domain-level rules cannot be bypassed through a second client.
- [ ] Module contracts have documented ownership and responsible tests.

## Trade-offs and reversibility

A modular monolith demands code review and boundary tests. A future module may move to another process if necessary, but that requires contracts, failure semantics, transactional redesign and an explicit ADR. This ADR does not demand deployment isolation or a plugin ABI.

## Decision log

- **2026-10-17:** Proposed. Matches the current German architecture draft but not separately ratified.
