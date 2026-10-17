# HARALD — Language-neutral shared assets

> **Status:** Structure and guidance only. This directory does not contain a published schema, executable conformance harness or fixture dataset yet.

The `shared/` area is for **implementation-language-independent specifications and verification artifacts**, not for a runtime shared-memory region, foreign source tree, or a universal binary library.

| Folder | Purpose |
| --- | --- |
| [contracts/](contracts/README.md) | Proposed and later versioned catalog exchange/API/event/extension contracts. |
| [fixtures/](fixtures/README.md) | Synthetic representative media records for reproducible test cases. |
| [conformance/](conformance/README.md) | Future cross-language behavioral parity and compatibility test expectations. |

## Boundary rule

The authoritative rules for catalog identity, physical loan invariants and digital rights live in the approved requirements/architecture. Actual implementations must enforce them with native code and tests. Cross-language contracts are **wire/data contracts**, not a mandate to mirror one programming language's internal object model.

If only **one** backend is selected and other languages implement client apps, `shared/` will describe the **server's public API** and client test fixtures. If multiple backends are approved, `shared/` can host interoperability/behavior specifications that prevent implementations from drifting.

**Never give two independent servers concurrent write access to the same internal database.** A migration or synchronization protocol would need its own explicit design and authorization model.

See [Multilanguage Architecture](../docs/architecture/MULTI_LANGUAGE.md) and [ADR-0001](../docs/architecture/adr/0001-technology-stack-and-platforms.md).
