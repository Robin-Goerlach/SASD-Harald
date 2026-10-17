# HARALD — Language implementations

> **Status: directory scaffold only (2026-10-17).** These directories contain no executable application, published library, build definitions, API implementation, or language-specific test suite. Their existence does **not** mean that three implementations have been approved for production or that any target platform is supported.

This area accommodates independent, optional implementations or clients written in different languages. Initial **candidate languages** are **C#**, **C++**, and **Java**, motivated by the project's early technical discussions. New languages can be added later; none is the official runtime while [ADR-0001](../docs/architecture/adr/0001-technology-stack-and-platforms.md) remains Proposed.

Read the detailed [multilanguage architecture](../docs/architecture/MULTI_LANGUAGE.md), [root AGENTS.md](../AGENTS.md), [architecture](../docs/architecture/ARCHITECTURE.md), and [roadmap](../ROADMAP.md) before implementing anything.

## Directory map

```text
implementations/
├── README.md                  # This guidance
├── csharp/
│   ├── README.md
│   ├── src/                   # C# production code, after an ADR
│   ├── tests/                 # Verified C# tests, when implemented
│   └── examples/              # Minimal examples, if needed
├── cpp/
│   ├── README.md
│   ├── include/               # Public C++ headers, if required
│   ├── src/
│   ├── tests/
│   └── examples/
└── java/
    ├── README.md
    ├── src/                   # Java sources; Maven/Gradle layout not chosen
    ├── tests/
    └── examples/
```

The **empty source/test/example folders are maintained by `.gitkeep`**. They deliberately do **not** contain placeholder source files that pretend to compile, package manifests, or "tests pass" boilerplate. Once a build system is chosen, replace placeholder organization with idiomatic, documented module boundaries.

## What belongs where?

- **Language-specific source, test, build files, examples and packaging** stay under one language directory.
- **Portable contract proposals, fixtures and compatibility-test definitions** live in [../shared/](../shared/).
- **Actual product decisions, API stability policy and module boundaries** belong in versioned ADRs and architecture docs.
- **Generic human-facing docs** remain under [../docs/](../docs/).
- **Common generated binaries** are not committed.

## Do not confuse these two strategies

**A. One primary HARALD backend, clients in other languages:** A single deployment owns transactions and authoritative catalog data. C++, Java or C# clients use a versioned application API. This avoids duplicating domain rules, but depends on a stable transport contract.

**B. Multiple independent HARALD implementations:** Each language implements the same **defined behavior**, with separate storage/persistence adapters, build/release lifecycles and common compatibility fixtures. This has substantially higher maintenance and parity costs.

The directory layout permits **either**, but does not decide between them. Mixing the two strategies without a written ADR risks conflicting databases, circulation rules and unsupported compatibility promises.

## Ground rules

1. Work, Edition, Physical Item, Component, Asset, Rights, and Loan have distinct identities.
2. At most one active loan per physical item, even under concurrent requests.
3. No direct cross-language access to another implementation's private database.
4. Shared interchange contracts must be language-neutral, versioned, and access-controlled.
5. Untrusted plugins, network providers and files cannot bypass the application layer.
6. Preserve data export/restore ownership and verify Unicode/identifier round trips.
7. Do not add a new language because an empty directory looks like a release promise.
8. Report actual build/test results; no toolchain is selected yet.

## Starting a real implementation

First propose or accept the relevant [ADR](../docs/architecture/adr/README.md), define its role (server, standalone app, CLI or client), and identify the roadmap milestone. Then add a **small vertical slice**: one work, one edition, two distinct physical copies, persistence, tests and a demonstrable interaction. Only then expand.

**No language is a "reference implementation" until explicitly selected and tested.**
