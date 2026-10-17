# HARALD Architecture Decision Records (ADRs)

**Architecture baseline:** [ARCHITECTURE.md](../ARCHITECTURE.md) (German, HARALD-ARCH-001).  
**Roadmap:** [ROADMAP.md](../../../ROADMAP.md).  
**Current status:** Design proposal. **No implementation stack, framework or platform runtime has been finally accepted.**

## Why ADRs?

HARALD is intended to support changing requirements: new media formats, alternative UI technologies, further languages and runtimes, importer providers, future operating systems, and optional integrations. This only works if architectural choices are explicit and revisable.

An ADR records:
- **Problem/context** — why a choice became necessary.
- **Quality requirements** — portability, security, performance, maintainability, deployment and data ownership.
- **Options considered** — including a simple alternative.
- **Decision and status** — what was selected, by whom and when.
- **Consequences** — trade-offs, testing requirements, future reversibility.
- **Evidence** — experiments, measurements, relevant requirements and commits.
- **Compatibility path** — how the choice can be changed without breaking stored data and public contracts.

A proposed ADR is **not** permission to implement its preferred option.

## Status workflow

| Status | Meaning |
| --- | --- |
| **Proposed** | Written proposal awaiting review and evidence |
| **Accepted** | Decision approved by the maintainer; normative from the recorded date |
| **Rejected** | Considered, explicitly not selected |
| **Superseded** | Replaced by a later ADR with a link to the successor |
| **Deprecated** | Previously accepted but being phased out, with a migration plan |

Create ADRs as numbered Markdown files. Once published, do not reuse numbers or erase decisions; update status with a dated explanation or supersede them.

## Current register

| ID | Topic | Status | Milestone |
| --- | --- | --- | --- |
| [ADR-0001](0001-technology-stack-and-platforms.md) | Implementation language, runtime, platforms and client packaging | **Proposed / decision open** | M1 (blocking) |
| [ADR-0002](0002-modular-monolith-and-module-boundaries.md) | Modular monolith, dependency direction and domain boundaries | **Proposed / not ratified** | M1–M2 |
| [ADR-0003](0003-catalog-identities-and-extension-model.md) | Work/Edition/Item/Asset identities and extension strategy | **Proposed / not ratified** | M2–M3 |
| [ADR-0004](0004-configurable-persistence-and-remote-api.md) | User-configurable storage profiles; JSON/SQLite/remote SQL and remote HARALD REST | **Proposed / detailed requirements received, not ratified** | M1–M3 / R1+ |

Next candidates when actual implementation requires them: concrete JSON/SQL migration/storage mechanics under ADR-0004; UI client approach; public API versioning; digital asset authorization; metadata adapters; plugin permissions/isolation; supported package targets; backup/restore atomicity.

## Proposed review and decision process

1. Explain the use case with roadmap milestone and relevant requirements.
2. Identify at least two credible options, including "do nothing / defer" if reasonable.
3. Distinguish mandatory constraints from personal preferences.
4. Evaluate user-visible behavior, performance, security, portability, cost and operational complexity.
5. For risky technology choices, build a **small reproducible proof of concept** and record commands, platform, dependency versions and results.
6. Request maintainer approval. Only then mark **Accepted**, with date and consequences.
7. Update architecture, roadmap, tests, code and documentation in the same change or tracked work item.
8. Define evidence that would trigger reevaluation and a migration/compatibility strategy.

**Reserved authority:** The repository maintainer approves architecture decisions. Automatic agents may *propose* but must not mark their own preference **Accepted** without clear authorization.

## Template

~~~markdown
# ADR-XXXX — Concise decision title

- **Status:** Proposed
- **Date:** YYYY-MM-DD
- **Owner / approver:** To be decided
- **Requirements / milestone:** ...
- **Supersedes:** None

## Context
What problem requires a decision now? What must remain changeable?

## Decision drivers
Security, testability, packaging, supported platforms, operational cost, licensing, ...

## Options
### Option A
Pros, cons, tests, migration consequences.
### Option B
Pros, cons, tests, migration consequences.
### Defer / keep reversible
Pros, cons.

## Proposed decision
A proposal, not accepted until authorized.

## Consequences and boundaries
What changes in code and documentation? What is explicitly NOT implied?

## Verification
Exact proof of concept and tests before accepting.

## Reversibility and future work
Migration and compatibility strategy.

## Decision log
Date / status / approver / reason.
~~~

## Rules against fake certainty

- An architecture draft may say "preferred" without claiming something has been built.
- Not selecting a runtime yet is a legitimate, recorded decision.
- An **Accepted** ADR should specify versions/constraints only where there is real validation.
- Public API contracts and plugin SDKs become stable **only with implementation and tests**.
- Platform compatibility is proven by actual builds/runs on that platform, not cross-compilation claims alone.

See also [AGENTS.md](../../../AGENTS.md).
