/*---------------------------------------------------
HTTP 1.1 Outdoor Webserver for WeMos Mini
for ESP8266 adapted Arduino IDE

by Daniel 07/2017 - free for anyone
---------------------------------------------------*/

#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
#include <SPI.h>
#include <SD.h>
#include <Wire.h>                        // I2C
#include <Adafruit_INA219.h>             // INA219 Strommessung
#include "Adafruit_MCP23008.h"           // MCP23008
#include "time_ntp.h"
#include "DHT.h"

// WiFi connection
const char* ssid = "Noname_MUC_N";
const char* password = "270487ddd";

// ntp timestamp
unsigned long ulSecs2000_timer=0;

// storage for Measurements; keep some mem free; allocate remainder
#define KEEP_MEM_FREE 10240
#define MEAS_SPAN_H 4                   // Dauer bis Speicher, voll in Stunden 744h-->31Tage Messung ca. all 20 Min.
unsigned long ulMeasCount=0;            // values already measured
unsigned long ulNoMeasValues=0;         // size of array
unsigned long ulMeasDelta_ms;           // distance to next meas time
unsigned long ulNextMeas_ms;            // next meas time
unsigned long *pulTime;                 // array for time points of measurements
float *pfTemp,*pfHum,*pfDist;           // array for temperature, humidity and Distance measurements
float pfPres, pfTempIn, pfHumIn;        // Werte Luftdruck außen, Temperatur und Luftdruck innen
float pfSolarSp, pfSolarSt, pfSolarLe;  // Werte für Solar Spannung Strom und Leistung
float pfVerbSp, pfVerbSt, pfVerbLei;    // Werte für Verbraucher Spannung Strom und Leistung
String stStatus;                         // Array für Status 

unsigned long ulReqcount;       // how often has a valid page been requested
unsigned long ulReconncount;    // how often did we connect to WiFi

// Create an instance of the server on Port 80
WiFiServer server(80);

//////////////////////////////
// DHT21 / AMS2301 is at GPIO0
//////////////////////////////
#define DHTPIN D3

//////////////////////////////
// Ultraschall Sensor HC-SR04 Pin definition
//////////////////////////////
#define TRIGGER D1
#define ECHO    D2


// Uncomment whatever type you're using!
//#define DHTTYPE DHT11   // DHT 11 
#define DHTTYPE DHT22   // DHT 22  (AM2302)
//#define DHTTYPE DHT21   // DHT 21 (AM2301)

// init DHT; 3rd parameter = 16 works for ESP8266@80MHz
DHT dht(DHTPIN, DHTTYPE,16); 

// set up variables using the SD utility library functions:
Sd2Card card;
SdVolume volume;
SdFile root;
// change this to match your SD shield or module;
// WeMos Micro SD Shield: D8
const int chipSelect = D8;


//mathematische Definition des Volumens der Zisterne



// needed to avoid link error on ram check
extern "C" 
{
#include "user_interface.h"
}
// Deklariert Digitalport expander MCP23008
Adafruit_MCP23008 mcp;

// Deklariert StromMessensor INA219 
Adafruit_INA219 ina219in;                           //Sensor vor MCP73871
Adafruit_INA219 ina219out(0x41);                    //Sensor nach MCP73871

