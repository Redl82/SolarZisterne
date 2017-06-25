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


}
