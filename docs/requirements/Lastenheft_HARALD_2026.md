# HARALD — Lastenheft (Bedarf und Nutzungsziele)

> **Dokument-ID:** HARALD-LH-001  
> **Version:** 0.1, Entwurf vom 29.10.2026  
> **Status:** Anforderungen aus den Projektgesprächen erfasst; **noch keine formale Release-/Produktfreigabe**  
> **Geltungsbereich:** Open-Source-Bibliotheks- und Multimedia-Sammlungsverwaltung HARALD  
> **Quelle:** Projektgespräche vom 29.10.2026, bisheriges [Pflichtenheft](Pflichtenheft_Open_Source_Multimedia_Bibliotheksverwaltung_2026.md), [Roadmap](../../ROADMAP.md) und drei Detailkonzepte.  
> **Rollenverständnis:** Dieses Lastenheft beschreibt **was** Bibliotheksbetreiber und Mitglieder benötigen und **warum**. Implementierungsdetails und technische Nachweise gehören zum Pflichtenheft bzw. zur Architektur.

## 1. Ausgangslage und Nutzen

HARALD soll nicht nur Titel erfassen, sondern einen wirklich vorhandenen Bibliotheksbestand verlässlich verwalten. Bibliotheken besitzen oft mehrere **physisch eigenständige Exemplare derselben Ausgabe**. Diese Stücke altern unterschiedlich, können getrennt verliehen und beschädigt werden und müssen bei Bedarf einzeln ausgesondert werden können.

Mittelfristig sollen Mitglieder Bücher auch **ohne unmittelbar anwesendes Bibliothekspersonal** ausleihen und zurückgeben können, sofern die Übergabe bzw. Rücknahme nachweisbar und der Vorgang sicher ist.

Ein Wechsel von bestehenden Bibliotheksverwaltungssystemen soll ohne manuelle Neueingabe des gesamten Bestandes möglich sein. Fehlende oder unvereinbare Daten müssen **vorher sichtbar**, nicht still verloren gehen.

Übergreifendes Ziel ist eine **alltagstaugliche, nachvollziehbare, nicht überladene Bedienung** für Katalogisierung, Ausleihe, Inventur und spätere Migration. Das System soll lokal/offline nutzbar bleiben; öffentliche Internetdienste sind optional und niemals Voraussetzung für die Grundverwaltung.

## 2. Nutzergruppen

| Gruppe | Erwarteter Nutzen |
| --- | --- |
| Bibliotheksleitung / Betreiber | Zuverlässige Bestandszahlen, Umzug ohne unbemerkten Datenverlust, kontrollierte Aussonderung |
| Bibliotheksmitarbeiter / Inventarisierer | Schnelle Identifikation per Exemplarbarcode, einfache Zustandsprüfung bei Rückgabe |
| Bibliotheksmitglied | Klare Ausleihfristen, spätere Selbstbedienung, nachvollziehbare Rückgabequittung |
| Administrator / Migrationsverantwortlicher | Prüfbarer Import mit Konfliktvorschau, Berechtigungen, Wiederanlauf und Abnahmebericht |
| Private Sammler / kleinere Einrichtungen | Wenig Pflichtfelder, geringer Betriebsaufwand, freie Datenhoheit |

## 3. Funktionale Bedarfe und prüfbare Ergebnisse

Alle nachfolgenden IDs sind **Lastenheft-Bedarfe**, keine zusätzlich freigegebenen Pflichtenheft-/Releaseanforderungen.

### 3.1 Physische Exemplare, Zustand und Aussonderung

