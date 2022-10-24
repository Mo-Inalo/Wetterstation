#include "DHT.h" //DHT Bibliothek laden
#include "LiquidCrystal.h"





#define DHTPIN 13 //Der Sensor wird an PIN 2 angeschlossen    

#define DHTTYPE DHT22    // Es handelt sich um den DHT11 Sensor

const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
DHT dht(DHTPIN, DHTTYPE); //Der Sensor wird ab jetzt mit „dth“ angesprochen

void setup() {
  Serial.begin(9600); //Serielle Verbindung starten
  Serial.println("DHT22 Programmstart");
  dht.begin(); //DHT11 Sensor starten
  lcd.begin(16, 2);
  lcd.print("Programmstart");
  pinMode( 0 , INPUT); 
  pinMode(7, OUTPUT);
}

void loop() {
  
  // Eine Sekunde Verzögerung zwischen Messungen
  // --> Lesen der Temperatur / Feuchte dauert ca. t = 0,25 Sekunden
  delay(3000);

  // Lesen von Feuchte und Temperatur und Schreiben der Werte in die float-Variablen h und t 
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  int Sensorwert = analogRead(0);
  if ( t > 24 ||h > 61){
    digitalWrite(7,HIGH);
    
    
  }
  // Überprüfung, ob ein Lesevorgang gescheitert ist, evtl. Fehlerausgabe über seriellen Monitor
  if (isnan(h) || isnan(t)) {
    Serial.println(F("Lesevorgang DHT Sensor fehlgeschlagen!"));
    return;
  }

  // Ausgabe der Werte über
  Serial.print(F("Luftfeuchte: "));
  Serial.print(h);
  Serial.print(F("%  Temperatur: "));
  Serial.print(t);
  Serial.print(F("°C ")); // Nach Befehl  Serial.println("XYZ");  wird im seriellen Monitor in nächste Zeile geschrieben
  Serial.print("Der erfasste Wert lautet : "); 
  Serial.println(Sensorwert, DEC); 

  // Cursor des LCDs auf Spalte 0 und Zeile 0 setzen
  // Achtung: Zeile 1 oder Spalte 1 ist die zweite Zeile / Spalte, da bei 0 angefangen wird zu zählen
  // set the cursor to column 0, line 1
  lcd.setCursor(0,0);
  // Schreiben der Luftfeuchte in die erste Zeile des LCDs
  lcd.print("Luftf.: ");
  lcd.print(h);
  lcd.print(" %");
  // Cursor des LCDs auf Spalte 0 und Zeile 1 (also zweite Zeile) setzen
  lcd.setCursor(0, 1);
  // Schreiben der Raumtemperatur in die zweite Zeile des LCDs
  lcd.print("Temp. : ");
  lcd.print(t);
  lcd.print(" \337C"); // Kürzel \337 für das °-Zeichen verwenden
  delay(3000);
  lcd.setCursor(0,0);
  lcd.print("                ");
  lcd.setCursor(0,1);
  lcd.print("                ");

  lcd.setCursor(0, 0);
  // Schreiben der Raumtemperatur in die zweite Zeile des LCDs
  lcd.print("Luftqualitaet : ");
   
  lcd.setCursor(0, 1);
  // Schreiben der Raumtemperatur in die zweite Zeile des LCDs
  lcd.print("Wert:");
  lcd.setCursor(8, 1);
  lcd.print(Sensorwert);
  
}
