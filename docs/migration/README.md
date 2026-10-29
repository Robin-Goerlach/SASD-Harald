# HARALD — Data Import, Export and Migration Plan

> **Status:** Design draft. An experimental SQLite **catalog schema and basic Work → Edition → Copy persistence exist**, but **no CSV/JSON importer/exporter, foreign-ILS migration, full-fidelity exchange or backup/restore implementation** has been verified. See [C++ implementation](../../implementations/cpp/README.md).

> **Traceability:** [HARALD Lastenheft LH-MI-01–07](../requirements/Lastenheft_HARALD_2026.md), [historical Pflichtenheft §7.12 with HARALD addendum](../requirements/Pflichtenheft_Open_Source_Multimedia_Bibliotheksverwaltung_2026.md), [MIG-001–012 and MIG-AT-01–12](../requirements/MIGRATION_FROM_OTHER_SYSTEMS.md), and [M9 roadmap](../../ROADMAP.md).

HARALD's central migration goal is to allow operators to **leave HARALD without losing their information**, and to import collections from other tools without silently collapsing works, editions and physical copies. A **foreign-system migration**, a HARALD-JSON exchange, a change of HARALD storage backend and a schema upgrade/backup restore are four different operations. No client directly edits the legacy product's database.

## Planned migration stages

1. **Discover source:** version, data format, type systems, field definitions, encodings, external IDs, ownership and rights.
2. **Preview mapping:** show source columns and the destination Work/Edition/Item/Asset/Component/Collection/Location relationships, including **each physical item and its own inventory barcode**; do not use title or ISBN as an item key.
3. **Validate:** required attributes, ISBN/EAN checks, barcode uniqueness, unknown creator roles, language/encoding, cross-references and privacy.
4. **Dry run:** record planned creations, duplicates, warnings and rejected records without writing live data.
5. **Commit in a controlled transaction/batch:** stop or recover safely on error and document partial progress when unavoidable.
6. **Verify counts and graph links:** compare works, editions, **individual copies, conditions and locations**, components, assets and active loans where separately authorized/imported. Preserve source-qualified IDs for safe reruns.
7. **Record provenance:** source program/version, import ID, original identifiers, license and field conflict decisions.
8. **Export and round-trip test:** test clean install → import → export and compare permitted data and relationships.
9. **Cutover and rollback:** perform a protected source backup, keep old data available, freeze source writes for the final reconciliation, verify results and authorize the new source of truth. An import is not a live two-way sync.

### Specific migration safeguards

- Treat three copies of the same edition as **three distinct items** even if title, author and ISBN match. Condition and withdrawal are **item attributes**.
- A dry-run or canceled job changes **no production domain records**. Ambiguous source IDs, barcode conflicts, unknown states, unrecognized fields and mismatched borrower references generate **reviewable reports**, not silent guesses.
- Import batches are transactionally consistent and restart from verified checkpoints. Replaying an identical job must **not** produce more copies; changes to source files/mappings are explicitly detected.
- Members, active loans, holds, credentials and digital rights are **not part of an implicit bibliographic import**. A separately authorized migration of active circulation requires correct item/member mapping and may be postponed without lying about completion.
- All staging data and logs follow security/retention controls, especially where borrower information is present.

## Intended formats and integration candidates

Initial plans: UTF-8 CSV views for common items and a versioned JSON exchange package including a manifest and relationship-preserving identifiers. Actual format schemas are open decisions and must be tested before publication.

Possible later adapters include Calibre, Tellico, GCstar, Data Crow, Koha or other systems. Their upstream export formats and rights must be evaluated at the time of implementation. **No importer for these products currently exists in HARALD.**

## Export principles

- No vendor-specific lock-in or undocumented database dumps as the only escape route.
- An authorized export should be self-describing and versioned.
- Optional digital file transfer must respect ownership, copyright and access rights.
- Personal/member data must be filtered according to permissions and retention.
- Unknown fields should be preserved where the schema supports extensions, otherwise surfaced as explicit losses.
- Large migrations should produce usable error reports and recoverable progress.
- Backups and human-friendly CSV reports are distinct from full-fidelity exchange exports.

## Release gate

At R1, a complete synthetic catalog, including at least two copies of an edition and a private digital file, should export, import into a clean compatible installation, restore its relationships and authorizations, and produce a verifiable comparison report. Separately, a mapped foreign-source CSV fixture with **three copies of one edition** must survive dry-run, import and rerun with no silent duplication, conflicts or losses.

**Scope:** Generic CSV/UTF-8 and versioned HARALD-JSON exchange are existing **R1 targets**; a guided migration wizard is a **proposed R2 enhancement**; native Koha/FOLIO/Calibre/Tellico and MARC21 adapters require **later tested source-specific implementations**, not a promise of present support.

See [Requirements](../requirements/README.md), [Test Strategy](../testing/TEST_STRATEGY.md), [Operations](../operations/OPERATIONS.md), and [Roadmap](../../ROADMAP.md).
