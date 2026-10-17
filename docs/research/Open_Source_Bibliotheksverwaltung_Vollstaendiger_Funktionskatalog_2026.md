# Open-Source-Bibliotheksverwaltung und Medienkataloge

## Ausführlicher, quellenorientierter Funktionskatalog für alle 24 genannten Programme

**Stand:** 17. Oktober 2026  
**Sprache:** Deutsch  
**Umfang:** Professionelle Bibliothekssysteme, kleine Bibliotheken, Sammlungsverwaltungen und digitale Bibliotheken; Bücher, DVDs, Blu-rays, Musik-CDs, Hörbuch-CDs, E-Books und digitale Hörbücher. **Ausgabe:** überarbeitete und vertiefte Fassung 2.0.

> **Ziel des Dokuments:** Möglichst umfassende, quellenbasierte Beschreibung der dokumentierten **Funktionsbereiche** aller 24 Programme aus der vorangegangenen Übersicht. Ein buchstäblich lückenloses Inventar sämtlicher Schaltflächen, Konfigurationsoptionen und Drittanbieter-Plugins aller Versionen wäre nur durch eine reproduzierbare Installation und vollständige Funktionsprüfung jeder Anwendung möglich. Dieses Dokument unterscheidet deshalb zwischen **ausdrücklich dokumentierten Funktionen**, **durch konfigurierbare Datensätze möglichen Anwendungsfällen** und **nicht verifizierten Fähigkeiten**. Nicht aufgeführte Funktionen gelten nicht automatisch als technisch unmöglich.

## Inhaltsverzeichnis

