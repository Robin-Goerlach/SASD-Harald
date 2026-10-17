# HARALD — Requirements baseline

> **Status:** Historical draft material used as the starting point for HARALD. The documents are not yet formally approved as a final product contract.  
> **Language:** German source; current HARALD onboarding and engineering guides are in English.  
> **Date:** 2026-10-17

## Source document

[Pflichtenheft — Offene Multimedia-Bibliotheks- und Sammlungsverwaltung (2026)](Pflichtenheft_Open_Source_Multimedia_Bibliotheksverwaltung_2026.md)

This is the **complete original requirements draft** (document ID OMB-PFH-001) previously prepared for a generic open-source multimedia library. It contains detailed functions, acceptance criteria, identifiers, technical suggestions, 24 comparison programs, 110 traced source requirements and staged R0–R3 scope. It was copied here as a provenance-preserving baseline, **not rewritten or silently approved**.

The feature research underpinning it is archived at [docs/research](../research/README.md). The current project design is in [ARCHITECTURE.md](../architecture/ARCHITECTURE.md), and the delivery order is in [ROADMAP.md](../../ROADMAP.md).

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

- [Original full Pflichtenheft](Pflichtenheft_Open_Source_Multimedia_Bibliotheksverwaltung_2026.md)
- [Research baseline — 24 programs](../research/README.md)
- [Architecture](../architecture/ARCHITECTURE.md)
- [Roadmap](../../ROADMAP.md)
- [Test strategy](../testing/TEST_STRATEGY.md)

**Next step:** review and approve the R1 MUST requirements, update obsolete placeholder references in a new explicitly versioned revision, then map agreed acceptance tests to real implementation work.
