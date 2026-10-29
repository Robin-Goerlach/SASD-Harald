# HARALD — Requirements baseline

> **Status:** Historical draft material used as the starting point for HARALD. The documents are not yet formally approved as a final product contract.  
> **Language:** German source; current HARALD onboarding and engineering guides are in English.  
> **Date:** 2026-10-17

## Source document

[Pflichtenheft — Offene Multimedia-Bibliotheks- und Sammlungsverwaltung (2026)](Pflichtenheft_Open_Source_Multimedia_Bibliotheksverwaltung_2026.md)

This is the **complete original requirements draft** (document ID OMB-PFH-001) previously prepared for a generic open-source multimedia library. It contains detailed functions, acceptance criteria, identifiers, technical suggestions, 24 comparison programs, 110 traced source requirements and staged R0–R3 scope. It was copied here as a provenance-preserving baseline, **not rewritten or silently approved**.

The additional [HARALD Lastenheft (HARALD-LH-001, 2026-10-29)](Lastenheft_HARALD_2026.md) is a **new proposed statement of user needs**, focusing on copy-specific condition, later self-service circulation and migration from other library software. This is distinct from the historical supplier-oriented Pflichtenheft. The original Pflichtenheft now also contains clearly marked **HARALD addenda** in the relevant chapters; the earlier source baseline has not been silently approved.

The feature research underpinning it is archived at [docs/research](../research/README.md). The current project design is in [ARCHITECTURE.md](../architecture/ARCHITECTURE.md), and the delivery order is in [ROADMAP.md](../../ROADMAP.md).

## New requirements addendum (2026-10-17)

[HARALD-REQ-ADD-001 — Planned book acquisitions and systematic shelving](ACQUISITIONS_AND_SHELVING.md) records the newly requested procurement/reading-list workflow (ACQ-001–ACQ-012), optional Dewey-style classification and physical shelf-location separation (SHELF-001–SHELF-010), and proposed acceptance cases.

**Status:** proposed details, not an accepted release commitment and not implemented. In the user's request a further second feature was explicitly postponed; the addendum does **not** guess what it is.

## Proposed self-service circulation addendum (2026-10-29)

[HARALD-REQ-ADD-002 — Self-service checkout and return](SELF_SERVICE_CIRCULATION.md) records the new request for reader-operated loans and returns (SSC-001–SSC-012). It explicitly distinguishes an authenticated checkout, a return announcement, verified physical intake and completed return/condition inspection. The proposal recommends R2 after M6/M7 but does **not** silently change the R1 baseline. **No implementation is claimed.**

## Proposed foreign-system migration addendum (2026-10-29)

[HARALD-REQ-ADD-003 — Migrating existing collections from other library systems](MIGRATION_FROM_OTHER_SYSTEMS.md) specifies a safe, source-aware migration process, including per-copy identity, a preview/dry run, explicit conflict handling, source-ID crosswalks, rollback and acceptance checks (MIG-001–012; MIG-AT-01–12). It reuses existing R1 CSV/JSON requirements (IMP-002–010); system-specific adapters remain later scope under IMP-016/019. **No importer is implemented.**

The original Pflichtenheft is the historical source baseline. An earlier clarification of per-copy condition/withdrawal was appended directly to that document. The new migration and self-service proposals are maintained separately; all proposed addenda require prioritization and integration into a future approved revision.

## What changed after the original draft?

| Original draft wording | Current HARALD interpretation |
| --- | --- |
| OMB / Offene Medienbibliothek was a working name | **HARALD** is the actual project and repository name |
| Choice of open-source license was unresolved | **MIT** is selected and present in [LICENSE](../../LICENSE) |
| GitHub repository had not been fixed | **Robin-Goerlach/SASD-Harald** is established |
| Stack, first UI, storage technology, platform support and plugin runtime were proposals | They **remain decisions to make** through ADRs and prototypes |
| Source requirements were drafted | They are planning input, **not implementation or release evidence** |
| R0/R1/R2/R3 appear in the draft | They remain useful release stages; the current [roadmap](../../ROADMAP.md) refines them |

**No field in the historical draft should be interpreted as proof a feature exists.** Some factual claims about third-party projects are tied to the original research date and must be refreshed before integration.

## Reading and traceability

- **Feature identifiers F001–F110:** research-checklist entries in the catalog; see the historical requirements' traceability section.
- **HARALD user-need IDs:** LH-EX-*, LH-SS-*, LH-MI-*, LH-Q-* (Lastenheft; traceable to technical requirements below).
- **Requirement IDs:** CAT-*, LOC-*, VID-*, MUS-*, AUD-*, DIG-*, CIR-*, IAM-*, SEA-*, IMP-*, INV-*, SEC-*, UI-*, NFR-* and ADV-*.
- **Acceptance tests:** AT-001 through AT-024, with R1 and later-stage distinctions.
- **Work packages:** P00–P17, now mapped to **M0–M17+** in the English roadmap.
- **Release statuses:** MUST/SHOULD/MAY or German M/S/K represent target priority, not measured implementation progress.

A future approved revision should be versioned (for example, HARALD-REQ-001), retain stable IDs when possible, include approval date, and record a change log explaining removed or re-prioritized requirements.

## Workflow for changing scope

1. Identify the source requirement ID and the user problem.
2. Check domain and security invariants in the architecture.
3. State release impact (R0/R1/R2/R3), implementation dependency and test consequences.
4. Propose a new requirement or a change to the draft **without destroying the original provenance**.
5. If an implementation-level choice is cross-cutting, write an [ADR](../architecture/adr/README.md).
6. Once approved, update the roadmap, associated tests and current README.
7. Do not mark a requirement delivered until a real test and implementation exist.

## Critical boundaries that must survive changes

- Work ≠ Edition ≠ Physical Item ≠ Component ≠ Digital Asset.
- ISBN/EAN ≠ inventory barcode, even when identifiers happen to share values.
- External metadata is optional; the core must work offline.
- Physical loans and licensed digital access follow different business rules.
- Authorization applies to searches, exports, APIs and digital files.
- Import/export plus clean-install restore must prove operator data ownership.
- Plugins and external UIs cannot bypass the domain/application layer.

## Documents

- [HARALD Lastenheft — user needs and priorities](Lastenheft_HARALD_2026.md)
- [Historical Pflichtenheft with explicit HARALD addenda](Pflichtenheft_Open_Source_Multimedia_Bibliotheksverwaltung_2026.md)
- [New acquisition and classification addendum](ACQUISITIONS_AND_SHELVING.md)
- [Proposed self-service checkout and return addendum](SELF_SERVICE_CIRCULATION.md)
- [Proposed migration from other library systems addendum](MIGRATION_FROM_OTHER_SYSTEMS.md)
- [Research baseline — 24 programs](../research/README.md)
- [Architecture](../architecture/ARCHITECTURE.md)
- [Roadmap](../../ROADMAP.md)
- [Test strategy](../testing/TEST_STRATEGY.md)

**Next step:** review and approve the R1 MUST requirements, update obsolete placeholder references in a new explicitly versioned revision, then map agreed acceptance tests to real implementation work.
