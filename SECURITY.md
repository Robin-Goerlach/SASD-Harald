# HARALD Security Policy

> **Security status:** planning/pre-alpha (2026-10-17). HARALD has not made a stable release or promised production support. The current repository contains project documentation and a conceptual screenshot, not a deployable application.

Security and user data ownership are foundational to HARALD. Library systems may store names, borrowing histories, private collections, digital publications, account credentials, and user-generated files. A defect can therefore expose sensitive information or destroy irreplaceable catalog records.

## 1. Supported versions

| Version | Security maintenance |
| --- | --- |
| Planning documentation / main | No released software; documentation and design issues reviewed as available |
| R0 / prototypes (future) | Experimental; not intended for production or Internet exposure |
| R1 stable (future) | Support policy to be published when a first stable release exists |
| R2 / R3 (future) | Not yet released; no support commitments |

**Do not deploy experimental prototypes with real private user data or expose them publicly.**

## 2. Private vulnerability reporting

**Please do not disclose vulnerabilities in public GitHub issues, discussions or pull requests.** In particular, do not post exploitable reproduction details, private patron records, credentials or private media files.

Preferred sequence:

1. Visit the repository's **Security** tab and look for the **"Report a vulnerability"** option (GitHub private vulnerability reporting), **if enabled**.
2. If that option is not available, use a verified private maintainer contact channel listed on the repository owner's profile or other official project communication channel.
3. If no private channel can be verified, do not post exploit details publicly; request a secure contact method **without describing the vulnerability** in a public issue.

No guaranteed response time or dedicated security address is established yet. Such commitments will be added only when a real support process exists.

### Information to provide privately

- Affected commit, branch, release and operating system.
- Vulnerability category, affected component and configuration.
- Impact on data confidentiality, integrity, availability, or rights.
- Minimal steps to reproduce, using **synthetic data** whenever possible.
- Expected and actual authorization/data behavior.
- Relevant logs sanitized of tokens, keys, personal information and content.
- Whether any real data or online installations have been exposed.
- Suggested mitigation, if available.

Do not test against installations without authorization. Avoid destructive payloads, service disruption, data exfiltration or accessing another user's content.

## 3. Intended security design

The following are **requirements**, not capabilities already implemented:

### Identity and authorization

- Default-deny access control with explicit actions, roles, resource scopes and ownership.
- Authorization at application-use-case boundaries, enforced equally for HTTP, UI, CLI, exports, search, files and background jobs.
- Protected credential storage and no secrets in source control or logs.
- Separate administrative capabilities from content access where practical.
- Audit meaningful security and circulation actions without collecting unnecessary personal data.

### Digital media

- Digital assets reside outside public webroots and are retrieved through controlled handlers.
- Uploads are untrusted: type inspection, size limits, path normalization, quarantine, checksum and malware-risk assessment where appropriate.
- Protected assets require rights-aware authorization for each request and generated derivative.
- Temporary files, cache entries, thumbnails and exports must not bypass protections.
- Uploading content is never implicit permission for public sharing or DRM circumvention.

### Data and storage

- Enforce database constraints/transactions for circulation and consistency.
- Separate account information, borrower history, inventory, catalog and digital access-rights records.
- Protect backups and export packages; verify restoration rather than assuming it worked.
- Favor private-by-default setup, explicit network exposure and transport security.
- Prevent path traversal, unauthorized overwrite, SSRF from provider URLs, cross-site request forgery and injection in all relevant contexts.
- Minimize retention of personal data and make deletion/export policies explicit.
- Protect integrity across DB schema changes, file writes and interrupted operations.

### Third-party services and extensions

- External metadata requests are optional and configured; access tokens are stored securely.
- External data and plugins are never trusted merely because they appear in a catalog provider.
- Future extensions need capabilities, resource limits, isolation and a compatibility policy.
- Avoid loading arbitrary untrusted native extensions in the central privileged process.
- Assess dependency vulnerabilities, supply-chain provenance, copyright and provider license terms.

### Logging and privacy

- No default telemetry or mandatory external cloud service.
- No credential values, API keys, full private content or sensitive member records in normal logs.
- Trace operations using safe internal identifiers and redacted errors.
- Define operator-facing retention, export and deletion rules; avoid unsupported compliance promises.

## 4. Threat-model examples

| Threat | Example | Intended control |
| --- | --- | --- |
| Broken object-level authorization | Guest guesses a private item's ID | Resource-level authorization on every fetch/query |
| Data leakage in search | Public OPAC indexes borrowers' notes | Separate approved public projection and test |
| Unauthorized file download | Webroot serves EPUB directly | Protected storage and access-gated file service |
| Unsafe upload | Archive/path traversal/malicious content | Validation, quarantine, limits, safe parsing |
| Duplicate loan | Two simultaneous checkouts | Atomic transaction and unique active-loan constraint |
| Metadata SSRF | Adapter fetches attacker-controlled local URL | Allowlisted provider endpoints and network controls |
| Insecure backups | Backup contains PII and e-books in public directory | Access-controlled storage and tested encrypted offsite copy where selected |
| Extension privilege escalation | Plugin accesses DB or secrets | Capability-based contract and isolation |
| Supply chain | Compromised build dependency | Dependency review, locked versions and reproducible builds when implemented |
| Broken migration | Upgrade corrupts inventory and references | Versioned migration plus verified rollback/restore |

Detailed trust boundaries and additional mitigations appear in [docs/architecture/ARCHITECTURE.md](docs/architecture/ARCHITECTURE.md).

## 5. Security release gates

Before a stable release, the maintainer should require:
- Tests that reject unauthorized member, asset, catalog, export and administrative access.
- Concurrent checkout tests proving at most one active loan per physical copy.
- Dependency and secret scans on an actual CI pipeline.
- Validated upload limits/types and protected file access.
- Successful backup and clean-install restore with integrity checks.
- Review of migrations and rollback implications.
- Explicit supported-platform and transport configuration guidance.
- A triage/disclosure channel and published handling expectations.
- Assessment of exploitable critical/high findings before release.

No security badge or audit result should be shown unless the audit was actually performed.

## 6. Responsible handling after a report

The maintainers intend to:
1. Confirm receipt through a secure channel when available.
2. Reproduce and classify the report without exposing reporter details.
3. Assess impact and affected versions/configurations.
4. Develop a minimal fix with regression coverage.
5. Coordinate remediation and release information.
6. Publish an appropriate advisory after affected operators have a reasonable mitigation opportunity.
7. Credit reporters with their consent.

This is a **process goal**, not a contractual service-level agreement.

## 7. Privacy and media rights

HARALD may catalog copyrighted works. The MIT license does **not** grant distribution rights to books, films, music, cover images, metadata provider databases or imported personal content.

HARALD must not be used to bypass DRM, pirate publications or convert legal possession of one physical disc into unrestricted digital redistribution. Privacy law obligations depend on deployment and organization; operators remain responsible for lawful processing, retention and access.

## 8. Security changes to this document

If an implemented authentication method, asset delivery mechanism, API, plugin system, disclosure route, supported-version table or security contact changes, update this policy with the same development/release change. Keep statements verifiable.

See also [AGENTS.md](AGENTS.md), [CONTRIBUTING.md](CONTRIBUTING.md), and the [test strategy](docs/testing/TEST_STRATEGY.md).
