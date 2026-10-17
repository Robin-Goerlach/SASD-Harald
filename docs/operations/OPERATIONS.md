# HARALD — Operations, Backup, Restore and Upgrade Design

> **Status:** Proposed operations plan (2026-10-17). HARALD has **no executable server, installer or backup command** yet. No procedure below should be mistaken for a working administrative instruction.  
> Related: [README](../../README.md), [Architecture](../architecture/ARCHITECTURE.md), [Roadmap](../../ROADMAP.md), [Security Policy](../../SECURITY.md).

## 1. Operating profiles and responsibilities

HARALD is designed primarily for a local personal collection and a small home, club or school library. Hosting must remain manageable without a mandatory cloud service.

| Proposed profile | Intended user | Operational concerns |
| --- | --- | --- |
| Personal local | One user on a workstation | Local data ownership, safe filesystem permissions, automated or manual backups |
| Small LAN server | Family, club, school, small library | Accounts, authentication, HTTPS/proxy, shared transactions, recovery |
| Headless | Scripts and external clients | Secured API/CLI, documented versions and configuration |
| Public discovery (later) | OPAC, read-only guests | Strong isolation of public metadata from private catalog/member/assets |
| Larger institutional (later) | Multi-site environments | Stronger database, policy, deployment and compliance controls |

There is currently **no selected runtime, port number, Docker image, service unit or installer**. Do not manufacture examples that look executable.

### Roles

- **Owner/administrator:** manages upgrades, backups, credentials, storage and recovery.
- **Catalog/inventory user:** manages catalog and copies but should not automatically have host-level permissions.
- **Circulation user:** manages members and loans within granted scope.
- **Reader/guest:** accesses only authorized catalog views, own loans and permitted digital assets.
- **Service integration:** receives narrowly scoped permissions.

Operating system administrator permissions and HARALD application roles must not be conflated.

## 2. Configuration model (design target)

A versioned configuration schema should be published **after** a stack is selected. It should identify:
- Application identity, supported instance type and locale.
- Network listen interface, canonical origin, TLS/proxy trust configuration.
- Database driver/location and relevant concurrency constraints.
- Private asset root outside the public webroot; quotas and file-type policies.
- Session/authentication and account bootstrap method.
- Default-deny public discovery and digital distribution settings.
- External provider enablement, network timeout/rate limits and secret references.
- Backup destination, schedule, retention, encryption and restore requirements.
- Logs, audit retention, privacy settings and diagnostics.
- Feature flags for optional integrations.

**Never put credentials or access tokens in a committed configuration sample.** An example of a setting is not proof it is implemented.

## 3. Installation and supported platforms

Before any production release, publish for each supported OS:
1. Exact runtime/compiler/OS version prerequisites.
2. Download/verification of signed/checksummed artifacts where applicable.
3. Installation and first-run initialization.
4. Local-only defaults, secure admin bootstrap and optional network access.
5. Configuration of database and protected assets.
6. Migration from earlier supported versions.
7. Service execution model and platform service registration if needed.
8. Firewall/TLS/proxy guidance for non-local access.
9. Backup before opening the instance to users.
10. Uninstall/reinstallation without accidental deletion of user data.

Do not claim that Windows has no external runtime requirement until package/install testing proves it. FreeBSD/OpenBSD remain evaluation targets unless/ until an explicit release provides tested support.

## 4. Storage layout and invariants

The durable logical components should include:
- **Database:** catalog, links, physical items, loans, accounts/rights and relevant configuration.
- **Protected asset store:** original authorized digital files, not served through static paths.
- **Manifest:** content-addressed or checksum-linked inventory of assets and storage versions.
- **Schema migration state:** applied version and recovery notes.
- **Operator configuration:** versioned non-secret settings plus references to secret storage.
- **Indexes/caches:** rebuildable artifacts, not a replacement for authoritative state.
- **Audit/history:** events with retention/access controls appropriate to the installation.

Changes involving multiple durable resources (DB + filesystem) require explicit retry/compensation semantics. A database transaction alone does **not** make arbitrary filesystem writes atomic.

## 5. Backup design

A backup is only successful if the complete application state can later be restored.

### Minimum contents

1. Consistent database snapshot including schema/migration metadata.
2. Every required original asset referenced by the snapshot.
3. Versioned manifest with item/file counts, identifiers, sizes and cryptographic checksums.
4. Explicit description of configuration and recovery of **secrets/keys** (secrets should not be accidentally stored in plaintext archives).
5. Software version and export/backup schema version.
6. Validation report and durable success/failure marker.

Optional reproducible previews and indexes can be omitted **only when rebuilding them is documented and tested**.

### Proposed backup phases

1. Check available destination space, configured retention and permissions.
2. Establish a consistent snapshot protocol that coordinates database state and asset manifest.
3. Read the database using its supported online/snapshot facility (never assume copying an active SQLite file is safe).
4. Transfer all referenced assets with checksum verification.
5. Produce and validate the manifest.
6. Mark backup complete **only after all components verify**.
7. Protect the result (access controls and encryption when appropriate); replicate to independent storage.
8. Test a restore periodically and record results.

