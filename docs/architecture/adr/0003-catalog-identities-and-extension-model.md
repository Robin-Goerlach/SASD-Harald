# ADR-0003 — Stable Catalog Identities and Extensible Media Profiles

- **Status:** Proposed — acceptance pending
- **Date:** 2026-10-17
- **Approver:** Repository maintainer
- **Milestone:** M2–M3
- **References:** [Architecture](../ARCHITECTURE.md), [Requirements](../../requirements/README.md)

## Context

A single HARALD catalog must hold printed books, DVDs/Blu-rays, audio, audiobooks, EPUB/PDF assets, comics and future types without losing their distinct semantics. External identifiers are imperfect and different physical copies must not share their inventory state.

## Options

1. **Work → Edition → Item/Asset with typed media profiles (proposed):** Stable identities and validation, support for new media without rewriting all fields.
2. **One universal record with many nullable columns:** Simple initially but weak type safety, confusing queries and migrations.
3. **Everything in unvalidated JSON/EAV:** Easy to add fields but poor indexing/invariants and ambiguous interoperability.
4. **Separate databases per medium:** Strong specialization but duplicates catalog identities, search and circulation concepts.

## Proposed decision

Define stable core identities and explicitly connected records:

- **Work** — creative content and relationships.
- **Edition** — published/released form with publication metadata and typed identifiers.
- **Physical Item** — one owned item or set, inventory barcode, condition, location, loan state.
- **Component** — disc, volume, booklet or accessory of an item.
- **Digital Asset** — content reference, checksum, storage state and rights metadata.
- **Media Profile** — validated medium-specific edition attributes; use typed common fields and controlled extension fields.

Do not use external ISBN/EAN codes as permanent database primary keys. A digital file is not a lendable physical copy. Public reads must be permission-filtered; profile extensions cannot bypass core invariants.

## Verification before acceptance

- [ ] A work has two editions, and one edition has two independently inventoried copies.
- [ ] The same film has separate DVD and Blu-ray editions.
- [ ] A boxed audiobook has six checkable discs without six independent full-edition entries.
- [ ] A private EPUB asset is linked to an edition without granting public download rights.
- [ ] Export/import and backup/restore preserve IDs and graph relationships.
- [ ] A new media profile can be added without adding unrelated nullable columns.
- [ ] Unknown imported fields are either preserved according to schema or reported, never silently deleted.

## Consequences

Requires clearly versioned persistence and exchange schemas, valid identifier scopes, media profile validation, migration discipline, and dedicated tests. A fully dynamic user-defined media type editor is **not** implied in R1.

## Decision log

- **2026-10-17:** Proposed. Aligns with the detailed Pflichtenheft and architecture; awaiting formal ratification.
