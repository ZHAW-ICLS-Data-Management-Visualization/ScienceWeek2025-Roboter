#include <Servo.h> // Bibliothek für die Steuerung von Servomotoren einbinden

Servo servoFuss; // Erstes Servo-Objekt erstellen
Servo servoBox; // Zweites Servo-Objekt erstellen

const int potiPin1 = A0; // Pin für das erste Potentiometer festlegen
const int potiPin2 = A1; // Pin für das zweite Potentiometer festlegen
const int servoFussPin = 4; // Pin für das erste Servo festlegen
const int servoBoxPin = 6; // Pin für das zweite Servo festlegen

const int delta = 2; // Schwelle, ab wann sich das Servo bewegen soll

int letzterWinkel1 = 90; // Startwinkel für das erste Servo
int letzterWinkel2 = 90; // Startwinkel für das zweite Servo

void setup() {
  Serial.begin(9600); // Serielle Verbindung starten (für Ausgaben am PC)
  servoFuss.attach(servoFussPin); // Erstes Servo mit Pin verbinden
  servoBox.attach(servoBoxPin); // Zweites Servo mit Pin verbinden
  servoFuss.write(letzterWinkel1); // Erstes Servo auf Startwinkel setzen
  servoBox.write(letzterWinkel2); // Zweites Servo auf Startwinkel setzen
}

void loop() {
  int potiWert1 = analogRead(potiPin1); // Wert vom ersten Potentiometer auslesen
  int potiWert2 = analogRead(potiPin2); // Wert vom zweiten Potentiometer auslesen

  int winkel1 = map(potiWert1, 0, 1023, 0, 180); // Wert in Winkel für servoFuss umrechnen
  int winkel2 = map(potiWert2, 0, 1023, 0, 180); // Wert in Winkel für servoBox umrechnen

  // servoFuss nur bewegen, wenn sich der Winkel genug geändert hat
  if (abs(winkel1 - letzterWinkel1) > delta) {
    servoFuss.write(winkel1); // Neues Winkel an servoFuss senden
    letzterWinkel1 = winkel1; // Winkel merken
  }

  // servoBox nur bewegen, wenn sich der Winkel genug geändert hat
  if (abs(winkel2 - letzterWinkel2) > delta) {
    servoBox.write(winkel2); // Neues Winkel an servoBox senden
    letzterWinkel2 = winkel2; // Winkel merken
  }

  // Werte auf dem Computer anzeigen
  Serial.print("Poti1: "); // Text ausgeben
  Serial.print(potiWert1); // Wert vom ersten Potentiometer ausgeben
  Serial.print(" -> Winkel1: "); // Text ausgeben
  Serial.print(winkel1); // Winkel vom Servo Fuss ausgeben
  Serial.print(" | Poti2: "); // Text ausgeben
  Serial.print(potiWert2); // Wert vom zweiten Potentiometer ausgeben
  Serial.print(" -> Winkel2: "); // Text ausgeben
  Serial.println(winkel2); // Winkel vom Servo Box ausgeben und Zeile beenden

  delay(100); // 0,1 Sekunden warten, bevor alles wiederholt wird
}
