# Contributing to HARALD

Thank you for helping build **HARALD**, an open-source, extensible library and multimedia collection manager.

> **Current project stage:** planning / pre-alpha. This repository does not yet contain a runnable application. Development instructions and build commands will be published **after** the language, platform targets and build system are selected in an accepted ADR.

## 1. Before you begin

Please read [README.md](README.md), [ROADMAP.md](ROADMAP.md), the [architecture proposal](docs/architecture/ARCHITECTURE.md), [AGENTS.md](AGENTS.md), and the [ADR register](docs/architecture/adr/README.md). Check [GitHub Issues](https://github.com/Robin-Goerlach/SASD-Harald/issues) to avoid duplicate work.

The project follows an important distinction: **a media catalog entry**, a **particular edition**, an **individual physical item**, and a **digital asset** are not interchangeable. Contributions should preserve these identities and the authorization/privacy boundaries around them.

## 2. Useful contributions now

We especially welcome:
- Corrections to the requirements, architecture, roadmap, and domain terminology.
- Concrete workflows for books, DVD/Blu-ray, music, audiobook box sets, EPUB/PDF, comics and journals.
- Critical feedback on stack portability to Windows/Linux and feasibility for FreeBSD/OpenBSD.
- Reproducible comparisons of build/runtime/package footprints (clearly identify platform and versions).
- Threat modeling for circulation data, public catalogs, private file access and plugins.
- Licensing/data-provenance observations about metadata or artwork providers.
- Detailed acceptance tests, representative **synthetic** fixtures, migration/export schemas, or API designs.
- German/English terminology and accessibility review.

Please distinguish requirements from feature suggestions and prototypes from stable interfaces.

## 3. Issues and feature proposals

Search existing issues first. A useful new issue includes:

**For a bug once software exists:** version or commit; operating system and deployment type; preconditions; reproduction steps; expected and observed result; safe/redacted logs; whether data or permissions are affected.

**For a feature or architectural proposal:** problem and target user; example media and workflows; proposed behavior and explicit non-goals; affected milestones/requirement IDs (if known); privacy, storage, licensing, migration and compatibility consequences; concrete acceptance criteria.

Changes to core architecture, technology stack, public API, database ownership or extension trust model require an **ADR proposal**. The [ADR guide](docs/architecture/adr/README.md) explains statuses and the review process.

Do not post confidential details, personally identifiable member data, private e-books or exploit instructions in public issues. Use [SECURITY.md](SECURITY.md) for vulnerability reports.

## 4. Proposed contribution workflow

1. Create an issue or refer to an existing agreed work item for significant changes.
2. Agree the smallest scoped increment and its acceptance checks.
3. Make changes on a focused branch, unless the maintainer explicitly requests and authorizes direct commits to main.
4. Preserve the modular domain/application/adapter boundaries from the architecture.
5. Add or update tests. A change to an invariant, API contract, schema or access rule needs corresponding tests.
6. Document any new configuration, migration, operation, extension contract or public behavior.
7. Run **actual available** build, formatting, test and validation commands; include results in the pull request.
8. Review the diff for unrelated changes, generated files, binary assets, secret keys, unlicensed material and dependency modifications.
9. Submit a clearly titled pull request referencing the issue/requirements/milestone. Explain what was **not** tested.
10. Respond to review feedback; do not force-push protected branches or rewrite other authors' history without agreement.

Because there is currently no build system, **no specific command is yet official**. Do not invent one to make a contribution checklist look complete.

## 5. Engineering expectations

- Favor readable, testable, maintainable code with **comments explaining non-obvious business rules and design choices**.
- Keep domain code independent of UI frameworks, database frameworks, HTTP and service SDKs.
- Use application use cases to enforce permissions and transactions.
- Do not write or update another module's tables as a shortcut.
- Avoid overly generic frameworks and plugin systems before a genuine second use case exists.
- Validate untrusted metadata, identifiers, uploads and file paths; prevent unauthorized information in search/export.
- Preserve Unicode and identifiers through import/export and database migrations.
- Treat external providers as optional, untrusted, rate-limited and possibly unavailable.
- Ensure an item cannot have two active loans under concurrent checkout.
- Record changes in [CHANGELOG.md](CHANGELOG.md) under Unreleased when meaningful.
- Never claim unsupported operating systems, tested versions, security guarantees or release dates.

## 6. Commit and PR conventions

Suggested commit prefixes:
- **docs:** documentation or roadmap
- **feat:** new user capability
- **fix:** behavior or security correction
- **test:** tests and fixtures
- **refactor:** structural change without intended behavior change
- **build:** toolchain/dependency/build-system change
- **ci:** continuous-integration change
- **chore:** low-risk maintenance

Examples:
- docs: clarify Work versus Edition identity
- test: cover concurrent checkout rejection
- feat(catalog): add edition identifier validation

Keep commits coherent; explain *why* unusual behavior is needed in code comments or the commit message. Do not mix unrelated reorganizations with feature work.

Pull requests should describe:
- Goal, scope and affected issue/requirements.
- Design choices and ADR references.
- Changed user behavior and compatibility.
- Tests executed and outputs; tests not run and why.
- Security, privacy, licensing and data-migration impact.
- Screenshots if and only if UI has actually been implemented (concept art should be labeled).

## 7. Documentation contributions

The repository intentionally includes German requirements and architecture notes alongside English onboarding materials. Technical symbol and interface names are planned in English; translations and localized user copy may expand later.

When editing:
- Keep links relative where practical.
- Do not remove requirement IDs or silently alter release priority.
- Treat a **Proposed** ADR as undecided.
- State when a diagram, JSON schema, API route or UI is only conceptual.
- Update README/ROADMAP if a substantive project state changes.
- Add sources and version context for third-party feature claims.

## 8. Code, data and licensing

HARALD uses the [MIT License](LICENSE). Contributions intended for inclusion should be offered under terms compatible with that license and must not knowingly contain third-party proprietary code. Check dependencies, generated content, logos, cover art and external metadata licenses before committing.

Do not add real borrowers' details, personal libraries, commercial books, films or music as fixtures. Prefer original synthetic sample data.

No formal contributor license agreement is currently defined. If rights to a proposed contribution are uncertain, raise the issue before submitting.

## 9. Reviews and acceptance

A reviewer will look for:
1. Alignment with the correct milestone and approved scope.
2. Domain invariants and authorization.
3. Clear module boundaries and documented migrations.
4. Tests that fail for a meaningful regression, not placeholder assertions.
5. Minimal dependency and platform footprint.
6. Helpful comments and documentation.
7. Privacy, security and legal correctness.

Acceptance of a contribution does not imply a release date. Release readiness requires the full checklist in [ROADMAP.md](ROADMAP.md).

---

**Principle:** Contribute a small verified improvement now while preserving freedom to add new media types and clients later.
