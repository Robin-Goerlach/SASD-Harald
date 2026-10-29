# HARALD — Umstieg von anderen Bibliotheksverwaltungssystemen

> **Dokument-ID:** HARALD-REQ-ADD-003  
> **Stand:** 2026-10-29  
> **Status:** Vorgeschlagene Anforderungen, **nicht implementiert und nicht als Releaseumfang freigegeben**  
> **Thema:** Einmalige und wiederholbare Übernahme aus einem **fremden Bibliothekssystem** (ILS) in HARALD  
> **Bezug:** [Pflichtenheft](Pflichtenheft_Open_Source_Multimedia_Bibliotheksverwaltung_2026.md), besonders IMP-002–010/016/019/020, CAT-001/014, LOC-001/005/009, CIR-001–009, IAM-*, DIG-*, [Roadmap M9](../../ROADMAP.md), [Teststrategie](../testing/TEST_STRATEGY.md) und [Backendwechsel](../architecture/STORAGE_PROVIDERS.md).

## 1. Ziel und Abgrenzung

Wer auf HARALD wechselt, soll möglichst **seinen vollständigen zulässigen Bestand** übernehmen können: nicht nur bibliografische Titel, sondern auch **alle einzelnen Exemplare**, Standorte, Zustände, Medienbestandteile und – nach gesonderter datenschutzrechtlicher und fachlicher Freigabe – Mitglieder, aktive Leihen und Vormerkungen. Ein bereits erfasstes Buch mit fünf physischen Exemplaren darf nicht auf *einen* Titeldatensatz mit nur einem vermeintlichen Exemplar reduziert werden.

Diese Anforderung präzisiert den bereits bestehenden R1-Import/-Export (IMP-002–010) sowie die späteren professionellen Adapter (IMP-016/019). Sie ist **keine** Anweisung, sofort alle Fremdsystemformate zu implementieren.

Vier Vorgänge bleiben strikt verschieden:

| Vorgang | Bedeutung | Nicht verwechseln mit |
| --- | --- | --- |
| **Fremdsystem-Übernahme** | Daten aus Koha, FOLIO, Evergreen, SLiMS, Calibre, Tellico, CSV usw. auf das HARALD-Modell abbilden | blindem Kopieren fremder Datenbanktabellen |
| **HARALD-Export/-Import** | Daten aus einem versionierten HARALD-Austauschformat einlesen | Fremdformatkonverter ohne Mapping |
| **HARALD-Storage-Migration** | Dieselbe HARALD-Bibliothek zwischen geprüften Backends (z. B. SQLite → PostgreSQL) bewegen | Aktivieren eines anderen Speicherprofils |
| **Schema-Upgrade / Backup-Restore** | Bestehendes HARALD-Datenmodell migrieren bzw. eine konsistente Installation wiederherstellen | fortlaufendem Fremdsystem-Sync |

**Nichtziel:** Direkter Schreibzugriff in die produktive Datenbank des alten Systems, ungeprüfte Zwei-Wege-Synchronisation oder stille Verschmelzung verschiedener Exemplare/Personen.

## 2. Priorisierung: nutzbarer Einstieg statt Konnektor-Sammlung

| Ausbaustufe | Vorschlag | Status/Abhängigkeit |
| --- | --- | --- |
| **R1 / M9** | Allgemeiner, offlinefähiger **CSV-/UTF-8-Import mit Zuordnung, Vorschau, Dry-run, Fehlerprotokoll**; versionierter **HARALD-JSON-Import/-Export**, IDs und Beziehungen erhalten | Bereits in IMP-002–010 gefordert; tatsächlich noch nicht implementiert |
| **R1 / M9** | Einfache **Migrationsanleitung**: Daten aus Altsystem exportieren, kontrolliert auf HARALD-CSV-Struktur abbilden, Exemplare verifizieren, sicher übernehmen | Teil der vorgeschlagenen Abnahme; kein neuer Fremdsystemtreiber |
| **Nach R1 (R2-Kandidat)** | Komfortabler **Importassistent** mit gespeicherten Mappingprofilen, Konfliktprüfung und möglichen Vorlagen für verbreitete CSV-Exporte | Abhängig von echten Migrationsbeispielen; keine V1-Pflichtänderung ohne Freigabe |
| **R3 gemäß IMP-016/019** | Spezifische Adapter z. B. Koha, FOLIO, Evergreen, SLiMS, Calibre/Tellico, MARC21/MARCXML/ISO-2709 | Nur bei realen Quellformaten/Testfixtures; Priorisierung später entscheiden |

