#include "LiquidCrystal_I2C.h"
#include <SD.h>
#define I2C_SDA A4
#define I2C_SCL A5
#define SD_CS 7

const int Rele = 9;
const int tlacitka[] = {3,2,5,4};
bool stisk[] = {0, 0, 0, 0};

LiquidCrystal_I2C lcd(0x27, 16, 2);

void cti_stisk(int cislo) {
  stisk[cislo] = digitalRead(tlacitka[cislo]);
}

void setup() {
  Serial.begin(9600);
  pinMode(Rele, OUTPUT);
  digitalWrite(Rele, HIGH);
  lcd.begin();
  lcd.clear();
}

void loop() {
  lcd.clear();
  for(int x=0; x<4; x++)
  {
    pinMode(tlacitka[x], INPUT_PULLUP);
  }

  cti_stisk(0);
  cti_stisk(1);
  cti_stisk(2);
  cti_stisk(3);

  if (stisk[0] == LOW){
    Serial.println("1");
  }

  if (stisk[1] == LOW){
    Serial.println("2");
  }

  if (stisk[2] == LOW){
    Serial.println("3");
  }

  if (stisk[3] == LOW){
    Serial.println("4");
  }

  digitalWrite(Rele, LOW);
  Serial.println("jedu?");
  delay(3000);
  Serial.println("...");
  digitalWrite(Rele, HIGH);
  delay(3000);

  while (!SD.begin(SD_CS)) {
    Serial.println("SD karta neni pripojena nebo je vadna!");
    Serial.println("...");
  }

  File sd = SD.open("data.txt", FILE_WRITE);
  while (!sd) sd = SD.open("data.txt", FILE_WRITE);
  sd.println("Zápis proběhl.");
  sd.close();
  Serial.println("Zapis na kartu uspesny!");

  Serial.println(analogRead(A0));

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("TEST TEST");
  delay(2000);
}