For SQLite, the actual strategy may use the Backup API or approved snapshot approach, but must match application state and be tested. A PostgreSQL adapter would need its own procedure.

### Backup failure behavior

- Never replace the last verified successful backup with an incomplete one.
- Incomplete snapshots remain explicitly marked failed and are not used as successful restore candidates.
- Report missing assets, corrupt manifests, invalid checksum, permission failure, out-of-space and incompatible schema.
- Never silently omit borrower permissions or asset rights because they are harder to export.
- Cleanup jobs must preserve retention and not delete the sole viable backup.

## 6. Restore design

**Restore is the actual deliverable; backup creation alone is insufficient.**

Proposed safe sequence:
1. Identify compatible application/database/asset schema versions.
2. Create/prepare a **clean target** (or isolate an existing instance).
3. Validate archive content, hashes and read privileges before writing.
4. Restore database, protected assets and required configuration/key material securely.
5. Check referential integrity, item/loan consistency, asset checksums and file access rights.
6. Rebuild derived search indexes if they are not part of the backup.
7. Exercise smoke tests: login, catalog find, item status, active loans, authorized asset fetch and denied private fetch.
8. Provide a success report naming source backup and destination version.
9. Start/enable production access only after validation passes.

A failed restore must leave the target **not ready** and explain whether it can be safely retried or must be recreated. Do not "fix" partial restoration by silently inventing missing items/files.

### Recovery objectives

**RPO/RTO are not yet committed numbers.** They depend on operator profile, storage, backup frequency and measured restore time. Define product defaults and administrator guidance after repeatable test results.

## 7. Upgrades and schema migrations

- Schema versions and binary versions are distinct; do not assume a binary downgrade reverses a schema upgrade.
- Publish supported upgrade paths, known breaking changes and required free space.
- Take a verified backup before destructive or irreversible migration.
- Stop incompatible concurrent writers for migration where required.
- Keep migrations repeatable/idempotent or explicitly one-time with recorded state.
- On migration failure: stop, report, and follow an approved restore path.
- Only update public APIs or export schemas with a documented compatibility and migration plan.
- Avoid requiring online external providers during schema upgrades.
- Record test evidence for upgrade from every supported older version.

## 8. Integrity monitoring and diagnostics

Planned authorized diagnostics:
- Database schema version and migration health.
- Orphaned/broken item relationships and duplicate inventory codes.
- Assets missing on disk or mismatched hashes.
- Deferred indexing/jobs backlog and last successful completion.
- Backup freshness, last successful restore drill and known warnings.
- Unauthorized access attempt signals without leaking contents or borrower identities.
- Optional storage quotas, disk pressure and scan error metrics.

Diagnostics must never expose credentials, library patron history, protected filenames or digital content to unauthorized users.

## 9. Network exposure

- Default to private local access; any external binding must be explicit.
- Authentication required for non-public operations; non-loopback secrets and sessions need appropriate TLS.
- Do not blindly trust forwarded headers or arbitrary reverse proxies.
- Limit upload sizes, request concurrency and external provider destinations.
- Protect against brute-force login, abuse of public search, enumeration and mass data export.
- Public OPAC projections must have separate authorization and carefully selected data fields.
- Audit changes to account roles, file rights, backups and public visibility.
- Document network topology and firewall assumptions for actual supported deployment.

## 10. Troubleshooting and incident workflow

When the application is eventually available, each incident report should capture:
- Version/commit, OS/runtime, database and deployment profile.
- Recent upgrade/migration or config changes.
- Observable symptoms, correlated safe logs, scope of affected data.
- Whether to stop writes to preserve integrity.
- Snapshot and restore viability before attempting risky repair.
- Failed and successful actions and follow-up tests.

Never recommend destructive SQL or filesystem operations before an operator has a verifiable backup, an assessed recovery path and an explicit reason.

## 11. Disaster and fault scenarios to test

- Crash during checkout.
- Crash after digital asset write but before metadata commit.
- Failed migration or partially applied database schema.
- Corrupt backup manifest and missing asset file.
- Source filesystem becomes full during import.
- Unreachable external metadata provider.
- A revoked user trying to access a previously indexed asset.
- Unexpected duplicate barcode during inventory.
- Backup restore on a different supported operating system.
- Expired credentials or unavailable notification service.

Each scenario should yield a documented diagnostic and no unjustified "success" state.

## 12. Operations release gate

Before a stable R1:
- [ ] Supported installation profiles have tested instructions.
- [ ] Default security configuration is appropriate for local and LAN use.
- [ ] Backup and clean-install restore have automated and manual evidence.
- [ ] Upgrade/migration and failure recovery are verified.
- [ ] Logging/auditing redacts sensitive information.
- [ ] Protected files cannot be fetched from the static file server.
- [ ] Installer/package/license information is accurate.
- [ ] Release notes list required admin steps and known constraints.
- [ ] Operational runbooks use **real** commands from the selected stack.

**This document is a design checklist, not an operational how-to for a product that does not exist yet.**