/////////////////////
// the setup routine
/////////////////////
void setup() 
{
  // setup globals
  ulReqcount=0; 
  ulReconncount=0;
    
  // start serial
  Serial.begin(9600);
  Serial.println();
  Serial.println("########################################################################################################");
  Serial.println("#Zisternen Wasserstandsanzeige, Temperatur und Feuchtigkeitslogger - D. Redlich 04/2017                #");
  Serial.println("#Basis des Programms kann unter:                                                                       #");
  Serial.println("#https://blog.thesen.eu/wlan-lufttemperatur-und-feuchte-logger-mit-grafischer-darstellung-fuer-esp8266/#");
  Serial.println("#gefunden werden.                                                                                      #");
  Serial.println("########################################################################################################");
  Serial.println();
  
  //Start I2C
  Wire.begin();
  Serial.println("########################################################################################################");
  Serial.println("");
  Serial.println("I2C initialisiert!");
  Serial.println("SCL auf Pin D1 und SCA auf Pin D2");
  //Sucht nach benutzten GPIO Adressen
  byte error, address;
  int nDevices;

  Serial.println("Suche nach Geräten...");
  
  nDevices = 0;
  for(address = 1; address < 127; address++ ) 
  {
    // The i2c_scanner uses the return value of
    // the Write.endTransmisstion to see if
    // a device did acknowledge to the address.
    Wire.beginTransmission(address);
    error = Wire.endTransmission();

    if (error == 0)
    {
      Serial.print("I2C Gerät auf adresse 0x");
      if (address<16) 
        Serial.print("0");
      Serial.print(address,HEX);
      Serial.println("  gefunden !");

      nDevices++;
    }
    else if (error==4) 
    {
      Serial.print("Unknown error at address 0x");
      if (address<16) 
        Serial.print("0");
      Serial.println(address,HEX);
    }    
  }
  if (nDevices == 0)
    Serial.println("No I2C devices found\n");
  else
    Serial.println("Fertsch\n");

  mcp.begin();                // use default address 0x20 oder 0 GPIO Expander 
  
  Serial.println("GPIO Erweiterung auf 0x20 eingerichtet!");
  
  mcp.pinMode(0, INPUT);      // definiert Pin 0 als Input --> PG
  mcp.pinMode(1, INPUT);      // definiert Pin 1 als Input --> STAT2
  mcp.pinMode(2, INPUT);      // definiert Pin 2 als Input --> STAT1
  mcp.pullUp(0, HIGH);        // turn on a 100K pullup internally
  mcp.pullUp(1, HIGH);        // turn on a 100K pullup internally
  mcp.pullUp(2, HIGH);        // turn on a 100K pullup internally

  Serial.println("GPIO0 --> PG");
  Serial.println("GPIO1 --> STAT1");
  Serial.println("GPIO2 --> STAT2");

  Serial.println("Pull-Up Wiederstände wurden eingeschaltet");
  
  Serial.println("");
  Serial.println("########################################################################################################");
  Serial.println("");
  Serial.println("########################################################################################################");
  Serial.println("");
  ina219in.begin();
  ina219out.begin();
  Serial.println("Sensor zum messen des Solar Eingans Stromes und Spannung wurden auf der Adresse 0X40 eingerichtet");
  Serial.println("Sensor zum messen des Verbrauchten Stromes und Spannung wurden auf der Adresse 0X41 eingerichtet");
  Serial.println("");
  Serial.println("########################################################################################################");
  Serial.println("");
  
  //Definition der Pins für Ultraschall Sensor
  pinMode(TRIGGER, OUTPUT);
  pinMode(ECHO, INPUT);
  Serial.println("########################################################################################################");
  Serial.println("");
  Serial.println("Ultraschall Sensor wurde wie folgt eingerichte:");
  Serial.println("Ultraschall Sensor wird eingerichte:");
  Serial.print("Triger auf Pin ");
  Serial.println(TRIGGER);
  Serial.print("Echo auf Pin ");
  Serial.println(ECHO);
  Serial.println("");
  Serial.println("Ultraschall Sensor wurde wie folgt eingerichte:");
  Serial.println("");
  Serial.println("########################################################################################################");
  
  // inital connect
  WiFi.mode(WIFI_STA);
  WiFi.hostname("Zisterne");
  WiFiStart();

  //Einrichten der SD-Karte

  Serial.println("");
  Serial.println("########################################################################################################");
  Serial.println("");
  Serial.println("Initializing SD card...");
  if (!card.init(SPI_HALF_SPEED, chipSelect)) 
  {
    Serial.println("Es wurde keine SD-Karte gefunden! Es können keine Messdaten gespeichert werden extern gespeichert werden!");
    //Serial.println("* is a card inserted?");
    //Serial.println("* is your wiring correct?");
    //Serial.println("* did you change the chipSelect pin to match your shield or module?");
    //return;
  } 
  else 
  {
    Serial.println("SD-Karte wurde gefunden. Karte wird eigerichtet, damit Messdaten darauf gespeichert werden können!");

      // print the type of card
      Serial.print("Card type: ");
      switch (card.type()) {
        case SD_CARD_TYPE_SD1:
          Serial.println("SD1");
          break;
        case SD_CARD_TYPE_SD2:
          Serial.println("SD2");
          break;
        case SD_CARD_TYPE_SDHC:
          Serial.println("SDHC");
          break;
        default:
          Serial.println("Unknown");
      }
      // Now we will try to open the 'volume'/'partition' - it should be FAT16 or FAT32
      if (!volume.init(card)) {
        Serial.println("Could not find FAT16/FAT32 partition.\nMake sure you've formatted the card");
        return;
      }
        // print the type and size of the first FAT-type volume
      uint32_t volumesize;
      Serial.print("Volume type is FAT");
      Serial.println(volume.fatType(), DEC);
      volumesize = volume.blocksPerCluster();    // clusters are collections of blocks
      volumesize *= volume.clusterCount();       // we'll have a lot of clusters
      volumesize *= 512;                            // SD card blocks are always 512 bytes
      Serial.print("Volume size (bytes): ");
      Serial.print(volumesize);
      Serial.println("  (Muss nicht stimmen)");
      // see if the card is present and can be initialized:
      if (!SD.begin(chipSelect)) 
      {
        Serial.println("Card failed, or not present");
        // don't do anything more:
      }
      Serial.println("Einrichten der SD-Karte abgeschlossen");
  
    }

  Serial.println("");
  Serial.println("########################################################################################################");
  Serial.println("");

  // allocate ram for data storage
  uint32_t free=system_get_free_heap_size() - KEEP_MEM_FREE;
  ulNoMeasValues = free / (sizeof(float)*3+sizeof(unsigned long));  // humidity & temp --> 2 + time
  pulTime = new unsigned long[ulNoMeasValues];
  pfTemp = new float[ulNoMeasValues];
  pfHum = new float[ulNoMeasValues];
  pfDist = new float[ulNoMeasValues];
  
  if (pulTime==NULL || pfTemp==NULL || pfHum==NULL || pfDist==NULL)
  {
    ulNoMeasValues=0;
    Serial.println("Error in memory allocation!");
  }
  else
  {
    Serial.print("Allocated storage for ");
    Serial.print(ulNoMeasValues);
    Serial.println(" data points.");
    
    float fMeasDelta_sec = MEAS_SPAN_H*3600./ulNoMeasValues;
    ulMeasDelta_ms = ( (unsigned long)(fMeasDelta_sec+0.5) ) * 1000;  // round to full sec
    Serial.print("Measurements will happen each ");
    Serial.print(ulMeasDelta_ms);
    Serial.println(" ms.");
    
    ulNextMeas_ms = millis()+ulMeasDelta_ms;

    Serial.println("");
    Serial.println("########################################################################################################");
    Serial.println("");
  }
 
}