| ID | Nutzerbedarf | Beobachtbares Abnahmeergebnis | Priorität/Ziel |
| --- | --- | --- | --- |
| **LH-EX-01** | Mehrere identische Bücher separat verwalten | Drei Exemplare derselben Ausgabe haben eigenständige Inventarnummern, Standorte und Ausleihstatus | Kernbedarf R1 |
| **LH-EX-02** | Den physischen Zustand jedes Exemplars erfassen | Gut erhaltenes Exemplar A und beschädigtes Exemplar B bleiben unabhängig dokumentiert | Kernbedarf R1 |
| **LH-EX-03** | Zustand bei Rückgabe kontrollieren und bei Bedarf ändern | Rückgabe von B dokumentiert Schaden nur an B; B ist bis zur Freigabe nicht mehr ausleihbar | Kernbedarf R1 |
| **LH-EX-04** | Verschlissenes Exemplar einzeln aussondern | Exemplar C wird mit Grund ausgesondert; A/B, Titel und Ausgabe bleiben erhalten | Kernbedarf R1 |
| **LH-EX-05** | Zustandsänderungen nachvollziehen | Berechtigtes Personal kann früheren Zustand, Datum, Anlass und Änderung sehen | Kernbedarf R1; konkrete Historientiefe abstimmen |

Erhaltungszustand (z. B. abgenutzt) und Ausleihstatus (z. B. ausgeliehen oder gesperrt) dürfen **nicht verwechselt** werden: Ein älteres, benutzbares Buch kann weiterhin verfügbar sein; ein beschädigtes Buch darf nicht automatisch erneut verliehen werden.

### 3.2 Selbstständige Ausleihe und Rückgabe

| ID | Nutzerbedarf | Beobachtbares Abnahmeergebnis | Priorität/Ziel |
| --- | --- | --- | --- |
| **LH-SS-01** | Selbst-Ausleihe an einem Terminal ohne Mitarbeiter | Berechtigtes Mitglied kann ein tatsächlich übernommenes Exemplar scannen und nach Prüfung ausleihen | **Später**, R2-Kandidat |
| **LH-SS-02** | Spätere Ausleihe per Web/Smartphone | Mitglieder erhalten eine sichere, verständliche Oberfläche; bloße Barcodekenntnis reicht nicht zur Buchung | **Später**, R2-Kandidat |
| **LH-SS-03** | Selbstständige Rückgabe auch ohne Personal | Physische Annahme wird erkennbar von bloßer Rückgabeankündigung unterschieden; Quittung beschreibt den tatsächlichen Status | **Später**, R2-Kandidat |
| **LH-SS-04** | Schutz vor Verlust und missbräuchlicher Benutzung | Keine zweite Ausleihe desselben Exemplars, keine falsche Fernrückgabe, keine Anzeige fremder Mitgliedsdaten | **Später**, zwingend vor Freigabe |
| **LH-SS-05** | Rückgabe außerhalb der Öffnungszeiten ermöglichen | Eine sichere Annahmestelle kann eine belegbare Einlieferung erfassen; Prüfung darf zeitversetzt stattfinden | **Optionale spätere** Ausbaustufe |

**Fachliche Erwartung:** Online „zurückgeben“ von zu Hause ist zunächst höchstens eine Ankündigung. Erst nach glaubwürdig belegter physischer Annahme kann eine Rückgabe nach festgelegten Regeln verbucht werden; bis zur Zustandskontrolle bleibt das Stück ggf. nicht ausleihbar. Verzögerte Prüfung durch Personal darf den nachweislich rechtzeitigen Einwurf nicht unfair zur Verspätung machen.

**Abgrenzung:** RFID, ein öffentlich erreichbarer Server, Zugangsschranken und die automatische Rückgabebox werden **nicht** als Voraussetzungen des R1-Kerns festgelegt.

### 3.3 Übernahme aus anderen Bibliothekssystemen