**Wichtig:** MARC21-Bibliografiedaten beschreiben nicht automatisch alle Ausleihen, Mitglieder und Exemplarzustände. Holdings-/Item-Daten und Transaktionsdaten brauchen jeweils **einen gesondert geprüften Export und Abgleich**. Kein System wird ohne echten Test als „vollständig unterstützt“ beworben.

## 3. Fachliche Feldzuordnung und Identität

Ein Fremdimport muss ausdrücklich zwischen folgenden Ebenen unterscheiden:

| HARALD-Ziel | Typische Fremddaten | Kritische Migrationsregel |
| --- | --- | --- |
| `Work` | Titel, Alternativtitel, Urheber, Werkbeziehungen | Werkidentität nicht aus dem Titeltext allein ableiten |
| `Edition` | Auflage, Jahr, Format, Sprache, Verlag, ISBN/EAN | Gleiche ISBN oder gleicher Titel ist **kein** Beweis identischer Ausgabe |
| `PhysicalItem` | **Fremd-Item-ID**, Inventarbarcode, Standort, Eigentümer, Zustand, Sperre, Aussonderung | **Jedes einzelne Exemplar** erhält genau eine eindeutige HARALD-Identität |
| `ItemComponent` | Disc-/Band-/Beilagenlisten, Vollständigkeit | Teil eines Sets bleibt seinem Besitzer zugeordnet |
| `DigitalAsset` | Datei-/Asset-Verweis, Hash, Nutzungsrechte | Dateiübernahme nur nach Berechtigung/Integritätsprüfung, nicht durch bloße URL |
| `Member` / `UserAccount` | Mitglieds-ID, minimale Stammdaten, Kontostatus | Personen nur im autorisierten Sonderpfad; **keine Passwörter/Session-Tokens importieren** |
| `Loan` / `Hold` | Aktive Ausleihe, Fälligkeit, Vormerkung, Leihhistorie | Nur nach Prüfung, dass **Exemplar und Mitglied** eindeutig gemappt sind; nie zwei aktive Leihen pro Item |
| `Classification` / `CallNumber` / Location | Signatur, DDC-artige Notation, Regal, Zweigstelle | Klassifikation/Signatur und physischer Standort bleiben getrennt |

**Identitätsregel:** Fremd-IDs werden als `(source_system, source_instance, entity_type, source_id)` mit Provenienz zum HARALD-Datensatz geführt – niemals ungeprüft zu lokalen Primärschlüsseln. `ISBN` ist kein eindeutiger Item-Schlüssel. Barcodes können zwischen zwei Herkunftsbibliotheken kollidieren; Konflikte müssen vor der Übernahme entschieden werden, ohne automatisch eine inventarisierte Kopie zu überschreiben.

**Hinweis zum C++-Prototyp:** Er verwendet bislang SQLite-generierte Integer-IDs, nicht die später angestrebten backendübergreifend stabilen IDs. Die konkrete Migrations-/Crosswalk-Speicherung erfordert eine eigene Schema- und ADR-Prüfung.

## 4. Importquelle und Mapping

**Erste, überprüfbare Interchange-Stufe:** Dateien statt Quell-Datenbankzugriff. Offizielle Exportfunktionen bevorzugen; ein nötiger spezieller Exporter läuft am Altbestand **nur lesend** und mit eigener Berechtigung.

Ein einfacher Quellbestand kann beispielsweise aus drei durch Quell-IDs verknüpften CSV-Dateien bestehen:

```text
works.csv:    source_work_id, title, creator
editions.csv: source_edition_id, source_work_id, edition_label, isbn, format
items.csv:    source_item_id, source_edition_id, inventory_code, location, condition
```

