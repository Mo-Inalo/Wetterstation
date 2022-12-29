
#include "DHT.h"  // importieren der DHT Bibliotheken fuer den Temprature und Luftfeuchtigkeit Sensor
#include "LiquidCrystal_I2C.h" // importieren der LCD Bibliotheken fuer das LCD Display
#include "virtuabotixRTC.h" // importieren der RTC Bibliotheken fuer die Echtzeituhr

#define DHT1PIN 12 // Festlegung pin 12 fuer dht-sensor1 
#define DHT2PIN 13  // Festlegung pin 13 fuer dht-sensor2
#define DHTTYPE DHT22  // Festlegung DHTtyp mit dem wert DHT22

LiquidCrystal_I2C lcd(0x27,16,2); //initialierung eines LCD Variable mit adresse 0X27 und 16 Spalten und 2 Zeilen

DHT dht1(DHT1PIN, DHTTYPE); //Der Sensor wird ab jetzt mit „dth1“ angesprochen
DHT dht2(DHT2PIN, DHTTYPE); //Der Sensor wird ab jetzt mit „dth2“ angesprochen

const int RecordTime = 3;  // Variable zur zaehlung der Sekunden
const int SensorPin = 3;   // Pin 3 als input fuer den Anemometer

int InterruptCounter;  // Variable zur Zaelhung von Pulsen
float windSpeed; // Variable zur Berechnugn von Windgeschwindigkeit

virtuabotixRTC myRTC(9,10,11); //initialierung eines Echtzeituhr mit Pins 9,10 und 11

void clearLcd(); // Deklaration einer Funktion zum Löschen alle Ausgaben auf der LCD
void meassure(); // Deklaraiton einer Funktion zu Messung von Windgeschwindigkeit
 
void setup() {
  
  Serial.begin(9600); // Serielle Verbindung starten
  Serial.println("Wetterstation Programmstart"); // Einamlige Begruessungsnachricht auf dem Seriellen Monitor
  dht1.begin(); // DHT1 Sensor starten
  dht2.begin(); // DHT2 Sensor starten
  lcd.init(); // Initialisieren des LCDs
  lcd.backlight();
  lcd.setCursor(1,0); // Cursor auf der Zweite Spalte der ersten Zeile setzen : Numerierung beginnt mit 0
  lcd.print("Programmstart"); // Ausgabe der Nachricht auf dem LCD
  lcd.setCursor(1,1);  // Cursor auf der Zweite Spalte der zweiten Zeile setzen : Numerierung beginnt mit 0
  lcd.print("Wetterstation");
  delay(2000); // Mit der ausgegeben Nachricht 2 Sekunden warten
  pinMode( 0 , INPUT); // Analog pin 0 als input pin fuer den MQ135 Luftgualitaetssensor definieren
  pinMode(7, OUTPUT); // Pin 7 als output Pin für roter LED
  pinMode(8, OUTPUT);  // Pin 8 als output Pin für gruener LED
}


// Funktion zu Loeschung aller Ausgaben auf dem LCD indem alles mit einer Leertasten eingesetzt wird
void clearLcd (){
  lcd.setCursor(0,0);
  lcd.print("                ");
  lcd.setCursor(0,1);
  lcd.print("                ");   
}


// Funktion zur Ausgabe von der RTC daten auf dem Seriellenmonitor in einem bloch mit Eckigenklammern
void serialTimeDate(uint8_t hour, uint8_t min, uint8_t sec, uint8_t day, uint8_t month, int year){
  char s[50];
  sprintf(s,"%02u/%02u/%04d %02u:%02u:%02u", day, month, year, hour, min, sec); 
  Serial.print("["); 
  Serial.print(s);
  Serial.print("]   "); 
}

// Funktion zur Ausgabe der Daten aus dem DTH22, Mq135 und de Anemometer auf dem Seriellenmonitor in einer Zeile
void serialValues (float temp1, float hum1,float temp2,float hum2,float quali,float wsped ) {
  char t1[20];
  char h1[20];
  char t2[20];
  char h2[20];
  char q[20];
  char windspeed[20];
  float windspeedms = wsped/3.6f;
  char windspeedmschar[20];

  dtostrf (temp1,5,1,t1);
  dtostrf (hum1,5,1,h1);
  dtostrf (temp2,5,1,t2);
  dtostrf (hum2,5,1,h2);
  dtostrf (quali,6,1,q);
  dtostrf (wsped,-6,2,windspeed);
  dtostrf (windspeedms,-6,2,windspeedmschar);

  // Ausgeben der Daten auf dem Seriellen Monitor
  // Daten der dht1
  Serial.print("T1:");
  Serial.print(t1);
  Serial.print(" C    ");
  Serial.print("H1:");
  Serial.print(h1);
  Serial.print(" %    ");
  // Daten der dht2
  Serial.print("T2:");
  Serial.print(t2);
  Serial.print(" C    ");
  Serial.print("H2:");
  Serial.print(h2);
  Serial.print(" %    ");
  // Daten der MQ135
  Serial.print("Luftqualitaet");
  Serial.print(q);
  Serial.print("    ");
  // Daten der Anemometer
  Serial.print("Speed: ");
  Serial.print(windspeed);  
  Serial.print(" km/h    ");
  Serial.print("Speed: ");
  Serial.print((windspeedmschar));  
  Serial.println(" m/s ..");
}

