# HARALD — Developer Setup and Engineering Workflow

> **2026-10-26 update:** An experimental **C++20/SQLite catalog CLI** and real build/test commands now exist. No production release or accepted final language/GUI decision exists.

## Start here

Read [AGENTS.md](../../AGENTS.md), [README.md](../../README.md), [ROADMAP.md](../../ROADMAP.md), [Architecture](../architecture/ARCHITECTURE.md), [ADR register](../architecture/adr/README.md) and [Test Strategy](../testing/TEST_STRATEGY.md).

Current source tree includes a real experimental C++20/SQLite CLI and tests, alongside planning/reference documents, artwork and the MIT license. C# and Java remain placeholder tracks. Use GitHub Issues for larger tasks and do not introduce a competing framework scaffold while ADR-0001 remains Proposed.

## First executable C++/SQLite slice (tested locally on Linux)

Run these commands from the repository root. Requires CMake 3.20+, a C++20 compiler, and SQLite development headers/library:

```sh
cmake -S implementations/cpp -B implementations/cpp/build -DCMAKE_BUILD_TYPE=Debug
cmake --build implementations/cpp/build --parallel
ctest --test-dir implementations/cpp/build --output-on-failure
./implementations/cpp/build/harald_cli --db /tmp/harald-demo.sqlite init
./implementations/cpp/build/harald_cli --db /tmp/harald-demo.sqlite seed
./implementations/cpp/build/harald_cli --db /tmp/harald-demo.sqlite list
./implementations/cpp/build/harald_cli --db /tmp/harald-demo.sqlite show 1
```

The real use cases, CLI arguments, test evidence and limitations are described in [implementations/cpp/README.md](../../implementations/cpp/README.md). Do not use valuable library data in this prototype; backup/restore, access control and the graphical desktop UI are not yet implemented.

## Prerequisites — to be decided

The accepted [ADR-0001](../architecture/adr/0001-technology-stack-and-platforms.md) should state:
- Programming language, compiler/SDK and exact supported versions.
- First supported Windows/Linux versions and tested optional BSD evaluation.
- Required package/build tools, editor setup, runtime distribution strategy.
- Database storage engine, setup/migration tool and concurrency limitations.
- UI/API/CLI development loop, launch configuration and local ports if any.
- Secret management, logging and secure development defaults.
- License/dependency policy and update cadence.

Until then, only basic Git is required for document contributions.

### Clone the repository

~~~sh
git clone https://github.com/Robin-Goerlach/SASD-Harald.git
cd SASD-Harald
git status -sb
~~~

This merely retrieves the project. It **does not** run an application.

## Proposed directory boundaries

Potential logical boundaries are domain, application/use cases, infrastructure adapters, transport/API and UI. The exact structure depends on the chosen stack and accepted ADRs. Module boundaries matter more than names.

A project layout should make it possible to:
- Compile/test domain rules without UI, database or network.
- Substitute a persistence or metadata provider adapter in a test.
- Add media profiles without editing unrelated domain modules.
- Use the same application use cases from alternative clients.
- Keep protected digital files and secret configuration outside public roots.
- Run database migrations from controlled, versioned tooling.
- Locate unit, integration, contract, end-to-end, security and performance tests.

## The first development slice

Once ADR-0001 has been approved, prefer:
1. Work and Edition identity with stable IDs.
2. Two physical copies with unique item/inventory IDs and independent locations.
3. A versioned database schema and repository adapter.
4. Minimal UI/CLI or API calling application use cases.
5. Real build/test/CI commands and Unicode fixtures.
6. Verified export/restore of the sample model.
7. Architectural and permission tests.

Do not mix first-slice delivery with provider integrations, a full player or generic third-party plugin execution.

## Review checklist for code changes

- Problem, milestone, requirements and scope are clear.
- Public interfaces expose DTOs, not ORM entities.
- Domain and application do not import UI/DB frameworks.
- Transaction, authorization, migration and file-storage impacts are explicit.
- Non-obvious code is commented with the underlying business reason.
- Unit, integration and negative tests exist and were actually run.
- Cross-platform claims are backed by executed commands.
- No production private media, credentials or personally identifiable data are committed.
- Docs, changelog, ADRs and roadmap are accurate.

## Future build commands

Once implemented, this section will name precise commands for:
- Environment setup and dependency restore.
- Build and clean rebuild.
- Formatting and lint.
- Unit/integration/e2e test suites.
- Database init and migration.
- Start local development service/UI.
- Package release artifacts.
- Backup and restore.
- Dependency/secret/license scans.

**Do not publish speculative commands.** Their exact spellings must be copied from working toolchains with recorded expected results.