Diese Spalten sind ein **unverbindliches Mappingbeispiel**, noch kein veröffentlichtes HARALD-Importformat. Ein vorhandener Ein-Datei-CSV-Export darf ebenfalls unterstützt werden; dabei muss die Zuordnung zu Werk, Ausgabe und einzelnem Exemplar **vorher** bestätigt werden. Wiederholte Titel-/Autor-Felder dürfen nicht zu einer stillen Zusammenführung unterschiedlicher Auflagen führen.

Eine JSON-Datei eines Fremdsystems ist **nicht automatisch** das versionierte HARALD-JSON-Austauschformat. Ein Quelladapter muss seine konkrete Version und Struktur identifizieren. MARC21 (bibliografisch/Bestandsdaten), MARCXML oder ISO-2709 sind spätere, gesondert zu testende Eingabeadapter; MARC-Bibliografie allein genügt nicht für die Inventar- oder Benutzerübernahme.

Offizielle Referenzen zur späteren Adapterprüfung:
- Library of Congress: [MARC21 Bibliographic](https://www.loc.gov/marc/bibliographic/) und [MARC21 Holdings](https://www.loc.gov/marc/holdings/).
- [FOLIO Data Import](https://docs.folio.org/docs/data-import/) beschreibt die Trennung von bibliografischen Datensätzen, Holdings und Items; diese externe Dokumentation bestätigt **keine** HARALD-Kompatibilität.

## 5. Vorschlag für den grafischen HARALD-Migrationsassistenten

```text
Quelldaten wählen → Herkunft/Version → Analysieren
                 → Feldzuordnung/Mappings prüfen
                 → Dubletten und Konflikte prüfen
                 → Vorschau/Dry-run + Verlustbericht
                 → Backup/Bestätigung/Übernahme
                 → Verifikation, Protokoll, Freigabe
```

Der Assistent soll einfach benutzbar, tastaturbedienbar und für größere Bestände paginiert sein; die **Prüfung findet unabhängig von der Oberfläche in der Application-Schicht** statt.

### Lebenszyklus eines Import-Jobs (konzeptionell)

1. **Inventur und Backup der Quelle:** Originalsystem, Version, Datenumfang, Zeitzone, Zeichensatz und Exportzeit dokumentieren; konsistente, lesbare Sicherung **vor** Migration behalten.
2. **Gesicherter Datei-Ingest:** Nur unterstützte Formate, Größen-/Datensatzgrenzen, UTF-8-/Encodingprüfung, sichere Pfade, schädliche Inhalte und Dateimanifest prüfen. Rohdaten außerhalb öffentlich lesbarer Verzeichnisse staging-gesichert behandeln.
3. **Normalisieren und zuordnen:** Technische Herkunftsdaten in vorläufige `Work/Edition/Item/...-Import-Drafts` überführen. Originalwerte + Mappingversion für nachvollziehbare Diagnose erhalten (mit Aufbewahrungs-/Datenschutzregeln).
4. **Fachliche Validierung:** Pflichtfelder, ISBN-Format je Typ, Exemplarbarcode, Status, Standort, Elternbeziehungen, Medienbestandteile und fehlende Referenzen melden. Unbekannte Werte **nicht** still verwerfen.
5. **Konflikte sichtbar machen:** Unterscheiden zwischen identischem erneutem Datensatz, tatsächlich anderem Exemplar, möglicher gleicher Ausgabe, Barcode-Kollision und widersprüchlichen lokalen Änderungen. Mögliche Dubletten nur vorschlagen; Administrator wählt `neu / zuordnen / überspringen / konfliktbehaftet`. Kein stilles „Last writer wins“.
6. **Dry-run:** Nichts im produktiven HARALD-Bestand ändern. Vorschau mit Zahlen für `neu`, `zugeordnet`, `übersprungen`, `Fehler`, `unklar`, `nicht übertragbar`; Export eines **geschützten** Verlust-/Konfliktberichts.
7. **Kontrollierte Übernahme:** Berechtigten Import bestätigen. Neue und existierende Daten nur über autorisierte Application-Commands, referenzielle/Transaktionsgrenzen und geeignete Batches übernehmen. Jeder Batch muss seine vollständige Eltern-/Kind-Konsistenz behalten; fehlgeschlagene Batches rollen zurück.
8. **Wiederholung und Abbruch:** Import-Job-ID, Quell-Fingerprint, Mappingversion und Source-ID-Crosswalk sorgen dafür, dass erneute Ausführung **keine doppelten Exemplare** erzeugt. Ein veränderter Export oder ein anderes Mapping gilt **nicht** automatisch als derselbe Job; Konflikt statt heimlichem Überschreiben. Wiederaufnahme nur am **verifizierten Commit-Checkpoint**.
9. **Nachkontrolle:** Quell- und Zielzahlen sowie Beziehungen/Inventarlisten, Zustands- und Standortverteilungen, nicht übertragene Felder und Prüfsummen vergleichen. Die alte Bibliothek bleibt bis zur Abnahme unangetastet.
10. **Produktivumschaltung:** Schreibfreeze und finaler konsistenter Export (ggf. Delta-Übernahme) mit klarer Cutover-Entscheidung, Wiederanlauf-/Rollbackstrategie und Nachweis, welches System fortan den autoritativen Bestand führt. **Keine unbemerkte Parallelbearbeitung beider Systeme.**

## 6. Datenschutz, Sicherheit und laufender Ausleihbetrieb

**Bibliografische Metadaten** sind der risikoärmste Einstieg. **Mitglieder, aktive Leihen, Historien, Kontaktdaten, Gebühren und Digitalrechte** benötigen getrennte Importfreigaben, Berechtigungskontrollen und datenschutz-/vertragsrechtliche Prüfung.

- Mitglieder dürfen nicht nur anhand eines Namens automatisch zusammengeführt werden. Konten werden neu angebunden; alte Passwörter/Passworthashes, Tokens, Sitzungscookies und API-Geheimnisse werden **nicht** übernommen. Neuausgabe/Zurücksetzen von Zugangsdaten erfolgt durch HARALD.
- **Aktive Ausleihen**: genau ein aktuell ausgeliehenes `PhysicalItem`, ein eindeutig zugeordneter `Member`, nachvollziehbares Leih-/Fälligkeitsdatum und stabile Referenz. Bei Mehrdeutigkeit: **Import blockieren und manuell klären**, nicht als ausgeliehen/ausleihbar erraten.
- Ein **ausgesondertes, gesperrtes, beschädigtes oder verlorenes** Item wird nicht als frei verfügbar importiert. Unbekannter Zustand ist prüfpflichtig, nicht automatisch „gut“.
- Leihhistorie und private Bemerkungen werden nur mit definiertem Zweck, Freigabe, Rollen, Verfalls-/Löschfristen und Audit übertragen. Ein Katalogimport darf nicht versehentlich personenbezogene Felder veröffentlichen.
- Ein physisch vorhandenes oder digital referenziertes Medium berechtigt **nicht automatisch** zur Weitergabe seiner digitalen Dateien. Übertragen werden nur erlaubte Assets/Metadaten mit Rechten und Integritätsnachweis.
- Staging, Diagnose und Exportberichte müssen mit den gleichen Schutzmaßnahmen wie ihre sensibelsten Quelldaten behandelt werden; Logs enthalten keine Credentials. Ressourcenbegrenzung verhindert speichererschöpfende oder schädliche Eingaben.

## 7. Konkrete Anforderungen und Abnahmefälle (neue Vorschlags-IDs)

| ID | Ziel / Vorschlag | Voraussetzung oder erwartetes Verhalten |
| --- | --- | --- |
| **MIG-001** | R1/M9: Eingabe als dokumentierte CSV-UTF-8-/HARALD-JSON-Daten, in einer isolierten Staging-Phase | Kein Fremdformat wird ohne definiertes Mapping als kompatibel ausgegeben. |
| **MIG-002** | R1/M9: Import bewahrt Werk–Ausgabe–Exemplar-Relationen und identifiziert **jedes einzelne Inventarexemplar** | Gleiche Ausgabe mit drei Exemplarbarcodes ergibt drei Items. |
| **MIG-003** | R1/M9: Quellidentitäten werden typisiert mit `source_system/instance/id` nachvollziehbar zugeordnet | Identische ISBN ist keine automatische lokale Identität. |
| **MIG-004** | R1/M9: Dry-run, Prüfreport, Konflikt-/Verlustübersicht **vor** jeder Änderung | Fehlerhafte Dateien ändern die Bibliothek nicht. |
| **MIG-005** | R1/M9: explizite Benutzerfreigabe bei Konflikten, keine destruktiven Auto-Merges | Bestehende lokale Titelkorrektur bleibt ohne Zustimmung erhalten. |
| **MIG-006** | R1/M9: transaktionale Teilbatches, wiederanlaufbare, idempotente Import-Jobs | Abbruch nach Batch 3 und Wiederholung erzeugt keine Dubletten/Teilaggregate. |
| **MIG-007** | R1/M9: Importabschluss vergleicht Zahlen und Beziehungen mit Prüffeldern | Nicht übernommene Felder sind gelistet, keine falsche Erfolgsmeldung. |
| **MIG-008** | R1/M9: Eingabebegrenzung/Encodingprüfung/Datenschutz und rollenbasierter Adminimport | Unberechtigte Person kann keinen Bestand ersetzen oder Personendaten exportieren. |
| **MIG-009** | R2-Kandidat: geführter Importassistent mit gespeicherten, versionierten Feldmappings | Ein Importprofil kann wiederverwendet werden, ohne neue Regeln zu erfinden. |
| **MIG-010** | Nach Basiskern: Mitglieder und aktive Leihen als **gesondertes genehmigtes Verfahren** | Kein neuer aktiver Loan ohne eindeutiges Item-/Mitgliedsmapping und Transaktionsinvariante. |
| **MIG-011** | R3 gemäß IMP-016/019: konkrete Altsystem-/MARC-Adapter | Adapter nennt exakt geprüfte Exportversionen und unterstützte Felder. |
| **MIG-012** | Vor produktivem Umstieg: gesicherter Cutover, letzte Differenzen, Restore-/Fallbackplan | Quell-Backup und überprüfbarer Zielzustand bleiben bis zur Abnahme verfügbar. |

**MIG-AT-01 — Mehrfache identische Exemplare:** Zwei Datensätze derselben Ausgabe mit drei Exemplaren (separaten Barcodes, Standorten und Schäden) importieren; alle drei Items bleiben unabhängig, auch nach Neustart.

**MIG-AT-02 — Ausgabe vs. ISBN:** Zwei unterschiedliche Editionen mit gleicher oder fehlender ISBN bleiben korrekt unterscheidbar; Dublettenhinweis darf nicht automatisch verschmelzen.

**MIG-AT-03 — Quellen-Kollision:** Zwei Fremdbibliotheken nutzen `000123` als Barcode. Import meldet Konflikt und verändert keine bereits inventarisierte Kopie.

**MIG-AT-04 — Wiederholung:** Identischen Export zweimal importieren; zweiter Lauf legt keine weiteren Werke, Ausgaben oder Items an und berichtet „bereits verarbeitet“.

**MIG-AT-05 — Teilfehler:** Strom-/Speicher-/Transaktionsfehler in einem Batch; kein partielles Work–Edition–Item-Aggregat. Fortsetzung ab echtem Commit-Checkpoint.

**MIG-AT-06 — Dry-run:** Voransicht zeigt Zahlen und Fehler, erzeugt im Ziel jedoch keine fachlichen Änderungen.

**MIG-AT-07 — Verlustbericht:** Unbekannter Zustand, fehlender Autor oder proprietäres Feld wird zugeordnet, erhalten oder ausdrücklich als Verlust markiert – niemals still verworfen.

**MIG-AT-08 — Datenschutz:** Gast-/Katalogimport kann keine Mitglieder-, Historien-, Konto- oder Geheimnisdaten einlesen bzw. offenlegen.

**MIG-AT-09 — Aktive Leihen:** Autorisierter Sonderimport weist Item und Member eindeutig zu; unklare Referenz oder paralleler aktiver Loan stoppt den betroffenen Batch ohne Phantom-Verfügbarkeit.

**MIG-AT-10 — Zustandsprüfung:** Verlorenes/gesperrtes/ausgesondertes Exemplar wird nicht plötzlich ausleihbar; ein gutes Exemplar derselben Ausgabe bleibt verfügbar.

**MIG-AT-11 — Encoding/Größe:** Nicht-ASCII-Titel, CSV-Trennzeichen/Zeilenumbrüche, ungültige UTF-8-Bytes und übergroße Eingaben werden deterministisch erhalten, berichtigt oder sicher verworfen.

**MIG-AT-12 — Cutover:** Ein Vollabzug plus finaler Delta-Abzug wird nur nach Stilllegung der Quelle und geprüftem Abgleich freigegeben; ein Fehlschlag lässt die originale Bibliothek weiterhin wiederherstellbar.

## 8. Architekturvorgabe ohne vorschnelle API-Festlegung

```text
Quellsystem-Export (lesend)
          |
    SourceImporter (formatbezogener Adapter)
          |
    Normalized Import Staging + Source Identity Crosswalk
          |
    Validation / Conflict Planner / Dry-run
          |
    Authorized Import Application Use Cases
          |
    Domain and persistence ports
          |
    SQLite (zuerst) / weitere geprüfte Adapter
```

- **Domain:** Regeln über `Work`, `Edition`, `PhysicalItem`, `Loan`; kennt weder MARC-Parser noch CSV noch UI noch SQLite.
- **Application:** Import-Jobs, Sicherheit, Mappingfreigabe, atomare Fachtransaktionen, Idempotenz, Audit und Wiederaufnahme.
- **Infrastructure:** Adapter für Fremdformate, isoliertes Staging, konkrete SQLite- und spätere Storage-Treiber.
- **Presentation:** Dashboard, Mappingtabelle, Fehler-/Dubletten-Review und Abschlussbericht im SASD UI Toolkit; nur Application-Fassade aufrufen.
- Kein generischer Cross-System-DB-Treiber und kein Plugin-Framework, solange der erste CSV-Import nicht als Vertical Slice nachgewiesen ist.
- Für komplizierte Übernahmen (Leihen, Personen, große Datenmengen, Verschmelzung mit existierenden HARALD-Beständen) sind konkrete Transaktions-, ID- und Wiederanlaufverträge **vor Implementierung** als Proposed ADR oder geprüfte Spezifikation zu dokumentieren. Bestehende `ADR-0004` bleibt Proposed.

## 9. Kleinster nächster überprüfbarer Vertical Slice

1. Ein synthetischer, kleiner **3-Datei-CSV-Export** mit einem Werk, einer Ausgabe und **drei unterschiedlich erhaltenen Exemplaren**; absichtlich zusätzlich ein fehlerhafter Barcode und eine unklare Ausgabenzuordnung als negative Fälle.
2. Reiner **UTF-8-CSV-Leser + Import-Vorschau** mit isolierten Datentypen und Testfällen; keine bestehenden echten Bibliotheksdaten ändern.
3. Explizites Mapping zu `BookDraft` und Kopien; keine ISBN=Identität-Annahme. Bestehende C++-API kann derzeit noch **keinen** Zustand speichern, daher nachweislich **nicht** so tun, als sei Zustandsmigration vollständig. Zustand erst nach gesicherter Item-Schema-Erweiterung tatsächlich importieren.
4. Darauf aufbauend geprüfte `CatalogService`-Anwendungsfälle verwenden; negative Tests für Barcode-Konflikt, Querverweise, Abbruch und erneuten Import.
5. Erst nach sicherem Backup, Migrationsschema und Testnachweis mit produktivem Übernahmeassistenten werben.

**Produktentscheidung offen:** Welche konkreten Quellsysteme müssen wir als erste unterstützen? Es ist sinnvoll, **echte anonymisierte Beispiel-Exporte** der wichtigsten Kandidaten zu vergleichen, bevor wir einen speziellen Parser priorisieren. Exakte Versions-/Exportformat-Kompatibilität wird erst nach Tests zugesagt.
