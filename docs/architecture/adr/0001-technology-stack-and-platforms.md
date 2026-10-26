# ADR-0001 — Implementation Stack, Runtime and Supported Platforms

- **Status:** Proposed — **decision OPEN**
- **Date:** 2026-10-17
- **Owner/approver:** Repository maintainer
- **Milestone:** M1 (blocking before production source scaffolding)
- **Related documents:** [Architecture](../ARCHITECTURE.md), [Roadmap](../../../ROADMAP.md)
- **Supersedes:** None

## Context

HARALD must serve a local or small self-hosted multimedia library and remain modular enough for future native clients, headless services, additional media profiles, plugins, metadata sources, and possible BSD portability. The implementation language/runtime and primary UI form are undecided.

An early arbitrary framework selection would constrain packaging, third-party dependencies, Windows deployment, available contributors, future SASD UI integration, and BSD feasibility.

## Decision drivers

- Correctness and testability of transactional inventory/circulation.
- Clear domain and adapter boundaries.
- Good development experience, maintainable dependencies and tooling.
- Windows/Linux packaging and self-hosting simplicity.
- **Runtime footprint:** ability to distribute a functional Windows executable without requiring an end user to install a separate runtime (if desired), with installer/size trade-offs stated.
- **FreeBSD/OpenBSD feasibility** evaluated honestly with real toolchains, not advertised prematurely.
- Secure built-in networking if a local web server/API is selected.
- MIT-compatible dependencies and acceptable long-term maintenance.
- Open API and multiple UI clients without domain rewrites.

## Alternatives to evaluate

| Option | Potential strengths | Risks/questions to measure |
| --- | --- | --- |
| **C#/.NET plus thin UI/API adapters** | Expressive domain modeling, testing ecosystem, multiple UI options, self-contained deployment modes | SDK and runtime portability, BSD deployment status, package sizes, native dependencies, AOT constraints |
| **C++/Qt with explicit core library** | Native executable paths, Qt cross-platform toolkit, potential BSD ecosystem, low-level control | Dependency packaging, memory safety burden, development speed, UI/core isolation, toolchain differences |
| **Other stack** | May meet goals with low operational footprint | Must provide demonstrated advantages and credible support/test tooling |
| **Defer / prototype only** | Avoids irreversible choices while requirements are refined | Blocks R0 source development if prolonged |

Technology choices should not be decided through popularity or unsupported claims about build/runtime requirements.

## Proposed decision

**None yet.** Record a comparison and proof-of-concept results before marking this ADR Accepted. Architectural boundaries should be specified in language-neutral terms until then.

Do not treat the examples above as an approved dual implementation or a commitment to maintain C#, C++ and other languages simultaneously.

## Repository directory preparation (non-decision)

The repository now contains a **locally built experimental C++20 catalog slice** under `implementations/cpp/`; C# and Java remain placeholders and `shared/` remains guidance-only. See [MULTI_LANGUAGE.md](../MULTI_LANGUAGE.md).

This does **not** favor any candidate, ratify this ADR, choose an authoritative backend, require three releases, or prove runtime/OS compatibility. The competing options and evidence requirements below remain open.

## Evidence from C++ experiment (2026-10-26)

[The first C++ slice](../../../implementations/cpp/README.md) now creates one Work, one Edition and two separate Physical Items, persists them through SQLite schema v1, and exposes a CLI. GCC/Clang integration tests passed locally on Linux. An optional SASD UI Toolkit `TableModel`/`TableView` console preview is present as source but was **not compiled against an installed toolkit**. No actual native graphical catalog window exists yet.

This is **evidence in favor of feasibility**, not a finalized stack ADR. Java remains a valid alternative. Platform packaging, graphical UI and data portability still need proof.

## Proof-of-concept acceptance checklist

- [ ] Build the same small Work → Edition → two Items model in candidate stacks.
- [ ] Run unit and database persistence tests on selected target environments.
- [ ] Show exact toolchain/compiler/runtime versions and a fresh-machine build procedure.
- [ ] Package a minimal sample for Windows and Linux; list runtime dependencies and sizes.
- [ ] If BSD is a requirement, run actual FreeBSD/OpenBSD builds or document blockers.
- [ ] Demonstrate a clean domain library without UI/database/HTTP imports.
- [ ] Demonstrate SQLite transaction correctness for a conflicting write scenario.
- [ ] Evaluate optional local API or native client path.
- [ ] Compare build duration, startup, memory, debugging tools and maintenance burden.
- [ ] Inventory license and third-party dependencies.
- [ ] Record reversible interfaces and costs of migration.

## Consequences after acceptance

An Accepted decision will specify the language/runtime, minimum supported platforms, packaging target, first UI strategy, test tooling and maintenance expectations. Other platform claims remain experimental until validated. Subsequent design choices may be separate ADRs and should not be quietly smuggled into this decision.

## Decision log

- **2026-10-17:** Proposed. No selection authorized; data model and modularity can be discussed independent of implementation language.