///////////////////
// (re-)start WiFi
///////////////////
void WiFiStart()
{
  ulReconncount++;
  
  // Connect to WiFi network
  Serial.println();

  Serial.print("Connecting to ");
  Serial.println(ssid);
  
  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) 
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  
  // Start the server
  server.begin();
  Serial.println("Server started");

  // Print the IP address
  Serial.println("");
  Serial.println("#############################################################################################");
  Serial.print("# Die Messwert sind im Browser unter 'Zisterne' oder unter der IP:");
  Serial.print(WiFi.localIP());
  Serial.println(" erreichbar! #");
  Serial.println("#############################################################################################");
  Serial.println("");
    
  ///////////////////////////////
  // connect to NTP and get time
  ///////////////////////////////
  Serial.println("Aktuelle Uhrzeit wird ermittel...");
  ulSecs2000_timer=getNTPTimestamp();
  Serial.print("Current Time UTC from NTP server: " );
  Serial.println(epoch_to_string(ulSecs2000_timer).c_str());

  ulSecs2000_timer -= millis()/1000;  // keep distance to millis() counter
}


/////////////////////////////////////
// make html table for measured data
/////////////////////////////////////
unsigned long MakeTable (WiFiClient *pclient, bool bStream)
{
  unsigned long ulLength=0;
  
  // here we build a big table.
  // we cannot store this in a string as this will blow the memory   
  // thus we count first to get the number of bytes and later on 
  // we stream this out
  if (ulMeasCount==0) 
  {
    String sTable = "Noch keine Daten verf&uuml;gbar.<BR>";
    if (bStream)
    {
      pclient->print(sTable);
    }
    ulLength+=sTable.length();
  }
  else
  { 
    unsigned long ulEnd;
    if (ulMeasCount>ulNoMeasValues)
    {
      ulEnd=ulMeasCount-ulNoMeasValues;
    }
    else
    {
      ulEnd=0;
    }
    
    String sTable;
    sTable = "<table style=\"width:100%\"><tr><th>Zeit / UTC</th><th>T &deg;C</th><th>Hum &#037;</th><th>F&uuml;llstand &#037;</th></tr>";
    sTable += "<style>table, th, td {border: 2px solid black; border-collapse: collapse;} th, td {padding: 5px;} th {text-align: left;}</style>";
    for (unsigned long li=ulMeasCount;li>ulEnd;li--)
    {
      unsigned long ulIndex=(li-1)%ulNoMeasValues;
      sTable += "<tr><td>";
      sTable += epoch_to_string(pulTime[ulIndex]).c_str();
      sTable += "</td><td>";
      sTable += pfTemp[ulIndex];
      sTable += "</td><td>";
      sTable += pfHum[ulIndex];
      sTable += "</td><td>";
      sTable += pfDist[ulIndex];
      sTable += "</td></tr>";

      // play out in chunks of 1k
      if(sTable.length()>1024)
      {
        if(bStream)
        {
          pclient->print(sTable);
          //pclient->write(sTable.c_str(),sTable.length());
        }
        ulLength+=sTable.length();
        sTable="";
      }
    }
    
    // remaining chunk
    sTable+="</table>";
    ulLength+=sTable.length();
    if(bStream)
    {
      pclient->print(sTable);
      //pclient->write(sTable.c_str(),sTable.length());
    }   
  }
  
  return(ulLength);
}
  