| ID | Nutzerbedarf | Beobachtbares Abnahmeergebnis | Priorität/Ziel |
| --- | --- | --- | --- |
| **LH-MI-01** | Bestehenden Bestand ohne Neuerfassung übernehmen | Ein unterstützter CSV-/JSON-Export kann geprüft und in HARALD eingelesen werden | Grundimport R1 |
| **LH-MI-02** | Titel **und alle einzelnen Exemplare** vollständig übertragen | Ein Titel mit fünf verschiedenen Barcodes ergibt fünf getrennte Bestandsobjekte mit korrekten Standorten/Zuständen | Grundimport R1 |
| **LH-MI-03** | Dubletten, Lücken und Formatfehler vorab sehen | Vorschau zeigt Konflikte/Verluste; Abbruch verändert keinen produktiven Datensatz | Grundimport R1 |
| **LH-MI-04** | Auch große Imports sicher wiederholen | Abbruch und Neustart erzeugen keine heimlichen Duplikate oder unvollständigen Exemplar-Beziehungen | Grundimport R1 |
| **LH-MI-05** | Ergebnis der Übernahme kontrollieren | Abgleich und schriftlicher Bericht dokumentieren importierte, übersprungene und nicht übertragene Informationen | Grundimport R1 |
| **LH-MI-06** | Später komfortabel zwischen Fremdsystemen umziehen | Geführter Assistent und bei Bedarf Quellsystemadapter, z. B. für Koha/FOLIO | Assistent R2-Kandidat; konkrete Adapter später/R3 |
| **LH-MI-07** | Optional Mitglieder, laufende Ausleihen und Vormerkungen übernehmen | Nur ausdrücklich berechtigte Übernahme mit eindeutig zugeordneten Exemplaren/Mitgliedern und Datenschutzprüfung | **Späterer gesonderter Freigabepunkt** |

**Wesentlich:** Ein Titel mit identischer ISBN ist nicht das gleiche wie eine einzelne Kopie. Mitglieder, Passwörter, aktive Leihen und Digitalrechte sind nicht automatisch Teil eines gewöhnlichen Katalogimports. Das Altsystem und eine gesicherte Ausgangskopie bleiben bis zur bestätigten Umstellung verfügbar.

## 4. Qualitäts- und Bedienerwartungen

- **LH-Q-01 – Datenintegrität:** Keine stillen Löschungen, unbemerkten Zusammenführungen, doppelten Leihvorgänge oder widersprüchlichen Verfügbarkeiten.
- **LH-Q-02 – Einfachheit:** Ein Mitarbeiter kann Zustand und Rückgabe mit möglichst wenigen Eingaben erfassen; nur Abweichungen erfordern zusätzliche Details. Importkonflikte werden verständlich und möglichst in einer übersichtlichen Liste dargestellt.
- **LH-Q-03 – Datenschutz:** Interne Zustandsnotizen, Mitglieder- und Ausleihdaten sind nur berechtigten Personen zugänglich; Selbstbedienung gibt keine fremden Informationen preis.
- **LH-Q-04 – Nachvollziehbarkeit:** Änderungen, Importentscheidungen und Aussonderungen sind mit erforderlichem Kontext dokumentierbar; Historie und personenbezogene Daten unterliegen Aufbewahrungsregeln.
- **LH-Q-05 – Datenhoheit:** Bibliotheksbetrieb, Ex-/Import und Wiederherstellung sollen ohne verpflichtende Cloudkonten möglich bleiben.
- **LH-Q-06 – Portabilität:** Plattform- und Speichertechnologieentscheidungen richten sich nach geprüfter Architektur und Tests, nicht nach dieser Bedarfsbeschreibung.

## 5. Scope, Abgrenzung und Abnahme

**R1-Basis, bereits im bisherigen Pflichtenheft angelegt:** Werk/Ausgabe/physisches Exemplar, individuelle Zustandserfassung, kontrollierte Aussonderung, personalbediente Ausleihe/Rückgabe, grundlegender CSV-/JSON-Datenaustausch mit Vorschau, Dubletten-/Konfliktprüfung und Wiederherstellbarkeit.

**Spätere Kandidaten:** Selbstbedienung an Terminal/Smartphone, physische Annahmeterminals/Rückgabeboxen, geführter Migrationsassistent, dedizierte Koha/FOLIO/MARC-Adapter, automatisierte Übernahme sensibler Mitglieder und laufender Leihen. Die endgültige Zuordnung zu R2/R3 und zu einzelnen Meilensteinen erfolgt erst nach gesonderter Entscheidung.

**Nicht zugesagt:** Vollständige Funktionsgleichheit zu Koha/FOLIO/Evergreen; sofortige Unterstützung jeder Exportversion; dauerhaftes unkontrolliertes Zwei-Wege-Synchronisieren; automatisches Remote-Checkout aufgrund bekannter Barcodes; automatisch abgeschlossene Rückgabe durch einen Webklick.

