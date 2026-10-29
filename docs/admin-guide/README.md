# HARALD — Administrator Guide (Planned)

> **No deployable HARALD application exists yet.** This is the outline of a future verified administrator manual and must not be interpreted as working setup instructions.

## Planned administration topics

- Supported OS/runtime versions and exact installer/package prerequisites.
- Secure initial bootstrap, local-only defaults, administrator recovery.
- Optional LAN access: authentication, HTTPS, firewall, trusted proxy configuration.
- Roles, resource permissions, member privacy and retention.
- Library identity, physical locations, media policy, loan periods and limits.
- Physical-item condition categories, inspection/audit policy, restricted-item release and reasoned **individual copy withdrawal**, not title deletion.
- Optional future self-service configuration: handover/intake proof, kiosk session timeouts, disabled-by-default channels, receipt and inspection rules.
- Database initialization, schema migrations and supported concurrency.
- Protected asset storage, capacity planning and integrity scans.
- Optional provider credentials, consent, caching and quotas.
- Catalog export/import and safe migration from previous software: source format/version, owner-qualified source IDs, per-copy identity, field mapping, staging, dry-run, unknown-field/conflict/loss report, checkpointed reruns and verified cutover.
- Any member and active-loan migration as a **separately authorized data-protection workflow**; no silent import of old login secrets or public exposure of personal data.
- Consistent database **and** asset backups, retention and test restores.
- Upgrade and rollback planning with version compatibility.
- Logging, audit record access, troubleshooting and incident response.
- Optional external clients, provider adapters, plugins and their permission boundaries.
- Verified operational health reports and performance limits.
- Public catalog configuration (future), protecting sensitive and licensed assets.

See [Operations Plan](../operations/OPERATIONS.md), [Security Policy](../../SECURITY.md), [API Plan](../api/README.md) and [Roadmap](../../ROADMAP.md).

A future stable release **must replace this outline** with version-specific tested commands, screenshots from working software, failure/recovery steps and cross-platform installation evidence.
