#include "LiquidCrystal_I2C.h"

#define I2C_SDA A4
#define I2C_SCL A5

LiquidCrystal_I2C lcd(0x27, 16, 2);

void napis_radek(byte cislo_radku, String text, bool clear) {
  if (clear) {
    lcd.clear();
  }
  lcd.setCursor(0, cislo_radku);
  lcd.print(text);
}

void setup() {
  Serial.begin(9600);
  lcd.begin();
}

void loop() {
  napis_radek(0, "TEST 1", true);
  delay(1000);
  napis_radek(1, "TEST 2", false);
  delay(1000);
  napis_radek(0, "TEST 3", true);
  delay(1000);
  napis_radek(1, "TEST 4", false);
  delay(1000);
}
