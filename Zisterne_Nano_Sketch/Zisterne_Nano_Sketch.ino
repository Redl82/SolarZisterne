#include "DHT.h"


//////////////////////////////
// DHT21 / AMS2301 is at GPIO0
//////////////////////////////
#define DHTPINOUT 3
#define DHTPININ 4

// Uncomment whatever type you're using!
//#define DHTTYPE DHT11   // DHT 11 
#define DHTTYPE DHT22   // DHT 22  (AM2302)
//#define DHTTYPE DHT21   // DHT 21 (AM2301)

// init DHT;
DHT dhtout(DHTPINOUT, DHTTYPE);
DHT dhtin(DHTPININ, DHTTYPE); 


//////////////////////////////
// ACS712 Strom Messung
//////////////////////////////
const int SolarStromPin = A0;
const int ESPStromPin = A1;

void setup() 
{
  // start serial
  Serial.begin(9600);
  Serial.println();
  Serial.println("########################################################################################################");
  Serial.println("#Zisternen Wasserstandsanzeige, Temperatur und Feuchtigkeitslogger - D. Redlich 06/2017                #");
  Serial.println("#Der Arduino Nano wird zur ermittlung aller Sensor Messwerte benutzt.                                  #");
  Serial.println("#Dieser übermittelt die Messwerte dann mittels I2C an den EP8266                                       #");
  Serial.println("########################################################################################################");
  Serial.println();
  
  //start Temp und luftf. Sensoren
  dhtout.begin();
  dhtin.begin();

  Serial.println("Temperatur und Luftfeutigkeitssensoren wurden initialisiert");

}

void loop() {
  // Wait a few seconds between measurements.
  delay(3000);

  // Reading temperature or humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
  float h_out = dhtout.readHumidity();
  // Read temperature as Celsius (the default)
  float t_out = dhtout.readTemperature();
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
  float h_in = dhtin.readHumidity();
  // Read temperature as Celsius (the default)
  float t_in = dhtin.readTemperature();


  // Check if any reads failed and exit early (to try again).
  if (isnan(h_out) || isnan(t_out)) {
    Serial.println("Failed to read from DHT sensor OUT!");
    return;
  }
    if (isnan(h_in) || isnan(t_in)) {
    Serial.println("Failed to read from DHT sensor IN!");
    return;
  }

  Serial.print("Humidity out: ");
  Serial.print(h_out);
  Serial.print(" %\t");
  Serial.print("Temperature out: ");
  Serial.print(t_out);
  Serial.print(" *C ");
  Serial.print("Humidity in: ");
  Serial.print(h_in);
  Serial.print(" %\t");
  Serial.print("Temperature in: ");
  Serial.print(t_in);
  Serial.println(" *C ");
  Serial.print("Solarstrom: ");
  Serial.print(StromMessen(100, SolarStromPin));
  Serial.println(" Amper");

}

float StromMessen(int mitteln, int Pin) 
{
// Den ACS712 Stromsensor auslesen
// Sens ist im Datenblatt auf Seite 2 mit 185 angegeben.
// Für meinen Sensor habe ich 186 ermittelt bei 5.0V Vcc.
// Sens nimmt mit ca. 38 pro Volt VCC ab.
//
// 3,3V muss zu Analog Eingang 5 gebrückt werden.
// Der Sensoreingang ist Analog 1
//
// Parameter mitteln : die Anzahl der Mittlungen
// 
// Matthias Busse 9.5.2014 Version 1.0

float sense=185.0;           // mV/A Datenblatt Seite 2
float sensdiff=39.0;         // sense nimmt mit ca. 39/V Vcc ab
float vcc, vsensor, amp, ampmittel=0;
int i;
  
  for(i=0;i< mitteln;i++) {
    vcc = (float) 3.52 / analogRead(A5) * 1023.0;       // Ermittelt und Errechnet die Wirkliche Versorgungsspannung ermitteln. 3.5V Anpassen wenn bessere Versorgungsspannung verfügbar
    vsensor = (float) analogRead(Pin) * vcc / 1023.0;   // Errechnet die Sapannung die tatsächlich am Analogeingang anliegt, bei 0A --> ca.2,5V
    vsensor = (float) vsensor - (vcc/2);                // Nulldurchgang (vcc/2) abziehen, bei 0A-->0V
    sense = (float) 185.0 ;//-((5.00-vcc)*sensdiff);      // sense für Vcc korrigieren, korrigiert die nichtlinearität des sensors (noch nciht ganz verstanden, erklärung hier: http://shelvin.de/den-acs-712-5a-strom-sensor-am-arduino-auslesen/
    amp = (float) vsensor /sense *1000 ;                // Ampere berechnen
    ampmittel += amp;                                   // Summieren
  }
  return ampmittel/mitteln;
}
