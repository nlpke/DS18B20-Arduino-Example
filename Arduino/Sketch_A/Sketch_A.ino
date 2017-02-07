//DS18B20 - Sketch A
//github.com/nlpke/DS18B20-Arduino-Tutorial


//Benötigte Bibliotheken importieren
#include <OneWire.h>
#include <DallasTemperature.h>

//OneWire Schnittstelle auf PIN9
OneWire schnittstelle(9);

//Temperatursensor an der Onewire Schnittstelle
DallasTemperature sensor(&schnittstelle);

//Anzahl der Sekunden ab Start des Programmes
int sekunden = 0;

void setup() {
  Serial.begin(9600);

  //Sensor initialisieren
  sensor.begin();
  //Genauigkeit einstellen
  sensor.setResolution(TEMP_12_BIT);

  Serial.println("BEREIT");
}

void loop() {
 //Temperaturwerte auslesen
 sensor.requestTemperatures();

 //Zeit Temperatur ausgeben

 Serial.print(sekunden);
 Serial.print(" ");
 Serial.print(sensor.getTempCByIndex(0));

 
 Serial.println();

 //2 Sek. warten
 sekunden = sekunden + 2;
 delay(2000);

 //Die ausgegebenen Informationen lassen sich in eine Tabellenkalkulation importieren
 //Um dann daraus Diagramme zu zeichnen.

}
