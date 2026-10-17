# HARALD — Data Import, Export and Migration Plan

> Status: design draft. No implemented importer, exporter or catalog schema is available yet.

HARALD's central migration goal is to allow operators to **leave HARALD without losing their information**, and to import collections from other tools without silently collapsing works, editions and physical copies.

## Planned migration stages

1. **Discover source:** version, data format, type systems, field definitions, encodings, external IDs, ownership and rights.
2. **Preview mapping:** show source columns and the destination Work/Edition/Item/Asset/Component/Collection/Location relationships.
3. **Validate:** required attributes, ISBN/EAN checks, barcode uniqueness, unknown creator roles, language/encoding, cross-references and privacy.
4. **Dry run:** record planned creations, duplicates, warnings and rejected records without writing live data.
5. **Commit in a controlled transaction/batch:** stop or recover safely on error and document partial progress when unavoidable.
6. **Verify counts and graph links:** compare works, editions, copies, components, assets and active loans where imported.
7. **Record provenance:** source program/version, import ID, original identifiers, license and field conflict decisions.
8. **Export and round-trip test:** test clean install → import → export and compare permitted data and relationships.

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

At R1, a complete synthetic catalog, including two copies of an edition and a private digital file, should export, import into a clean compatible installation, restore its relationships and authorizations, and produce a verifiable comparison report.

See [Requirements](../requirements/README.md), [Test Strategy](../testing/TEST_STRATEGY.md), [Operations](../operations/OPERATIONS.md), and [Roadmap](../../ROADMAP.md).
