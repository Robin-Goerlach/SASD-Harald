# HARALD — Self-service checkout and return (requirements proposal)

> **Document ID:** HARALD-REQ-ADD-002  
> **Date:** 2026-10-29  
> **Status:** Proposed functional addendum; **not implemented or approved for a release**  
> **Scope:** Physical-item loans and returns without a librarian at the moment of the action  
> **Baseline:** [Pflichtenheft](Pflichtenheft_Open_Source_Multimedia_Bibliotheksverwaltung_2026.md), especially CIR-001–009, IAM-*, LOC-*, SEC-* and AT-007–009.  
> **Dependency:** Working staff-operated circulation (M7), authentication/authorization (M6), item-level condition tracking and a safely exposed application service.

## 1. Motivation and terminology

Readers should eventually be able to borrow and return physical media **without requiring a staff member to execute the transaction**. This is *self-service circulation* and differs from simply reserving a title online.

There are at least three separate access channels:

| Channel | Example | What is established |
| --- | --- | --- |
| **Self-checkout on site** | Authenticated library kiosk with barcode scanner | A reader initiates checkout of a specific item in the library. A barcode scan alone is **not** proof that the reader legitimately obtained the item. The deployment must establish suitable access/hand-off controls. |
| **Mobile/web self-checkout** | Signed-in reader with phone | The same use case may be offered only when the deployment can establish authorized collection/possession (e.g. controlled pickup). A remote reader knowing a printed barcode is **not** sufficient. |
| **Self-return / self-check-in** | Controlled return terminal, secured drop box or member portal | Declaring an intention to return, recording physical receipt, and completing condition inspection are **distinct events**. A web button from home is not proof of physical return. |

**Key distinction:** A reader-initiated checkout is a real loan only after the trusted HARALD application confirms entitlement, specific physical item and any required handover condition. A reader-initiated online return notification is **not automatically** a completed return or newly available inventory.

The online transport is a *future* implementation option, not a commitment to a browser UI, publicly reachable service or mandatory cloud. HARALD must remain usable offline for ordinary catalog and staff circulation.

## 2. Proposed user journeys

### 2.1 On-site self-checkout

1. Reader authenticates to an enabled self-service kiosk or approved client.
2. Reader scans the **item inventory barcode**, not its ISBN/EAN or the edition ID.
3. HARALD displays minimal authorized item details and the loan's due date.
4. The trusted use case validates identity/membership status, limits, holds, item availability/condition, and that this channel is authorized to perform a handover.
5. Reader confirms. A transactional, idempotent checkout creates **one** active loan for the specific item.
6. The client shows an explicit success/failure and an optional privacy-safe receipt. Kiosk sessions expire and clear the next reader's personal data.

If reliable self-service handover conditions cannot be established, the channel must offer a **pickup request/hold** instead of automatically creating a loan.

### 2.2 Reader-operated return terminal

1. Reader scans the physical item's barcode at an approved intake point.
2. HARALD records a return intake **only with trustworthy evidence of physical receipt** appropriate to the installation. A scan or click by itself is not sufficient.
3. If condition/components can be inspected as part of a controlled process, authorized completion closes the loan and determines whether the item is available, held for another reader or blocked.
4. If condition verification is outstanding, the item enters a **pending inspection/quarantine** workflow and is **not lendable**. The treatment of the reader's loan and due date must be defined by policy without claiming verification that did not occur.
5. The reader receives a confirmation that accurately names the accomplished state: `return announced`, `physically received / pending inspection`, or `return completed`.

A drop box may use an intake receipt plus later staff reconciliation. If physical custody cannot be trusted yet, it is only a return announcement; the system must not prematurely make the item available.

### 2.3 Online return announcement (away from the library)

The reader may report an intended drop-off or request help, but **may not complete a physical return from home** by selecting an item in a web portal. HARALD records a pending announcement and instructions for the actual handover; the loan remains subject to the documented return policy until trusted intake. An operator can resolve a dispute using intake evidence without relying on a client-controlled timestamp.

## 3. Proposed requirements (new IDs, not silently added to R1)

| ID | Proposed priority | Requirement | Acceptance |
| --- | --- | --- | --- |
| **SSC-001** | Candidate R2 | Enable self-service circulation only per authorized library/channel; default disabled. | Fresh installation cannot borrow or return via an unauthenticated public endpoint. |
| **SSC-002** | Candidate R2 | Self-checkout associates the authenticated member with **one scanned physical-item identity**; never accepts arbitrary target member or edition ISBN as inventory identity. | Another member's ID or ISBN/EAN cannot be submitted as a legitimate checkout. |
| **SSC-003** | Candidate R2 | Reuse staff circulation policy, transactional invariants and authorizations; self-service actor has narrower permissions. | Blocked, lost, reserved-for-another-reader, incomplete or already-loaned item cannot be self-checked out. |
| **SSC-004** | Candidate R2 | An authorized handover/possession policy gates final checkout, particularly for remotely reachable clients. | Knowing/scanning a visible barcode remotely does not suffice to borrow stock from the shelf. |
| **SSC-005** | Candidate R2 | Make a remote return *announcement*, proven physical *intake*, and completed *return/inspection* distinct steps. | Portal-only click does not close a loan or change availability. |
| **SSC-006** | Candidate R2 | Pending inspections are not lendable; condition and missing components can block the specific item only. | Returned damaged copy is not available while healthy copies of the edition remain unaffected. |
| **SSC-007** | Candidate R2 | Repeated/competing requests are idempotent or rejected as conflicts; record immutable relevant audit context without exposing other readers. | Two simultaneous mobile/kiosk requests produce at most one active loan. Network retry cannot create two returns. |
| **SSC-008** | Candidate R2 | Clear kiosk sessions and sensitive information automatically; apply rate limits, secure session and token handling and minimal visible PII. | Subsequent kiosk user cannot view predecessor's account or receipt. |
| **SSC-009** | Candidate R2 | Clearly show success, rejection and pending states, with accessible and scanner-friendly interactions. | No pending return is displayed as `completed`; an interrupted connection has a recoverable result. |
| **SSC-010** | Candidate R2 | Reconcile deposit time, late fees/due-date policy and disputed intake transparently using trusted evidence. | Delayed staff inspection does not silently impose a false "late" return; a fabricated client clock cannot backdate receipt. |
| **SSC-011** | Candidate R2 | Define acceptable offline behavior of a kiosk; no uncoordinated offline authoritative loans. | During disconnection it refuses final checkout or queues only non-authoritative requests until the server validates them. |
| **SSC-012** | Candidate R2 | Staff can inspect, reconcile and resolve pending returns through authorized workflows, with audit evidence. | A missing/damaged drop-box item is not silently marked available or deleted. |

