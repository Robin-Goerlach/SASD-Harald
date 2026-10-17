# HARALD — Documentation Index

Welcome to the project documentation for **HARALD**, an open-source multimedia library and collection management system.

> **Current status (2026-10-17):** Planning / pre-alpha; design documents and a conceptual UI image exist, but there is no runnable product yet. All proposals, diagrams and example workflows are **future targets** unless accompanied by verified source and tests.

## Quick navigation

| Area | Document | What you will find |
| --- | --- | --- |
| Overview | [README.md](../README.md) | Project vision, scope, current status |
| Delivery plan | [ROADMAP.md](../ROADMAP.md) | M0–M17+, R0–R3, dependencies and acceptance gates |
| Automation and engineering | [AGENTS.md](../AGENTS.md) | Invariants, module boundaries, coding and evidence rules |
| Architecture (German) | [ARCHITECTURE.md](architecture/ARCHITECTURE.md) | Core design, portability, extension model, rights, testing and open decisions |
| Multi-language architecture (German) | [MULTI_LANGUAGE.md](architecture/MULTI_LANGUAGE.md) | C#, C++, Java layout; one backend vs independent implementations; contract boundaries |
| Language tracks | [implementations](../implementations/README.md) | Empty source/test directories with local guidance; no language chosen |
| Shared cross-language material | [shared](../shared/README.md) | Future contracts, fixture samples and conformance checks |
| Decisions | [ADR index](architecture/adr/README.md) | Proposed/accepted decisions and decision template |
| Requirements | [Requirements index](requirements/README.md) | Status notes and full 2026 German Pflichtenheft |
| New requirements | [Book acquisition and systematic shelving addendum](requirements/ACQUISITIONS_AND_SHELVING.md) | Future purchases, DDC-style shelfmarks, physical locations, test scenarios |
| Research | [Research index](research/README.md) | Full 24-program feature catalog and F001–F110 |
| Testing | [TEST_STRATEGY.md](testing/TEST_STRATEGY.md) | Golden fixtures, invariant tests, concurrency, security and acceptance evidence |
| Operating HARALD | [OPERATIONS.md](operations/OPERATIONS.md) | Proposed backup/restore, upgrade, deployment and incident model |
| Development | [DEVELOPMENT.md](development/DEVELOPMENT.md) | Pre-stack status and future build workflow |
| API/integration | [API guide](api/README.md) | Versioning, permissions and conceptual use cases (no API exists yet) |
| Migration | [Migration plan](migration/README.md) | Round-trip data ownership and adapter strategy |
| End-user guide | [User guide outline](user-guide/README.md) | Planned catalog and lending workflows |
| Administrator guide | [Admin guide outline](admin-guide/README.md) | Planned secure operations |
| Contribution | [CONTRIBUTING.md](../CONTRIBUTING.md) | Issues, proposed workflow, PR and review expectations |
| Security | [SECURITY.md](../SECURITY.md) | Responsible reporting and security baseline |
| Changelog | [CHANGELOG.md](../CHANGELOG.md) | Documented unreleased changes |
| License | [LICENSE](../LICENSE) | MIT license selected in repository |

## Which document is authoritative?

- **LICENSE:** actual legal license, MIT.
- **Approved requirements / accepted ADRs:** intended product behavior and binding technical choices when formally accepted.
- **Architecture draft:** a robust design proposal with deliberately open platform/UI/plugin choices.
- **ROADMAP:** sequencing and desired completion checks, not automatic approval or implementation evidence.
- **README:** public summary of project state.
- **Executable code/tests once they exist:** evidence of delivered functionality; docs must be updated to match.

If historical requirements disagree with current project name or license, the actual repository is authoritative: **HARALD**, **MIT**. Do not edit historical source material in place just to conceal such differences; document them in a new reviewed revision.

## Three starting paths

**Want to help plan or review?** Read the requirements index, German architecture, and ADR-0001.

**Want to implement features?** First read AGENTS.md, ROADMAP.md, accepted ADRs (when any exist), and the testing strategy. Do not invent a stack.

**Want to run HARALD?** It cannot be installed yet. Watch the roadmap for the first executable R0 slice and later R1 release.

## Documentation maintenance

- Use stable relative links and Markdown with readable headings.
- Mark *implemented* only when code/tests verify it.
- Keep original source requirements and research citable and traceable.
- Update the roadmap, change log, README and appropriate ADR together when a substantial decision or release occurs.
- Do not leak personal data, secrets or copyrighted content in examples.

**HARALD — One library. Many media. Your data.**
