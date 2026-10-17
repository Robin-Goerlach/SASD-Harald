# HARALD — C# Implementation Track

**Status:** Reserved directory, **not implemented**. There is no .NET solution, SDK pin, NuGet dependency, WinForms/WPF/web UI, or published executable here.

[All implementation tracks](../README.md) · [Multilanguage design](../../docs/architecture/MULTI_LANGUAGE.md) · [ADR-0001](../../docs/architecture/adr/0001-technology-stack-and-platforms.md)

## Purpose

This directory is reserved for an eventual C#-based HARALD backend, desktop UI, service, API client, command-line tool, or evaluation prototype **if approved**. No choice among .NET desktop, server, or native compilation has been made.

## Reserved folders

- `src/` — domain, application, adapters, host/UI code in a later idiomatic layout.
- `tests/` — unit, integration, architectural, contract and security tests as needed.
- `examples/` — small runnable examples, only after a real build exists.

The empty folders are present via `.gitkeep`. Do not create a fake solution or boilerplate "hello world" claiming that the application is ready.

## C#-specific questions before first production commit

- Which .NET version, SDK and lifecycle?
- Is this a standalone local app, an API service, or a client of another implementation?
- How are Windows deployment, self-contained runtime, NativeAOT and package sizes evaluated?
- Is the UI WinForms, WPF, Avalonia, web, or deliberately a separate application?
- How will domain assemblies avoid direct UI, HTTP, EF Core or database references?
- Which platforms are **actually** buildable and supported, including any planned BSD checks?
- What is the test framework, formatter, analyzer set and package license policy?

Do not depend directly on another SASD project without explicit architectural approval. Portable interchange should go through [shared contracts](../../shared/contracts/README.md), not through language-private ORM types.

## Initial proof

A testable **Work → Edition → two Physical Items** slice with stable IDs, distinct inventory barcodes, persisted relationships, an adapter boundary and failure cases. Write down real build/test commands when it exists.