## 4. Architecture and security

- All clients (staff desktop, kiosk, mobile and possible remote HARALD REST) call **the same application use cases**. No separate kiosk-only loan table, direct client SQL, browser credentials or bypass of core circulation policies.
- Application-side authorization distinguishes `circulation.self_checkout`, `circulation.return_announce`, `circulation.intake`, and `circulation.return_complete` as **conceptual** permissions; these strings are not yet a stable published API.
- The authenticated reader and session are derived from the trusted security context; a request payload cannot select a different borrower. Dedicated kiosk/device identities are constrained separately.
- SQLite/other storage must enforce the one-active-loan-per-item invariant under concurrency. Multi-step returns have explicit, versioned transitions; no second active loan while inspection is pending.
- Avoid charging a reader for a staff inspection delay by retaining evidence of confirmed custody and configurable policy. Do not equate a remote announcement with custody.
- The public-facing interface must not expose other borrowers, internal damage notes, credential details, or unapproved catalog contents.
- QR codes, barcodes and RFID can be **input devices/identifiers**; they are never, by themselves, authentication or reliable physical handover evidence. Hardware integrations (RFID/SIP2) remain separately optional and are not required for the conceptual feature.
- Request IDs/idempotency tokens must be bound to actor, item and operation. Failed acknowledgments are resolved by querying the authoritative result, not by generating an unrelated retry.
- No assumption that REST, online authentication, controlled gates or automated drop boxes exist in the current C++ prototype.

## 5. Acceptance scenarios to automate after prerequisites

**SSC-AT-01 – Successful on-site loan:** Authenticated reader borrows available `INV-101`; due date and loan owner are correct, staff loan logic remains reusable.

**SSC-AT-02 – Ineligible/impersonated loan:** Account A attempts to borrow for account B; member suspension, unapproved pickup, competing hold or item damage prevents loan without stock mutation.

**SSC-AT-03 – Barcode without possession:** Remote caller knows `INV-101` barcode but no trusted handoff. No real active loan is created.

**SSC-AT-04 – Simultaneous requests:** Kiosk and staff/mobile attempt to borrow the same copy. Exactly one checkout succeeds; retry is stable.

**SSC-AT-05 – Remote "return" click:** Reader presses Return at home. A pending announcement is stored, but loan/physical availability are not falsely completed.

**SSC-AT-06 – Controlled intake:** The return point confirms receipt of `INV-101` while inspection is pending; item cannot be issued to the next reader. Later completion reconciles the loan and status according to policy.

**SSC-AT-07 – Damage and sibling isolation:** After drop-box inspection, `INV-102` is damaged and blocked. `INV-101` remains independently lendable.

**SSC-AT-08 – Fault and repeated scan:** Lost acknowledgment, repeated scanner input, DB rollback and offline kiosk do not duplicate loans/returns or expose inconsistent availability.

**SSC-AT-09 – Session privacy:** Idle kiosk clears sessions, account data and receipts; another reader cannot impersonate the previous one.

**SSC-AT-10 – Audit and fairness:** Proven drop-off time is recorded separately from staff inspection, not sourced from the reader's device clock. Disputes can be investigated by authorized personnel.

Tests require an actual circulation model, a controlled physical-intake simulation, an authorization context, transaction/concurrency tests and a UI/transport boundary. Documentation-only review does **not** satisfy these tests.

## 6. Proposed sequencing and open product decisions

1. Complete and harden **M6 identity/authorization** and **M7 staff-operated lending/returns** with per-copy conditions, holds and concurrency.
2. Implement a tiny **authenticated on-site self-checkout pilot** using the existing application service and one credible handover policy.
3. Add intake/pending-inspection states and prove that pending items stay non-lendable and return timestamps are fair.
4. Reuse the same contracts for kiosk/mobile/web only after security and physical control scenarios pass.
5. Decide whether the feature becomes part of R1 or stays an **R2 enhancement**. This document **proposes R2** to avoid silently increasing the original R1 scope. The maintainer must approve any reclassification.

**Open:** Which deployment modes are wanted first (library kiosk, reader phone on site, authenticated external portal)? What constitutes verified handover/intake in the target library? Are self-service returns after hours required? Which items/reader groups qualify? How are pending returns and due dates treated? These choices affect security and acceptance and must be resolved before code commits claiming the feature.
