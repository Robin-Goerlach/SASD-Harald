# Language-neutral contracts — reserved

There are **no finalized schemas or public contracts** in this directory yet.

Once real consumers justify a stable interface, proposals can define:
- Versioned Work, Edition, Physical Item, Component and Digital Asset data transfer representations.
- Stable internal IDs vs external ISBN/EAN/UPC/barcode identifiers.
- Typed media profile fields, language tags, Unicode, date and null semantics.
- Import/export archive manifest, integrity checks and schema version.
- Permission-scoped queries and redacted public catalog projections.
- Error envelopes, idempotency, optimistic concurrency and pagination.
- Optional metadata provider or plugin messages, only after an isolation decision.

A schema becomes normative **only after an accepted ADR, a published version, and positive/negative contract tests**.

Do **not** export private SQL tables/ORM types as the public contract. Do **not** treat physical and digital lending as the same permission. Consult [API design](../../docs/api/README.md), [requirements](../../docs/requirements/README.md), and [architecture](../../docs/architecture/ARCHITECTURE.md).
