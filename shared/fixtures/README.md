# Shared test fixtures — reserved

This directory will eventually hold **small synthetic or explicitly licensed** sample records. No test dataset exists yet.

Minimum planned cases:
- One Work with two Editions and two physically distinct copies.
- Same film released on DVD and Blu-ray, each with its own identifiers.
- Music CD with tracks/performer metadata.
- Six-disc audiobook with individually registered components.
- Authorized EPUB/PDF asset with private access rules and integrity checks.
- Non-ASCII/multilingual titles and creator names.
- Duplicate barcode and invalid identifier cases.
- Synthetic member accounts with different roles, no real PII.
- Export → clean import → equivalent relationship graph.

Each fixture must state license/source, intended schema version, and expected assertions. Private personal libraries, copyrighted e-books, commercial covers and real borrower information must not be committed.

See [test strategy](../../docs/testing/TEST_STRATEGY.md).