1. [Schnellantwort: Lassen sich DVDs, Blu-rays, CDs, Hörbücher und E-Books verwalten?](#1-schnellantwort-zu-den-medienarten)
2. [Alle 24 untersuchten Programme](#2-alle-24-untersuchten-programme)
3. [Vergleich der Medienarten](#3-vergleich-der-medienarten)
4. [Umfassender Funktionskatalog: Welche Funktionen gibt es grundsätzlich?](#4-umfassender-funktionskatalog)
5. [Professionelle Bibliothekssysteme (9 Programme)](#5-professionelle-bibliothekssysteme)
6. [Kleine Bibliotheksverwaltungen (3 Programme)](#6-kleine-bibliotheksverwaltungen)
7. [Sammlungsverwaltungen (5 Programme)](#7-sammlungsverwaltungen)
8. [Digitale Bibliotheken und E-Book-Server (7 Programme)](#8-digitale-bibliotheken-und-e-book-server)
9. [Technische Datenmodelle für gemischte Medienbestände](#9-technische-datenmodelle-für-gemischte-medienbestände)
10. [Empfehlungen und Auswahlverfahren](#10-empfehlungen-und-auswahlverfahren)
11. [Quellen und Prüfhilfen](#11-quellen-und-prüfhilfen)
12. [Praxisprofile und wichtige Unterschiede der 24 Programme](#12-praxisprofile-für-alle-24-programme)
13. [Systematisches Prüfprotokoll mit 110 Einzelanforderungen](#13-systematisches-prüfprotokoll-mit-110-einzelanforderungen)
14. [Technische und lizenzrechtliche Ergänzungen](#14-technische-und-lizenzrechtliche-ergänzungen)

---

# 1. Schnellantwort zu den Medienarten

**Ja: Viele der Programme können Bücher, DVDs, Blu-rays, Musik-CDs und Hörbuch-CDs gemeinsam katalogisieren.** Insbesondere Koha, Evergreen, FOLIO, SLiMS, RERO ILS, BiblioteQ, Tellico, GCstar, Data Crow und Shelf kommen für einen gemischten Bestand in Betracht. **Bei E-Books muss man unterscheiden:** Ein Katalog kann eine E-Book-Ausgabe lediglich mit Titel und Link *nachweisen*; ein E-Book-Server kann die Datei dagegen *speichern, bereitstellen und lesen lassen*. Bei digitalen Hörbüchern ist ein echter Audioplayer mit Fortschrittssynchronisation wiederum etwas anderes als das Verzeichnen einer Hörbuch-CD.

Die fünf häufigsten Anforderungen bedeuten nicht dasselbe:

1. **Katalogisieren:** Datensatz zu einem Medium erfassen (Titel, Urheber, EAN/UPC/ISBN, Format, Jahr, Inhalt, Cover).
2. **Physische Exemplare verwalten:** Einzelne DVDs/CDs/Bücher mit Barcode, Standort, Zustand und Stückzahl dokumentieren.
3. **Physisch ausleihen:** Ausleiher, Leihfrist, Verlängerung, Vormerkung, Rückgabe und Verlust protokollieren.
4. **Digitale Medien bereitstellen:** EPUB, PDF, MP3, M4B oder andere Dateien verwalten und berechtigten Personen zum Download/Stream anbieten.
5. **Digital lesen oder hören:** Integrierter EPUB/PDF-Reader beziehungsweise Audio-Streaming mit Position, Kapiteln und gegebenenfalls Offline-Synchronisierung.

**Wichtig:** DVD- und Blu-ray-**Katalogisierung** bedeutet nicht, dass das Programm die Disc rippt, einen Blu-ray-Player mitbringt oder DRM/Regionalcodes umgehen kann. Für E-Books und Hörbücher gelten außerdem Urheberrecht, Lizenzbedingungen und gegebenenfalls DRM. Ein technisch möglicher Dateiupload begründet kein Recht zur öffentlichen digitalen Ausleihe.

---

# 2. Alle 24 untersuchten Programme

| Nr. | Programm | Kategorie | Hauptzweck | Projekt / Quellcode |
|---:|---|---|---|---|
| 1 | Koha | Professionelles ILS | Bibliotheksbetrieb, Medienausleihe, OPAC | [koha-community.org](https://koha-community.org/) |
| 2 | Evergreen ILS | Professionelles ILS | Große Bibliotheken und Verbünde | [evergreen-ils.org](https://evergreen-ils.org/) |
| 3 | FOLIO | Bibliotheksplattform | Wissenschaftliche Bibliotheken und E-Ressourcen | [folio.org](https://folio.org/) |
| 4 | SLiMS | Bibliotheks-ILS | Kleine und mittlere Bibliotheken | [GitHub](https://github.com/slims/slims9_bulian) |
| 5 | RERO ILS | Bibliotheks-ILS | Netzwerke, Bibliografien und Ausleihe | [GitHub](https://github.com/rero/rero-ils) |
| 6 | PMB | Bibliotheks-ILS | Bibliotheken und Dokumentationszentren | [sigb.net](https://www.sigb.net/) |
| 7 | InvenioILS | Bibliotheks-ILS | API- und JSON-orientierte Bibliotheken | [Projekt](https://inveniosoftware.org/products/ils/) |
| 8 | ABCD | Bibliotheks-/Dokumentationssystem | Frei konfigurierbare Dokumentationsdatenbanken | [Dokumentation](https://abcd-devcom.github.io/docs/) |
| 9 | Next-L Enju Leaf | Bibliotheks-ILS | Bibliotheksabläufe und öffentliche Suche | [GitHub](https://github.com/next-l/enju_leaf) |
| 10 | BiblioteQ | Kleine Bibliothek / Desktop | Multimedialer Katalog mit Ausleihe | [GitHub](https://github.com/textbrowser/biblioteq) |
| 11 | OpenBiblio (deutscher Zweig) | Kleine Bibliothek / Web | Mitglieder, Medien und Ausleihe | [openbiblio.de](https://openbiblio.de/) |
| 12 | OpenLibry | Schulbibliothek / Web | Schnellbedienung, Bücher und Ausleihe | [GitHub](https://github.com/jzakotnik/openlibry) |
| 13 | Tellico | Desktop-Sammlungsverwaltung | Bücher, Musik, Videos und Sammlungen | [tellico-project.org](https://tellico-project.org/) |
| 14 | GCstar | Desktop-Sammlungsverwaltung | Bücher, Musik, DVDs, Blu-rays, Spiele | [Dokumentation](https://gcstar.gitlab.io/gcstar_docs/en/) |
| 15 | Data Crow | Sammlungsverwaltung | Medien aller Art mit eigenen Modulen | [datacrow.org](https://datacrow.org/de/) |
| 16 | Shelf | Persönlicher Web-Katalog | Multimedialer Bestandskatalog mit Scans | [GitHub](https://github.com/dgahagan/shelf) |
| 17 | uBiblio | Persönliche Web-Bibliothek | Bücher, E-Books und einfache Ausleihe | [GitHub](https://github.com/seanboyce/ubiblio) |
| 18 | Calibre | Desktop-E-Book-Management | E-Book-Bibliothek, Reader, Konvertierung | [calibre-ebook.com](https://calibre-ebook.com/) |
| 19 | Calibre-Web | Web-E-Book-Verwaltung | Webzugriff auf eine Calibre-Datenbank | [GitHub](https://github.com/janeczku/calibre-web) |
| 20 | BookOrbit | Digitaler Lese-/Hörserver | E-Books, Comics, digitale Hörbücher | [GitHub](https://github.com/bookorbit/bookorbit) |
| 21 | BookLore | Digitaler Leseserver | E-Books, PDFs, Comics (Wartungsmodus) | [GitHub](https://github.com/booklore-app/booklore) |
| 22 | Kavita | Digitaler Leseserver | E-Books, Comics, Manga | [GitHub](https://github.com/Kareadita/Kavita) |
| 23 | Komga | Digitaler Leseserver | Comics, Manga, Zeitschriften, E-Books | [GitHub](https://github.com/gotson/komga) |
| 24 | Inventaire | Kollaborativer Buchkatalog | Eigene Bestände, Teilen, Verleihen | [inventaire.io](https://inventaire.io/) |

**Begriff:** ILS = *Integrated Library System*, OPAC = *Online Public Access Catalog* (öffentlich recherchierbarer Bibliothekskatalog).

---

# 3. Vergleich der Medienarten

## 3.1 Legende

- **K** – Physischer Medientyp ist ausdrücklich dokumentiert bzw. zuverlässig als Katalog-/Exemplartyp konfigurierbar. Ausleihe nur, wenn die Anwendung einen Ausleihprozess besitzt.
- **D** – Digitale Datei steht im Zentrum: gezieltes Speichern, Lesen, Ausliefern oder Abspielen wird dokumentiert; Umfang je nach Format verschieden.
- **L** – Verweis, Metadaten, Dateianhang oder sonstige **eingeschränkte** digitale Verwaltung; kein vollwertiger digitaler Medienserver nachgewiesen.
- **A** – Mit eigenen Feldern, eigenem Medientyp oder zweckentfremdetem Schema prinzipiell katalogisierbar; nicht notwendigerweise fertiger Medientyp.
- **?** – Produktdokumentation nicht ausreichend für belastbare Zusage.
- **—** – Kein passender nativer Schwerpunkt; eine allgemeine Softwareänderung oder Dateiverlinkung ist nicht als Produktfunktion zu werten.

Diese Tabelle beantwortet vor allem **Bestandsverwaltung**, nicht lizenzrechtliche digitale Ausleihe, Abspielen geschützter Blu-rays oder Disc-Ripping.

| Programm | Bücher (Papier) | DVD | Blu-ray | Musik-CD | Hörbuch-CD | E-Book-Dateien | Digitale Hörbücher |
|---|:---:|:---:|:---:|:---:|:---:|:---:|:---:|
| Koha | K | K | K | K | K | L | L |
| Evergreen | K | K | K | K | K | L | L |
| FOLIO | K | K | K | K | K | L | L |
| SLiMS | K | K | K | K | K | L | L |
| RERO ILS | K | K | K | K | K | L | L |
| PMB | K | K | K | K | K | L | L |
| InvenioILS | K | A | A | A | A | L | ? |
| ABCD | K | A | A | A | A | L | L |
| Next-L Enju Leaf | K | A | A | A | A | L | ? |
| BiblioteQ | K | K | A | K | A | L | L |
| OpenBiblio | K | K | A | K | A | L | ? |
| OpenLibry | K | ? | ? | ? | ? | ? | ? |
| Tellico | K | K | K | K | A | L | L |
| GCstar | K | K | K | K | A | L | L |
| Data Crow | K | K | K | K | A | L | L |
| Shelf | K | K | K | K | K | L | L |
| uBiblio | K | ? | ? | ? | ? | L | ? |
| Calibre | A | — | — | — | — | D | L |
| Calibre-Web | A | — | — | — | — | D | L |
| BookOrbit | — | — | — | — | — | D | D |
| BookLore | — | — | — | — | — | D | D |
| Kavita | — | — | — | — | — | D | — |
| Komga | — | — | — | — | — | D | — |
| Inventaire | K | — | — | — | — | A | — |

**Zur Einordnung der Tabelle:** Ein generisches ILS mit konfigurierbaren Medienarten erhält bei physischer DVD/CD gegebenenfalls ein **K**, auch wenn kein filmspezifischer Metadatenimport existiert. Andersherum kann beispielsweise Shelf DVDs und Musik-CDs mit Film-/Musikdaten anreichern, ohne deshalb professionelle Fernleihe zu besitzen. Bei BiblioteQ ist DVD und Musik-CD ausdrücklich beschrieben; die Blu-ray lässt sich nach vorliegenden Quellen eher über Film-/DVD-Felder erfassen (**A**). Bei E-Book-Servern bedeutet **D** nicht automatisch, dass jedes proprietäre, verschlüsselte Format geöffnet werden kann.

## 3.2 Die besten Kandidaten für *alle* genannten Medien

- **Shelf:** Besonders überzeugend für einen *privaten* gemischten Bestand: Bücher, DVDs/Blu-rays, CDs, Schallplatten, Hörbücher, E-Books, Comics und Spiele. Die README dokumentiert EAN/UPC-Scans, Filmmetadaten über TMDb, Musikpressungen über MusicBrainz, Standorte, physische Exemplare und Leihvorgänge. **Nicht** gleichbedeutend mit einem integrierten universellen Videoplayer oder einer professionellen Digitalausleihe.
- **Data Crow:** Die flexibelste klassische Desktop-Sammlungsverwaltung; vorhandene Module für Bücher, Filme und Musik, eigene Module und Datenfelder sowie ein übergreifender Medienüberblick. Hörbuch-CD als Audioprodukt oder eigener Typ modellierbar.
- **Tellico / GCstar:** Weniger Bibliotheksbürokratie und gute Katalogisierung von Videos, CDs und Büchern. Für private Sammler häufig praktischer als ein Großbibliotheks-ILS.
- **BiblioteQ:** Interessant, wenn *echte Ausleihe* gedruckter und physischer audiovisueller Medien wichtig ist und eine lokale, Qt-basierte Oberfläche gewünscht wird.
- **Koha:** Stärkster Allrounder, wenn mehrere Personen Medien aus einer *Bibliothek* ausleihen sollen; DVD und Blu-ray lassen sich ausdrücklich durch Materialarten und unterschiedliche Ausleihregeln trennen.
- **BookOrbit:** Ergänzung, wenn *digitale* E-Books **und** Hörbücher gelesen/gehört werden sollen. Es verwaltet keine physischen DVDs als Hauptfunktion.

---

# 4. Umfassender Funktionskatalog

Dieser Abschnitt erläutert den Funktionsvorrat, nach dem Bibliotheksverwaltungsprogramme sachlich verglichen werden sollten. Es handelt sich **nicht** um eine Behauptung, jedes untersuchte Programm besitze jede dieser Funktionen.

## 4.1 Titel-, Werk- und Ausgabenverwaltung

Ein **Werk** bezeichnet den abstrakten Inhalt (z. B. Roman, Musikwerk, Film); eine **Ausgabe** bezeichnet die konkrete Veröffentlichung (z. B. gebundene deutsche Ausgabe 2018, englische EPUB-Ausgabe oder Blu-ray-Sonderedition); ein **Exemplar** ist ein physisch vorhandenes Einzelstück. Leistungsfähige Systeme halten diese Ebenen auseinander, sodass zehn DVDs derselben Ausgabe zehn verschiedene Inventarnummern, Standorte und Ausleihzustände erhalten können. Sammlungsprogramme führen teils nur einen Eintrag pro Ausgabe oder Titel; das Verhalten muss dann besonders bei Mehrfachexemplaren geprüft werden.

## 4.2 Bibliografische Katalogisierung

Erfassbar sind je nach Produkt Titel, Untertitel, Urheber/Beiträger mit Rollen, Verlag oder Label, Erscheinungs- und Veröffentlichungsdatum, Sprache, Edition, ISBN/ISSN/ISMN, EAN/UPC, sonstige Identifikatoren, Sachgebiete, Schlagwörter, Zusammenfassung, Reihen-/Bandinformation, Zielgruppe, Altersfreigabe, physischer Umfang, Laufzeit, Datenträgerart, Cover und eigene Notizen. Wissenschaftliche ILS pflegen zusätzlich Normdatensätze und präzise bibliografische Formate; Sammlerprogramme konzentrieren sich eher auf Felder, die unmittelbar beim Wiederfinden helfen.

## 4.3 Spezifische Film- und Videometadaten

Für DVDs, Blu-rays und gegebenenfalls UHD-Blu-rays sollten sich erfassen lassen: EAN/UPC, Film-/Serientitel, Ausgabe und Verpackung, Produktionsjahr, Land, Regie, Darstellerrollen, Drehbuch, Studio, Laufzeit, Genre, Filmreihe, Staffel/Episode, Altersfreigabe (FSK), Disc-Anzahl, Regionalcode, Seitenverhältnis, Bild- und Tonformat, Sprache, Tonspuren, Untertitel, Bonusmaterial, Zustand, Kaufpreis und Lagerplatz. **Filmwerk, Edition und vorhandene Disc sind verschiedene Entitäten.** Bei mehrteiligen Boxsets sollten Einzel-Discs und Verpackung als zusammengehörige Einheit erfasst werden können.

## 4.4 Spezifische Musik- und Hörbuchmetadaten

Musik-CDs: Album-/Release-Titel, Künstler, beteiligte Musiker, Komponisten, Dirigenten, Ensemble, Genre, Label, Katalognummer, Barcode, Release-Datum, Land, Medium (CD, Vinyl, Kassette), Trackliste mit Nummer/Laufzeit, Disc-Nummer, Edition und Pressung. Hörbücher: Autor des Buches, Sprecher/Erzähler, Verlag/Audio-Label, gekürzte/unabridged Fassung, Anzahl der CDs, Gesamtspieldauer, Sprache, Kapitel, Band-/Serienbezug und physischer Zustand. Eine CD-Box mit mehreren Discs sollte als **ein ausleihbares Set** oder als Einzeldiscs modellierbar sein. Für digitale MP3/M4B-Hörbücher sind Kapitel, Wiedergabefortschritt und Streaming eigenständige Anforderungen.

## 4.5 Katalogrecherche, OPAC und Entdeckung

Einfache Suche durchsucht Titel/Autor/ISBN; erweiterte Suche kombiniert Filter nach Medientyp, Sprache, Erscheinungsjahr, Standort, Genre und Verfügbarkeit. Volltextsuche, facettierte Suche, Autovervollständigung, fehlertolerante Suche, Sortierungen, Trefferlisten und Empfehlungen können das Finden verbessern. Ein OPAC stellt diese Funktionen Leserinnen und Lesern im Web bereit und zeigt gegebenenfalls Standort, Ausleihstatus und Vormerkmöglichkeiten an. Ein *privater Katalog* ist nicht automatisch ein öffentlicher OPAC.

## 4.6 Exemplare, Inventarnummern und Standorte

Typische Aufgaben sind Inventarnummern/Barcodes vergeben, Signaturen, Regale und Räume modellieren, Kauf- und Beschaffungsdaten erfassen, Eigentümer unterscheiden, beschädigte oder fehlende Exemplare markieren, Bestand verschieben, physische Prüfungen durchführen und ausgeschiedene Exemplare dokumentieren. Bei DVD-/CD-Medien zählen außerdem **Mehrteiligkeit und Vollständigkeitsprüfung** (Hülle, Booklet, Disc 1–3).

## 4.7 Ausleihe und Rückgabe

Bibliothekssysteme verwalten Leser-/Mitgliedskonten, Ausleihlimits, Leihdauern pro Materialart und Benutzergruppe, Verlängerungen, Rückgabe, Rückgabequittung, Überfälligkeit, Verlust, Mahnungen und Gebühren. Unterschiedliche Regeln – beispielsweise Bücher 28 Tage, DVDs 7 Tage, Präsenzexemplare nicht verleihbar – sollten konfigurierbar sein. Private Programme unterstützen meist nur eine einfachere Leihnotiz („verliehen an / verliehen seit“).

## 4.8 Vormerkungen, Reservierungen und Fernleihe

Vormerkungen organisieren Warteschlangen für ausgeliehene Titel, Abholorte, Bereithaltefristen und Benachrichtigungen. Interbibliothekarische Leihe (ILL/Fernleihe) erfordert zusätzliche Vorgänge zwischen Bibliotheken, Transport-/Lieferstatus und Regeln. Die Existenz eines **Reservierungsbuttons** ist kein Beleg für einen vollständigen Fernleihprozess.

## 4.9 Benutzer, Rollen und Datenschutz

Mögliche Funktionen: Benutzer anlegen und importieren, Rollen für Gäste/Bibliothekare/Administratoren, Berechtigungen nach Standort, Leserausweise und Barcodekarten, Ablauf von Mitgliedschaften, Kommunikation, Ausleihhistorie, Datenschutz- und Löschfristen. Bei privaten Diensten sind oft lediglich Eigentümer-/Mitnutzerkonten und Freigaberechte vorhanden. Besondere Aufmerksamkeit verdienen personenbezogene Ausleihhistorien und Datensparsamkeit.

## 4.10 Erwerbung und Lieferanten

Professionelle ILS verwalten Anschaffungsvorschläge, Warenkörbe/Bestellungen, Lieferanten, Budgets, Etatpositionen, Rechnungen, Lieferstatus, EDI sowie die automatische Katalogisierung aus Bestelldatensätzen. Eine einfache Angabe des Kaufpreises in Tellico ist **keine** Erwerbungsverwaltung.

## 4.11 Zeitschriften, Zeitungen und fortlaufende Ressourcen

Serien- und Periodikaverwaltung unterscheidet Zeitschriftentitel, Abonnements, erwartete Hefte, Jahrgänge, Hefteingänge, Reklamationen und Bindeeinheiten. Diese Funktionen sind beispielsweise in Koha, Evergreen, FOLIO, RERO ILS, SLiMS und ABCD unterschiedlich tief umgesetzt. Ein bloßes Feld „Zeitschrift“ zählt nicht als Heftkontrolle.

## 4.12 E-Books, Dokumente und Medienbereitstellung

Funktionen umfassen EPUB/PDF/MOBI/AZW3/CBZ-Dateien importieren, Metadaten aus Dateien lesen, Lesezeichen/Markierungen speichern, konvertieren, im Browser lesen, auf Geräte übertragen oder über OPDS bereitstellen. Separat zu bewerten sind DRM, Lizenzverwaltung, zeitlich limitierte Ausleihen, geschützte Zugänge, Dateiversionen und Metadatenpflege. **Bibliografischer Nachweis + URL** bleibt unterhalb einer echten E-Book-Bibliothek.

## 4.13 Digitale Hörbücher und Audio

Ein digitaler Hörbuchserver kann MP3/M4B/M4A/OPUS/OGG importieren, Alben und Kapitel zuordnen, über HTTP streamen, Abspielpositionen sichern, Benutzerfortschritte synchronisieren und Downloads für Offline-Nutzung anbieten. Das digitale Hörbuch ist nicht mit der physischen Hörbuch-CD gleichzusetzen. Nur wenige der 24 Produkte besitzen eine ausgewiesene Hörbuch-Streaming- und Fortschrittsfunktion; **BookOrbit** ist der klarste Kandidat.

## 4.14 Metadatenimporte und Fremddatenanreicherung

Die Erfassung kann über ISBN, EAN/UPC, ISSN, Z39.50, SRU, MARC-Daten, Open Library, DNB, Google Books, MusicBrainz, Discogs, TMDb oder andere Quellen beschleunigt werden. Nicht jedes System kennt jeden Anbieter. Ein Importer kann veralten, wenn ein Webdienst seine API ändert; externe API-Keys, Nutzungsregeln, Datenqualität und manuelle Korrekturen sind deshalb relevant.

## 4.15 Barcodes, RFID, Etiketten und Scanner

Barcode-Leser verhalten sich oft als Tastatur; EAN-13, UPC-A und interner Exemplarbarcode sind unterschiedliche Kennzeichen. Druckfunktionen können Rückenschilder, Inventaretiketten oder Leser-Ausweise erzeugen. RFID-/SIP2-Integration ist ein gesonderter technischer Bereich und darf aus einfachem Barcode-Support nicht abgeleitet werden.

## 4.16 Berichte, Kennzahlen und Inventur

Häufige Auswertungen: Anzahl Medien/Exemplare, Verteilung nach Typ/Sprache/Genre, Neuzugänge, Ausleihzahlen, säumige Leser, verlegte/verlorene Bestände, Anschaffungsbudgets, Inventurdifferenzen, Sammlungswert, Dubletten sowie frei definierbare CSV-/SQL-Berichte. Eine Berichtsfunktion ist nur dann praktikabel, wenn Zugriffsrechte und sensible Daten berücksichtigt werden.

## 4.17 Import, Export, Portabilität und Migration

Mindestens CSV/TSV/JSON/XML für Bibliografien und Exemplare prüfen; bei professionellen ILS zusätzlich MARC21/UNIMARC, ISO 2709, Dublin Core, Normdaten und Z39.50/SRU. Auch Benutzer, Leserverknüpfungen und Leihvorgänge müssen bei einer vollständigen Migration exportierbar sein. Proprietäre Dateianhänge, Bilddateien, benutzerspezifischer Lesefortschritt und Verknüpfungen werden bei einfachen Exporten häufig vergessen.

## 4.18 Mehrstandort-, Mehrmandanten- und Verbundfähigkeit

Mehrstandortbetrieb bedeutet typischerweise gemeinsame Bibliografien bei lokalen Exemplaren, abweichende Öffnungszeiten, Leihregeln und Berechtigungen. Bibliotheksverbünde benötigen zusätzliche Eigentümer-, Organisations- und Transportlogik. Ein Server mit fünf Benutzerkonten ist noch kein Bibliotheksverbund.

## 4.19 Erweiterbarkeit, Schnittstellen und Betrieb

Relevante Aspekte sind REST-APIs, Import-/Export-APIs, Webhooks/Plugins, eigene Felder, Datenbankmodell, Skriptbarkeit, Docker/Podman, Aktualisierbarkeit, TLS, Backup/Restore, Migrationstests, Logging und Monitoring. Lizenz und Quellcodeverfügbarkeit entscheiden, ob ein Projekt dauerhaft frei betrieben und angepasst werden kann. SQL-Zugriff allein ersetzt keine stabile öffentliche API.

## 4.20 Lesekomfort und soziale Funktionen

Digitale Bücherplattformen bieten zum Teil Lesefortschritt, Markierungen, Anmerkungen, Geräte-Sync, dynamische Regale, Empfehlungen, Bewertungen und Leseziele. Gemeinsame Katalogplattformen ermöglichen Wunschlisten und soziale Ausleih-/Tauschanfragen. Solche Funktionen sind Zusatznutzen, aber kein Ersatz für eine rechtssichere Ausleihverwaltung einer öffentlichen Bibliothek.

---
# 5. Professionelle Bibliothekssysteme

## 5.1 Koha

**Kurzprofil:** Etabliertes, webbasiertes integriertes Bibliothekssystem mit klassischem Geschäftsgang vom Erwerbungsvorschlag bis zur Aussonderung. **Technik:** insbesondere Perl, MariaDB/MySQL und Weboberfläche. **Lizenz:** GPL. **Einsatz:** öffentliche, Schul-, Spezial- und Hochschulbibliotheken sowie Bibliotheksverbünde.

**Dokumentierte Funktionsbereiche:**

1. **Bibliografische Katalogisierung:** Erstellen, Bearbeiten und Verknüpfen von bibliografischen MARC-Datensätzen. Konfigurierbare MARC-Frameworks bestimmen, welche Felder bei einem Materialtyp angeboten werden; Normdaten unterstützen eine konsistente Erschließung.
2. **Exemplarverwaltung:** Zu einer bibliografischen Ausgabe lassen sich mehrere physische Exemplare mit Barcode, Signatur, Standort, Eigentümerbibliothek, Zustand, Preis und Ausleihstatus halten. Stapeländerungen und Inventur-/Bestandswerkzeuge ergänzen die Einzelbearbeitung.
3. **Verschiedene Materialarten:** Eigene Typen für Buch, CD, DVD und ausdrücklich auch **Blu-ray**; Typen lassen sich hierarchisch gruppieren. Dadurch können Film-DVDs und Blu-rays gemeinsam als „Filme“ gesucht, aber unterschiedlich verliehen werden.
4. **Mitglieder-/Leserverwaltung:** Kontaktdaten, Benutzerkategorien, Ausweise, Berechtigungen, Sperren und individuelle Ausleihinformationen; Datenschutz und Aufbewahrungsregeln sind bei der Einrichtung zu konfigurieren.
5. **Ausleihtheke:** Ausleihe, Rückgabe, Verlängerung, Verlustbehandlung und Sonderregeln für nicht ausleihbare Bestände. Leihdauer, Mengenlimits und Gebühren können von Bibliothek, Benutzergruppe und Materialart abhängen.
6. **Vormerkungen und Bereitstellung:** Reservierung von Titeln/Exemplaren, Wartelisten, Bereithaltung und Regeln über Standorte hinweg. Benutzer können je nach Konfiguration eigene Vormerkungen und Verlängerungen bearbeiten.
7. **Online-Katalog (OPAC):** Websuche, Medienfilter, Exemplaranzeige, Benutzerkonto und Vormerkungen; das Layout und Anzeigeverhalten können angepasst werden.
8. **Erwerbung:** Lieferanten, Bestellungen, Budgets, Etatüberwachung, Lieferungen, Rechnungen und je nach Konfiguration elektronischer Bestellaustausch (EDI).
9. **Zeitschriften:** Abonnements, Erscheinungsrhythmen, erwartete und eingegangene Hefte, Reklamation und Zeitschriftenbestände.
10. **Benachrichtigungen und Gebühren:** Ausleihhinweise, Erinnerungen, Mahnungen, Gebühren und Vorlagen für Leserkommunikation; Versand setzt korrekte Mail-/Druckkonfiguration voraus.
11. **Verwaltung und Auswertung:** Statistik- und SQL-Berichte, Import/Export, Etiketten-/Barcode-Druck, Batch-Werkzeuge, Berechtigungen und Administrationsparameter.
12. **Interoperabilität:** MARC, Z39.50/SRU und Bibliotheksschnittstellen, je nach Betrieb und Konfiguration. Koha ist häufig gut in bestehende Bibliotheks-IT integrierbar.
13. **Elektronische Ressourcen (ERM):** Lizenzverträge, Agreements, E-Buch-/E-Zeitschriften-Pakete, Zugangsbedingungen und Nutzungsinformationen von elektronischen Beständen nachhalten. Diese Verwaltung ist vom Hosten beliebiger EPUB-Dateien zu unterscheiden.
14. **Fernleihe (ILL):** Externe Bestellungen und Leihwünsche zwischen Einrichtungen bearbeiten, soweit das ILL-Modul und die beteiligten Dienste eingerichtet sind.
15. **Semester- und Kursapparate:** Lehrveranstaltungen zugeordnete Medien und Sonderausleihbedingungen über Course Reserves organisieren.
16. **Bestandserhaltung:** Preservation-Funktionen zur Dokumentation von Maßnahmen und betroffenen Exemplaren; Details sind abhängig von der konkreten Version und Konfiguration.
17. **Verkauf/Point of Sale:** Verkäufe und Zahlungen in dafür vorgesehenen Geschäftsgängen abwickeln, wenn das entsprechende Modul betrieben wird.

**DVD/Blu-ray/Musik/Hörbuch:** Besonders gut für **Katalog und physische Ausleihe** geeignet. Für Musik-CDs, Hörbuch-CD-Sets und Blu-rays sollten eigene Medienarten und geeignete MARC-Felder (Mitwirkende, Laufzeit, Sprache, Disc-Zahl) eingerichtet werden. **E-Books:** Bibliografische Nachweise, URLs und gegebenenfalls externe Plattformen; kein Ersatz für ein eigenständiges DRM-gestütztes E-Book-Leihportal.

**Grenzen und Aufwand:** Einführung, Bibliotheksregeln, Normdaten und MARC benötigen Fachkenntnis; für eine private Sammlung meist überdimensioniert. Medienabspielgeräte oder Rip-Funktionen gehören nicht zum Funktionsumfang.

**Quellen:** [Koha-Manual – Administration und Materialarten](https://koha-community.org/manual/latest/de/html/administration.html) · [Katalogisierung](https://koha-community.org/manual/latest/en/html/cataloging.html) · [Erwerbung](https://koha-community.org/manual/latest/en/html/acquisitions.html)

## 5.2 Evergreen ILS

**Kurzprofil:** Skalierbares ILS, bekannt für Bibliotheksnetze und differenzierte Ausleihregeln. **Technik:** überwiegend Perl und PostgreSQL, Web-Client und Serverdienste. **Lizenz:** GPL. **Einsatz:** kommunale Bibliotheken, große Standorte und Konsortien.

**Dokumentierte Funktionsbereiche:**

1. **Katalogisierung:** Bibliografische Datensätze und konkrete Exemplare, bibliografische Suche, Dubletten-/Datensatzpflege und Import externer Datensätze.
2. **Mehrbibliotheksbetrieb:** Hierarchische Organisationsstruktur mit zentralen und lokalen Einstellungen; gemeinsame Titelbestände bei standortbezogenen Exemplaren.
3. **Materialarten und Ausleihmodifikatoren:** Leihregeln lassen sich pro Bibliothek, Lesertyp und Medientyp differenzieren; die Dokumentation enthält Beispiele für **Buch, DVD und Musik**.
4. **Ausleihe:** Checkout, Check-in, Verlängerungen, Leihfristen, Gebühren und Überfälligkeitsbehandlung samt umfangreicher Entscheidungsregeln.
5. **Reservierungen:** Vormerkungen, Warteschlangen, Bereithaltungsprozesse und standortübergreifende Bereitstellung.
6. **Leser:** Benutzerkonten, Ausweise, Berechtigungsklassen, Kommunikationswege und kontobezogene Vorgänge.
7. **Öffentlicher Katalog:** Recherche, Standort-/Bestandsanzeige, Leseranmeldung und bestellbare beziehungsweise vormerkbare Medien.
8. **Erwerbung:** Etas/Fonds, Lieferanten, Bestellungen, Rechnungen, EDI, Stapelimport von Lieferanten-Bibliografien und Bestellüberwachung.
9. **Fortlaufende Werke:** Zeitschriften- und Heftverwaltung mit fachlichen Workflows für Periodika.
10. **Berichte und Administration:** Berechtigungen, Konfiguration, regelbasierte Abläufe, Berichte und Werkzeuge für große Bibliotheksorganisationen.
11. **Integration:** Schnittstellen und Bibliotheksprotokolle; durch den Verbundbetrieb besonders wertvoll bei bestehender IT-Landschaft.
12. **Feingranulare Vormerkarten:** Vormerkungen auf Titel-, Band-/Teil-, Ausgaben-/Format- und Exemplar-Ebene; auch eine mehrteilige DVD kann mit passender Teilzuordnung verwaltet werden.
13. **Transport/Bereithaltung:** Vormerkungen zwischen Zweigstellen auffinden, bereitstellen, mit Transportstatus versehen und am Abholort aushändigen.
14. **Weitere Ausleihprozesse:** Sperren, verlorene Medien, angeblich zurückgegebene Exemplare und Mehrfachvormerkungen in dokumentierten administrativen Abläufen.

**Medien:** DVDs, Blu-rays, Musik- und Hörbuch-CDs lassen sich als physische Medien mit individuellen Regeln erfassen. Eine Blu-ray kann beispielsweise eine andere Leihdauer als ein Buch bekommen. **E-Books** werden katalogisiert/verlinkt oder über externe elektronische Dienste verfügbar gemacht, nicht primär im Evergreen-eigenen Reader verwaltet.

**Grenzen:** Die Architektur und Regelwerke sind auf Bibliotheksbetrieb ausgerichtet; Installation, Pflege und Katalogmigration sind kein kleines Privatprojekt. Bei einer Medienverwaltung ohne Ausleihe sind Data Crow oder Shelf einfacher.

**Quellen:** [Evergreen-Dokumentation](https://docs.evergreen-ils.org/docs/latest/) · [Ausleihregeln mit DVD und Musik](https://docs.evergreen-ils.org/docs/latest/admin_initial_setup/borrowing_items.html) · [Acquisitions](https://docs.evergreen-ils.org/docs/latest/acquisitions/introduction.html)

## 5.3 FOLIO

**Kurzprofil:** Modulare, verteilte *Library Services Platform* mit besonderer Stärke bei elektronischen Ressourcen. **Technik:** Java-Backend-/Microservice-Architektur, Web-Apps, PostgreSQL und zusätzliche Infrastruktur. **Lizenz:** Apache-2.0. **Einsatz:** vor allem wissenschaftliche Bibliotheken.

**Dokumentierte Funktionsbereiche:**

1. **Modulares App-Konzept:** Geschäftsgänge sind auf spezialisierte, miteinander vernetzte Anwendungen verteilt; Änderungen und Erweiterungen sollen nicht zwangsläufig den gesamten Kern berühren.
2. **Inventory:** Unterscheidung zwischen *Instance* (bibliografisches Werk/Ausgabe), *Holdings* (Bestand einer Bibliothek) und *Item* (konkretes physisches Exemplar). Dadurch können Standort, Exemplarstatus und bibliografische Beschreibung sauber getrennt werden.
3. **Materialtypen und Exemplardaten:** Frei konfigurierbare Materialarten, Barcodes, Signaturen, Stückzahlen und Beschreibung mehrteiliger Sets; die Dokumentation nennt als Beispiel ein Set mit sieben CDs.
4. **Ausleihe und Rückgabe:** Check-out, Check-in, Verlängerungen, Forderungen, Vormerkungen, Leihregeln, Gebühren und Benachrichtigungen.
5. **Benutzerverwaltung:** Unterschiedliche Nutzer-/Personalgruppen mit Berechtigungen sowie mit den Ausleihprozessen verbundenen Daten.
6. **Erwerbung:** Bestellungen, Lieferanten, Haushaltsmittel, Fonds, Rechnungen und zugehörige Metadaten-Workflows.
7. **ERM (Electronic Resource Management):** Elektronische Zeitschriften, Datenbanken, E-Book-Pakete, Lizenzinformationen, Vertrags-/Agreement-Daten und elektronische Bestände; dies ist eine der größten Besonderheiten von FOLIO.
8. **Datenimport/-export:** Metadatenverarbeitung, MARC-bezogene Prozesse, Zuordnung von importierten Datensätzen und Integration in weitere Apps.
9. **Reports:** Durch separate Reporting-Werkzeuge und institutionelle Integrationen können Bestands-, Nutzungs- und Erwerbungsdaten ausgewertet werden.
10. **API und Erweiterbarkeit:** Modulare Dienste unterstützen Integration mit lokalen Discovery-Portalen, Authentifizierung und externen Plattformen.
11. **Mehrstandortfähigkeit:** Standort- und Holdings-Modell eignen sich für komplexe Hochschul-/Verbundstrukturen.
12. **Finanzbuchung im Erwerbungsbereich:** Finanzmittel und Budgets verwalten, Bestellpositionen und Rechnungen damit verknüpfen sowie den Wareneingang nachhalten.
13. **Lizenz- und E-Ressourcenverwaltung:** Vereinbarungen, Lizenzen, elektronische Holdings und Knowledge-Base-Einträge differenziert bearbeiten.
14. **Datenmodell und Integrationskette:** *Instance*, *Holdings* und *Item* mit Source Record Storage, Datenimport und weiteren Apps verknüpfen; konkrete Apps werden je Deployment separat betrieben.

**Medien:** Physische Bücher, DVD, Blu-ray, Musik- und Hörbuch-CDs lassen sich über Materialtypen und Exemplare verwalten. **E-Books** können als elektronische Ressourcen samt Lizenzen/Beständen geführt werden; das ist nicht dasselbe wie EPUB-Dateihosting in BookOrbit.

**Grenzen:** Hoher Infrastruktur- und Integrationsaufwand; ein einzelnes Familienregal rechtfertigt die verteilte Architektur nicht. Der Umfang einzelner FOLIO-Apps hängt von Installation und Version ab.

**Quellen:** [FOLIO-Funktionsübersicht](https://docs.folio.org/docs/about-folio/features/) · [Inventory](https://docs.folio.org/docs/metadata/inventory/) · [Resource Access](https://docs.folio.org/docs/access/)

## 5.4 SLiMS – Senayan Library Management System

**Kurzprofil:** Webbasierte Bibliothekssoftware mit erstaunlich umfangreichem Funktionsumfang für vergleichsweise überschaubare Infrastruktur. **Technik:** PHP und MySQL/MariaDB. **Lizenz:** GPL-3.0. **Einsatz:** Schulen, kleinere bis mittelgroße Bibliotheken, Institutionen.

**Dokumentierte Funktionsbereiche:**

1. **Bibliography:** Bibliografische Titelerfassung, ISBN, Autoren, Verlag, Klassifikation, Themen, Medientyp und Cover; auch elektronische Dokumente beziehungsweise andere Materialien können beschrieben werden.
2. **Items:** Mehrere physische Exemplare pro Titel mit Barcode, Standort, Beschaffungsangaben und Ausleihstatus.
3. **Circulation:** Ausleihe, Rückgabe, Verlängerung und konfigurierbare Leihregeln; neuere Versionen pflegen auch Reservierungsabläufe.
4. **Membership:** Leser und Mitgliedschaftstypen anlegen, bearbeiten, suchen, sperren oder löschen.
5. **OPAC:** Öffentlicher Katalog mit erweiterter beziehungsweise fehlertoleranter Suche, Vorlagen und Medienanzeige.
6. **Stock Taking:** Inventurworkflow mit Bestandsprüfung und Aufbereitung von Abweichungen.
7. **Serial Control:** Abonnements und einzelne Periodikahefte verwalten, einschließlich Heft-/Eingangskontrolle.
8. **Reporting:** Reports zu Bibliografie, Lesern und Ausleihe, inzwischen auch PDF-Ausgabe für verschiedene Listen.
9. **Master File:** Norm-/Referenzdaten wie Autoren, Themen, allgemeine Materialbezeichnung und andere kontrollierte Listen.
10. **Systemverwaltung:** Benutzerrollen für Personal, Bibliothekseinstellungen, Indexwartung, Backup-Funktionen und Oberflächenkonfiguration.
11. **Dateianhänge:** Dokumente und Multimediadateien können an Einträge gebunden werden; in der Konfiguration sind etwa PDF, MP3 und Videodateiendungen berücksichtigt. Ein umfassender Reader/Streamer für alle Formate ist damit noch nicht belegt.
12. **Import und Schnittstellen:** Bibliografische Import-/Exportfunktionen, MARC-Verarbeitung, Erweiterungspunkte und Plugins; neuere Releases erweitern Such-, Sicherheits- und Konfigurationsmöglichkeiten.

**Medien:** Eine anpassbare allgemeine Materialbezeichnung erlaubt Bücher, DVD, Blu-ray, Musik- und Hörbuch-CDs. **E-Books und MP3-Dateien** sind eher Anhänge/digitale Dokumente als eine moderne vollständig verwaltete Streaming-Bibliothek.

**Grenzen:** Für anspruchsvolle deutschsprachige Normdaten- und Bibliotheksverbundprozesse prüfen, wie gut Workflows übersetzt und lokal angepasst sind. Durch PHP-Updates und Plugins entsteht administrativer Aufwand.

**Quellen:** [SLiMS-Quellcode und Projektbeschreibung](https://github.com/slims/slims9_bulian) · [Release-Historie](https://github.com/slims/slims9_bulian/releases) · [Konfiguration von Dateianhängen](https://github.com/slims/slims9_bulian/blob/master/sysconfig.inc.php)

## 5.5 RERO ILS

**Kurzprofil:** In der Schweiz entwickelte moderne Bibliotheksverwaltung, besonders geeignet für Bibliotheken in Organisationsnetzwerken. **Technik:** Invenio/Python, Webanwendung, JSON-orientierte Metadaten und APIs. **Lizenz:** AGPL-3.0. **Einsatz:** Bibliotheksnetze, auch unabhängige Bibliotheken.

**Dokumentierte Funktionsbereiche:**

1. **Verbund-/Mandantenmodell:** Organisationen mit mehreren Bibliotheken nutzen einen gemeinsamen bibliografischen Datenpool, können aber Einstellungen pro Organisation/Bibliothek anpassen.
2. **Katalogisierung:** Moderner Editor für verschiedene Dokumentarten; Bezug auf RDA und BIBFRAME-orientierte Datenmodelle.
3. **Physische Exemplare:** Bestände, Standorte und Leihstatus mit der zentralen Bibliografie verknüpfen.
4. **Ausleihe und Rückgabe:** Nutzung professioneller Checkout-/Check-in-Workflows und Patron Management.
5. **Bestellungen/Vormerkungen:** Anfragen und Reservierungen im Bibliotheksalltag sowie Kontoansichten im öffentlichen Portal.
6. **Fernleihe:** Interlibrary-Loan-Unterstützung wird ausdrücklich dokumentiert.
7. **Periodika:** Abonnements, Prognosen für kommende Ausgaben und Hefteingänge.
8. **Online-Katalog:** Recherche, Filter, organisationsbezogene Darstellung und Benutzer-Selbstverwaltung.
9. **Externe E-Ressourcen:** Anzeige von Dokumenten externer Plattformen (E-Books, Datenbanken usw.) im Suchkatalog.
10. **API/Datenaustausch:** JSON-basierte Bibliografien, Programmierschnittstelle, Abfragen, Exporte und Systemintegration.
11. **Webbetrieb:** Personal und Leser benötigen im Normalfall lediglich einen Browser; die Serverplattform kann institutionell betrieben werden.

**Medien:** Bibliografische Beschreibung unterschiedlicher physischer Dokumente einschließlich DVD, Blu-ray und Audio-CD möglich. **E-Books** lassen sich insbesondere über externe Plattformen nachweisen. Kein als Kernfunktion ausgewiesener allgemeiner Film- oder Hörbuchplayer.

**Grenzen:** Für die lokale Einzelinstallation müssen Serverbetrieb, Docker-Setups, Datenmigration und die vorhandenen deutschsprachigen Arbeitsabläufe geprüft werden.

**Quellen:** [RERO ILS Online-Hilfe](https://bib.rero.ch/help/intro/) · [RERO ILS GitHub](https://github.com/rero/rero-ils)

## 5.6 PMB

**Kurzprofil:** Französisches freies Bibliotheks- und Dokumentationssystem für physische wie digitale Ressourcen. **Technik:** PHP mit SQL-Datenbank und Weboberfläche. **Lizenz:** CeCILL. **Einsatz:** Bibliotheken, Mediotheken, Fachinformationsstellen, Dokumentationszentren.

**Dokumentierte beziehungsweise breit belegte Funktionsbereiche:**

1. **Bibliografischer Katalog:** Datensätze für Bücher, AV-Medien, Zeitschriften und Dokumente mit klassifikatorischen und inhaltlichen Angaben.
2. **Exemplare und Standorte:** Einzelne Medien, Verfügbarkeit, räumlicher Standort und Bestandszustand.
3. **Leserkonten:** Benutzergruppen und Ausleihstatus, verknüpft mit der Ausleihtheke.
4. **Ausleihe:** Ausgabe, Rückgabe, Verlängerung, Einschränkungen und Vormerkungen.
5. **Öffentliche Recherche (OPAC):** Suchoberfläche für Leser, Filterung und Dokumentanzeigen.
6. **Dokumentenportal:** Gestaltung und Präsentation eines Informationsportals mit redaktionellen Inhalten neben Katalogeinträgen.
7. **Vokabulare/Thesauri:** Inhaltliche Erschließung, Klassifikationen und fachliche Schlagwortsysteme; relevant für Spezialbibliotheken.
8. **Periodika:** Nachweis fortlaufender Medien und entsprechende verwaltende Workflows.
9. **Erwerbung:** Bestandsaufbau, Beschaffungs- und verwaltungsbezogene Abläufe abhängig von Konfiguration/Version.
10. **Digitale Dokumente:** Nachweis, Links und Einbindung digitaler Quellen neben dem physischen Bestand.
11. **Mehrstandortorganisation:** Unterschiedliche Bibliotheken und dokumentarische Einheiten können in einem gemeinsamen System abgebildet werden.
12. **Anpassung:** Umfangreiche Parametrierbarkeit und Dienstleistungsangebot des kommerziellen Projektträgers, obwohl die Software selbst frei lizenziert ist.

**Medien:** PMB ist für eine **Mediothek** geeignet, also neben Büchern auch CDs, DVDs, Blu-rays und Hörbücher als katalogisierte und ausleihbare Objekte. **E-Books** als digitale Quellen/Dateien erfordern gesonderte Prüfung des konkreten Medienzugriffs und der Lizenzanbindung.

**Grenzen:** Französisches Ökosystem; verfügbare Open-Source-Builds, Installationswege, lokale Übersetzungen und einzelne Module sollten vor Einführung praktisch überprüft werden. Einige hier genannten Abläufe können versions-/implementierungsabhängig sein.

**Quellen:** [PMB Services](https://www.sigb.net/) · [Funktions-/Hintergrundüberblick](https://fr.wikipedia.org/wiki/PMB_%28logiciel%29)

## 5.7 InvenioILS

**Kurzprofil:** Auf dem Invenio-Framework aufbauendes Bibliothekssystem, dessen Datenmodell auf strukturierten JSON-Schemas beruht. **Technik:** Python/Invenio-Backend, Weboberfläche/React, weitere Serverdienste. **Lizenz:** MIT (Invenio-App-ILS). **Einsatz:** wissenschaftliche und spezialisierte Bibliotheken, etwa in Forschungsumgebungen.

**Dokumentierte Funktionsbereiche:**

1. **JSON-basierte Bibliografie:** Strukturierte *Documents*, *Series*, *Items* und *Electronic Items* statt eines nur auf gedruckte Bücher zugeschnittenen Modells.
2. **Katalogisierung:** Titel-/Dokumente erfassen, bearbeiten, suchen und mit Exemplaren verbinden.
3. **Physische Bestände:** Exemplare mit Status und zugehörigen bibliografischen Informationen.
4. **Elektronische Bestände:** Eigener Datensatztyp für *Electronic Items* und Beziehungen zu digitalem Material.
5. **Benutzer-/Leserverwaltung:** Konten und Rollen für Bibliotheksmitarbeiter und Nutzende.
6. **Ausleihe:** Konfigurierbare Ausleih- und Rückgabevorgänge sowie Übersichten offener Arbeiten.
7. **Anfragen:** Leserwünsche, Reservierungen und Bearbeitungszustände.
8. **Erwerbung:** Einfachere Beschaffungs-/Zugangsvorgänge.
9. **Fernleihe:** Eigener Bereich für Interlibrary Loans.
10. **Dashboards:** Aufgaben- und Arbeitsstandsübersichten für das Bibliothekspersonal.
11. **API-Orientierung:** Erweiterung durch Invenio-Module und programmgesteuerte Datenverarbeitung, sinnvoll bei individueller Integration.

**Medien:** Papierbücher und unterschiedliche andere Dokumente sind konzeptionell möglich; bei DVD/Blu-ray/CD muss die praktische Oberfläche und das Feldermodell geprüft werden. E-Books werden über Electronic-Item-Datensätze adressiert, **nicht** automatisch als allgemeine EPUB-/M4B-Streamingbibliothek.

**Grenzen:** Der Begriff „ILS“ garantiert keine vollständige Funktionsgleichheit mit Koha; besondere Erwerbungs-, Zeitschriften- oder Medienmetadatenvorgänge sind auf der konkreten Installation zu prüfen.

**Quellen:** [InvenioILS-Produktseite](https://inveniosoftware.org/products/ils/) · [Backend-Repository](https://github.com/inveniosoftware/invenio-app-ils) · [Frontend](https://github.com/inveniosoftware/react-invenio-app-ils)

## 5.8 ABCD – Automation of Libraries and Centres of Documentation

**Kurzprofil:** Modularer Baukasten für Bibliotheken und Dokumentationszentren mit traditionellem CDS/ISIS-/CISIS-Hintergrund. **Technik:** überwiegend PHP/IsisScript/CISIS. **Lizenz:** LGPL-3.0, Abhängigkeiten mit eigenen Lizenzen. **Einsatz:** spezialisierte Informationsbestände, Bibliotheken mit individuellen Datenstrukturen.

**Dokumentierte Funktionsbereiche:**

1. **Eigene Datenbanken:** Frei definierbare Datenbanken mit Felddefinitionen, Indexstrukturen, Darstellungsformaten und Eingabemasken statt ausschließlich eines festen Bibliotheksschemas.
2. **Katalogisierung:** Bibliografische Datensätze für Bücher und Zeitschriften in unterschiedlichen Schemata; unter anderem MARC21, Dublin Core und spezifische Fachstandards.
3. **Exemplare:** Zuordnung von Verfügbarkeit und Bestandsinformationen je nach Datenbankentwurf.
4. **Erwerbung:** Beschaffungsvorgänge im Modul ABCD Central.
5. **Ausleihe:** Leserverwaltung und Buchung von Medienbewegungen.
6. **Statistiken:** Bibliotheks- und Bestandsauswertungen.
7. **Bibliotheksdienste:** Barcode-/Label-Druck, selektive Informationsverbreitung und Datenqualitätsfunktionen.
8. **Datenbank-Utilities:** Im-/Export, Druck, Datensatzsperren, globale Massenänderungen und administrative Werkzeuge.
9. **Native OPAC:** Suche über mehrere Katalogdatenbanken mit Facetten, mehrsprachiger und anpassbarer Oberfläche.
10. **iAH-OPAC:** Alternative Suchoberfläche für bibliothekarische/rechercheorientierte Datenbestände.
11. **ABCD Site:** Portal-/CMS-Bereich für redaktionelle Inhalte, Links und Informationsangebote.
12. **OAI-PMH:** Metadatenabgabe an externe Sammler in standardisierten Formaten.
13. **Interoperabilität:** Z39.50 und andere bibliografische Austauschmöglichkeiten.

**Medien:** Frei definierbare Felder und Masken erlauben spezialisierte Kataloge für DVDs, Blu-rays, Musik-/Hörbuch-CDs, Videos und elektronische Dokumente. Die **konkreten** Schemata und Ausleihlogik dafür müssen von der betreibenden Einrichtung entworfen beziehungsweise angepasst werden.

**Grenzen:** ABCD ist funktional sehr offen, verlangt aber mehr Datenmodellierungs- und Administrationskompetenz. In der offiziellen Einführung werden einige Erweiterungen wie umfassende digitale Volltextbibliothek und Online-Dokumentlieferdienst als neu, geplant oder noch unvollständig dokumentiert beschrieben: **nicht ohne Prüfung als produktionsreif voraussetzen**.

**Quellen:** [ABCD-Übersicht mit Modulen und Hinweisen zu geplanten Funktionen](https://abcd-devcom.github.io/docs/2.0/abcd-introduction/overview) · [Katalogisierung](https://abcd-devcom.github.io/docs/3.4/cataloguing) · [Quellcode/Lizenz](https://github.com/ABCD-DEVCOM/ABCD)

## 5.9 Next-L Enju Leaf

**Kurzprofil:** Japanisches Open-Source-ILS mit Websuche, Ausleihe und klassischem Bibliotheksbetrieb. **Technik:** Ruby on Rails. **Lizenz:** MIT. **Einsatz:** vor allem japanische Bibliothekslandschaft; international nur nach Lokalisierungsprüfung.

**Dokumentierte Funktionsbereiche:**

1. **Bibliografische Recherche:** Medienbestände suchen und Details öffentlich anzeigen.
2. **Datensatzerfassung:** Titel und zugehörige Exemplare pflegen; Materialformen im System hinterlegen.
3. **Material- und Ausleihklassen:** Physische Dokumenttypen mit ausleihbezogenen Regeln verknüpfen.
4. **Leserkonten:** Nutzerinformationen bearbeiten und Berechtigungen verwalten.
5. **Ausleihe:** Material per Barcode und Lesernummer ausgeben und Ausleihstatus anzeigen.
6. **Rückgabe:** Medien zurückbuchen; vorgemerkte Materialien gesondert behandeln.
7. **Verlängerung:** Bestehende Leihvorgänge verlängern, soweit Ausleihregeln es zulassen.
8. **Vormerkung:** Neue Reservierungen, Änderungen, Stornierung und Verwaltung bereitgelegter Exemplare.
9. **Überfälligkeit:** Anzeige überzogener Ausleihen und dazugehöriger Transaktionen.
10. **Zeitschriften und Neuerwerbungen:** Eingang und Bereitstellung von Titeln und fortlaufenden Beständen.
11. **Inventur:** Prüfung des vorhandenen Bestands.
12. **Statistik:** Bibliotheksbetriebliche Auswertungen.
13. **Datenexport/Web-API:** Programmgesteuerte Such-/Ergebnisabfragen, Export zum Beispiel als TSV und RSS in den dokumentierten Workflows.
14. **Veranstaltungen/Schließtage:** Verwaltung von Bibliothekskalenderdaten laut Betriebshandbuch.

**Medien:** Dokumentformen sind konfigurierbar; DVD/Blu-ray/CD/Hörbuch sind daher **als Datenmodell** möglich, aber eine fertig lokalisierte Film- oder Musikkatalogisierung ist nicht aus der eingesehenen Dokumentation belegt. Bei E-Books ist ein bibliografischer Nachweis plausibel, nicht jedoch ein vollwertiger EPUB-Reader.

**Grenzen:** Das ausführliche Handbuch ist überwiegend japanisch; einzelne Dokumentationsseiten beziehen sich auf ältere Versionen und weisen ausdrücklich auf damals fehlende oder fehlerhafte Features hin. Vor produktiver Nutzung aktuellen Code und Demo testen.

**Quellen:** [Repository](https://github.com/next-l/enju_leaf) · [Betriebshandbuch](https://next-l.github.io/manual/1.1/) · [Ausleihe, Rückgabe, Vormerkungen](https://next-l.github.io/manual/1.3/enju_operation_6.html) · [Material-/Ausleihklassen](https://next-l.github.io/manual/1.2/enju_setup_3.html)

---
# 6. Kleine Bibliotheksverwaltungen

## 6.1 BiblioteQ

**Kurzprofil:** Klassische grafische, vielseitige Bibliotheksverwaltung mit lokalem oder SQL-basiertem Datenbestand. **Technik:** C++/Qt, SQLite oder PostgreSQL. **Lizenz:** BSD-3-Clause. **Plattformen:** u. a. Linux, Windows, macOS, FreeBSD und OpenBSD.

**Dokumentierte Funktionsbereiche:**

1. **Mehrere Materialkategorien:** Native Katalogisierung von **Büchern, DVDs, Musik-CDs**, Zeitschriften, Journalen, grauer Literatur, Fotosammlungen und Videospielen.
2. **Katalogeinträge:** Fachspezifische Eingabedialoge, Titel, Identifikatoren, Inhaltsdaten, individuelle Felder, Preise, Währungen und weitere Eigenschaften.
3. **Buchcover und Abbildungen:** Bilder abrufen, hineinziehen, aus der Zwischenablage einfügen oder anpassen.
4. **Leser-/Mitgliedsdaten:** Informationen über Ausleihende und eigene Rechte für Mitarbeiter/Administratoren.
5. **Verleih:** Ausgegebene Medien, Verfügbarkeiten, Ausleih- beziehungsweise Rückgabevorgänge und überfällige Artikel nachhalten.
6. **Reservierungen:** Medien reservieren, angefragte und reservierte Elemente auflisten; bei Bedarf Historien für Leser speichern.
7. **Online-Recherche:** ISBN-/Katalogdaten über Open Library, SRU oder Z39.50 abrufen und bestehende Datensätze ergänzen.
8. **Bibliografische Austauschformate:** MARC21 und UNIMARC im geeigneten Funktionsbereich; Verarbeitung lokaler MARC-Felder.
9. **Suche:** Felder durchsuchen, Listen filtern und auch benutzerdefinierte SQL-Abfragen ausführen.
10. **Import/Export:** Buch-CSV-Import, CSV-Export von Ansichten und Zusammenführen von SQLite-Datenbanken.
11. **Datenspeicher:** Komplett offline mit SQLite arbeiten oder PostgreSQL für Berechtigungen und mehrere Konten einsetzen. PostgreSQL-Rechte und teilweise zeilenbezogene Zugriffskontrolle werden dokumentiert.
12. **Dateianhänge:** Dateien zu Medien verknüpfen, externe Anwendungen verwenden und – abhängig von der Bibliothek/Build-Konfiguration – einen PDF-Reader integrieren.
13. **Drucken:** Listen und Dokumente mit Druckvorschau; Barcode-Scanner können wie Tastatureingaben eingesetzt werden.
14. **Internationalisierung:** Unter anderem deutschsprachige Oberfläche, mehrere Iconsätze und portable Installationsvarianten.
15. **Datenschutz und Offlinebetrieb:** Ein lokaler SQLite-Katalog benötigt keinen fremden Cloud-Dienst; der Einsatz externer Metadatenquellen ist eine gesonderte Entscheidung.
16. **Ausfallsichere Datenänderungen:** Datenbankoperationen transaktional ausführen; bei PostgreSQL zusätzlich Benutzerkonten, Berechtigungen und zeilenbezogene Zugriffskontrollen berücksichtigen.

**Medien:** **DVD und Musik-CD werden ausdrücklich unterstützt.** Blu-ray lässt sich als Videodatensatz mit passendem Medium kennzeichnen; wie weit Blu-ray-spezifische Felder fertig vorhanden sind, ist weniger eindeutig. Hörbuch-CDs lassen sich als Audioartikel oder eigene Kennzeichnung erfassen. **E-Books** können als Datensätze/Anhänge verknüpft, gegebenenfalls PDFs betrachtet werden; kein nachgewiesenes eReader-Sync-Ökosystem.

**Grenzen:** Gegenüber Koha weniger weitreichende bibliothekarische Geschäftsprozesse. Beim Import von Film- und Musik-Metadaten sind Z39.50/Open-Library-Quellen nicht mit speziellen Filmdatenbanken gleichzusetzen. Eine eigene mobile Weboberfläche ist nicht der klassische Kern.

**Quellen:** [README und vollständige Projekt-Featureliste](https://github.com/textbrowser/biblioteq) · [BSD-3-Clause-Lizenzdatei](https://github.com/textbrowser/biblioteq/blob/master/LICENSE)

## 6.2 OpenBiblio (deutsche Fortführung)

**Kurzprofil:** Kompakte webbasierte Verwaltungssoftware für kleine Bibliotheken. **Technik:** PHP, SQL-Datenbank. **Lizenz:** GPL. **Einsatz:** Vereine, Schulbibliotheken, kleinere Einrichtungen. Hinweis: Hier geht es insbesondere um die unter openbiblio.de gepflegte Fortführung, nicht um die nicht mehr gepflegte historische SourceForge-Version.

**Dokumentierte Funktionsbereiche:**

1. **Katalogisierung:** Medientitel und Einzelexemplare anlegen, suchen, korrigieren und löschen.
2. **Medienarten:** Eigene Materialtypen mit Bezeichnung, Symbol, Ausleihlimit und Kataloganzeige konfigurieren.
3. **Klassifikationen/Genres:** Fachliche beziehungsweise thematische Gruppen zur Bestandsorganisation festlegen.
4. **Mitglieder:** Bibliotheksmitglieder anlegen, ändern, suchen und löschen.
5. **Ausleihe:** Medien auf Mitgliedskonten ausgeben, einsehen und zurückbuchen.
6. **Vormerkungen:** Reservierungen und Vorbestellungen innerhalb der Bibliothek bearbeiten.
7. **Gebühren:** Gebühreninformationen und damit zusammenhängende Leserhistorie verwalten.
8. **Rückgabeablage:** Rückgaben in einen geordneten Bearbeitungszustand übernehmen.
9. **Mitarbeiterkonten:** Personal anlegen, Passwörter und Berechtigungen verwalten.
10. **Administration:** Allgemeine Bibliothekseinstellungen, Materialarten, Genres und anpassbare Layoutdarstellung.
11. **Berichte:** Auswertungen und Listen zu Bibliotheksdaten.
12. **Etiketten:** Druckbare Labels für Medienverwaltung.
13. **OPAC:** Öffentliche Katalogsuche neben der Verwaltungsoberfläche.

**Medien:** DVDs, CDs und Hörbuch-CDs können über **eigene Medienarten** katalogisiert werden; Blu-ray ist als zusätzlich zu definierender Typ sinnvoll. **E-Books:** Ein Datensatz oder URL-Hinweis kann denkbar sein; ein moderner EPUB-Webreader, M4B-Audioplayer oder DRM-Ausleihserver ist nicht nachgewiesen.

**Grenzen:** Weniger umfassend als Koha, insbesondere bei Lieferanten, ERM und bibliografischer Normdatenarbeit. Bei Medienerfassung muss überprüft werden, ob die Standardmaske alle benötigten Filmsprache-/Audiofelder enthält.

**Quellen:** [OpenBiblio-Installation und Funktionsübersicht](https://openbiblio.de/openbiblio/home/index.php) · [Medienarten-Dokumentation](https://openbiblio.github.io/openbiblio_docs/sysadmin/root.html) · [deutsches Projekt](https://openbiblio.de/)

## 6.3 OpenLibry

**Kurzprofil:** Deutschsprachige, moderne Anwendung für Schulbibliotheken, bewusst auf schnelle Erfassung und Ausleihe von Büchern ausgelegt. **Technik:** Weboberfläche/Next.js und SQLite-basierter Betrieb. **Lizenz:** MIT. **Betrieb:** lokal, Raspberry Pi, Docker oder Server.

**Dokumentierte Funktionsbereiche:**

1. **Büchererfassung:** Titel, Autoren, ISBN und Exemplarinformationen verwalten.
2. **Cover-Automatik:** Buchcover aus externen Quellen abrufen.
3. **Schnellsuche:** Sofortige Trefferlisten bei der Eingabe, um den Tresenbetrieb zu beschleunigen.
4. **Ausleihe:** Bücher mit Barcode-Scanner auf Schüler-/Mitgliedskonten ausgeben.
5. **Rückgabe:** Medien zügig wieder einbuchen und als verfügbar kennzeichnen.
6. **Benutzerverwaltung:** Schülerinnen/Schüler beziehungsweise andere Bibliotheksnutzer erfassen und pflegen.
7. **Ausleihzeiten:** Leihdauern und zugehörige Abläufe konfigurieren.
8. **Mahnungen und Labels:** Grundlegende Konfiguration von Mahnungs-/Etikettenprozessen laut Projektdokumentation.
9. **Statistiken:** Bestands- und ausleihbezogene Kennzahlen.
10. **Datenübernahme:** Bücher und Nutzerdaten aus Excel und OpenBiblio importieren.
11. **Responsive Weboberfläche:** Browserbetrieb auf Computer, Tablet oder Smartphone.
12. **Deployment:** Docker und Raspberry Pi, außerdem Serverbetrieb hinter Reverse Proxy.

**Medien:** **Bücher stehen eindeutig im Vordergrund.** Eine verlässlich dokumentierte native Verwaltung spezifischer DVD-/Blu-ray-/Musik-CD-/Hörbuch-CD- oder EPUB-/M4B-Typen ist in den öffentlich gelesenen Hauptquellen **nicht belegt**. Dafür müsste die Version installiert beziehungsweise die Datenmaske geprüft werden.

**Grenzen:** Für eine reine Schulbibliothek attraktiv; für eine Mediothek mit vielen Sonderfeldern ist BiblioteQ, SLiMS oder Koha wahrscheinlich die sicherere Wahl.

**Quellen:** [OpenLibry GitHub](https://github.com/jzakotnik/openlibry) · [Dokumentation](https://openlibry.de/site)

---

# 7. Sammlungsverwaltungen

## 7.1 Tellico

**Kurzprofil:** Sehr anpassbares KDE/Qt-Programm für unterschiedliche Sammlungen. **Technik:** C++/Qt/KDE, lokale, dokumentbasierte Sammlung (XML-basiertes eigenes Dateiformat). **Lizenz:** GPL. **Einsatz:** private Fachbibliotheken, Film-, Musik- und andere Sammlungen.

**Dokumentierte Funktionsbereiche:**

1. **Sammlungsvorlagen:** Bücher, Bibliografien, Comics, **Videos**, **Musik**, Videospiele, Brettspiele, Münzen, Briefmarken, Karten, Weine und allgemeine frei definierbare Sammlungen.
2. **Frei konfigurierbare Felder:** Text, Langtext, Zahl, Ja/Nein, Auswahl, Datum, Tabelle, Bewertung, URL, Bild und berechnete Felder; auch Fachinformationen wie Disc-Zahl/Region/FSK können ergänzt werden.
3. **Buchfelder:** Titel, Untertitel, Autor, Einband, Verlag, ISBN, Seitenzahl, Reihe, Sprache, Genre, Zustand, Kaufdatum, Bewertung, Cover und weitere standardmäßige Felder.
4. **Videofelder:** Medium, Produktionsjahr, Laufzeit, Regie, Rollenbesetzung, Genre, Region, Sprache, Ton-/Untertitelspuren, Seitenverhältnis, Studio, Cover und Bewertungen.
5. **Musikfelder:** Albumtitel, Künstler, Label, Erscheinungsjahr, Medium, Genre, Tracks, Bewertung und Cover.
6. **Online-Anreicherung:** Metadaten aus verschiedenen Datenquellen, unter anderem Buch-, Film- und Musikquellen; aktuelle Projektseite nennt Google Books, IMDb, Discogs und IGDB.
7. **Gruppierung und Filter:** Einträge nach selbst ausgewählten Eigenschaften sortieren, filtern und in verschiedenen Ansichten anzeigen.
8. **Mehrfachbearbeitung:** Zahlreiche Einträge gemeinsam ändern und Daten bei Bedarf aktualisieren.
9. **Ausleihvermerk:** Einfache Verleihkontrolle innerhalb privater Sammlungen (nicht identisch mit einer ILS-Ausleihtheke).
10. **Berichte:** Sammlungsübersichten mit Vorlagen generieren und drucken.
11. **Import:** Verschiedene Fremdformate und Dateilisten übernehmen, unter anderem Datenaustausch mit anderen Sammlungsprogrammen.
12. **Export:** Unter anderem XML, ZIP, HTML, CSV, BibTeX, ONIX und GCstar-Formate je nach Datenart.
13. **Automation:** Kommandozeilenparameter und D-Bus-Schnittstelle für technische Integrationen.
14. **Datenhoheit:** Lokale Dateien ohne zwingenden fremden Cloud-/SQL-Server.

**Medien:** **Sehr gut für DVD, Blu-ray, Musik-CD und Hörbuch-CD**, letztere nötigenfalls als spezieller Musikeintrag oder eigene Sammlung. Videos besitzen sogar Tonspur-, Untertitel- und Regio-Felder. Für E-Books kann ein Datensatz mit Datei/URL gepflegt werden, aber Tellico ist **kein E-Book-Reader oder Musikplayer**. Mehrfach-Exemplare und komplexe Ausleihe können Zusatzfelder erfordern.

**Grenzen:** Katalogsoftware, kein ILS mit mehreren Bibliothekszweigstellen. Laut Handbuch weder Audio-/Videoplayer noch Multimediaeditor.

**Quellen:** [Tellico-Projekt](https://tellico-project.org/) · [Offizielles Handbuch mit Funktionsgliederung](https://docs.kde.org/trunk_kf6/en/tellico/tellico/index.html) · [Video- und Musiksammlungen](https://docs.kde.org/stable_kf6/en/tellico/tellico/collection-types.html)

## 7.2 GCstar

**Kurzprofil:** Freier, plattformübergreifender Sammlungsmanager mit mehreren Medienmodellen. **Technik:** Perl und GTK. **Lizenz:** GPL (genaue Version der verwendeten Distribution im Repository prüfen). **Plattformen:** Linux, Windows, FreeBSD, macOS.

**Dokumentierte Funktionsbereiche:**

1. **Sammlungstypen:** Fertige Modelle für Bücher, Filme, Comics, Musik, Fernsehserien, Videospiele, Brettspiele, Spielzeug, Münzen, Briefmarken und weitere Kategorien.
2. **Filmkatalog:** Titel, Beteiligte, Medienformat, Genre und andere für DVDs/Blu-rays relevante Informationen.
3. **Musikalben:** CD-/Musikkataloge mit Künstler-, Album- und gegebenenfalls Titeldaten.
4. **Eigene Modelle:** Struktur/Anzeige individuell anpassen und für neue Medienarten erweitern.
5. **Online-Plugins:** Daten aus Online-Diensten herunterladen und lokale Einträge damit vervollständigen.
6. **Barcode-Erkennung:** Dokumentierte Nutzung von Barcodes für **Bücher, CDs, DVDs und Blu-rays**.
7. **Suchfunktionen:** Filtern und Suchen innerhalb der Sammlung, verschiedene Ansichtsformen.
8. **Ausleihkontrolle:** Verliehene Sammlungseinträge einer Person zuordnen und Rückgaben nachhalten.
9. **Import:** Unter anderem von kompatiblen Sammlungsprogrammen und textuellen Austauschformaten.
10. **Export:** HTML-Ausgaben mit Formatvorlagen, CSV sowie Datenaustausch mit Tellico und Data Crow.
11. **Bedienoberfläche:** Desktop-Anwendung mit Medienbildern, Feldern und anpassbaren Darstellungen.

**Medien:** **DVDs, Blu-rays, Musik-CDs und Bücher** sind ausdrücklich im Funktionsansatz enthalten. Hörbuch-CDs können als Audio-/Musikalbum oder mit eigenem Modell gepflegt werden. E-Books/digitale Hörbücher sind eher Datei-/Metadatenobjekte; echter Reader beziehungsweise Hörbuchserver ist nicht der Kern.

**Grenzen:** Kein vollständiges OPAC-/Bibliotheksverbundsystem; Online-Datenquellen können ausfallen. Dokumentationsstand und tatsächlichen Entwicklungsstand getrennt prüfen.

**Quellen:** [Offizielle GCstar-Dokumentation](https://gcstar.gitlab.io/gcstar_docs/en/) · [Ausleihverwaltung](https://gcstar.gitlab.io/gcstar_docs/en/)

## 7.3 Data Crow

**Kurzprofil:** Leistungsfähiger, sehr flexibler Sammlungsmanager mit getrennten Modulen, freien Datenfeldern und eigenen Modultypen. **Technik:** Java, Desktop und je nach Version Web-/Client-Server-Komponenten. **Lizenz:** GPL-3.0-or-later. **Einsatz:** Große private Medien- und Objektsammlungen mit verschiedensten Medienarten.

**Dokumentierte Funktionsbereiche:**

1. **Buchmodul:** Bücher und E-Books (insbesondere PDF) aufnehmen; Autoren und Verlage in eigenen miteinander verbundenen Datenbereichen verwalten.
2. **Filmmodul:** Filme samt Filmdaten, Besetzung, Medienart, Cover, Genre und verwandten Eigenschaften katalogisieren.
3. **Musikalbenmodul:** Musik-CDs und digitale Alben mit Interpreten, Veröffentlichungsdetails und musikbezogenen Metadaten erfassen.
4. **Software-/Spielemodul:** Programme und Videospiele katalogisieren und Hersteller/Entwickler verknüpfen.
5. **Übergreifendes Medienmodul:** Daten verschiedener Medienmodule in einer gemeinsamen Sicht überblicken.
6. **Eigene Sammlungstypen:** Neue Module für beispielsweise Hörbücher, Fotoarchive oder beliebige Gegenstände definieren.
7. **Eigene Felder:** Bestehende Module erweitern und Feldtypen/Anzeige an die Sammlung anpassen.
8. **Hierarchische Standorte/Container:** Gebäude → Etage → Raum → Schrank → Regal → Fach; sehr hilfreich für physische Disc- und Buchsammlungen.
9. **Online-Suche:** Metadaten über unterschiedliche Dienste beziehen; Beispiele sind Open Library für Bücher und Discogs für Musik.
10. **Dateiimport:** Vorhandene Medienfiles analysieren; bei Musik können unter anderem MP3-, OGG- und FLAC-Metadaten gelesen werden.
11. **Kontakte:** Personen verwalten, die Gegenstände aus der Sammlung ausleihen.
12. **Verleihverwaltung:** Festhalten, wer welches Objekt geliehen hat und wann eine Rückgabe fällig ist.
13. **Berichte:** Modulspezifische Auswertungen; JasperReports im klassischen System.
14. **Datenübernahme:** Import aus bestehenden Sammlungsbeständen, Text-/Dateiquellen und Exportmöglichkeiten.
15. **Benutzerkonten:** Bei mehrbenutzerfähigen Betriebsweisen Konten und Berechtigungen verwalten.
16. **Anpassbarkeit:** Aussehen, Felder und Modulstrukturen weitgehend ohne Anpassung des Java-Quellcodes verändern.

**Medien:** **Eine der besten Optionen für alle physischen Medien.** Blu-ray kann als Film mit Formatangabe geführt werden, Hörbuch-CD als Musik-/Audioobjekt oder eigenes Hörbuchmodul. Bücher/EPUB/PDF-Dokumente lassen sich über Buchmodul beziehungsweise Dateiverweis verwalten. **Kein universelles Blu-ray-Abspiel- oder Hörbuch-Streaming-System.**

**Grenzen:** Größerer Einrichtungsaufwand als Tellico; flexible Module erfordern ein sauberes eigenes Datenmodell. Die Dateiverwaltung ist nicht mit einem modernen E-Book-Reader samt Gerätesynchronisierung gleichzusetzen.

**Quellen:** [Data Crow – Einführung mit Einzelmodulen](https://datacrow.org/de/docs/einfuhrung/) · [Projektwebsite](https://datacrow.org/de/) · [Quellcode und Builds](https://datacrow.org/de/code/)

## 7.4 Shelf (dgahagan/shelf)

**Kurzprofil:** Selbst gehosteter, multimedialer Haushaltskatalog mit moderner Barcode-/UPC-Erfassung; deutlich breiter als ein reines Buchregalprogramm. **Technik:** Python/FastAPI, SQLite, HTML/HTMX, Docker. **Lizenz:** AGPL-3.0. **Einsatz:** private Heimmediathek/Familie, ggf. kleine Gruppen.

**Dokumentierte Funktionsbereiche:**

1. **Viele Medientypen:** Bücher, Kinderbücher, Manga, Comics, Magazine, E-Books, Hörbücher, **DVDs, Blu-rays, CDs, Schallplatten, Kassetten, digitale Musik und Videospiele**.
2. **Barcode-Scan:** Gerätekamera oder USB/Bluetooth-Scanner; ISBN, EAN-13/8 und UPC-A/-E.
3. **Intelligente Medienerkennung:** Barcode und Produkttext liefern Vorschläge für Buch, Film, Musik oder Spiel; falsch zugeordnete Medien können korrigiert werden.
4. **Bücher-Metadaten:** Open Library, Google Books, Hardcover und für passende ISBNs nationale Bibliotheksdienste, z. B. DNB.
5. **Filmdaten:** DVD-/Blu-ray-Erfassung mit optionaler TMDb-Anbindung für Titel, Beschreibung und Cover.
6. **Musikpressungen:** MusicBrainz-Suche nach Interpret, Titel, Barcode oder Katalognummer; Unterscheidung von Pressungen, Labeln, Ländern, Ausgabejahren und Tracklisten mehrteiliger Alben.
7. **Spiele-Daten:** Metadaten/Plattformen über IGDB, auch für ältere Konsolen.
8. **Fotoerfassung ganzer Regale:** Foto einer Bücherreihe durch ein lokales oder externes Bildmodell auslesen lassen, Ergebnisse überprüfen und erst dann übernehmen. Optional, nicht Voraussetzung für den Grundbetrieb.
9. **Mehrere Scan-Modi:** Hinzufügen, Wunschliste, Ausleihen, Zurückgeben, Verschieben, Inventur, Nachschlagen und Schnellbewerten.
10. **Exemplare und Standorte:** Mehrere Exemplare verwalten, Standorte vergeben, innerhalb eines Regals sortieren und verschieben.
11. **Inventur:** Standort auswählen, tatsächliche Objekte einscannen und Fehlbestände erkennen.
12. **Verleihen und Zurückgeben:** Leihende, ausgegebene Medien und Rückgaben verfolgen.
13. **Lesestatus und Wunschlisten:** Gelesen/gesehen/gespielt, Wunschlisten, Bewertungs- und Statusinformationen je nach Medienart.
14. **Medienbeziehungen:** Physische und digitale Ausgabe eines Titels sowie Vorlage, Hörbuch und Verfilmung miteinander verknüpfen.
15. **Coversuche:** Bildquellen medienabhängig wählen; fehlende Cover manuell oder über Dienstesuche ergänzen.
16. **Periodika:** Publikation und Hefte zusammenhalten; ISSN-gestützte Erfassung mit 977-Barcodes ist dokumentiert.
17. **Mehrbenutzerbetrieb:** Haushaltskonten mit Rollen und differenzierten Berechtigungen.
18. **PWA/Offline-Ladenmodus:** In einem Geschäft ohne Netz prüfen, ob ein gescanntes Buch vorhanden oder auf der Wunschliste steht; spätere Synchronisation.
19. **Import/Export/Backups:** Sammlung sichern und Daten übertragen; optionale Integrationen für andere Services.
20. **Zusatzintegrationen:** Audiobookshelf (digitale Hörbücher), Komga (Comics), RomM (Spiele), Hardcover, TMDb, IGDB, Discogs und weitere Dienste; einzelne Quellen/Features verlangen Zugangsschlüssel.
21. **Wertschätzung:** Optionaler Zugriff auf ISBNdb für Versicherungs-/Bestandswerte; ein externer kostenpflichtiger Dienst kann beteiligt sein.
22. **Datenschutz/Betrieb:** Lokal in einem Docker-Container mit SQLite; Integrationen und externe Bild-/Metadaten-Abfragen sind optional und sollten datenschutzseitig bewertet werden.
23. **Exemplar- und Leihhistorie:** Einzelne physische Kopien und vergangene Ausleihvorgänge getrennt verfolgen; gelöschte Objekte bleiben zunächst in einem wiederherstellbaren Papierkorb.
24. **Musikalben im Detail:** Mehrere Veröffentlichungen desselben Albums mit Land, Label, Pressung und Tracklisten je Disc unterscheiden, damit CD und Vinyl nicht verwechselt werden.
25. **Flexible Integrationen:** Audio-/Comic-/Spielebestände etwa mit Audiobookshelf, Komga und RomM verknüpfen; ein Kataloglink ersetzt deren Streaming-/Lesefunktion nicht.

**Medien:** Unter den privaten Katalogen **besonders breit ausdrücklich multimedial dokumentiert**: DVD, Blu-ray, Musik-CD und Hörbuch-CD können erfasst werden. E-Books und digitale Hörbücher erscheinen ebenfalls als Sammlungstypen; die integrierte **Abspiel-/Lese-Funktion** ist jedoch nicht mit einem spezialisierten Lese-/Hörserver gleichzusetzen. Für Hörbücher existiert eine **Audiobookshelf-Integration**.

**Grenzen:** Relativ kleines Projekt; professioneller Bibliotheksbetrieb (MARC-Workflows, Budget-Erwerbung, Mahnwesen, Verbund-OPAC) ist nicht sein Ziel. Bild-KI benötigt je nach Backend Rechenkapazität oder API-Zugang; optionaler Onlinezugriff ist nicht „vollständig offline“ im Sinne jeder einzelnen Integration.

**Quellen:** [Offizielle README mit detaillierter Funktionsliste](https://github.com/dgahagan/shelf) · [Docker-Dokumentation und optionale Integrationen](https://github.com/dgahagan/shelf/blob/main/DOCKERHUB_README.md) · [Security](https://github.com/dgahagan/shelf/blob/main/SECURITY.md)

## 7.5 uBiblio

**Kurzprofil:** Kleines selbst gehostetes Webprogramm zum Verwalten und Teilen einer eigenen Büchersammlung. **Technik:** Webserver-Anwendung. **Lizenz:** GPL-3.0. **Einsatz:** Familie, Bekannte, private Buchclubs.

**Dokumentierte Funktionsbereiche:**

1. **Buchverwaltung:** Bücher anlegen, ändern, löschen und suchen.
2. **Papier und E-Books:** Das Projekt nennt ausdrücklich eine einheitliche Verwaltung physischer Bücher und elektronischer Bücher.
3. **ISBN-Autovervollständigung:** Buchfelder anhand eingegebener ISBN befüllen lassen.
4. **Kamera-Scan:** ISBN per Smartphonekamera erfassen.
5. **Benutzer:** Administratoren und weitere Nutzer; Einladung mit einmalig verwendbarem Link.
6. **Leselisten:** Pro Benutzer eigene geplante oder laufende Lektüre organisieren.
7. **Wunschlisten:** Gesuchte und nicht im Bestand befindliche Titel vormerken.
8. **Ausleihe:** Bücher ausgeben, Rückgaben erfassen und offene Ausleihen anzeigen.
9. **Gemeinschaftlicher Katalog:** Bestände mit Bekannten teilen; das Projekt beschreibt zudem föderierte Suche zwischen verbundenen Installationen.
10. **Selbsthosting:** Betrieb im Heimnetz oder isoliert auf einem einzelnen Rechner ohne zwingenden externen Cloudaccount.
11. **E-Book-Dateien:** Elektronische Bücher separat von physischen Exemplaren hochladen und berechtigten Nutzern zum Download anbieten. Das belegt nicht automatisch einen eingebauten EPUB-Reader.
12. **Bilder:** Mehrere Bilder oder Cover je Buch nach optionaler Aktivierung vorhalten, einschließlich Miniaturansichten.
13. **Anpassbare Felder:** Zwei zusätzliche konfigurierte Felder ergänzen das feste Buchschema.
14. **Backup/Restore:** Datenbank und hochgeladene Dateien gemeinsam sichern und wiederherstellen.
15. **Gerätezugang:** Schlichte, ressourcensparende Weboberfläche, die laut Projekt auch auf manchen E-Reader-Browsern verwendbar ist.

**Medien:** **Gedruckte Bücher und E-Books sind sicher belegt.** Ein native DVD-/Blu-ray-/Musik-CD-Verwaltung ist aus der Hauptdokumentation nicht ersichtlich. Digitale Hörbücher sollten daher nicht ohne Weiteres als unterstützt angenommen werden.

**Grenzen:** Kein Ersatz für Koha oder einen Multimedia-Server; Umfang der E-Book-Lesefunktionen und Aktivität des Projekts vor Migration prüfen.

**Quellen:** [uBiblio GitHub/README](https://github.com/seanboyce/ubiblio)

---
# 8. Digitale Bibliotheken und E-Book-Server

## 8.1 Calibre

**Kurzprofil:** Umfangreiche Desktop-Suite für E-Books und digitale Texte. **Technik:** Python/C++/Qt und integrierter Content-Server. **Lizenz:** GPL-3.0. **Plattformen:** Windows, Linux, macOS.

**Dokumentierte Funktionsbereiche:**

1. **Digitale Bibliotheken:** Eine oder mehrere Bibliotheken mit Titel, Autor, Reihe, Sprache, Schlagwörtern, Bewertungen, ISBN, Covern und Dateiformaten.
2. **Metadatenpflege:** Einträge bearbeiten, mehrere Bücher auf einmal aktualisieren, eigene Spalten anlegen sowie Metadaten aus Internetquellen beziehen.
3. **Ein Buch, mehrere Formate:** Zum selben bibliografischen Titel EPUB, PDF, AZW3 und andere E-Book-Dateien halten.
4. **Dateiverwaltung:** Dateien importieren, Bibliotheken wechseln, Dubletten erkennen beziehungsweise organisatorisch bearbeiten und auf Datenträger exportieren.
5. **Konvertierung:** Umfangreiche Formatumwandlung, Schriften-/Layoutanpassung, Inhaltsverzeichnisse und Optimierung für Lesegeräte.
6. **E-Book-Editor:** EPUB- und Kindle-nahe Formate bearbeiten, Quelltext/HTML/CSS und Inhaltsstruktur verändern.
7. **E-Book-Reader:** Integrierte Leseoberfläche mit Suche, Lesezeichen, Markierungen, Notizen, Vorlesefunktion (Text-to-Speech) und verschiedenen Layouts.
8. **Gerätesynchronisation:** Bücher via Kabel oder drahtlos an viele E-Reader übertragen und geeignete Formate automatisch bereitstellen.
9. **Content-Server:** Die eigene Bibliothek im Browser anzeigen, durchsuchen, lesen und herunterladen; je nach Setup Benutzerzugriffe konfigurieren.
10. **News/RSS:** Artikel aus Nachrichtenquellen in lesbare E-Books umwandeln und an Geräte übertragen.
11. **Kataloge und Berichte:** Buchlisten und exportierbare Katalogdarstellungen erzeugen.
12. **Plugins:** Erweiterungen über integrierten Plugin-Browser installieren; Verfügbarkeit und Sicherheit einzelner Plugins getrennt prüfen.
13. **Kommandoschnittstelle:** Bibliotheksverwaltung und Konvertierung automatisieren, etwa mit `calibredb` oder `ebook-convert`.
14. **Backup/Portabilität:** Bibliotheken und Metadaten exportieren/sichern und auf andere Geräte übertragen.

**Medien:** Hervorragend für **E-Books und PDFs**. Physische DVD, Blu-ray, Musik-CD und Hörbuch-CD werden nicht als klassische Leih-/Inventarobjekte verwaltet. Das Hinterlegen zusätzlicher Daten oder nichtstandardisierter Dateien ist kein Ersatz für ein Audiobook-/Video-System. Text-to-Speech ist **nicht** die Verwaltung eines professionell eingesprochenen Hörbuchs.

**Grenzen:** Keine klassische physische Ausleihe mit Benutzerausweisen, Rückgabefristen und CD-Barcodeinventur. DRM-geschützte gekaufte Bücher unterliegen weiterhin den jeweiligen Einschränkungen.

**Quellen:** [Calibre – Funktionsübersicht](https://calibre-ebook.com/about) · [Benutzerhandbuch](https://manual.calibre-ebook.com/) · [Content-Server](https://manual.calibre-ebook.com/server.html)

## 8.2 Calibre-Web

**Kurzprofil:** Mehrbenutzerfähige Weboberfläche für vorhandene **Calibre-Datenbanken**. Kein identischer Ersatz für die Calibre-Desktopsoftware. **Technik:** Python-Webanwendung. **Lizenz:** GPL-3.0. **Betrieb:** lokaler Server, NAS-/Linux-/Docker-Setups, soweit Dateisystem und Version passen.

**Dokumentierte Funktionsbereiche:**

1. **Zugriff auf Calibre-Daten:** Vorhandene Calibre-Bibliotheken über einen Browser öffnen und durchsuchen.
2. **Buchanzeige:** Cover, Autoren, Reihen, Kategorien, Bibliografien, Downloads und Filter.
3. **Erweiterte Suche:** Felder und Kategorien kombinieren und Ergebnisse einschränken.
4. **Regale:** Persönliche Bücherlisten und Collections organisieren.
5. **Benutzerverwaltung:** Mehrere Konten, detaillierte Leserechte, Administrator und eingeschränkter Gastzugang.
6. **Metadatenpflege:** Vorhandene Daten bearbeiten, Bücher löschen und neue Dateien hinzufügen, soweit die jeweilige Berechtigung es erlaubt.
7. **Automatische Metadaten:** Informationen aus externen Quellen beziehen; erweiterbar durch entsprechende Integrationen.
8. **Konvertierung:** Über optionale Calibre-Programme unterschiedliche Formate nach Bedarf konvertieren.
9. **Browser-Reader:** Unterstützte E-Books direkt online lesen.
10. **OPDS:** E-Book-Katalog für Lesegeräte-Apps bereitstellen.
11. **Kobo-Synchronisation:** Mit Calibre-Web verbundene Kobo-Geräte können E-Books aus dem Bestand abgleichen.
12. **Versand an E-Reader:** Bücher über eingerichtete Versandwege an Lesegeräte schicken.
13. **Zugriffskontrolle:** Downloads einschränken und Kategorien oder eigene Spalten je Benutzer ein-/ausblenden.
14. **Anmeldung:** Je nach Einrichtung lokale Nutzer, LDAP, OAuth oder Proxy-Authentifizierung und komfortable Anmeldung über Magic Links.
15. **Zusätzliche Datei-Uploads:** Die README erwähnt auch Audioformate, aber keinen vollständigen Hörbuchplayer als zentralen Funktionsumfang.
16. **Administration:** Mehrsprachigkeit, UI-Anpassungen, grafische Konfiguration und Wartungsoptionen.
17. **Anbindung vorhandener Benutzerverzeichnisse:** Unterstützte externe Authentifizierungsarten ermöglichen bestehende Konten zu verwenden; Rechte und Sichtbarkeit der Bücher bleiben in Calibre-Web gesondert zu konfigurieren.
18. **Individuelle Spalten:** Calibre-Benutzerspalten bei Anzeige, Suche und Zugriffskontrolle berücksichtigen; dadurch können eigene Felder wie Fachgebiet oder Lesestatus genutzt werden.

**Medien:** Ideal für **digitale Bücher**, nicht für physische DVDs und CDs. **Audio-Uploads** sind dokumentiert, aber native Kapitel-/Fortschrittsverwaltung für Hörbücher ist gegenüber BookOrbit/BookLore nicht als gleichwertig belegt.

**Grenzen:** Abhängigkeit von Calibres Datenbankschema und einer gültigen Bibliothek; gleichzeitige Schreibzugriffe auf dieselbe Datenbank und Backup-Strategie müssen geplant werden. Plugins und externe Konverter müssen gegebenenfalls zusätzlich installiert werden.

**Quellen:** [Calibre-Web README](https://github.com/janeczku/calibre-web) · [Releases](https://github.com/janeczku/calibre-web/releases)

## 8.3 BookOrbit

**Kurzprofil:** Selbst gehostete Bibliothek für **E-Books, Comics und digitale Hörbücher** mit integriertem Lese- und Hörzugriff. Laut Projekten offizieller Nachfolger von BookLore. **Technik:** moderner Webserver/-Client (siehe Repository). **Lizenz:** AGPL-3.0 mit ergänzenden Lizenz-/Attributionsbestimmungen; konkrete Hinweise des Projekts lesen.

**Dokumentierte Funktionsbereiche:**

1. **Digitale Bibliotheken:** Mehrere getrennte Verzeichnisse/Sammlungen mit eigenen Scanregeln und Formatprioritäten.
2. **E-Book-Import:** EPUB, KEPUB, PDF, MOBI, AZW/AZW3 und FB2.
3. **Comic-Import:** CBZ, CBR und CB7 mit passenden Reader-Ansichten.
4. **Hörbuch-Import:** M4B, MP3, M4A, OPUS, OGG und FLAC; mehrteilige Hörbücher aus Unterordnern wie „CD 1“/„Disc 2“ als ein Werk bündeln.
5. **Web-E-Book-Reader:** Bücher im Browser lesen und Fortschritt speichern.
6. **Audio-Streaming:** Hörbücher anhören; Kapitel und individuelle Wiedergabepositionen sind Teil des Hörbuchkonzepts.
7. **Lese-/Hörsynchronisation:** Lesen über Web, Kobo und KOReader mit bidirektionaler Fortschritts-/Anmerkungssynchronisierung im unterstützten Funktionsbereich.
8. **Mobile Nutzung:** Projekt beschreibt native iPhone-/Apple-Watch-App mit Offline-Lesen beziehungsweise Hörbuchwiedergabe; **Geräte-/OS-Mindestanforderungen prüfen** (laut README iOS 26/watchOS 26 und BookOrbit v3+).
9. **Metadaten:** Verschiedene Quellen wie Open Library, Google Books, Audible/Audnexus und weitere Anbieter; Auswahl und verfügbare Felder sind medienabhängig.
10. **Automatischer Import:** Überwachter Ordner („Book Dock“) für neue Dateien.
11. **Regale und intelligente Filter:** Manuelle Sammlungen, dynamische Listen und Such-/Metadatenfilter.
12. **Anmerkungen:** Markierungen, Lesestand und bibliotheksbezogene Nutzerdaten verwalten.
13. **Mehrbenutzerbetrieb:** Separate Nutzerdaten, Rechte und OIDC/SSO-Integration etwa über Authentik/Keycloak.
14. **Geräteauslieferung:** OPDS sowie Send-to-Kindle.
15. **Synchronisierung nach außen:** Integrationen mit Leselisten-/Notizdiensten wie Hardcover, Readwise oder StoryGraph nach Konfiguration.
16. **Statistiken:** Lesedaten, Nutzungsinformationen und Zusatzfunktionen zum Leseverhalten.
17. **Selbsthosting:** Eigene Speicherung, Konfiguration und Dateien; das Projekt warnt vor Risiken nicht unterstützter Netzwerk-Dateisysteme bei schreibenden Operationen.
18. **Mehrsprachige Anbieterabdeckung:** Laut Projekt sind 14 Metadatenquellen aus Buch-, Comic- und Hörbuchbereichen integriert, zum Beispiel Audible, Libro.fm und iTunes. Anbieter können eigene Nutzungsbedingungen oder Zugangsgrenzen besitzen.
19. **Aktuelle Mobilanwendung:** Die dokumentierte iOS-App unterstützt auch iPad-Bedienung und Offline-Operationen; die konkrete Funktionalität hängt von der jeweiligen Server-/Client-Kombination ab.
20. **Unterstütztes Dateisystem:** Für Bibliotheksdateien nach Möglichkeit lokale persistente Speicherung und ein getrenntes, überprüfbares Backup einsetzen; riskante Netzwerkdateisystem-Konstellationen sind keine zugesicherte Option.

**Medien:** **Sehr gut für E-Books und digitale Hörbücher**, auch wenn das digitale Hörbuch ursprünglich von einer physischen Hörbuch-CD stammt und rechtmäßig digitalisiert wurde. **Keine** physische DVD-/Blu-ray-/Musik-CD-Inventur als Kernfunktion.

**Grenzen:** Nicht gleichbedeutend mit DRM-Befreiung, Blu-ray-Playback oder bibliothekarisch lizenzierter E-Book-Ausleihe. Lizenzzusätze und Client-Voraussetzungen vor einer betrieblichen Entscheidung prüfen.

**Quellen:** [BookOrbit-README](https://github.com/bookorbit/bookorbit) · [Dateiformate und Bibliotheksstruktur](https://bookorbit.app/creating-a-library)

## 8.4 BookLore

**Kurzprofil:** Selbst gehosteter Mehrbenutzer-Leseserver für digitale Bücher, Comics **und – laut aktueller Projektdokumentation – auch Hörbücher**. Der ursprüngliche Haupt-README hebt vor allem E-Books/Comics hervor; die ausführlichere Dokumentation beschreibt zusätzlich Audiobooks. **Status 2026:** Übergang in Wartungsmodus zugunsten BookOrbit. **Technik:** Java/Spring Boot, Weboberfläche und MariaDB. **Lizenz:** AGPL-3.0.

**Dokumentierte Funktionsbereiche:**

1. **Digitale Sammlungen:** Mehrere Buchbibliotheken mit Ordnern, Scanregeln und getrennten Medienbereichen.
2. **Formate:** EPUB, PDF, CBZ/CBR/CB7, MOBI, AZW/AZW3, FB2 sowie – laut aktueller Dokumentation – **M4B/M4A/MP3**.
3. **Ordner-/Dateiscan:** Bestehende Dateiverzeichnisse automatisch durchsuchen, Metadaten extrahieren und Cover generieren.
4. **BookDrop:** Neue Dateien in einem überwachten Verzeichnis erkennen, anreichern und vor dem Import bestätigen lassen.
5. **Mehrere Formate pro Werk:** EPUB, PDF und Hörbuch als verschiedene Dateien derselben Buchentität zusammenhalten, abhängig vom gewählten Organisationsmodell.
6. **E-Book-Reader:** Lesen im Browser, inklusive Lesezeichen, Markierungen, Suche, Schriftoptionen und Fortschritt.
7. **PDF-/Comic-Reader:** Spezialisierte Darstellungen für PDF-Dokumente und Comicarchive.
8. **Hörbuchplayer:** Die Projektdokumentation nennt MP3/M4B-Player mit Track-/Kapitelanzeige, Wiedergabegeschwindigkeit und Fortschrittssynchronisierung.
9. **Metadaten:** Buchdaten, Cover, Bewertungen, Beschreibung und externe IDs automatisch abrufen und bearbeiten.
10. **Intelligente Regale:** Dynamische Sammlungen über Regeln, Suchfelder und Filter.
11. **Mehrbenutzerbetrieb:** Konten, individuelle Regale und Nutzungs-/Lesefortschritte; Authentifizierung auch mit OIDC.
12. **Geräteintegration:** Kobo, KOReader und OPDS; daneben kompatible Comic-Clients über zusätzliche API-Funktionen.
13. **Versand und Bereitstellung:** Dateien an Kindle/E-Mail weitergeben, sofern passend eingerichtet und rechtlich zulässig.
14. **Metadaten-Sidecars:** Bestandsinformationen aus eingebetteten oder externen Dateien laden beziehungsweise als Dateien ablegen.
15. **Dateisystemschutz:** Bei Netzlaufwerken empfiehlt das Projekt einen besonderen Modus, der schreibende Dateioperationen deaktiviert; unsichere NAS-Schreibzugriffe können Daten beschädigen.

**Medien:** **E-Books, Comics und digitale Hörbücher:** ja. **Physische** DVD/Blu-ray/Musik-CD/Hörbuch-CD: nicht als allgemeiner Inventar-/Leihbestand. Die aktuelle Hörbuchfunktion ist stärker, als es die kurze GitHub-Projektbeschreibung zunächst vermuten lässt.

**Grenzen:** Weil BookOrbit die aktive Weiterentwicklung übernimmt, sollte für neue Installationen zuerst BookOrbit bewertet werden. Einzelne BookLore-Dokumentationsseiten und Versionsstände können voneinander abweichen; Audio-Funktionen im konkreten Release überprüfen.

**Quellen:** [BookLore README / Nachfolgehinweis](https://github.com/booklore-app/booklore) · [Getting Started: Hörbuchplayer](https://github.com/booklore-app/booklore-docs/blob/master/docs/getting-started.md) · [Unterstützte Formate](https://github.com/booklore-app/booklore-docs/blob/master/docs/library/setup-first-library.md) · [Organisation mehrteiliger Hörbücher](https://github.com/booklore-app/booklore-docs/blob/master/docs/library/organization-modes.md)

## 8.5 Kavita

**Kurzprofil:** Digitaler Bibliotheksserver mit Schwerpunkt auf Comics, Manga, Webtoons und E-Books. **Technik:** C#/.NET, Weboberfläche, plattformübergreifend. **Lizenz:** GPL-3.0, optionales kostenpflichtiges Kavita+ mit zusätzlichen Diensten.

**Dokumentierte Funktionsbereiche:**

1. **Comics/Manga:** CBZ, CBR, ZIP, RAR/RAR5, 7z und Bildserien je nach lesbarem Format.
2. **E-Books:** EPUB und PDF in Bücherbibliotheken einbinden.
3. **Web-Reader:** Responsives Lesen auf Desktop, Tablet und Smartphone.
4. **Spezielle Leserichtungen:** Comicseiten, Webtoon-Scrolling, kontinuierliche Wiedergabe und E-Book-Seitenansichten.
5. **Metadaten:** Serien, Bücher, Autoren, Beschreibungen, Schlagwörter und bibliotheksbezogene Anzeigen; passende externe Quellen je nach Add-on.
6. **Sammlungen:** Einzelne Titel zu Collections gruppieren, Leselisten erzeugen und Wunsch-/Merkliste führen.
7. **Suche und Filter:** Metadaten durchsuchen, Bedingungen kombinieren und persönliche Filter speichern.
8. **Mehrbenutzerbetrieb:** Rollen, Leserechte, Altersbeschränkungen und getrennte Nutzerbereiche.
9. **Fortschritt:** Leseposition und Status pro Benutzer speichern.
10. **Gerätezugriff:** Browserbasierter Zugriff sowie OPDS-/kompatible Integrationen in unterstützten Versionen.
11. **Optik:** Themes und Anpassung des Leseerlebnisses.
12. **Zusatzangebot Kavita+:** Erweiterte Internet-/Metadaten-/Empfehlungsfunktionen; **nicht alles** in der Open-Source-Grundfunktion enthalten.

**Medien:** **E-Books, Comics und Manga: ja.** Film-DVD/Blu-ray, Musik-CD und physische Hörbuch-CD gehören nicht zum Anwendungszweck. **Digitale Hörbücher:** Kein ausgewiesener nativer vollständiger Audiobook-Player in der Hauptdokumentation; hier wäre BookOrbit besser.

**Grenzen:** Digitale Lesebibliothek statt Katalog-/Ausleihsoftware für physische Objekte. Zusatzfunktionen auf kostenlose und kostenpflichtige Teile prüfen.

**Quellen:** [Kavita GitHub/README](https://github.com/Kareadita/Kavita)

## 8.6 Komga

**Kurzprofil:** Freier Medienserver für Comics, Manga, grafische Literatur, Magazine und E-Books. **Technik:** Kotlin/Java/Spring Boot und Weboberfläche. **Lizenz:** MIT. **Einsatz:** Digitale Comic- und E-Book-Bibliotheken.

**Dokumentierte Funktionsbereiche:**

1. **Digitale Bibliotheken:** Serien und Buchdateien aus lokalen Verzeichnissen verwalten.
2. **Serienverwaltung:** Einzelne Hefte, Bände und Reihen sinnvoll in einer Sammlungsstruktur zusammenhalten.
3. **Dateierkennung:** Eingebettete Comic-/Buchmetadaten automatisch importieren.
4. **Metadatenbearbeitung:** Buch-/Serienangaben ändern, ordnen, filtern und korrigieren.
5. **Webreader:** Comic- und E-Book-Ansichten mit verschiedenen Lesemodi.
6. **Leselisten/Collections:** Eigene Sammlungen und definierte Reihenfolgen erstellen.
7. **Nutzerverwaltung:** Mehrere Leser mit bibliotheksspezifischen Rechten, Alters- und Labelbeschränkungen.
8. **Lesefortschritt:** Status beziehungsweise Position je Nutzer verwalten.
9. **OPDS v1/v2:** Katalog für kompatible E-Reader- und Lesesoftware anbieten.
10. **Kobo-Sync:** Synchronisierung mit unterstützten Kobo-Geräten.
11. **KOReader-Sync:** Fortschritts-/Geräteintegration mit KOReader.
12. **Downloads:** Ganze Titel, Serien oder Leselisten exportieren/herunterladen.
13. **Dublettenprüfung:** Doppelte Dateien und teilweise auch identische Comicseiten erkennen; Entfernung bedarf Sorgfalt.
14. **Dateiimport:** Buchdateien aus anderen Ordnern in bestehende Serienstrukturen übernehmen.
15. **REST-API:** Integration von Drittclients, Automatisierungsskripten und Community-Werkzeugen.
16. **Import von Leselisten:** Bestimmte ComicRack-Listen einlesen.

**Medien:** **Digitale Comics, Manga und E-Books:** ja. **Physische** DVDs, Blu-rays, Musik-CDs und Hörbuch-CDs: nein als native Bestandsobjekte. Kein vollwertiger Musik- oder Hörbuchserver.

**Grenzen:** Spezialisierung auf schrift-/bildbasierte Dateien; für Musik und Hörbücher eine andere Plattform ergänzen. API-Clients können selbst zusätzliche Voraussetzungen haben.

**Quellen:** [Komga GitHub/README](https://github.com/gotson/komga) · [Projekt-Dokumentation](https://komga.org/)

## 8.7 Inventaire

**Kurzprofil:** Offene soziale Plattform, auf der Menschen ihre **Bücher** katalogisieren, sichtbar machen und miteinander teilen können. **Technik:** Webanwendung und verknüpfte Wissensdaten. **Lizenz:** AGPL-3.0. **Betrieb:** gehostetes Inventaire oder nach Dokumentation eigene Instanz.

**Dokumentierte Funktionsbereiche:**

1. **Persönliche Bücherliste:** Eigene vorhandene Bücher und zusätzliche Wunschtitel führen.
2. **ISBN- und Titelsuche:** Bibliografische Daten nach ISBN, Buchtitel oder Autor suchen.
3. **Barcode-Erfassung:** ISBN mit Smartphone-/anderen geeigneten Scannern aufnehmen.
4. **Import:** Bücher aus Listen oder Diensten wie Goodreads, LibraryThing oder Babelio übernehmen, abhängig von verfügbaren Importern.
5. **Metadaten-Verknüpfungen:** Offene Wissensdaten, ISBNs und Wikidata-Bezüge zur bibliografischen Identifikation nutzen.
6. **Sichtbarkeit:** Bücher privat lassen oder für Freunde, Gruppen beziehungsweise öffentlich sichtbar schalten.
7. **Teilen und Verleihen:** Einträge als **verleihbar**, verschenkbar oder verkäuflich kennzeichnen und dadurch Transaktionen anbahnen.
8. **Soziale Nutzung:** Andere Personen finden beziehungsweise Bücher gemeinsam entdecken, Bestände vergleichen und in Gruppen arbeiten.
9. **Offenes Projekt:** Der frühere GitHub-Quellcode wurde archiviert und die Entwicklung nach Codeberg verlegt; „GitHub archiviert“ bedeutet hier nicht zwingend Produktende.

**Medien:** Starker Fokus auf **Bücher und ISBNs**. DVDs, Blu-rays, Musik-CDs und Hörbuch-CDs sind keine dokumentierten nativen Hauptkategorien. Eine digitale E-Book-Ausgabe kann bibliografisch denkbar sein; ein eigener Reader oder E-Book-Lizenzverleih ist **nicht** belegt.

**Grenzen:** Soziale Bücherverwaltung, keine professionelle Ausleihtheke und kein Digitalmedia-Server. Das Freigeben eines physischen Buchs für Freunde ist ein anderer Prozess als die formalisierte öffentliche Bibliotheksausleihe.

**Quellen:** [Inventaire-Projekt](https://inventaire.io/) · [Benutzerdokumentation: Bücher erfassen, verleihen, verschenken](https://wiki.inventaire.io/wiki/How_to_add_a_book_to_my_inventory/en) · [Altes GitHub-Repository und Lizenz](https://github.com/inventaire/inventaire) · [Codeberg-Organisation](https://codeberg.org/inventaire)

---
# 9. Technische Datenmodelle für gemischte Medienbestände

Dieser Abschnitt ist insbesondere wichtig, wenn ein Programm nicht nur Bücher, sondern eine **einzige zusammenhängende Sammlung aus physischen und digitalen Medien** verwalten soll. Er beschreibt fachliche Anforderungen an eine gute Datenstruktur; es handelt sich **nicht** um die interne Datenbank jedes untersuchten Produkts.

## 9.1 Empfohlene Datenebenen

| Ebene | Aufgabe | Beispiel |
|---|---|---|
| **Werk** | Abstrakter Inhalt, der verschiedene Medienausgaben verbindet | Ein Roman und seine Hörbuch-/Film-Adaption |
| **Veröffentlichung/Ausgabe** | Konkrete Edition, Sprache, Verlag/Label/Studio und Erscheinungsjahr | „Film XY“, deutsche Blu-ray-Sonderausgabe 2024 |
| **Physisches Exemplar** | Tatsächlich vorhandenes Einzelstück; Ausleih- und Inventarobjekt | Blu-ray mit Inventarbarcode `MED-000371` in Regal 3 |
| **Bestand/Standort** | Zugehörigkeit, Zweigstelle, Raum, Regal, Fach, Besitz | Wohnzimmer → Schrank B → Fach 4 |
| **Digitales Asset** | Verweis auf Datei oder digitale Lizenz, unabhängig von physischer Hülle | `titel.epub` oder `hoerbuch.m4b` mit Prüfsumme |
| **Beziehung** | Verbindung zwischen Werken/Editionen und anderen Medien | „Verfilmung von“ / „Hörbuch zu“ / „enthält Disc 1–3“ |
| **Benutzer/Ausleihe** | Wer leiht welches konkrete Exemplar bis wann? | Person A leiht `MED-000371` bis 30.11.2026 |
| **Nutzungsfortschritt** | Individuelles Lesen oder Anhören, unabhängig vom Eigentum | Leser B: 67 % des EPUB; 03:21:00 im Hörbuch |

**Warum diese Trennung?** Ein ISBN kennzeichnet eine Buchausgabe, aber keine einzelne Buchkopie. Eine EAN identifiziert häufig eine kommerzielle DVD-Veröffentlichung, aber ebenfalls nicht jede vorhandene Disc. Ein selbst vergebener Inventarbarcode identifiziert dagegen das tatsächlich ausgeliehene physische Objekt. Ein Datensatz darf deshalb nicht ISBN und Exemplarbarcode in ein einziges Pflichtfeld zwingen.

## 9.2 Ein sinnvolles Medienartenverzeichnis

```text
Medien
├── Gedrucktes
│   ├── Buch / Taschenbuch / Hardcover
│   ├── Zeitschrift / Zeitung / Einzelheft
│   └── Comic / Manga / Noten
├── Film und Video (physisch)
│   ├── DVD-Video
│   ├── Blu-ray
│   ├── Ultra HD Blu-ray
│   ├── VHS
│   └── TV-/Serien-Boxset
├── Musik (physisch)
│   ├── Audio-CD
│   ├── Vinyl / Single / LP
│   ├── Kassette
│   └── Sonstige Musikträger
├── Hörbuch (physisch)
│   ├── Hörbuch-CD
│   ├── Hörspiel-CD
│   └── Hörbuchkassette
├── Digitale Bücher
│   ├── EPUB / KEPUB
│   ├── PDF
│   ├── MOBI / AZW / AZW3
│   └── Comic-Archiv CBZ / CBR / CB7
├── Digitale Audioinhalte
│   ├── Hörbuch M4B / MP3
│   ├── Musik MP3 / FLAC / OGG / OPUS
│   └── Podcast / Hörspiel
└── Sonstiges
    ├── Videospiel
    ├── Brettspiel
    ├── Software
    └── Dokument / Foto / Archivobjekt
```

Die Kategorien **Medienart** (Blu-ray), **Inhaltstyp** (Spielfilm) und **Ausgabeformat** (4K, Dolby Atmos) sind bewusst getrennt. Das erlaubt neue Medienarten ohne grundlegenden Umbau aller anderen Stammdaten.

## 9.3 DVD und Blu-ray: empfohlenes Feldset

| Feld | Funktion |
|---|---|
| Werk-/Originaltitel | Film eindeutig finden, auch bei wechselnden deutschen Titeln |
| Verlag/Label/Studio | Konkreten Vertrieb und Disc-Ausgabe identifizieren |
| EAN/UPC, Katalognummer | Datenimport und Editionserkennung |
| Material: DVD/Blu-ray/UHD | Unterschiedliche Ausleihe, Suche und technische Darstellung |
| Jahr Film / Jahr Disc | Werkjahr und Ausgabejahr nicht verwechseln |
| Regie, Besetzung, Rollen | Filmspezifische Mitwirkendenliste |
| Genre, Reihe, Staffel | Filter und logische Zusammenfassung |
| Altersfreigabe | Jugendschutzrelevante Information |
| Laufzeit | Länge des Films/der Folgen |
| Region, Videoauflösung, Bildformat | Kompatibilitäts- und technische Metadaten |
| Tonsprachen, Audioformate, Untertitel | Sprach-/Geräteanforderungen erfüllen |
| Disc-/Teilzahl, Booklet, Bonusmaterial | Vollständigkeit eines Sets kontrollieren |
| Inventarnummer, Zustand, Kaufpreis, Standort | Physisches Exemplar verwalten |
| Status, Person, Fälligkeitsdatum | Ausleihe und Rückgabe bearbeiten |

## 9.4 Musik-CD: empfohlenes Feldset

| Feld | Funktion |
|---|---|
| Album / Release Group / konkrete Pressung | Albumwerk, Veröffentlichung und Pressungsvariante trennen |
| Künstler, Komponisten, Mitwirkende | Künstlerrecherche und klassische Musik unterstützen |
| Label, Veröffentlichungsjahr, Land | Konkrete Ausgabe beschreiben |
| EAN/UPC, Katalognummer, MusicBrainz-IDs | Metadaten sauber übernehmen und Dubletten erkennen |
| Genre und Stil | Filterbarkeit |
| Disc-Zahl, Trackliste, Titellängen | Mehrfach-CDs und Disc-Inhalt erfassen |
| Cover, Booklet, Sonderausgabe | Sammlerrelevante Informationen |
| Zustand, Kaufpreis, Standort, Inventarbarcode | Eigentum und Ausleihe dokumentieren |

## 9.5 Hörbuch-CD und digitales Hörbuch: empfohlenes Feldset

| Feld | Funktion |
|---|---|
| Buchtitel und Audiotitel | Beziehung zur gedruckten Ausgabe herstellen |
| Autorin/Autor und Sprecher | Beide Rollen getrennt suchen können |
| Hörbuch/Hörspiel; gekürzt/ungekürzt | Werktyp und Fassung unterscheiden |
| ISBN/EAN, Label, Erscheinungsdatum | Edition eindeutig identifizieren |
| Disc-Zahl, Gesamtspielzeit, Kapitel | CD-Set und digitale Fassung strukturieren |
| Sprache, Zielgruppe, Altersfreigabe | Geeignete Ausgabe finden |
| MP3/M4B usw.; Dateigröße; Prüfsumme | Digitalbestand prüfen und wiederherstellen |
| Position je Benutzer | Wiedergabe später fortsetzen |
| Ausleihstatus einzelnes CD-Set | Physische und digitale Nutzungsrechte getrennt behandeln |

## 9.6 E-Book: empfohlenes Feldset

| Feld | Funktion |
|---|---|
| Werk-/Ausgabe-ID, ISBN-13, DOI falls vorhanden | Unterschiedliche Editionen einander zuordnen |
| Sprache, Format, Version | EPUB/PDF usw. zuverlässig unterscheiden |
| Verlag, Erscheinungsjahr, Reihe | Inhalt katalogisieren |
| Datei-Hash (z. B. SHA-256) | Integritätsprüfung und Backup-Abgleich |
| Speicherpfad/Objekt-ID, Dateigröße | Datei verlässlich wiederfinden |
| Lizenztyp, Zugriffsrechte, DRM-Status | Rechtmäßige Bereitstellung steuern |
| Lesegerätesynchronisation | Buch auf unterstütztem E-Reader verwenden |
| Notizen, Annotationen, Lesezeichen je Nutzer | Private Lesedaten vom bibliografischen Werk trennen |
| Exportformat und offene Metadaten | Migration und Datenhoheit sichern |

## 9.7 Drei technische Architekturvarianten

**Variante A – Ein einziges Multimedia-Katalogprogramm:** Für eine private Sammlung am einfachsten: **Data Crow, Shelf, Tellico oder GCstar**. Vorteile: ein gemeinsamer Bestand, einheitliche Suche, keine Synchronisierung zwischen Produkten. Nachteil: Ein Multimedia-Katalog ist häufig kein komfortabler digitaler Reader beziehungsweise kein professionelles ILS.

**Variante B – Bibliotheksverwaltung plus digitale Bibliothek:** **Koha (physische Bestände) + BookOrbit (E-Books/Hörbücher)**, beziehungsweise für spezialisierte Comics **Komga**. Vorteile: Jedes System tut das, was es gut kann. Nachteil: Titel/Benutzer/Identitäten können doppelt auftreten; für einen einheitlichen OPAC benötigt man einen Integrationsentwurf, stabile Kennungen und Synchronisation.

**Variante C – Persönliche Medienverwaltung plus Digitalserver:** **Shelf (Inventur, physische Medien, persönliche Übersicht) + BookOrbit (digitale Buch-/Hörbibliothek)**. Laut Shelf-Dokumentation gibt es bereits Integrationen für Audiobookshelf und Komga; eine automatische vollständige BookOrbit-Anbindung ist dadurch **nicht** belegt. Die beiden Systeme können organisatorisch nebeneinander existieren, ohne dass eine Integration versprochen werden kann.

---

# 10. Empfehlungen und Auswahlverfahren

## 10.1 Prioritäten für unterschiedliche Einsatzfälle

| Bedarf | Erste Wahl | Alternative | Begründung |
|---|---|---|---|
| Private Sammlung aus Büchern, DVDs, Blu-rays und CDs | **Shelf** | **Data Crow** | Direkte Multimedien-Unterstützung, Barcode-/UPC-Suche; Data Crow ist besonders flexibel |
| Große private Sammlung mit eigenen Metadatenfeldern | **Data Crow** | **Tellico** | Eigene Module, anpassbare Datenfelder und hierarchische Standorte |
| Klassischer lokaler Qt-Katalog mit Ausleihe | **BiblioteQ** | **GCstar** | Medienkatalog, Mitglieder-/Reservierungsfunktionen; GCstar einfacher als Sammlungssoftware |
| Professionelle Mediothek mit DVD-/CD-Ausleihe | **Koha** | **SLiMS**, **PMB** | Materialtypen, Exemplarverwaltung, Bibliotheksprozesse |
| Großer Bibliotheksverbund | **Evergreen** | **RERO ILS**, **Koha** | Mehrere Standorte, Regeln und Organisationsstrukturen |
| Wissenschaftliche Bibliothek mit E-Ressourcen | **FOLIO** | **RERO ILS**, **InvenioILS** | ERM, bibliografische Integration, modulare Infrastruktur |
| Kleine deutschsprachige Schulbibliothek mit Büchern | **OpenLibry** | **OpenBiblio** | Einfache Bedienung beziehungsweise klassischer Bibliotheksworkflow |
| E-Books am PC, Lesegeräte und Konvertierung | **Calibre** | **Calibre-Web** als Ergänzung | Besonders stark bei Bibliothekspflege, Konvertierung, E-Reader-Anbindung |
| E-Books und digitale Hörbücher auf eigenem Server | **BookOrbit** | **BookLore** (Wartungsmodus) | Reader und Audio-Streaming in einer Plattform |
| Comics/Manga/E-Books mit Webzugriff | **Komga** | **Kavita** | Spezialisierte Serien-, Leselisten- und Readerfunktionen |
| Eigene Bücher teilen und privat verleihen | **Inventaire** | **uBiblio** | Soziale Buchlisten beziehungsweise selbst gehosteter Mini-Verleih |

## 10.2 Praktischer Abnahmetest vor einer Entscheidung

Für jedes in Betracht gezogene Produkt dieselben sechs Testmedien erfassen:

1. **Buch:** Zwei Exemplare desselben Titels, unterschiedliche Inventarnummern und Standorte, eines verliehen.
2. **DVD:** Film mit Originaltitel, deutscher Ausgabe, FSK, zwei Tonspuren, einer Untertitelsprache und EAN.
3. **Blu-ray:** Sonderedition desselben Films wie die DVD, eigenes Medium, Barcode, anderer Regionalcode und anderes Cover.
4. **Musik-CD:** Mehrfachalbum mit zwei Discs und insgesamt 25 Tracks; Künstler, MusicBrainz-Release-ID und Katalognummer.
5. **Hörbuch-CD:** Sieben CDs in einer Box, Autor und Sprecher, gesonderte Laufzeit und ein Ausleihvorgang für die **gesamte Box**.
6. **E-Book plus Hörbuch-Datei:** Ein EPUB, eine PDF-Ausgabe und ein M4B-Hörbuch derselben Vorlage; Lesen, Hören, Dateiverknüpfung, Benutzerfortschritt und Export getrennt testen.

**Akzeptanzkriterien:**

- Ein Werk kann in mehreren **Formaten/Editionen** vorkommen, ohne ein Datenchaos zu erzeugen.
- DVD und Blu-ray unterscheiden sich in Suche, Datensatz und Ausleihregel.
- CDs und Hörbuch-Sets haben Track-/Disc- beziehungsweise Vollständigkeitsinformation.
- Physische Exemplare werden mit eigenem Barcode gezählt und verliehen.
- Nach Import sind Metadaten nachbearbeitbar, nicht nur automatisch übernommen.
- Ein CSV/JSON/XML/MARC-Export oder eine dokumentierte Backup-Migration bewahrt möglichst alle Informationen.
- Bei E-Books und Hörbüchern ist klar, ob nur Metadaten oder **wirklich abspielbare Dateien** gespeichert werden.
- Digitale Nutzerfortschritte bleiben zwischen Benutzerkonten getrennt.
- Updates und Backups lassen sich testen, bevor reale Daten importiert werden.

## 10.3 Bewertungskriterien mit beispielhafter Gewichtung

*Die folgende Gewichtung ist eine Entscheidungshilfe, kein veröffentlichtes Testergebnis über die Produkte.*

| Kriterium | Privatmediathek | Öffentliche Bibliothek |
|---|---:|---:|
| Unterstützung aller gewünschten Medienarten | 25 % | 15 % |
| Titel-, Ausgaben- und Exemplardatenmodell | 15 % | 15 % |
| Suche, Import, Barcode und Metadatenquellen | 20 % | 10 % |
| Ausleihe, Reservierung und Nutzerverwaltung | 10 % | 20 % |
| E-Book-/Hörbuchzugriff | 10 % | 10 % |
| Datenhoheit, Export, Backups | 10 % | 10 % |
| Betrieb, Sicherheitsupdates und Rechteverwaltung | 5 % | 10 % |
| Standards/Erwerbung/Periodika/Verbund | 5 % | 10 % |
| **Summe** | **100 %** | **100 %** |

**Zentrale Schlussfolgerung:** Für eine **persönliche Gesamt-Mediathek** ist eine spezialisierte Sammlungsverwaltung wahrscheinlich sinnvoller als ein ILS; für **wirkliche öffentliche Ausleihe** ist das umgekehrt. Soll beides inklusive Streaming vereint werden, ist oft eine Kombination aus physischem Katalog und Digitalserver die sauberste Lösung.

---

# 11. Quellen und Prüfhilfen

Die folgenden Links führen überwiegend zu offiziellen Projektseiten, Handbüchern, Quellcode-Repositories oder Projektdokumentationen. Die dortige Funktionsbeschreibung kann sich nach dem 17.10.2026 ändern. Bei Bedarf den konkreten Release-Tag des geplanten Einsatzes dokumentieren.

| Programm | Primärquelle / Handbuch | Ergänzende Fundstelle |
|---|---|---|
| Koha | [Community & Manual](https://koha-community.org/) | [Aktuelles Manual](https://koha-community.org/manual/latest/en/html/) |
| Evergreen | [Evergreen Dokumentation](https://docs.evergreen-ils.org/docs/latest/) | [Ausleihregel-Materialtypen](https://docs.evergreen-ils.org/docs/latest/admin_initial_setup/borrowing_items.html) |
| FOLIO | [FOLIO Features](https://docs.folio.org/docs/about-folio/features/) | [Inventory](https://docs.folio.org/docs/metadata/inventory/) |
| SLiMS | [Repository](https://github.com/slims/slims9_bulian) | [Release Notes](https://github.com/slims/slims9_bulian/releases) |
| RERO ILS | [Offizielle Hilfe](https://bib.rero.ch/help/intro/) | [Repository](https://github.com/rero/rero-ils) |
| PMB | [PMB Services](https://www.sigb.net/) | [Projektgeschichte](https://fr.wikipedia.org/wiki/PMB_%28logiciel%29) |
| InvenioILS | [Produktseite](https://inveniosoftware.org/products/ils/) | [Repository](https://github.com/inveniosoftware/invenio-app-ils) |
| ABCD | [Offizielle Moduldokumentation](https://abcd-devcom.github.io/docs/2.0/abcd-introduction/overview) | [Repository](https://github.com/ABCD-DEVCOM/ABCD) |
| Next-L Enju Leaf | [Projekt](https://github.com/next-l/enju_leaf) | [Japanisches Handbuch](https://next-l.github.io/manual/1.1/) |
| BiblioteQ | [README mit umfangreicher Featureliste](https://github.com/textbrowser/biblioteq) | [Lizenz](https://github.com/textbrowser/biblioteq/blob/master/LICENSE) |
| OpenBiblio | [Deutsche Demo-/Funktionsübersicht](https://openbiblio.de/openbiblio/home/index.php) | [Medienarten](https://openbiblio.github.io/openbiblio_docs/sysadmin/root.html) |
| OpenLibry | [Repository](https://github.com/jzakotnik/openlibry) | [Dokumentation](https://openlibry.de/site) |
| Tellico | [KDE-Handbuch](https://docs.kde.org/trunk_kf6/en/tellico/tellico/index.html) | [Projektseite](https://tellico-project.org/) |
| GCstar | [Offizielles Handbuch](https://gcstar.gitlab.io/gcstar_docs/en/) | [Projekt-Repository über Handbuch](https://gcstar.gitlab.io/gcstar_docs/en/) |
| Data Crow | [Einführung/Module](https://datacrow.org/de/docs/einfuhrung/) | [Quellcode](https://datacrow.org/de/code/) |
| Shelf | [README](https://github.com/dgahagan/shelf) | [Docker-/Featureübersicht](https://github.com/dgahagan/shelf/blob/main/DOCKERHUB_README.md) |
| uBiblio | [Repository/README](https://github.com/seanboyce/ubiblio) | – |
| Calibre | [Projektübersicht](https://calibre-ebook.com/about) | [Benutzerhandbuch](https://manual.calibre-ebook.com/) |
| Calibre-Web | [README](https://github.com/janeczku/calibre-web) | [Releases](https://github.com/janeczku/calibre-web/releases) |
| BookOrbit | [README](https://github.com/bookorbit/bookorbit) | [Dateiformate](https://bookorbit.app/creating-a-library) |
| BookLore | [README](https://github.com/booklore-app/booklore) | [Getting Started mit Hörbüchern](https://github.com/booklore-app/booklore-docs/blob/master/docs/getting-started.md) |
| Kavita | [README](https://github.com/Kareadita/Kavita) | [Projektwebsite](https://www.kavitareader.com/) |
| Komga | [README](https://github.com/gotson/komga) | [Dokumentation](https://komga.org/) |
| Inventaire | [Projekt](https://inventaire.io/) | [Inventarisieren/Verleihen](https://wiki.inventaire.io/wiki/How_to_add_a_book_to_my_inventory/en) |

## 11.1 Methodische Hinweise und offene Prüfpunkte

- **Belegstatus:** Aussagen zu speziellen Funktionsdetails stammen bevorzugt aus Projekt-README und offiziellen Handbüchern; wo solche Angaben fehlen, werden Konfigurierbarkeit und gesicherter Funktionsumfang ausdrücklich unterschieden.
- **Versionswechsel:** Besondere Vorsicht bei **BookLore → BookOrbit**, kleineren persönlichen Projekten und bei teilweise älteren Handbüchern zu **Next-L Enju Leaf**.
- **Offene Lizenz-/Funktionsdetails:** Für eine rechtlich relevante Fork- oder kommerzielle Weiterentwicklungsentscheidung immer **LICENSE-Dateien der konkret eingesetzten Version** lesen; auch Plugins können andere Bedingungen haben.
- **Nicht überprüft:** Es wurden nicht alle 24 Anwendungen installiert, durchgeklickt oder mit sechs echten Testmedien getestet. Angaben zu Metadatenimportern, Netzwerkfreigaben, Funktionsgleichheit zwischen Versionen und etwaigen kostenpflichtigen Zusatzdiensten sollten deshalb vor Beschaffung/Betrieb gezielt verifiziert werden.
- **Kein falsches E-Book-Versprechen:** Ein normaler Medienkatalog verleiht keine DRM-geschützten E-Books allein deshalb legal, weil er einen URL-, PDF- oder Dateianhang verwalten kann.

---


---

# 12. Praxisprofile für alle 24 Programme

Hier werden die Produktfunktionen aus den Kapiteln 5–8 in realistische Nutzungsszenarien übersetzt. **Dies sind Anwendungshinweise und vorgeschlagene Tests, keine Behauptung, dass jeder Arbeitsschritt in jeder Version ohne Konfiguration funktioniert.**


## 12.1 Koha

**Worin das Programm praktisch stark ist:** Der wesentliche Vorteil liegt im gemeinsamen Betrieb aller Medientypen: Bibliografische Daten bleiben unabhängig vom einzelnen verliehenen Exemplar. Ein Film kann mehrere DVD- und Blu-ray-Ausgaben besitzen, und jede Ausgabe kann mehrere Exemplare haben. Personal arbeitet in einer Verwaltungsoberfläche; Leserinnen und Leser recherchieren im OPAC. Die Einrichtung eigener MARC-Frameworks und Material-/Ausleihregeln ist dafür eine bewusste fachliche Aufgabe.

**Empfohlene Funktionsprobe:** Als Test werden drei Exemplare einer DVD, zwei Blu-rays derselben Produktion und ein Hörbuch-CD-Set erfasst. Danach je eine Leihfrist, eine Vormerkung und eine Benachrichtigung prüfen. Für ein digitales E-Book zusätzlich kontrollieren, ob nur ein Kataloglink oder eine integrierte Lizenzlösung vorliegt.


## 12.2 Evergreen ILS

**Worin das Programm praktisch stark ist:** Seine Stärke liegt weniger in Filmmetadaten als im Ausleihnetz. Eine Bibliothek kann einen Titel erfassen, zahlreiche Exemplare auf verschiedene Häuser verteilen und die Vormerkung über Regeln an ein verfügbares Exemplar weiterleiten. Die differenzierbaren Vormerkebenen sind gerade bei Serienbänden, Disc-Sets und verschiedenen Ausgaben hilfreich.

**Empfohlene Funktionsprobe:** Ein praxisnaher Test umfasst zwei Standorte, ein mehrteiliges DVD-Set, eine Vormerkung auf einen bestimmten Teil und einen Transport zwischen Zweigstellen. Zusätzlich sollten die Regeln für Medienverlust und Benachrichtigung realistisch konfiguriert werden.


## 12.3 FOLIO

**Worin das Programm praktisch stark ist:** Die Trennung zwischen bibliografischer *Instance*, bibliotheksbezogenen *Holdings* und physischen *Items* lässt auch komplexe Medienbestände strukturiert abbilden. Ein Film als bibliografischer Datensatz ist somit nicht mit dem einzelnen ausleihbaren Datenträger identisch. Hinzu kommen separate Erwerbungs- und Lizenzmodule für elektronische Datenbanken und Bücherpakete.

**Empfohlene Funktionsprobe:** In einem Test sollten ein Satz aus mehreren Hörbuch-CDs, eine Zeitschriftenreihe und ein lizenziertes E-Book-Paket parallel angelegt werden. Dabei besonders prüfen, welche App welche Stammdaten besitzt und wo sich Bestellungen, Nutzungsrechte und Ausleihregeln einstellen lassen.


## 12.4 SLiMS

**Worin das Programm praktisch stark ist:** Für eine Schule oder kleinere öffentliche Bibliothek bietet SLiMS wesentlich mehr als eine reine Bücherliste: Katalog, Leserdaten, Leihvorgänge, Zeitschriften und Inventur gehören zu getrennten administrativen Arbeitsbereichen. Datensätze können digitale Anhänge enthalten, aber der Funktionsumfang eines vollwertigen EPUB-/Audioplayers darf daraus nicht abgeleitet werden.

**Empfohlene Funktionsprobe:** Ein Beispielbestand mit Buch, DVD, Musik-CD, Hörbuch-CD und PDF soll in der Oberfläche unterschiedliche Materialtypen zeigen. Getestet werden Barcode-Etiketten, Ausleihe, verspätete Rückgabe, Nutzerkonto, Suchansicht und Berechtigungen für digitale Anhänge.


## 12.5 RERO ILS

**Worin das Programm praktisch stark ist:** RERO ILS positioniert sich zwischen professionellem Tagesgeschäft und modernen Schnittstellen. Bibliografische Datensätze, Ausleihen, Erwerbung, Organisationen und mehrere Bibliotheken werden über ein gemeinsames Datenmodell verbunden. Offene JSON- und REST-Schnittstellen sind attraktiv, wenn ergänzende lokale Anwendungen langfristig entstehen sollen.

**Empfohlene Funktionsprobe:** Ein sinnvoller Prüflauf katalogisiert ein Hörbuch samt Sprecher, führt Exemplare an zwei Standorten und simuliert eine Vormerkung über beide Bibliotheken. Zusätzlich sollte ein eigener Metadatenexport einschließlich Normdatenbezügen durchgeführt werden.


## 12.6 PMB

**Worin das Programm praktisch stark ist:** Als Bibliotheks- und Dokumentationssystem kann PMB physische Medien und digitale Dokumente in einer Katalogwelt führen. Historische offizielle Projektdokumentation beschreibt zusätzlich ein WebDAV-basiertes Dokumentenmanagement, Volltextindexierung und Betrachtung von EPUB-/Office-Dokumenten. Diese Einzelheiten sind versionsgebunden; beim heutigen Zielrelease müssen sie erneut bestätigt werden.

**Empfohlene Funktionsprobe:** Für den Praxistest drei Bestände anlegen: eine ausleihbare Blu-ray, eine Fachzeitschrift und ein elektronisches EPUB-Dokument. Anschließend Katalogsuche, Dokumentenzugriff, Benutzerrollen und Datensicherung testen. Besonders wichtig ist die Festlegung der genutzten freien PMB-Ausgabe.


## 12.7 InvenioILS

**Worin das Programm praktisch stark ist:** InvenioILS ist besonders interessant, wenn ein Team bibliografische Dienste über strukturierte JSON-Daten und eigene APIs erweitern möchte. Die Trennung von Dokumenten, physischen Exemplaren und elektronischen Einheiten ist fachlich flexibler als ein bloßer Bücher-Datensatz. Der genaue Ausbaustand einzelner Module ist weniger selbstverständlich als bei großen, etablierten Bibliotheksplattformen.

**Empfohlene Funktionsprobe:** Ein Prototyp sollte erst die Datensätze für DVD/Blu-ray und ein elektronisches PDF definieren, dann die API für Suche und Exemplarstatus benutzen. Danach lässt sich prüfen, ob die tatsächlich benötigten Erwerbungs-, Benutzer- und Leihprozesse verfügbar sind.


## 12.8 ABCD

**Worin das Programm praktisch stark ist:** ABCD ist ein frei konfigurierbarer Dokumentationsbaukasten. Seine Stärke liegt in selbst definierten Datensätzen, Eingabemasken und Suchindizes – nützlich für eine Fachsammlung mit ungewöhnlichen Objekten, beispielsweise historischen Computerzeitschriften, Audioaufzeichnungen oder mehreren Arten von Datenträgern. Diese Offenheit bedeutet zugleich mehr Verantwortung für Datenmodell und Qualität.

**Empfohlene Funktionsprobe:** Für einen Test zuerst die Felder einer Blu-ray-Ausgabe mit Regie, Format, Sprachen, Disc-Zahl und Signatur festlegen. Dann mindestens zwei Exemplare katalogisieren, eine Ausleihe durchführen und die Daten in einen interoperablen Export überführen.


## 12.9 Next-L Enju Leaf

**Worin das Programm praktisch stark ist:** Die Software bildet einen klassischen bibliothekarischen Ablauf mit Katalog, Exemplaren, Nutzern, Rückgabe und Vormerkung ab. Sie ist als Referenz für ein Rails-basiertes ILS interessant. Der größte praktische Unsicherheitsfaktor für den deutschsprachigen Einsatz liegt in Lokalisierung, Handbuchversionen und der Abdeckung spezifischer Medienfelder.

**Empfohlene Funktionsprobe:** Vor ernsthafter Nutzung sollten eine japanische Beispielinstallation und der aktuelle Quellcode gegen die deutschen Anforderungen abgeglichen werden. Ein Test mit CD-Box, DVD und E-Book-Link zeigt schnell, welche Erweiterungen nötig wären.


## 12.10 BiblioteQ

**Worin das Programm praktisch stark ist:** BiblioteQ eignet sich, wenn die Verwaltung ausdrücklich eine lokale Desktop-Anwendung sein soll: SQLite ermöglicht einfachen Offlinebetrieb, während PostgreSQL weitere Konten und Zugriffskontrollen erlaubt. Eigene Titel- und Ausleihdatensätze unterscheiden es von vielen reinen Büchersammlern; sein klassischer Qt-Ansatz passt gut zur Arbeit am PC.

**Empfohlene Funktionsprobe:** Test: Musik-CD und DVD erfassen, bei einer Blu-ray Medienformat und technische Eigenschaften ergänzen, einen Leser anlegen, ausleihen, reservieren, zurücknehmen, eine SQL-Suche ausführen und Daten in einem portablen Format sichern.


## 12.11 OpenBiblio

**Worin das Programm praktisch stark ist:** OpenBiblio deckt die alltägliche Bibliotheksausleihe überschaubar ab. Es erlaubt, Materialarten unabhängig von Bücherformaten zu definieren und dafür Regeln einzustellen. Eine Musik-CD kann somit als eigenes Medium behandelt werden; spezielle Titel-/Trackdaten werden durch diese Materialklasse allein jedoch nicht automatisch zum Standardfeld.

**Empfohlene Funktionsprobe:** Praxis: Drei Materialklassen Buch, DVD und Hörbuch-CD erzeugen, je einen Barcode ausgeben, eine kleine Leserdatenbank importieren und Mahn-/Rückgabefälle testen. Wichtig ist, ausdrücklich die PHP-8-taugliche deutsche Fortführung statt eines alten Pakets zu prüfen.


## 12.12 OpenLibry

**Worin das Programm praktisch stark ist:** Das Programm optimiert stark wiederkehrende Schulabläufe: Buch suchen, Scanner verwenden, ausleihen, zurücknehmen, Verwaltung und Statistik pflegen. Für eine Schulbücherei mit hauptsächlich Papierbüchern ist diese Priorisierung sinnvoll; sie schließt aber nicht automatisch eine ausgefeilte Musik-/Filmdatenbank ein.

**Empfohlene Funktionsprobe:** Als einfacher Akzeptanztest 100 Bücher aus Excel importieren, zehn Ausleihen per Scanner durchführen und eine Rückgabe- und Mahnungskonfiguration testen. Eine DVD oder Hörbuch-CD nur dann fest einplanen, wenn die konkreten Felder im Testlauf wirklich ausreichen.


## 12.13 Tellico

**Worin das Programm praktisch stark ist:** Tellico denkt eher in persönlichen Sammlungen als in Bibliotheksabteilungen. Für Bücher, Videos und Musik existieren eigene Vorlagen; zusätzliche Felder erlauben die Anpassung für Blu-ray, Sammlereditionen, Hörbuch-CDs oder technische Fachbücher. Suchfilter, Berichte und lokale Dateihoheit sind für die Pflege eines großen privaten Bestands besonders hilfreich.

**Empfohlene Funktionsprobe:** Ein guter Test importiert Bücher via ISBN, Filmdaten über eine Videovorlage und eine Musik-CD mit Album- und Trackangaben. Danach eigene Felder für Disc-Zahl, Regal und Kaufzustand hinzufügen, eine Ausleihe protokollieren und einen CSV- beziehungsweise XML-Export kontrollieren.


## 12.14 GCstar

**Worin das Programm praktisch stark ist:** GCstar eignet sich besonders für Personen, die Filme, Musik, Bücher und Spiele in getrennten, aber einheitlich bedienbaren Sammlungen führen. Gerade die ausdrücklich dokumentierte Barcode-Unterstützung für DVDs und Blu-rays ist ein Vorteil. Metadaten-Plugins sind allerdings von externen Webseiten und Perl-Abhängigkeiten abhängig.

**Empfohlene Funktionsprobe:** Ein Probelauf mit 20 DVDs, zehn Blu-rays, Musik-CDs und wenigen Büchern sollte prüfen, ob die gewünschten Webanbieter noch funktionieren. Danach die vollständige Sammlung als XML/CSV oder HTML exportieren und die Rückübernahme testweise durchführen.


## 12.15 Data Crow

**Worin das Programm praktisch stark ist:** Data Crow ist aufgrund eigener Module und frei gestaltbarer Beziehungen hervorragend für gemischte technische Sammlungen. Der Katalog kann etwa einen Film mit Regisseur, Medium, Lagerort und Ausleiher oder ein Musik-Release mit beteiligten Musikern verbinden. Die Trennung von physischen und digitalen Formaten sollte bewusst im eigenen Datenmodell erfolgen.

**Empfohlene Funktionsprobe:** Ein eigener Hörbuch-Modultyp mit Autor, Sprecher, Anzahl CDs, Länge und Auflage wäre ein gutes Pilotprojekt. Für die Inventur zusätzlich physische Standorte bis zum Regalfach anlegen und Export/Backup testen, bevor Hunderte Medien erfasst werden.


## 12.16 Shelf

**Worin das Programm praktisch stark ist:** Shelf konzentriert sich auf eine private Gesamtmediathek: Filme, CD-Pressungen, Bücher, Comics und Spiele passen in denselben Katalog. Die acht Scan-Modi verbinden Aufnahme, Suche, Inventur und einfache Ausleihe mit einer mobilen Oberfläche. Bei Musik ist die Unterscheidung mehrerer Albumpressungen eine ungewöhnlich nützliche Stärke.

**Empfohlene Funktionsprobe:** Test: EAN einer Blu-ray scannen, MusicBrainz-Daten einer mehrteiligen CD ergänzen, zwei physische Exemplare an unterschiedlichen Orten inventarisieren und eine Rückgabe buchen. Offline-PWA, KI-Fotoimport und externe Metadatenanbieter sollten separat bewertet werden, damit keine unerwarteten Cloudkosten entstehen.


## 12.17 uBiblio

**Worin das Programm praktisch stark ist:** uBiblio ist eine kleine Lösung für gemeinsame Papier- und E-Book-Bestände. Über Nutzerkonten und Einladungscodes entsteht schnell ein Buchclub-Katalog; Ausleih- und Rückgabefunktionen reichen für überschaubare Gruppen. Gespeicherte E-Book-Dateien lassen sich herunterladen, ohne dass damit ein hoch entwickelter integrierter Reader gemeint ist.

**Empfohlene Funktionsprobe:** Test: Drei Benutzer anlegen, ISBNs scannen, eine physische Ausgabe verleihen, eine elektronische Ausgabe hochladen, auf einem E-Reader herunterladen und danach Datenbank plus Dateien wiederherstellen. DVDs und CDs sollten nicht als fest eingeplante Standardfunktion gelten.


## 12.18 Calibre

**Worin das Programm praktisch stark ist:** Calibre ist die umfassendste lokale Werkzeugkette dieser Auswahl für E-Books: Dateiformate, Metadaten, Geräteschnittstellen, Konvertierung, Lesen und Editieren werden in einer Anwendung gebündelt. Die Stärke liegt in den digitalen Buchdateien, nicht in physischer Inventarnummerierung oder der Abwicklung von DVD-Ausleihen.

**Empfohlene Funktionsprobe:** Test: EPUB und PDF desselben Werks importieren, Metadaten aktualisieren, ein eigenes Feld anlegen, EPUB konvertieren und via Content-Server auf einem anderen Gerät lesen. Datensicherung sollte Bibliotheksdateien, Cover und Metadaten gemeinsam erfassen.


## 12.19 Calibre-Web

**Worin das Programm praktisch stark ist:** Calibre-Web erschließt eine bereits vorhandene Calibre-Bibliothek für mehrere Browsernutzer. Durch Rollen, Leserechte, OPDS und Kobo-Anbindung kann ein kleiner Familien-E-Book-Server entstehen. Konvertierung beruht gegebenenfalls auf zusätzlich installierten Calibre-Werkzeugen; Calibre-Web ersetzt deren Desktop-Editor nicht.

**Empfohlene Funktionsprobe:** Test: zwei Benutzer mit unterschiedlicher Sicht auf bestimmte Genres anlegen, auf einem Kobo synchronisieren, ein Buch an einen E-Reader senden und anschließend ein Backup wiederherstellen. Audio-Datei-Upload nicht mit fortgeschrittener Hörbuchfortschrittsverwaltung verwechseln.


## 12.20 BookOrbit

**Worin das Programm praktisch stark ist:** BookOrbit vereint mehrere digitale Lesewelten: EPUB/PDF, Comics und Hörbücher erhalten passende Reader beziehungsweise Audioplayer. Nutzerfortschritt, Lesezeichen, Mobilzugriff und Synchronisation machen das Programm stärker zu einer persönlichen digitalen Leseplattform als zu einer Ausleihtheke für physische Datenträger.

**Empfohlene Funktionsprobe:** Test: dasselbe Werk als EPUB, PDF und M4B ablegen, auf Web und Mobilgerät wechseln, Fortschritt und Anmerkungen prüfen und einen Offline-Download versuchen. Danach Backup, Dateisystemfreigaben und Server-/iOS-Version sorgfältig dokumentieren.


## 12.21 BookLore

**Worin das Programm praktisch stark ist:** BookLore bleibt interessant für bereits vorhandene Installationen und für einen Vergleich historischer Funktionsentwicklung. Die offizielle README nennt Smart Shelves, Metadaten, Reader, Geräte-Sync und mehrere Nutzer. Neuinstallationen sollten allerdings zuerst prüfen, welche Eigenschaften inzwischen nur noch im aktiv entwickelten Nachfolger BookOrbit voranschreiten.

**Empfohlene Funktionsprobe:** Für eine bestehende Installation Export und Migration nach BookOrbit mit einer Kopie der Bibliothek ausprobieren; insbesondere Cover, Lesefortschritte, eBook-Anmerkungen und Hörbuchdaten abgleichen. Vorher einen vollständigen datei- und datenbankkonsistenten Snapshot anfertigen.


## 12.22 Kavita

**Worin das Programm praktisch stark ist:** Kavita organisiert digitale Literatur besonders entlang von Reihen, Bänden und Leselisten. Dieser Ansatz passt sehr gut für Comics, Manga und umfangreiche EPUB-Sammlungen, bietet aber keine Verwaltung physischer DVD-Hüllen oder Musik-CD-Pressungen. Bei kostenpflichtigen Funktionen ist zwischen offener Grundsoftware und Kavita+ zu unterscheiden.

**Empfohlene Funktionsprobe:** Test: eine mehrbändige Comicreihe in CBZ und ein EPUB importieren, Benutzer mit Altersfiltern anlegen, Lesestand und Anmerkung speichern. Externe Metadatendienste getrennt von den Basisfunktionen prüfen.


## 12.23 Komga

**Worin das Programm praktisch stark ist:** Komga kann als privater digitaler Katalog- und Leseserver für Comics und E-Books dienen. Seine REST-API, OPDS-Angebote und Kobo-/KOReader-Anbindung sind eine gute Grundlage für ergänzende Clients. Ohne eigene Programmierung folgt daraus jedoch keine Inventur oder Ausleihlogik für physische CDs.

**Empfohlene Funktionsprobe:** Test: Serienordner mit mehreren Comicarchiven und EPUB-Dateien einlesen, Leselisten anlegen, getrennte Benutzerrechte setzen, über OPDS lesen und Metadaten via REST exportieren.


## 12.24 Inventaire

**Worin das Programm praktisch stark ist:** Inventaire stellt soziale Bestandsnachweise in den Mittelpunkt: Welche Bücher besitze ich, wer soll sie sehen, und möchte ich sie verleihen, verkaufen oder verschenken? Offene Wissensdaten helfen bei der Identifikation von Werken und Ausgaben. Für gemischte Medienbestände und reguläre Ausleihfristen einer Bibliothek ist der Funktionsansatz weniger passend.

**Empfohlene Funktionsprobe:** Test: eigene Bücher per ISBN erfassen, Sichtbarkeit auf privat/Freunde/öffentlich ändern, einem Kontakt ein Buch als verleihbar anbieten und externe Katalogdaten überprüfen. Film- und Musik-Datenträger gehören nicht zur zugesicherten Kernfunktion.

---

# 13. Systematisches Prüfprotokoll mit 110 Einzelanforderungen

**Hinweis:** Die folgenden 110 Punkte sind ein allgemeines Abnahme- und Anforderungsraster, **keine Positivliste eines bestimmten Programms**. Für jedes Produkt kann die Spalte „Ergebnis“ bei einem Praxistest ergänzt werden (`ja / mit Konfiguration / mit Plugin / nein / ungeprüft`).


## A. Werk, Titel, Ausgabe und Exemplar

- [ ] **F001** Trennung von Werk, Ausgabe/Edition und einzelnem Exemplar.

- [ ] **F002** Werke mit Übersetzungen, Hörbuch- und Filmadaptionen verknüpfen.

- [ ] **F003** Mehrere ISBN/EAN/UPC-Identifikatoren pro Ausgabe.

- [ ] **F004** Eine Ausgabe mit mehreren bestandsgeführten Exemplaren.

- [ ] **F005** Barcode/Inventarnummer pro Exemplar eindeutig vergeben.

- [ ] **F006** Signatur, Eigentümer, Zweigstelle und Standort pflegen.

- [ ] **F007** Mehrteilige Sets und individuelle Discs abbilden.

- [ ] **F008** Dubletten erkennen und gezielt zusammenführen.

- [ ] **F009** Zustand, Defekte und fehlende Teile vermerken.

- [ ] **F010** Aussonderung mit Grund und Verlauf erfassen.


## B. Bücher und periodische Druckwerke

- [ ] **F011** Autoren, Herausgeber, Übersetzer mit Rollen erfassen.

- [ ] **F012** Mehrere Verlage, Druck-/Ausgabejahre und Auflagen unterscheiden.

- [ ] **F013** ISBN-10, ISBN-13 und ISSN verarbeiten.

- [ ] **F014** Buchreihen, Bandnummern und Sammelbände verbinden.

- [ ] **F015** Schlagwörter, Normdaten und Klassifikation pflegen.

- [ ] **F016** Mehrsprachige Titel und Originaltitel hinterlegen.

- [ ] **F017** Kapitel-, Inhalts- und Abstract-Informationen erfassen.

- [ ] **F018** Zeitschriftenhefte und Abonnements dokumentieren.

- [ ] **F019** Erscheinungsvorhersagen und Hefteingänge verwalten.

- [ ] **F020** Buchcover, Schutzumschlag und Beilagenbilder speichern.


## C. DVDs, Blu-rays und Video

- [ ] **F021** DVD, Blu-ray und UHD-Blu-ray als verschiedene Formate pflegen.

- [ ] **F022** EAN/UPC und edition-spezifische Kennzeichen verwalten.

- [ ] **F023** Originaltitel, deutscher Titel und Alternativtitel speichern.

- [ ] **F024** Regie, Darsteller, Produktion und Drehbuch als Rollen erfassen.

- [ ] **F025** Veröffentlichungsjahr und Filmproduktionsjahr unterscheiden.

- [ ] **F026** FSK, Land, Genre und Filmlaufzeit speichern.

- [ ] **F027** Tonsprachen, Tonformate und Untertitel auflisten.

- [ ] **F028** Regionalcodes und Kopierschutzinformationen dokumentieren.

- [ ] **F029** Bonusmaterial und zusätzliche Discs als Set erfassen.

- [ ] **F030** Staffeln, Episoden, Boxsets und Filmreihen verbinden.


## D. Musik und physische Hörbücher

- [ ] **F031** Musik-CD, Vinyl, Kassette und digitale Musik getrennt modellieren.

- [ ] **F032** Label, Katalognummer und Pressung dokumentieren.

- [ ] **F033** Interpret, Komponist, Dirigent und Ensemble differenzieren.

- [ ] **F034** Tracklisten über mehrere Discs abbilden.

- [ ] **F035** Disc- und Tracknummern mit Dauer speichern.

- [ ] **F036** Versionen und Remaster desselben Albums verknüpfen.

- [ ] **F037** MusicBrainz-IDs und andere Musikkennungen speichern.

- [ ] **F038** Hörbuchautor, Sprecher und Audioverlag unterscheiden.

- [ ] **F039** Gekürzte und ungekürzte Lesung unterscheiden.

- [ ] **F040** Vollständigkeit von Hörbuchboxen vor Rücknahme prüfen.


## E. Digitalmedien, Lesen und Hören

- [ ] **F041** EPUB, PDF und andere Formate gezielt importieren.

- [ ] **F042** Mehrere digitale Formate einem Werk zuordnen.

- [ ] **F043** Dateispeicher, Backup und Prüfsummen verwalten.

- [ ] **F044** Dateien mit abweichenden Zugriffsrechten bereitstellen.

- [ ] **F045** Browser-Reader für EPUB und PDF prüfen.

- [ ] **F046** Buchmarkierungen und Notizen getrennt je Nutzer führen.

- [ ] **F047** M4B/MP3-Hörbücher importieren und streamen.

- [ ] **F048** Hörbuchkapitel, Tracks und Wiedergabeposition speichern.

- [ ] **F049** Offline-Lesen und Offline-Hören unterstützen.

- [ ] **F050** DRM-, Nutzungs- und Downloadrechte rechtlich sauber trennen.


## F. Recherche und Metadatenquellen

- [ ] **F051** Suche nach ISBN/EAN/UPC und Barcode anbieten.

- [ ] **F052** Volltextsuche in Metadaten und Dokumenten unterscheiden.

- [ ] **F053** Facetten nach Format, Sprache, Jahr und Standort bereitstellen.

- [ ] **F054** Tippfehler-, Varianten- und Alias-Suche prüfen.

- [ ] **F055** ISBN-Metadaten aus mehreren Quellen übernehmen.

- [ ] **F056** Filmmetadaten etwa aus TMDb importieren.

- [ ] **F057** Musikmetadaten etwa aus MusicBrainz importieren.

- [ ] **F058** Normdaten und MARC/SRU/Z39.50 verarbeiten.

- [ ] **F059** Bulk-Import mit Prüf- und Freigabeschritt anbieten.

- [ ] **F060** Herkunft und Aktualisierungszeit importierter Daten nachhalten.


## G. Ausleihe, Vormerkung und Leserdaten

- [ ] **F061** Benutzergruppen und Leserausweise verwalten.

- [ ] **F062** Leihfristen nach Medien- und Benutzerart konfigurieren.

- [ ] **F063** Ausleihe und Rückgabe per Scanner ausführen.

- [ ] **F064** Verlängerungen unter Berücksichtigung von Vormerkungen erlauben.

- [ ] **F065** Vormerkungswartelisten und Abholorte verwalten.

- [ ] **F066** Mahnungen und Benachrichtigungen auslösen.

- [ ] **F067** Gebühren, Erstattungen und Verluste verwalten.

- [ ] **F068** Datenschutzfreundliche Lösch- und Aufbewahrungsregeln setzen.

- [ ] **F069** Standortübergreifende Transporte protokollieren.

- [ ] **F070** Ausleihhistorie und Wiederherstellung kontrollieren.


## H. Inventur, Berichte, Finanzen

- [ ] **F071** Inventur per Barcode mit Soll-Ist-Abgleich durchführen.

- [ ] **F072** Verschollene und fehlende Exemplare protokollieren.

- [ ] **F073** Bestandsübersichten je Medium und Standort auswerten.

- [ ] **F074** Ausleihstatistiken nach Zeitraum und Medienart erstellen.

- [ ] **F075** Kaufpreise, Sammlungswerte und Währungen verwalten.

- [ ] **F076** Lieferanten und Erwerbungsvorschläge erfassen.

- [ ] **F077** Bestellungen, Budgets und Rechnungen verarbeiten.

- [ ] **F078** Periodika- und Bestellreklamationen nachhalten.

- [ ] **F079** Datenqualität und Dubletten statistisch auswerten.

- [ ] **F080** Revisionssichere administrative Protokolle prüfen.


## I. Betrieb, Sicherheit und Barrierefreiheit

- [ ] **F081** Linux-/BSD-/Windows-Betriebsform verbindlich testen.

- [ ] **F082** Offlinebetrieb und Cloudabhängigkeit getrennt prüfen.

- [ ] **F083** Benutzerrollen und Administrationsrechte minimieren.

- [ ] **F084** TLS, Reverse-Proxy und Zugangsschutz härten.

- [ ] **F085** Passwortverwaltung und gegebenenfalls OIDC/LDAP integrieren.

- [ ] **F086** Datenbank und Dateien konsistent sichern.

- [ ] **F087** Ein vollständiges Restore auf anderer Maschine testen.

- [ ] **F088** CSV/JSON/XML/MARC-Exporte mit Umlauten validieren.

- [ ] **F089** API und Automatisierung mit Berechtigungen prüfen.

- [ ] **F090** Mehrsprachigkeit, Zugänglichkeit und mobile Bedienung testen.


## J. Architektur, Weiterentwicklung und langfristige Pflege

- [ ] **F091** Lizenz und Copyright-Hinweise je Modul prüfen.

- [ ] **F092** Produkt-, Dokumentations- und API-Versionen pinnen.

- [ ] **F093** Testfälle für Medien- und Nutzerrechte dokumentieren.

- [ ] **F094** Fehlerhafte Importdaten rückgängig machen können.

- [ ] **F095** Import-/Export-Migration ohne Datenverlust beweisen.

- [ ] **F096** Plugins von Kernfunktionen abgrenzen.

- [ ] **F097** Externe Online-Dienste und ihre API-Keys dokumentieren.

- [ ] **F098** Lock-in durch proprietäre Formate prüfen.

- [ ] **F099** Aktivität, Issues und Sicherheitsreaktionen bewerten.

- [ ] **F100** Dokumentierte Update- und Rollback-Prozedur ausführen.


## K. Erweiterte Qualitäts- und Medienfunktionen

- [ ] **F101** Barcode-Scanner und Kameraerfassung gegenüberstellen.

- [ ] **F102** Drucklayouts für Etiketten und Leser-Ausweise testen.

- [ ] **F103** RFID und SIP2 separat prüfen.

- [ ] **F104** Echtzeit-Verfügbarkeiten im OPAC bereitstellen.

- [ ] **F105** Leselisten und Merklisten je Benutzer anbieten.

- [ ] **F106** Rezensionen, Bewertungen und Tags unterscheiden.

- [ ] **F107** Offene Kataloglinks und OPDS getrennt verwalten.

- [ ] **F108** Gerätesynchronisierung mit Kobo/KOReader prüfen.

- [ ] **F109** Serien und Adaptionen im Werkgraph verbinden.

- [ ] **F110** Zusätzliche Audiobookshelf- oder Comicserver integrieren.

---

# 14. Technische und lizenzrechtliche Ergänzungen

## 14.1 Nicht jedes „unterstützt E-Books“ bedeutet dasselbe

Ein bibliografischer Datensatz kann eine **digitale Ausgabe verzeichnen**, ohne die Datei zu verwalten. Ein Dateiverzeichnis kann EPUBs **speichern**, ohne sie im Browser anzuzeigen. Ein Reader kann ein EPUB **lesen**, ohne Nutzer- oder Lizenzmanagement für zeitlich befristete Ausleihe anzubieten. Eine professionelle ERM-Anwendung kann **Lizenzverträge und Holdings** verwalten, ohne selbst eine MP3 abzuspielen. Deshalb sollten Anforderungen an digitale Medien stets nach Katalogisierung, Dateiübernahme, Bereitstellung, Lesefunktion, Synchronisation und Lizenzprüfung getrennt bewertet werden.

## 14.2 Vergleich der Architekturphilosophien

| Typ | Beispiel | Stärke | Typischer Kompromiss |
|---|---|---|---|
| Ausgereiftes traditionelles ILS | Koha, Evergreen | Leihprozesse, Exemplare, Regeln, OPAC | Fachliche Einrichtung und Serverbetrieb |
| Moderne modulare Bibliotheksplattform | FOLIO, RERO ILS, InvenioILS | Strukturiertes Datenmodell, APIs, elektronische Ressourcen | Höhere technische Komplexität |
| Einfaches Web-ILS | OpenBiblio, SLiMS, OpenLibry | Schnelle Ausleihe, überschaubare Organisation | Teilweise weniger Spezialfelder und Verbundprozesse |
| Desktop-Sammlung | Tellico, GCstar, Data Crow, BiblioteQ | Lokale Kontrolle und individuelle Metadaten | Eingeschränkter Browser-/Mehrbenutzerbetrieb |
| Persönliche Medien-Webanwendung | Shelf, uBiblio | Smartphone, Familie, Barcode und Bestandsübersicht | Kein voller professioneller ILS-Funktionsumfang |
| Digitaler Lese-/Hörserver | BookOrbit, BookLore, Kavita, Komga | Dateien bereitstellen und im Browser lesen/hören | Keine Verwaltung physischer CD-/DVD-Exemplare |
| Digitale Buchsuite und Weboberfläche | Calibre, Calibre-Web | Konvertierung, Gerätezugriff und EPUB-Verwaltung | Keine professionelle physische Ausleihe |
| Gemeinsamer sozialer Buchkatalog | Inventaire | Teilen und offene Buch-Metadaten | Wenig Unterstützung von Film-/Musikdatenträgern |

## 14.3 Auffällige Besonderheiten, die bei der Vorauswahl nicht untergehen sollten

- **Koha** enthält laut aktuellem offiziellen Handbuch eigene Bereiche für ERM, Fernleihe, Kursapparate, Bestandserhaltung und Point of Sale. Diese liegen zusätzlich zu Katalogisierung, OPAC, Ausleihe und Erwerbung vor.
- **Evergreen** bietet differenzierte Vormerkungen bis hin zu einzelnen Teilen mehrteiliger Werke, was für DVDs und Boxsets besonders nützlich sein kann.
- **FOLIO** unterscheidet *Instance*, *Holdings* und *Item*; ERM umfasst Agreements, Lizenzen und eHoldings.
- **SLiMS** verfügt über einen Plugin-Ansatz, OAI-PMH-nahe Metadatendienste, Zeitschriftenmodule und Inventurfunktionen. Details sind releasespezifisch.
- **BiblioteQ** unterstützt lokale SQLite-Dateien und PostgreSQL sowie bibliografische Metadatendienste; es ist nicht automatisch ein moderner webbasierter Medienstreamer.
- **PMB** dokumentiert in älteren offiziellen Versionshinweisen auch Volltextsuche, WebDAV-Dokumentenverwaltung und EPUB-Anzeige. Diese Fähigkeiten müssen im vorgesehenen Release bestätigt werden.
- **Shelf** dokumentiert eigene Bibliotheksbestände für DVDs, Blu-rays, CDs, Schallplatten und E-Books sowie MusicBrainz-Pressungen, Barcode-/UPC-Scanning und optionale Fotoerkennung.
- **BookOrbit** nennt native iPhone-/iPad-/Watch-Nutzung, EPUB/PDF/Comic-/Hörbuch-Reader und bidirektionale Sync-Workflows; Server und Client haben konkrete Versionsanforderungen.
- **BookLore** bleibt als eigenes Programm im Katalog, wird vom Projekt aber zugunsten von BookOrbit nur noch begrenzt gepflegt.
- **Calibre-Web** kann Audio-Dateien hochladen; das ist kein Beweis für vollwertige Hörbuchkapitel- und Fortschrittssynchronisation.
- **Inventaire** wechselte zu Codeberg. Ein archivierter GitHub-Stand ist deshalb kein ausreichender Beleg für die Einstellung des Projekts.

## 14.4 Qualität der Aussagen und verbleibende Grenzen

**Direkt dokumentiert:** Der Funktionsbereich steht in einer offiziellen Projektbeschreibung oder Dokumentation. **Konfigurierbar:** Die Datenfelder und Prozesse erlauben prinzipiell die Verwendung für eine Medienart, die nicht ausdrücklich als fertiges eigenes Modul erwähnt wird. **Nicht verifiziert:** Für ein bestimmtes Format oder eine bestimmte Drittanbieterintegration liegt aus den konsultierten Quellen keine belastbare Zusage vor. **Praxistest erforderlich:** Ein Feature kann durch Versionswechsel, Plugins, Zahlungen, Betriebssystem oder externe API-Änderungen eingeschränkt sein.

Dieses Dokument hat deshalb den Charakter einer sorgfältig recherchierten **Funktions- und Anforderungslandkarte**, nicht einer reproduzierten Einzelprüfung jeder aktuellen Binärversion. Eine buchstäblich lückenlose Aufzählung aller internen Funktionen aller 24 Projekte ist ohne Installation, Quellcodeaudit und Versionsfixierung nicht seriös zu versprechen.

## 14.5 Zusätzliche unmittelbar überprüfte Primärquellen

- [Koha: Vollständige offizielle Modulübersicht](https://koha-community.org/manual/latest/en/html/using-koha.html)
- [Evergreen: differenzierte Vormerkungen und mehrteilige Medien](https://docs.evergreen-ils.org/docs/latest/circulation/basic_holds.html)
- [FOLIO: Inventory-Datenmodell](https://docs.folio.org/docs/metadata/inventory/)
- [FOLIO: elektronische Ressourcen](https://docs.folio.org/docs/erm/)
- [SLiMS: offizielles Repository und Systemanforderungen](https://github.com/slims/slims9_bulian)
- [RERO ILS: aktuelle Hilfe mit Modulen](https://bib.rero.ch/help/home_de/)
- [PMB Forge: offizieller historischer Funktionsüberblick](https://forge.sigb.net/projects/pmb/wiki/V40_EN)
- [BiblioteQ: Feature-README](https://github.com/textbrowser/biblioteq)
- [OpenBiblio Deutschland: Versionen, Sicherheit und PHP-Kompatibilität](https://openbiblio.de/anleitungen.php)
- [OpenLibry: Funktionen und Installation](https://github.com/jzakotnik/openlibry)
- [GCstar: offizielle Funktionsliste](https://gcstar.gitlab.io/gcstar_docs/en/)
- [Data Crow: Module und Anpassungsmöglichkeiten](https://datacrow.org/de/docs/einfuhrung/)
- [Shelf: aktueller Medien- und Scanfunktionsumfang](https://github.com/dgahagan/shelf)
- [uBiblio: Benutzer, E-Books, Backups](https://github.com/seanboyce/ubiblio)
- [Calibre: offizieller Funktionsüberblick](https://calibre-ebook.com/about)
- [Calibre-Web: offizieller Featurekatalog](https://github.com/janeczku/calibre-web)
- [BookOrbit: offizielle Funktionsliste und Lizenzhinweise](https://github.com/bookorbit/bookorbit)
- [BookLore: Status als Vorgänger von BookOrbit](https://github.com/booklore-app/booklore)
- [Kavita: offizielle Featureliste und Abgrenzung zu Kavita+](https://github.com/Kareadita/Kavita)
- [Komga: API, OPDS und Geräte-Sync](https://github.com/gotson/komga)
- [Inventaire: historische Repo-Archivierung und Codeberg-Umzug](https://github.com/inventaire/inventaire)

---

**Ende des Funktionskatalogs · Version 2.0 · 17.10.2026**
