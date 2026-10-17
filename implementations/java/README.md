# HARALD — Java Implementation Track

**Status:** Reserved directory, **not implemented**. No Maven/Gradle project, Java module, runtime version, UI framework, JAR, container or published Java API is available.

[All implementation tracks](../README.md) · [Multilanguage design](../../docs/architecture/MULTI_LANGUAGE.md) · [ADR-0001](../../docs/architecture/adr/0001-technology-stack-and-platforms.md)

## Purpose

Java is an optional future track. It may be used as a backend, a JVM desktop application, a library/client or a test implementation of portable contracts, provided a concrete use case and architecture decision justify it. **Java is not required for R1 simply because this directory exists.**

## Reserved folders

- `src/` — future code layout (e.g., language-idiomatic source roots only after a build tool is selected).
- `tests/` — future unit/integration/contract and security tests.
- `examples/` — verified minimal usage samples, once implemented.

Only placeholder `.gitkeep` files and this README are present.

## Questions before implementation

- JDK version and support/packaging policy (JRE/jlink/native image, if appropriate).
- Role: independent backend or client using another backend's contract.
- Maven vs Gradle vs another build system; reproducible dependency management.
- Domain isolation from JPA, HTTP, Swing/JavaFX or framework types.
- Transaction semantics and portable data identifiers.
- Actual supported OS/runtime profiles and size/security trade-offs.
- Licensing and maintenance expectations relative to C# and C++ tracks.

## Initial proof

A minimal Work/Edition/Physical Item use case, persistence and positive/negative tests with documented reproducible commands—not speculative code scaffolding.
