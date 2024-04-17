#include <SD.h>

#define SD_CS 4

String s = "";
int vlhkost = 0;
unsigned long cas = 0;

void setup() {
  Serial.begin(9600);
  pinMode(LED_BUILTIN, OUTPUT);

  while (!SD.begin(SD_CS)) {
    Serial.println("SD karta neni pripojena nebo je vadna!");
    Serial.println("...");
  }

  File sd = SD.open("venku.txt", FILE_WRITE);
  while (!sd) sd = SD.open("venku.txt", FILE_WRITE);
  sd.println("Novy experiment zacal.\nData:");
  sd.close();
  Serial.println("Zapis na kartu uspesny.");
}

void loop() {
  vlhkost = analogRead(A0);
  cas = millis();
  s = (String) cas + "\t" + (String) vlhkost;
  Serial.println(s);
  File sd = SD.open("venku.txt", FILE_WRITE);

  if (sd) {
    sd.println(s);
    sd.close();
    Serial.println("Zapis na kartu uspesny.");
    digitalWrite(LED_BUILTIN, HIGH);
    delay(500);
    digitalWrite(LED_BUILTIN, LOW);
  }
  else {
    Serial.println("Chyba pri otevreni souboru!");
  }

  delay(300000);
}
