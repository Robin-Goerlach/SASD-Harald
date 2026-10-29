# HARALD C++ desktop — manual verification checklist

**Status:** Experimental native Win32 / GTK4 catalog frontend, **not** a
certified application release. This checklist records intended human tests;
its existence does not assert that any of them have already been executed.

## Prerequisites

Use a throwaway SQLite database. Never use an irreplaceable personal
collection: there is no backup/restore workflow yet.

- Build `harald_desktop` with `HARALD_WITH_DESKTOP=ON`. See the
  [C++ build instructions](../README.md) for native Toolkit dependencies.
- Run `ctest --test-dir <build> -C Debug --output-on-failure`.
- Start with an empty database and run `harald_cli --db <file> seed` once.
- Launch `harald_desktop <file>` **without** `--smoke` to test interaction.

The `--smoke` mode exits after initial frame creation. It is only an
automated startup/renderer check and must not be mistaken for a manual test.

## Expected user interactions

1. **Initial catalog** — the seeded example appears as one edition with two
   physical copies; selecting a table row shows its title, author, edition,
   ISBN, inventory codes and locations.
2. **Search** — type `Example`, press **Search**, verify a matching result.
   Search for a missing title: zero results and no stale detail selection.
   Clear search and verify the complete list reappears.
3. **Multi-copy creation** — press **New book**; fill Title `Über Bücher`,
   Creator `Ada Lovelace`, Edition `Hardcover`, optional ISBN empty,
   inventory code `HAR-TEST-NEW-001`, location `Room A / Shelf 2`.
   Click **Add copy** and enter `HAR-TEST-NEW-002` / `Shelf 3` and
   **Add copy** again for `HAR-TEST-NEW-003` / `Shelf 4`.
   Use **Previous** and **Next** to verify each copy retains its input.
   Click **Save book**; verify the editor closes and all three persisted
   copies are visible in the selected edition's details.
4. **Validation** — open **New book**; leave Title blank and try Save. The
   editor must stay open, display an error and preserve every typed value.
5. **Duplicate** — try creating another book with the *same* inventory code
   `HAR-TEST-NEW-001`. The form must reject it and preserve its inputs.
   Returning to the catalog must reveal no partially created duplicate.
6. **Cancel/remove** — open a form, enter two copies, click **Remove copy**;
   verify the remaining copy is not changed and no database record exists
   yet. Remove must not eliminate the sole remaining row. Press **Cancel**;
   open **New book** again and verify the previous draft is not resurrected.
7. **Restart** — exit via Escape, restart with the same test SQLite file; the
   saved edition must still exist. A rejected duplicate must still be absent.
8. **Input and layout** — test mouse selection, Tab/Shift+Tab, typing `Über`
   and `日本語`, resizing the window smaller/larger and then selecting
   again. Record any text clipping, viewport issues, incorrect focus or
   failure to accept keyboard events.
9. **Details paging** — create or import an edition with at least seven
   copies. Verify **Copies >** and **< Copies** reveal all seven barcodes
   over three pages, with no duplicates or hidden last record. Selecting
   another edition must reset the paging position.
10. **Safety** — verify pressing Escape from the editor closes only the form;
   pressing Escape from browsing closes the application. Test with no network
   connectivity to confirm that local catalog operations remain offline.

## Evidence and reporting

Record OS build, architecture, compiler, CMake generator, toolkit commit,
SQLite version, window backend, build configuration and database fixture.
Collect the full configure/build/CTest transcript, console errors, and one
screenshot of the catalog plus one of the new-book editor. A problem report
should identify the numbered step, expected behavior and observed behavior.

**Known limits:** At most three physical copies are visible **per page**,
but all copies are reachable through the pager. Small-window form geometry
may still clip; the form does not yet scroll. Accessibility, IME/composed text, high-DPI and localization
require separate acceptance tests.

Do not mark these checklist items passed until a real desktop test run has
produced the corresponding evidence.
