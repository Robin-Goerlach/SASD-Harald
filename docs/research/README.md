# HARALD — Research and reference material

The original comparison of **24 open-source library, collection management, and digital reading/server projects** is preserved as a research baseline:

**[Open-Source Library Management — Full Feature Catalog (German, 2026)](Open_Source_Bibliotheksverwaltung_Vollstaendiger_Funktionskatalog_2026.md)**

It describes the capabilities and architectural ideas found in:
- **Professional ILS:** Koha, Evergreen, FOLIO, SLiMS, RERO ILS, PMB, InvenioILS, ABCD, Next-L Enju Leaf.
- **Smaller libraries:** BiblioteQ, OpenBiblio, OpenLibry.
- **Collection managers:** Tellico, GCstar, Data Crow, Shelf, uBiblio.
- **E-book/digital servers:** Calibre, Calibre-Web, BookOrbit, BookLore, Kavita, Komga, Inventaire.

The full source covers books, DVDs, Blu-rays, music and audiobook CDs, e-books, digital audiobooks, cataloging, circulation, metadata integrations, interfaces, licensing, and feature-checklist items **F001–F110**.

## Research is not implementation

- This is a **historical snapshot dated 2026-10-17**; upstream licenses, features, availability and project status may change.
- The research compares *capabilities and ideas*, **not code available for copying**. Respect upstream copyright, licenses and trademarks.
- A feature in Koha or another program does **not** automatically become an R1 commitment for HARALD.
- Differentiate cataloging a medium, physically lending an item, holding a digital file, and playing/streaming content.
- Statements about third-party projects should be independently verified against their current docs before an importer, provider or integration is implemented.
- HARALD is independent; it is not affiliated with the referenced products.

## How to use the research

1. Find the use case or source checklist item.
2. Check whether it appears in the [Pflichtenheft](../requirements/README.md).
3. Check the target release in [ROADMAP.md](../../ROADMAP.md).
4. Confirm it fits [architecture boundaries](../architecture/ARCHITECTURE.md).
5. Create an issue/ADR with acceptance tests and legal/metadata-source analysis before implementing.

The full original comparison is preserved for traceability rather than silently edited into the project's product claims.