Das Lastenheft ist **noch keine unterschriebene Abnahmevereinbarung**. Die konkrete Freigabe prüft nachvollziehbare Szenarien in Abschnitt 6 und die referenzierten Pflichtenheft-/Detailanforderungen.

## 6. Rückverfolgbarkeit und Szenarien

| Lastenheft | Bestehendes Pflichtenheft und technische Detailkonzepte | Geplante Prüfnachweise |
| --- | --- | --- |
| LH-EX-01–05 | BOK-005, LOC-001/002/005/009, CIR-005/008/009; [Pflichtenheft §7.8–7.9](Pflichtenheft_Open_Source_Multimedia_Bibliotheksverwaltung_2026.md) | Drei Exemplare; Schaden an B; Aussonderung von C; A unverändert; Rückgabe-Rollback |
| LH-SS-01–05 | CIR-001–009, IAM-*, SEC-*; [SSC-001–012](SELF_SERVICE_CIRCULATION.md) | [SSC-AT-01–10](SELF_SERVICE_CIRCULATION.md): Autorisierung, physische Annahme, Doppelbuchung, Datenschutz |
| LH-MI-01–07 | IMP-002–010, IMP-016/019/020; [MIG-001–012](MIGRATION_FROM_OTHER_SYSTEMS.md) | [MIG-AT-01–12](MIGRATION_FROM_OTHER_SYSTEMS.md): Mehrfachexemplare, Wiederanlauf, Cutover, Rechte |
| LH-Q-01–06 | CAT-*, LOC-*, CIR-*, IAM-*, IMP-*, SEC-*, NFR-* | [Teststrategie](../testing/TEST_STRATEGY.md), echte Durchläufe mit Ergebnisprotokoll |

**Szenario A – Drei identische Bücher:** A und B sind ausleihbar, C abgenutzt. Nach Rückgabe wird nur B als beschädigt gesperrt. C wird später berechtigt ausgesondert; A bleibt verfügbar, und keine Exemplarhistorie geht verloren.

**Szenario B – Selbstbedienung:** Ein Mitglied leiht ein tatsächlich übernommenes Exemplar selbst aus. Ein zweiter gleichzeitiger Versuch scheitert. Ein bloßer Webklick zur Rückgabe macht das Medium nicht verfügbar. Eine belegte physische Einlieferung führt zu zutreffender Quittung und gegebenenfalls späterer Prüfung.

**Szenario C – Bibliothekswechsel:** Ein Testexport enthält eine Ausgabe mit mehreren Exemplaren sowie einen absichtlichen Barcodekonflikt. HARALD zeigt den Konflikt im Dry-run. Nach dokumentierter Entscheidung werden die erlaubten Datensätze übernommen, nachvollziehbar abgeglichen und bei erneutem Import nicht verdoppelt.

## 7. Offene Auftraggeberentscheidungen

1. Sollen Selbstbedienung zunächst am **Bibliotheksterminal** oder über **Mitglieder-Smartphones/Web** angeboten werden?
2. Welche Art der physischen Übergabe/Einlieferung soll die erste Bibliothek nachweisen können? Wird eine Rückgabebox außerhalb der Öffnungszeiten benötigt?
3. Welche konkreten Altsysteme und Versionen sind für einen ersten geprüften Migrationsadapter relevant? Echte anonymisierte Beispieldaten werden benötigt.
4. Soll ein **vollständiger** Umzug mit Mitgliedern und laufenden Leihen bereits für einen bestimmten Release zwingend sein, oder genügt zunächst die Bestandsübernahme?
5. Welche Feinabstufungen des Erhaltungszustands und welche Aufbewahrungsfristen wünscht die Bibliothek?

**Dokumentenlenkung:** Ergänzende Entscheidungen werden versioniert festgehalten; historische Anforderungen werden nicht unbemerkt ersetzt. Umsetzung und nachgewiesene Testabdeckung sind unabhängig von diesem Planungsstand zu dokumentieren.
