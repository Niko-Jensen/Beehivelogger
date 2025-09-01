#include <DHT.h>
#include <SD.h>
#include <SPI.h>
#include <RTClib.h>


#define DHTPIN_INSIDE 6   
#define DHTPIN_OUTSIDE 7  
#define DHTTYPE DHT22     
#define LIGHTPIN A0       
#define SDPIN 53          


DHT dhtInside(DHTPIN_INSIDE, DHTTYPE);
DHT dhtOutside(DHTPIN_OUTSIDE, DHTTYPE);
RTC_DS3231 rtc;


File dataFile;
const unsigned long interval = 600000; 
unsigned long previousMillis = 0;


void setup() {
  Serial.begin(9600);
  dhtInside.begin();
  dhtOutside.begin();


  if (!rtc.begin()) {
    Serial.println("RTC fejl. Kontroller forbindelser eller batteri.");
    while (1);
  }


  if (!SD.begin(SDPIN)) {
    Serial.println("SD-kort fejl. Kontroller forbindelser.");
    while (1);
  }


  dataFile = SD.open("data.csv", FILE_WRITE);
  if (!dataFile) {
    Serial.println("Kunne ikke oprette CSV-fil. Tjek SD-kortet.");
  } else {
    Serial.println("CSV-fil oprettet korrekt.");
    dataFile.println("Dato,Tid,Sensor,Temp. (C),Fugtighed (%),Lysniveau");
    dataFile.close();
  }
}


void loop() {
  if (millis() - previousMillis >= interval) {
    previousMillis = millis();


    float tempInside = dhtInside.readTemperature();
    float humidityInside = dhtInside.readHumidity();
   
    if (isnan(tempInside) || isnan(humidityInside)) {
      Serial.println("Fejl med DHT sensor Inside.");
    }


    float tempOutside = dhtOutside.readTemperature();
    float humidityOutside = dhtOutside.readHumidity();
   
    if (isnan(tempOutside) || isnan(humidityOutside)) {
      Serial.println("Fejl med DHT sensor Outside.");
    }


    int lightLevel = analogRead(LIGHTPIN);


    DateTime now = rtc.now();


    String insideData = String(now.year()) + "-" + String(now.month()) + "-" + String(now.day()) + "," +
                        String(now.hour()) + ":" + String(now.minute()) + ":" + String(now.second()) + "," +
                        "Inside," +
                        String(tempInside, 1) + "," + String(humidityInside, 1) + ",NA";


    String outsideData = String(now.year()) + "-" + String(now.month()) + "-" + String(now.day()) + "," +
                         String(now.hour()) + ":" + String(now.minute()) + ":" + String(now.second()) + "," +
                         "Outside," +
                         String(tempOutside, 1) + "," + String(humidityOutside, 1) + "," +
                         String(lightLevel);


    Serial.println(insideData);
    Serial.println(outsideData);


    dataFile = SD.open("data.csv", FILE_WRITE);
    if (dataFile) {
      dataFile.println(insideData);
      dataFile.println(outsideData);
      dataFile.close();
    } else {
      Serial.println("Kunne ikke skrive til SD-kort.");
    }
  }
}


Denne del af koden er til personlig brug skal ikke med som bilag, da vi kun skal kigge på den.
MIS - MIS - MIS - MIS - MIS - MIS - MIS - MIS - MIS - MIS - MIS - MIS.


#include <DHT.h>
#include <SD.h>
#include <SPI.h>
#include <RTClib.h>


// Pin Definitioner
#define DHTPIN_INSIDE 6   // DHT sensor indenfor bistade
#define DHTPIN_OUTSIDE 7  // DHT sensor udenfor bistade
#define DHTTYPE DHT22     // DHT22 sensor type
#define LIGHTPIN A0       // Lyssensor udenfor bistade
#define SDPIN 53          // SD kort


DHT dhtInside(DHTPIN_INSIDE, DHTTYPE);
DHT dhtOutside(DHTPIN_OUTSIDE, DHTTYPE);
RTC_DS3231 rtc;
File dataFile;
const unsigned long interval = 600000; // 6000 er det samme som = 6 sekunder som bruges til testning, ændres til 600000 som er 10 minutter
unsigned long previousMillis = 0;


void setup() {
  Serial.begin(9600);
  dhtInside.begin();
  dhtOutside.begin();


  if (!rtc.begin()) {
    Serial.println("RTC fejl. Kontroller forbindelser eller batteri.");
    while (1);
  }


  if (!SD.begin(SDPIN)) {
    Serial.println("SD-kort fejl. Kontroller forbindelser.");
    while (1);
  }


  // Prøver at lave CSV fil, hvis den ikke findes allerede
  dataFile = SD.open("data.csv", FILE_WRITE);
  if (!dataFile) {
    Serial.println("Kunne ikke oprette CSV-fil. Tjek SD-kortet.");
  } else {
    Serial.println("CSV-fil oprettet korrekt.");
    dataFile.println("Dato,Tid,Sensor,Temp. (C),Fugtighed (%),Lysniveau");
    dataFile.close();
  }
}


void loop() {
  if (millis() - previousMillis >= interval) {
    previousMillis = millis();




    // Indenfor bistade data læsninger
    float tempInside = dhtInside.readTemperature();
    float humidityInside = dhtInside.readHumidity();
   
    // Check om læsninger kan valideres
    if (isnan(tempInside) || isnan(humidityInside)) {
      Serial.println("Fejl med DHT sensor Inside.");
    }


    // udenfor bistade data læsninger
    float tempOutside = dhtOutside.readTemperature();
    float humidityOutside = dhtOutside.readHumidity();
   
    // Check om læsninger kan valideres
    if (isnan(tempOutside) || isnan(humidityOutside)) {
      Serial.println("Fejl med DHT sensor Outside.");
    }


    // Lys Niveau
    int lightLevel = analogRead(LIGHTPIN);


    // Få den nuværende tid fra RTC
    DateTime now = rtc.now();


    // Idenfor data string
    String insideData = String(now.year()) + "-" + String(now.month()) + "-" + String(now.day()) + "," +
                        String(now.hour()) + ":" + String(now.minute()) + ":" + String(now.second()) + "," +
                        "Inside," +
                        String(tempInside, 1) + "," + String(humidityInside, 1) + ",NA";


    // udenfor data string
    String outsideData = String(now.year()) + "-" + String(now.month()) + "-" + String(now.day()) + "," +
                         String(now.hour()) + ":" + String(now.minute()) + ":" + String(now.second()) + "," +
                         "Outside," +
                         String(tempOutside, 1) + "," + String(humidityOutside, 1) + "," +
                         String(lightLevel);


    // Print til Serial Monitor
    Serial.println(insideData);
    Serial.println(outsideData);


    // Gem data til SD kort
    dataFile = SD.open("data.csv", FILE_WRITE);
    if (dataFile) {
      dataFile.println(insideData);
      dataFile.println(outsideData);
      dataFile.close();
    } else {
      Serial.println("Kunne ikke skrive til SD-kort.");
    }
  }
}