////////////////////////////////////////////////////
// make google chart object table for measured data
////////////////////////////////////////////////////
unsigned long MakeList (WiFiClient *pclient, bool bStream)
{
  unsigned long ulLength=0;
  
  // here we build a big list.
  // we cannot store this in a string as this will blow the memory   
  // thus we count first to get the number of bytes and later on 
  // we stream this out
  if (ulMeasCount>0) 
  { 
    unsigned long ulBegin;
    if (ulMeasCount>ulNoMeasValues)
    {
      ulBegin=ulMeasCount-ulNoMeasValues;
    }
    else
    {
      ulBegin=0;
    }
    
    String sTable="";
    for (unsigned long li=ulBegin;li<ulMeasCount;li++)
    {
      // result shall be ['18:24:08 - 21.5.2015',21.10,49.00],
      unsigned long ulIndex=li%ulNoMeasValues;
      sTable += "['";
      sTable += epoch_to_string(pulTime[ulIndex]).c_str();
      sTable += "',";
      sTable += pfTemp[ulIndex];
      sTable += ",";
      sTable += pfHum[ulIndex];
      sTable += ",";
      sTable += pfDist[ulIndex];
      sTable += "],\n";

      // play out in chunks of 1k
      if(sTable.length()>1024)
      {
        if(bStream)
        {
          pclient->print(sTable);
          //pclient->write(sTable.c_str(),sTable.length());
        }
        ulLength+=sTable.length();
        sTable="";
      }
    }
    
    // remaining chunk
    if(bStream)
    {
      pclient->print(sTable);
      //pclient->write(sTable.c_str(),sTable.length());
    } 
    ulLength+=sTable.length();  
  }
  
  return(ulLength);
}


//////////////////////////
// create HTTP 1.1 header
//////////////////////////
String MakeHTTPHeader(unsigned long ulLength)
{
  String sHeader;
  
  sHeader  = F("HTTP/1.1 200 OK\r\nContent-Length: ");
  sHeader += ulLength;
  sHeader += F("\r\nContent-Type: text/html\r\nConnection: close\r\n\r\n");
  
  return(sHeader);
}


////////////////////
// make html footer
////////////////////
String MakeHTTPFooter()
{
  String sResponse;
  
  sResponse  = F("<FONT SIZE=-2><BR>Aufrufz&auml;hler="); 
  sResponse += ulReqcount;
  sResponse += F(" - Verbindungsz&auml;hler="); 
  sResponse += ulReconncount;
  sResponse += F(" - Freies RAM=");
  sResponse += (uint32_t)system_get_free_heap_size();
  sResponse += F(" - Max. Datenpunkte=");
  sResponse += ulNoMeasValues;
  sResponse += F("<BR>Daniel Redlich 08/2017<BR></body></html>");
  
  return(sResponse);
}