// Funktion zur Ausgabe von der RTC daten auf dem LCD in zwei Zeilen.
void showLcdTimeDate(uint8_t hour, uint8_t min, uint8_t sec, uint8_t day, uint8_t month, int year){
  char s1[20];
  char s2[20];

  sprintf(s1,"%02u/%02u/%04d",day, month, year); 
  sprintf(s2,"%02u:%02u:%02u",hour, min, sec);  
  clearLcd();
  lcd.setCursor(3,0);
  lcd.print(s1); 
  lcd.println("       ");
  lcd.setCursor(4,1);  
  lcd.print(s2);
  lcd.println("        ");
  delay(3000);
  clearLcd();
  
}

// Funktion zur Ausgabe der Daten aus dem DTH22, Mq135 und de Anemometer auf dem LCD auf meheren Phasen/Ausgaben.
void showLcdValues(float temp1, float hum1,float temp2,float hum2,float quali,float wsped)
{
  char t1[20];
  char h1[20];
  char t2[20];
  char h2[20];
  char q[20];
  char windspeed[20];
  float windspeedms = wsped/3.6f;
  char windspeedmschar[20];

  dtostrf (temp1,5,1,t1);
  dtostrf (hum1,5,1,h1);
  dtostrf (temp2,5,1,t2);
  dtostrf (hum2,5,1,h2);
  dtostrf (quali,6,1,q);
  dtostrf (wsped,-6,2,windspeed);
  dtostrf (windspeedms,-6,2,windspeedmschar);

  // 1. Ausgabe
  // Daten der dht1
  lcd.setCursor(0,0);
  lcd.print("T1:");
  lcd.setCursor(4,0);
  lcd.print(t1);
  lcd.setCursor(11,0);
  lcd.print("\337C");
  lcd.setCursor(0, 1);
  lcd.print("H1:");
  lcd.setCursor(4, 1);
  lcd.print(h1);
  lcd.setCursor(12, 1);
  lcd.print("%");
  delay(3000);
  clearLcd();
  // 2. Ausgabe
  // Daten der dht2
  lcd.setCursor(0,0);
  lcd.print("T2:");
  lcd.setCursor(4,0);
  lcd.print(t2);
  lcd.setCursor(11,0);
  lcd.print("\337C");
  lcd.setCursor(0, 1);
  lcd.print("H2:");
  lcd.setCursor(4, 1);
  lcd.print(h2);
  lcd.setCursor(12, 1);
  lcd.print("%"); 
  delay(3000);
  clearLcd();
  // 3. Ausgabe
  // Daten der MQ135
  lcd.setCursor(1, 0);
  lcd.print("Luftqualitaet");
  lcd.setCursor(4, 1);
  lcd.print(q);
  delay(3000);
  clearLcd();
  // 4. Ausgabe
  // Daten der Anemometer
  lcd.setCursor(0, 0);
  lcd.print("Speed:");
  lcd.print(windspeed);  
  lcd.print("km/h");
  lcd.setCursor(0, 1);
  lcd.print("Speed:");
  lcd.print((windspeedmschar));  
  lcd.print("m/s");
}


// Funktion zur Berechnung von Windgeschwindigkeit in dem Pulsen in km/h umgerechnet werden.
void meassure() {
  InterruptCounter = 0;
  attachInterrupt(digitalPinToInterrupt(SensorPin), countup, RISING);
  delay(1000 * RecordTime);
  detachInterrupt(digitalPinToInterrupt(SensorPin));
  windSpeed = (float)InterruptCounter / (float)RecordTime * 2.4;
}

void countup() {
  InterruptCounter++;
} 





void loop() {
  
  // Eine Sekunde Verzögerung zwischen Messungen.
  // Lesen der Temperatur / Feuchte dauert ca. 250 ms Sekunden.
  delay(1000);

  // Aufruf der Funktion zur Berechnung der Windgeschwindigkeit 
  meassure();
  // Lesen von Feuchte und Temperatur und Schreiben der Werte in die float-Variablen temp1, hum1, temp2 und hum2.
  float temp1 = dht1.readTemperature(); 
  float hum1 = dht1.readHumidity();
  float temp2 = dht2.readTemperature();
  float hum2 = dht2.readHumidity();
  // Lesen von Luftqualitaet und Schreiben der Wert in der int Variable quali
  int quali = analogRead(0);


  // Leuchten vom roten LED mit pin 7 beim überschritten kritischer Werte
  if ( (temp1+temp2)/2 > 24 ||(hum1+hum2)/2 > 60){
    digitalWrite(7,HIGH); 
    digitalWrite(8,LOW); 
  } else {
  // Anderfall gruen Leuchten
    digitalWrite(7,LOW);
    digitalWrite(8,HIGH); 
  }
  
  // Überprüfung, ob ein Lesevorgang gescheitert ist, evtl. Fehlerausgabe über seriellen Monitor
  if (isnan(hum1) || isnan(temp1) || isnan(hum2) || isnan(temp2)) {
    Serial.println(F("Lesevorgang DHT Sensor fehlgeschlagen!"));
  }

  // Aktualiserung von Zeitdaten
  myRTC.updateTime();

  // Aufruf von Ausgabefunktionen
  showLcdTimeDate(myRTC.hours, myRTC.minutes, myRTC.seconds,myRTC.dayofmonth, myRTC.month, myRTC.year);
  showLcdValues(temp1, hum1, temp2, hum2, quali, windSpeed);
  serialTimeDate(myRTC.hours, myRTC.minutes, myRTC.seconds,myRTC.dayofmonth, myRTC.month, myRTC.year);
  serialValues(temp1, hum1, temp2, hum2, quali, windSpeed);

   
}
