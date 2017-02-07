//DS18B20 - Sketch B
//github.com/nlpke/DS18B20-Arduino-Tutorial

#include <OneWire.h>
#include <DallasTemperature.h>

#define ANSCHLUSS 9

//OneWire Schnittstelle 
OneWire ds18b20_wire(ANSCHLUSS);

//Sensor
DallasTemperature ds18b20(&ds18b20_wire);

long temp ;
int intervall_laenge = 30; //Ein Intervall dauert intervall_laenge * 2 Sekunden, also in diesem Fall 1 Min.

//Variablen für die Durchschnittsberechnung über die gesamte Zeit
int counter = 0;
long durchschnitt = 0;
long gesamt = 0;
int steigung = 0;

//Variablen für die Durchschnittsberechnung über ein Intervall
int intervall_counter = 0;
long intervall_durchschnitt = 0;
long intervall_gesamt = 0;


void setup() {
 Serial.begin(9600);

 //Sensor initialisieren
 ds18b20.begin();
 //Genauigkeit einstellen
 ds18b20.setResolution(TEMP_12_BIT);
 
 Serial.println("Bereit");

}



void loop() {


  //Temperatur auslesen und in Variable einspeichern
  ds18b20.requestTemperatures();
  temp = ds18b20.getTempCByIndex(0);
  //Temperatur ausgeben
  Serial.println("Temperatur: ");
  Serial.print(ds18b20.getTempCByIndex(0));
  Serial.print (" C");
  Serial.println();
  //Durchschnitt gesamt berechnen
  counter++;
  gesamt = gesamt + temp;
  durchschnitt = gesamt / counter;
  //Durchschnitt im Intervall berechnen 
  // ! ALLE DURSCHNITTSANGABEN SIND GANZZAHLIG !
  intervall_counter++;
  intervall_gesamt = intervall_gesamt + temp;
  intervall_durchschnitt = intervall_gesamt / intervall_counter;
  //Die Intervall_laenge wird oben weiter definiert
  if (counter % intervall_laenge == 0){ //Wenn sich der Counter durch die Intervall-Länge ohne Rest teilen lässt, dann ist das Intervall beendet.   
    Serial.println("================");
    Serial.println("Durchschnitt aller bisherigen Messwerte: " + String(durchschnitt));
    Serial.println("Durchschnitt im Messintervall (" + String(intervall_counter * 2) + " Sekunden):" + intervall_durchschnitt);
    Serial.println("================"); 
    //Intervall Variablen zurücksetzen
    intervall_counter = 0;
    intervall_gesamt = 0;
    intervall_durchschnitt = 0;
  }
  delay(2000);
}
