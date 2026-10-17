# HARALD — C++ Implementation Track

**Status:** Reserved directory, **not implemented**. There is no CMake project, compiler target, Qt application, native library, package or verified cross-platform build yet.

[All implementation tracks](../README.md) · [Multilanguage design](../../docs/architecture/MULTI_LANGUAGE.md) · [ADR-0001](../../docs/architecture/adr/0001-technology-stack-and-platforms.md)

## Purpose

This area may become a native HARALD application, a domain library, a desktop client, or a portability evaluation implementation. The eventual choice of Qt, a C++ standard, CMake, other libraries or third-party packaging is **open**.

## Reserved folders

- `include/` — eventual exported headers and versioned interfaces, if a C++ library is created.
- `src/` — internal implementation source and adapter/host code.
- `tests/` — domain, persistence, memory-safety, contract and integration tests.
- `examples/` — small verified examples after build tooling exists.

Only `.gitkeep` placeholders and this README exist. **No binary ABI is promised.**

## Decisions to evaluate

- C++ standard, compiler/library versions and platform support matrix.
- Native executable vs shared/static library vs API client.
- Compiler/runtime/Qt deployment requirements on Windows, Linux and experimental BSD targets.
- Dependency footprint, symbol visibility and ABI stability; prefer versioned data protocols across languages rather than a premature C ABI.
- Sanitizers, static analysis, deterministic tests, memory ownership and exception safety.
- Threading, database transactions, concurrency and filesystem atomicity.
- Separating domain objects from Qt types and GUI classes.
- Licensing for every native dependency and bundled component.

## Initial proof

Implement and test Work, Edition and two independently inventoried copies using a clean core/adapters boundary, including duplicate-barcode and concurrent-write behavior. Measure build, packaging and platform assumptions before asserting support.
