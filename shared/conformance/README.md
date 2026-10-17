# Conformance and cross-language parity — reserved

This folder may eventually contain language-neutral **conformance case definitions** for independent HARALD clients or implementations.

**No tests have been implemented or passed.**

## Intended test groups

1. **Model:** Work–Edition–Item relationships survive export/import; identifiers are stable.
2. **Media profiles:** DVD/Blu-ray, music, audiobook, books and digital formats preserve their typed semantics.
3. **Circulation:** one active loan per item even with competing requests; lost or incomplete sets handled.
4. **Authorization:** anonymous/public views never expose member data, private assets, or administrative fields.
5. **Interchange:** recognized versioned formats preserve Unicode, unknown-field policy and checksums.
6. **Compatibility:** versions reject unsupported changes safely and report differences explicitly.
7. **Failure:** provider outage, interrupted import/upload and backup restoration cannot report false success.

Actual harness and runner choice depends on language stacks and published contracts. **Do not create placeholder green test scripts**. Each test must declare input, expected result, exact runner environment, and evidence of execution.

See [test strategy](../../docs/testing/TEST_STRATEGY.md) and [architecture](../../docs/architecture/MULTI_LANGUAGE.md).
