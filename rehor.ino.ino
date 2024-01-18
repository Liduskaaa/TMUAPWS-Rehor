#define I2C_SDA A4
#define I2C_SCL A5
#include "LiquidCrystal_I2C.h"

LiquidCrystal_I2C lcd(0x27, 16, 2);

// Vsechna cisla, ktera nabyvaji jen malych hodnot, mohou byt byty.
const byte tlacitka[] = {3,2,5,4};
int stisk_1 = 0;
int stisk_2 = 0;
int stisk_3 = 0;
int vlhkost = 0;
int tlac = 0;
int cilova = 0;
int frek = 0;
const byte Rele = 6;

void setup() {
  Serial.begin(9600);
  lcd.begin();
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Rehor sees you");
  Serial.println("");
  Serial.println("NOVÉ TESTOVÁNÍ");
  for(int x=0; x<4; x++)
  {
    // zapojení tlačítek jako vstup s pull-up odporem
    pinMode(tlacitka[x], INPUT_PULLUP);
  }

  pinMode(Rele, OUTPUT);
  delay(3000);
  lcd.clear();
}

void loop() {
  vlhkost = analogRead(A0);
  Serial.println("chacha");
  lcd.clear();
  lcd.setCursor(0, 0);

  lcd.print("Hum: " + (String) vlhkost + "/" + (String) cilova);
  lcd.setCursor(0, 1);
  lcd.print("Frequency: ");

  digitalWrite(Rele, LOW);
  delay(2000);
  Serial.println("zapnuto?");
  delay(2000);
  digitalWrite(Rele, HIGH);

  // redundantni mereni
  //vlhkost = analogRead(A0);
  Serial.print("Vlhkost: ");
  Serial.println(vlhkost);
  delay(1000);

  while (stisk_1 == HIGH) {
    stisk_1 = digitalRead(tlacitka[0]);
    stisk_2 = digitalRead(tlacitka[0]);
  }

  if (stisk_1 == LOW) { // vytiskni pres sériovou linku číslo tlačítka a zprávu
    tlac = 1;
    Serial.print(tlac);
    Serial.println(" stisknuto");
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Change humidity:");
    lcd.setCursor(0, 1);
    lcd.print("<   " + (String) cilova + "   >");
    stisk_3 = digitalRead(tlacitka[2]);
    while (stisk_3 == LOW) {
      cilova = cilova - 5;
      delay(500);
      lcd.setCursor(0, 1);
      lcd.print("<   " + (String) cilova + "   >");
      stisk_3 = digitalRead(tlacitka[2]);
    }
    delay(500);
  }
/*
  else if (stisk_2 == LOW) {
    tlac = 2;
    Serial.print(tlac);
    Serial.println(" stisknuto");
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Change freq:");
    lcd.setCursor(0, 1);
    lcd.print("<   " + (String) frek + "   >");
  }*/
}
