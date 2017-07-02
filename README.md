# SolarZisterne

Es handelt sich bei diesem Projekt um einen Füllstandsmesser für eine Außen-Zisterne.
Der Füllstandsmesser wir über einen ESP8266 mit dem Netzwerkverbunden und agiert als eigenständiger Web-Server.
Die Stromversorgung wird über Solarzellen gewährleistet.
Das Projekt besitz die folgenden Sensoren:
- Ultraschall Sensor für Füllstand
- Temperatur/Luftfeuchte/Luftdruck Sensor außen
- Temperatur/Luftdruck Sensor innen
- Spannung/Strom Sensor Produktion Solarzellen
- Spannung/Strom Sensor Verbrauch Elektronik







Die Lade Schaltung kann die follgenden Zustände annehmen:
            GPIO2   GPIO1   GPIO0
     Wert   STAT1   STAT2   PG      Status
     7      1       1       1       Input Power Not OK / Shutdown
     6      1       1       0       Input Power OK / No Battery Present
     4      1       0       0       Input Power OK / Charge Complete - Standby
     3      0       1       1       Input Power Not OK / Low Battery Output
     2      0       1       0       Input Power OK / Chargin Batter in Constant Current/Voltage or Preconding Mode
     0      0       0       0       Input Power OK / Temperature Fault / Temperatur Fault
	 

