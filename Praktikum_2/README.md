# Praktikum 2

# Welche andere Anwendung von Ringpuffern oder aehnlichen Strukturen kennen sie?
Bei Dashcams werden immer aeltere Dateien ueberschrieben da wenn nicht auf
diese Dateien zugegriffen wird sie nicht noetig waren als Beweismittel

# Waere eine Sicherung dieser Art in einem Rechenzentrum sinnvoll?
Wenn man nur eine bestimmte anzahl an Speicher zur verfuegung hat speichert
diese Loesung das aelteste was in der Limitation passt

# Koennen wir als Techniker die Dauer der Aufbewahrung frei bestimmen oder gibt es gesetzliche Regelungen?
Buchhaltung, 10 Jahre Aufbewahrungspflicht
Es gibt keine pflicht zu backups, sondern nur zur Archivierung

# Nennen sie 3 Punkte, die sie im Rahmen des Backup-Szenarios verbessern wuerden

- Ringpuffer innerhalb Ringpuffer, um aenderungen zu einzelnen Dateien zu tracken
- keine age benutzen, statdessen size des buffers behalten und annehmen das der
  naechste immer der aelteste ist
- Ringpuffer constructen mit einem int um die laenge des puffers zu bestimmen
- Template machen fuer besser spezialisierung
- Moeglicherweise fuer mehrere versionen bei textdateien nur einen diff speichern zur letzen version und den mergen falls der backup entfernt wird