/////////////
// main look
/////////////
void loop() 
{
  ///////////////////
  // do data logging
  ///////////////////
  if (millis()>=ulNextMeas_ms) 
  {
    ulNextMeas_ms = millis()+ulMeasDelta_ms;
    //Messung der Entfernung
    digitalWrite(TRIGGER, LOW);  
    delayMicroseconds(2); 
  
    digitalWrite(TRIGGER, HIGH);
    delayMicroseconds(10); 
  
    digitalWrite(TRIGGER, LOW);
    pfDist[ulMeasCount%ulNoMeasValues]= map(((pulseIn(ECHO, HIGH)/2) / 29.1),0,200,0,100);     //Misst die Zeit von bis zur die Signal brauch vom Aussendenbis zur Rückkehr
                                                                                               // /2 /29,1 rechnet Zeit in Distanz in mm um
                                                                                               // Map Befehl errechnet daraus eine Prozent Zhal des Füll Standes    
    //Messung der Luftfeuchtigkeit und Temperatur
    pfHum[ulMeasCount%ulNoMeasValues] = dht.readHumidity();
    pfTemp[ulMeasCount%ulNoMeasValues] = dht.readTemperature();
    pulTime[ulMeasCount%ulNoMeasValues] = millis()/1000+ulSecs2000_timer;
    int i=0;
    while (isnan(pfHum[ulMeasCount%ulNoMeasValues])||isnan(pfTemp[ulMeasCount%ulNoMeasValues])||isnan(pulTime[ulMeasCount%ulNoMeasValues]))
    {
      i++;
      Serial.print("Fehlerhafte Messung: ");
      Serial.print (i);
      Serial.println(" !!!");
      Serial.println("Messwerte werden verworfen und Messung wird wiederholt");
      delay(1000);
      pfHum[ulMeasCount%ulNoMeasValues] = dht.readHumidity();
      pfTemp[ulMeasCount%ulNoMeasValues] = dht.readTemperature();
      pulTime[ulMeasCount%ulNoMeasValues] = millis()/1000+ulSecs2000_timer;
      if (i>=10)
      {
        pfHum[ulMeasCount%ulNoMeasValues] = 0;
        pfTemp[ulMeasCount%ulNoMeasValues] = 0;
        break;
      }
    }

    //Status der Solar-Lade Schaltung

    /*
            GPIO2   GPIO1   GPIO0
     Wert   STAT1   STAT2   PG      Status
     7      1       1       1       Input Power Not OK / Shutdown
     6      1       1       0       Input Power OK / No Battery Present
     4      1       0       0       Input Power OK / Charge Complete - Standby
     3      0       1       1       Input Power Not OK / Low Battery Output
     2      0       1       0       Input Power OK / Chargin Batter in Constant Current/Voltage or Preconding Mode
     0      0       0       0       Input Power OK / Temperature Fault / Temperatur Fault
    */
    
    switch (mcp.readGPIO()) 
    {
      case 0:
        stStatus="Input Power OK / Temperatur Fehler oder Timer Fehler (0)";
        break;
      case 1:
        stStatus="Nicht definert";
        break;
      case 2:
        stStatus="Input Power OK / Chargin Batter in Constant Current/Voltage or Preconding Mode (2)";
        break;
      case 3:
        stStatus="Input Power Not OK / Low Battery Output (3)";
        break;
      case 4:
        stStatus="Input Power OK / Charge Complete - Standby (4)";
        break;
      case 5:
        stStatus="Nicht definert";
        break;
      case 6:
        stStatus="Input Power OK / No Battery Present (6)";
        break;
      case 7:
        stStatus="Input Power Not OK / Shutdown (7)";
        break;
    }  


    //Seriele AUsgabe des Status
    Serial.print("Logging External Temperature: "); 
    Serial.print(pfTemp[ulMeasCount%ulNoMeasValues]);
    Serial.print(" deg Celsius - Humidity: "); 
    Serial.print(pfHum[ulMeasCount%ulNoMeasValues]);
    Serial.print("% - Filled: ");
    Serial.print(pfDist[ulMeasCount%ulNoMeasValues]);
    Serial.print("% - Pressure: ");
    Serial.print(pfPres);
    Serial.print("hPa - Time: ");
    Serial.println(pulTime[ulMeasCount%ulNoMeasValues]);
    Serial.print("Status: ");
    Serial.println(stStatus); 
    
  //////////////////////////////
  //Messwerte auf SD-Karte speichern
  //////////////////////////////


  // Check to see if the file exists:
  if (SD.exists("LogFile.csv")) 
  {
        File LogFile = SD.open("LogFile.csv", FILE_WRITE);
        // if the file is available, write to it:
        if (LogFile) 
        {
          LogFile.print(epoch_to_string(pulTime[ulMeasCount%ulNoMeasValues]).c_str());
          LogFile.print(";");
          String pfDistKomma =  String(pfDist[ulMeasCount%ulNoMeasValues]);         //wandelt Float ind String
          pfDistKomma.replace(".",",");                                            // ersetzt Punkt mit Komma
          LogFile.print(pfDistKomma);
          LogFile.print(";");
          String pfTempKomma =  String(pfTemp[ulMeasCount%ulNoMeasValues]);
          pfTempKomma.replace(".",",");
          LogFile.print(pfTempKomma);
          LogFile.print(";");
          String pfHumKomma =  String(pfHum[ulMeasCount%ulNoMeasValues]);
          pfHumKomma.replace(".",",");
          LogFile.print(pfHumKomma);
          LogFile.print(";");          
          LogFile.print("pfPres");
          LogFile.print(";");
          LogFile.print("pfTempIn");
          LogFile.print(";");
          LogFile.print("pfHumIn");
          LogFile.print(";");
          LogFile.print(stStatus);
          LogFile.print(";");
          LogFile.print("pfSolarSp");
          LogFile.print(";");
          LogFile.print("pfSolarSt");
          LogFile.print(";");
          LogFile.print("pfSolarLe");
          LogFile.print(";");
          LogFile.print("pfVerbSp");
          LogFile.print(";");
          LogFile.print("pfVerbSt");
          LogFile.print(";");
          LogFile.print("pfVerbLei");    
          LogFile.println(";");
          LogFile.close();
         
        }
        // if the file isn't open, pop up an error:
        else 
        {
          Serial.println("error opening Logfile.csv");
        }
  }
  else 
  {
    File LogFile = SD.open("LogFile.csv", FILE_WRITE);
    // if the file is available, write to it:
    if (LogFile) 
    {
      LogFile.println("\"sep=;\"");
      LogFile.print("Datum");
      LogFile.print(";");
      LogFile.print("Zisternen Fuellstand[%]");
      LogFile.print(";");
      LogFile.print("Temperatur Aussen[*C]");                //Schreibt Außen Temperatur
      LogFile.print(";");
      LogFile.print("Luftfeuchtigkeit Aussen[%]");
      LogFile.print(";");
      LogFile.print("Luftdruck Aussen[hPa]");
      LogFile.print(";");
      LogFile.print("Temperatur Innen[*C]");
      LogFile.print(";");
      LogFile.print("Luftdruck Innen[hPa]");
      LogFile.print(";");
      LogFile.print("Status");
      LogFile.print(";");
      LogFile.print("Solar Spannung[V]");
      LogFile.print(";");
      LogFile.print("Solar Strom[A]");
      LogFile.print(";");
      LogFile.print("Solar Leistung[W]");
      LogFile.print(";");
      LogFile.print("Verbrauch Spannung[V]");
      LogFile.print(";");
      LogFile.print("Verbrauch Strom[A]");
      LogFile.print(";");
      LogFile.print("Verbrauch Leistung[W]");
      LogFile.println(";");
      LogFile.close();
      Serial.println("Tabellenkopf wurde angelegt.");
    }
    // if the file isn't open, pop up an error:
    else 
    {
      Serial.println("error opening Logfile.csv");
    }
    
  }
    ulMeasCount++; 
  }
  //////////////////////////////
  // check if WLAN is connected
  //////////////////////////////
  if (WiFi.status() != WL_CONNECTED)
  {
    WiFiStart();
  }
  
  ///////////////////////////////////
  // Check if a client has connected
  ///////////////////////////////////
  WiFiClient client = server.available();
  if (!client) 
  {
    return;
  }
  
  // Wait until the client sends some data
  Serial.println("new client");
  unsigned long ultimeout = millis()+250;
  while(!client.available() && (millis()<ultimeout) )
  {
    delay(1);
  }
  if(millis()>ultimeout) 
  { 
    Serial.println("client connection time-out!");
    return; 
  }
  
  /////////////////////////////////////
  // Read the first line of the request
  /////////////////////////////////////
  String sRequest = client.readStringUntil('\r');
  //Serial.println(sRequest);
  client.flush();
  
  // stop client, if request is empty
  if(sRequest=="")
  {
    Serial.println("empty request! - stopping client");
    client.stop();
    return;
  }
  
  // get path; end of path is either space or ?
  // Syntax is e.g. GET /?show=1234 HTTP/1.1
  String sPath="",sParam="", sCmd="";
  String sGetstart="GET ";
  int iStart,iEndSpace,iEndQuest;
  iStart = sRequest.indexOf(sGetstart);
  if (iStart>=0)
  {
    iStart+=+sGetstart.length();
    iEndSpace = sRequest.indexOf(" ",iStart);
    iEndQuest = sRequest.indexOf("?",iStart);
    
    // are there parameters?
    if(iEndSpace>0)
    {
      if(iEndQuest>0)
      {
        // there are parameters
        sPath  = sRequest.substring(iStart,iEndQuest);
        sParam = sRequest.substring(iEndQuest,iEndSpace);
      }
      else
      {
        // NO parameters
        sPath  = sRequest.substring(iStart,iEndSpace);
      }
    }
  }
    
  
  ///////////////////////////
  // format the html response
  ///////////////////////////
  String sResponse,sResponse2,sHeader;
  
  /////////////////////////////
  // format the html page for /
  /////////////////////////////
  if(sPath=="/") 
  {
    ulReqcount++;
    int iIndex= (ulMeasCount-1)%ulNoMeasValues;
    sResponse  = F("<html>\n<head>\n<title>Zisternen F&uuml;llstandsanzeige, Temperatur- und Feuchtigkeitslogger</title>\n<script type=\"text/javascript\" src=\"https://www.google.com/jsapi?autoload={'modules':[{'name':'visualization','version':'1','packages':['gauge']}]}\"></script>\n<script type=\"text/javascript\">\nvar temp=");
    sResponse += pfTemp[iIndex];
    sResponse += F(",hum=");
    sResponse += pfHum[iIndex];
    sResponse += F(",dist=");
    sResponse += pfDist[iIndex];
    sResponse += F(";\ngoogle.load('visualization', '1', {packages: ['gauge']});google.setOnLoadCallback(drawgaugetemp);google.setOnLoadCallback(drawgaugehum);google.setOnLoadCallback(drawgaugedist);\nvar gaugetempOptions = {min: -20, max: 50, yellowFrom: -20, yellowTo: 0,redFrom: 30, redTo: 50, minorTicks: 10, majorTicks: ['-20','-10','0','10','20','30','40','50']};\n");
    sResponse += F("var gaugehumOptions = {min: 0, max: 100, yellowFrom: 0, yellowTo: 25, redFrom: 75, redTo: 100, minorTicks: 10, majorTicks: ['0','10','20','30','40','50','60','70','80','90','100']};var gaugedistOptions = {min: 0, max: 100, yellowFrom: 100, yellowTo: 100, redFrom: 0, redTo: 25, minorTicks: 10, majorTicks: ['0','10','20','30','40','50','60','70','80','90','100']};");
    sResponse += F("\nvar gaugetemp,gaugehum,gaugedist;\n\nfunction drawgaugetemp() {\ngaugetempData = new google.visualization.DataTable();\n");
    sResponse += F("gaugetempData.addColumn('number', '\260C');\ngaugetempData.addRows(1);\ngaugetempData.setCell(0, 0, temp);\ngaugetemp = new google.visualization.Gauge(document.getElementById('gaugetemp_div'));\ngaugetemp.draw(gaugetempData, gaugetempOptions);\n}\n\n");
    sResponse += F("function drawgaugehum() {\ngaugehumData = new google.visualization.DataTable();\ngaugehumData.addColumn('number', '%');\ngaugehumData.addRows(1);\ngaugehumData.setCell(0, 0, hum);\ngaugehum = new google.visualization.Gauge(document.getElementById('gaugehum_div'));\ngaugehum.draw(gaugehumData, gaugehumOptions);\n}\n");
    sResponse += F("function drawgaugedist() {\ngaugedistData = new google.visualization.DataTable();\ngaugedistData.addColumn('number', '%');\ngaugedistData.addRows(1);\ngaugedistData.setCell(0, 0, dist);\ngaugedist = new google.visualization.Gauge(document.getElementById('gaugedist_div'));\ngaugedist.draw(gaugedistData, gaugedistOptions);\n}\n");
    sResponse += F("</script>\n</head>\n<body>\n<font color=\"#000000\"><body bgcolor=\"#d0d0f0\"><meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0, user-scalable=yes\"><h1>Zisternen F&uuml;llstandsanzeige, Temperatur- und Feuchtigkeitslogger</h1>ESP8266 mit Ultraschall Sensor und DHT 22 <BR><BR><FONT SIZE=+1>Letzte Messung um ");
    sResponse += epoch_to_string(pulTime[iIndex]).c_str();
    sResponse += F(" UTC<BR>\n<div id=\"gaugedist_div\" style=\"float:left; width:160px; height: 160px;\"></div>\n<div id=\"gaugetemp_div\" style=\"float:left; width:160px; height: 160px;\"></div> \n<div id=\"gaugehum_div\" style=\"float:left; width:160px; height: 160px;\"></div>\n<div style=\"clear:both;\"></div>");
    
    sResponse2 = F("<p>Status Energieversorgung: <BR>");
    sResponse2 += stStatus;
    sResponse2 += F("<BR> <BR> F&uuml;llstand-, Temperatur- & Feuchtigkeitsverlauf - Seiten laden l&auml;nger:<BR>  <a href=\"/grafik\">Grafik</a>   <a href=\"/tabelle\">Tabelle</a>  <a href=\"/solar\">Solar</a>  <a href=\"/download\">Download Messerte</a></p>");
    sResponse2 += MakeHTTPFooter().c_str();
    
    // Send the response to the client 
    client.print(MakeHTTPHeader(sResponse.length()+sResponse2.length()).c_str());
    client.print(sResponse);
    client.print(sResponse2);
  }
  else if(sPath=="/tabelle")
  ////////////////////////////////////
  // format the html page for /tabelle
  ////////////////////////////////////
  {
    ulReqcount++;
    unsigned long ulSizeList = MakeTable(&client,false); // get size of table first
    
    sResponse  = F("<html><head><title>Zisternen F&uuml;llstandsanzeige, Temperatur- und Feuchtigkeitslogger</title></head><body>");
    sResponse += F("<font color=\"#000000\"><body bgcolor=\"#d0d0f0\">");
    sResponse += F("<meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0, user-scalable=yes\">");
    sResponse += F("<h1>Zisternen F&uuml;llstandsanzeige, Temperatur- und Feuchtigkeitslogger</h1>");
    sResponse += F("<FONT SIZE=+1>");
    sResponse += F("<a href=\"/\">Startseite</a><BR><BR>Letzte Messungen im Abstand von ");
    sResponse += ulMeasDelta_ms;
    sResponse += F("ms<BR>");
    // here the big table will follow later - but let us prepare the end first
      
    // part 2 of response - after the big table
    sResponse2 = MakeHTTPFooter().c_str();
    
    // Send the response to the client - delete strings after use to keep mem low
    client.print(MakeHTTPHeader(sResponse.length()+sResponse2.length()+ulSizeList).c_str()); 
    client.print(sResponse); sResponse="";
    MakeTable(&client,true);
    client.print(sResponse2);
  }
  else if(sPath=="/grafik")
  ///////////////////////////////////
  // format the html page for /grafik
  ///////////////////////////////////
  {
    ulReqcount++;
    unsigned long ulSizeList = MakeList(&client,false); // get size of list first

    sResponse  = F("<html>\n<head>\n<title>Zisternen F&uuml;llstandsanzeige, Temperatur- und Feuchtigkeitslogger</title>\n<script type=\"text/javascript\" src=\"https://www.google.com/jsapi?autoload={'modules':[{'name':'visualization','version':'1','packages':['corechart']}]}\"></script>\n");
    sResponse += F("<script type=\"text/javascript\"> google.setOnLoadCallback(drawChart);\nfunction drawChart() {var data = google.visualization.arrayToDataTable([\n['Zeit / UTC', 'Temperatur', 'Feuchtigkeit', 'Fuellstand'],\n");    
    // here the big list will follow later - but let us prepare the end first
      
    // part 2 of response - after the big list
    sResponse2  = F("]);\nvar options = {title: 'Verlauf',vAxes:{0:{viewWindowMode:'explicit',gridlines:{color:'black'},format:\"##.##\260C\"},1: {gridlines:{color:'transparent'},format:\"##,##%\"},},series:{0:{targetAxisIndex:0},1:{targetAxisIndex:1},2:{targetAxisIndex:1},},curveType:'none',legend:{ position: 'bottom'}};");
    sResponse2 += F("var chart = new google.visualization.LineChart(document.getElementById('curve_chart'));chart.draw(data, options);}\n</script>\n</head>\n");
    sResponse2 += F("<body>\n<font color=\"#000000\"><body bgcolor=\"#d0d0f0\"><meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0, user-scalable=yes\"><h1>Zisternen F&uuml;llstandsanzeige, Temperatur- und Feuchtigkeitslogger</h1><a href=\"/\">Startseite</a><BR>");
    sResponse2 += F("<BR>\n<div id=\"curve_chart\" style=\"width: 600px; height: 400px\"></div>");
    sResponse2 += MakeHTTPFooter().c_str();
    
    // Send the response to the client - delete strings after use to keep mem low
    client.print(MakeHTTPHeader(sResponse.length()+sResponse2.length()+ulSizeList).c_str()); 
    client.print(sResponse); sResponse="";
    MakeList(&client,true);
    client.print(sResponse2);
  }


  ///////////////////////////////////
  // format the html page for /Solar
  ///////////////////////////////////

  else if(sPath=="/solar")
  {
    ulReqcount++;
    sResponse  = F("<html><head><title>Zisternen F&uuml;llstandsanzeige, Temperatur- und Feuchtigkeitslogger</title></head><body>");
    sResponse += F("<font color=\"#000000\"><body bgcolor=\"#d0d0f0\">");
    sResponse += F("<meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0, user-scalable=yes\">");
    sResponse += F("<h1>Zisternen F&uuml;llstandsanzeige, Temperatur- und Feuchtigkeitslogger</h1>");
    sResponse += F("<FONT SIZE=+1>");
    sResponse += F("<a href=\"/\">Startseite</a><BR><BR>Letzte Messungen im Abstand von ");
    sResponse += ulMeasDelta_ms;
    sResponse += F("ms<BR>");


    sResponse2 = MakeHTTPFooter().c_str();
    
    // Send the response to the client - delete strings after use to keep mem low
    client.print(MakeHTTPHeader(sResponse.length()+sResponse2.length())); 
    client.print(sResponse); sResponse="";
    client.print(sResponse2);                
  }




  ///////////////////////////////////
  // format the html page for /download
  ///////////////////////////////////

  else if(sPath=="/download")
  {
    char tBuf[65];
    int clientCount = 0;
    ulReqcount++;
    File LogFile = SD.open("LogFile.csv");        //Öffnet Datei

    //Sendet Informationen zum Downlaod der Datei an den Browser
    client.println("HTTP/1.1 200 OK");
    client.println("Content-type: application/octet-stream");
    client.println("Content-disposition: attachment; filename=LogFile.csv");  //setz an den Dateinamen Das Datum un die Uhr zeit des Downloads
    client.println("Content-Length: " + String(LogFile.size()) + "\r\n");
    //client.println("Connection: keep-alive");
    //client.println();
    //Kümmert sich um das Versenden der Daten an den Browser, es werde immer 64 Byte auf einmal versendet
    if (LogFile)
    {
        while(LogFile.available()) 
        {
          clientCount = LogFile.read(tBuf,64);
          client.write((byte*)tBuf,clientCount);
         }
     LogFile.close();
     Serial.println("Datei wurde erfogreich übertragen");
     }
          
    else
    {
      Serial.println("Datei konnte nicht gefunden werden");
    }              
  }

  else
  ////////////////////////////
  // 404 for non-matching path
  ////////////////////////////
  {
    sResponse="<html><head><title>404 Not Found</title></head><body><h1>Not Found</h1><p>The requested URL was not found on this server.</p></body></html>";
    
    sHeader  = F("HTTP/1.1 404 Not found\r\nContent-Length: ");
    sHeader += sResponse.length();
    sHeader += F("\r\nContent-Type: text/html\r\nConnection: close\r\n\r\n");
    
    // Send the response to the client
    client.print(sHeader);
    client.print(sResponse);
  }
  
  // and stop the client
  client.stop();
  Serial.println("Client disconnected");
}

