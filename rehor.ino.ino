#define I2C_SDA A4
#define I2C_SCL A5
#include "LiquidCrystal_I2C.h"


LiquidCrystal_I2C lcd(0x27, 16, 2);

const byte tlacitka[] = {3,2,5,4};
bool stisk_1 = 0;
bool stisk_2 = 0;
bool stisk_3 = 0;
bool stisk_4 = 0;
int tlac = 0;

int vlhkost = 0;
int cilova = 0;

int cil_f = 0;

const byte Rele = 6;

void zobraz() {
  lcd.clear();
  lcd.setCursor(0, 0);
  vlhkost = analogRead(A0);
  lcd.print("Humidity: " + (String) vlhkost);
  lcd.setCursor(0, 1);
  lcd.print("Desired: " + (String) cilova);
}

void zobraz_f() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Frequency: " + (String) cil_f);
  lcd.setCursor(0, 1);
  lcd.print("Jeee jeee je");
}

// Lze pouzit i misto funkci nahore
void napis_radek(byte cislo_radku, String text, bool clear) {
  if (clear) {
    lcd.clear();}
  lcd.setCursor(0, cislo_radku);
  lcd.print(text);
}

void setup() {
  Serial.begin(9600);
  lcd.begin();
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Rehor sees you");
  delay(3000);
  Serial.println("");
  Serial.println("NOVÉ TESTOVÁNÍ");
  for(int x=0; x<4; x++)
  {
    pinMode(tlacitka[x], INPUT_PULLUP);
  }

  //pinMode(Rele, OUTPUT);

  zobraz();

  //stisk_2 = digitalRead(tlacitka[1]);
  //stisk_3 = digitalRead(tlacitka[2]);
  stisk_4 = digitalRead(tlacitka[3]);

  while (stisk_4 == HIGH) {

    stisk_2 = digitalRead(tlacitka[1]);
    stisk_3 = digitalRead(tlacitka[2]);
    stisk_4 = digitalRead(tlacitka[3]);

    if (stisk_2 == LOW && cilova >= 5) {
      cilova = cilova - 5;
      delay(500);
      zobraz();
      //stisk_2 = digitalRead(tlacitka[1]);
    }

    else if (stisk_3 == LOW && cilova <= 95) {
      cilova = cilova + 5;
      delay(500);
      zobraz();
      //stisk_3 = digitalRead(tlacitka[2]);
    }

  }
  
  napis_radek(0, "Jsi mimo", true);
  napis_radek(1, "Pust to", false);
  delay(2000);

  zobraz_f();

  stisk_4 = digitalRead(tlacitka[3]);

  while (stisk_4 == HIGH) {

    stisk_2 = digitalRead(tlacitka[1]);
    stisk_3 = digitalRead(tlacitka[2]);
    stisk_4 = digitalRead(tlacitka[3]);

    if (stisk_2 == LOW && cil_f >= 1) {
      cil_f = cil_f - 1;
      delay(500);
      zobraz_f();
      //stisk_2 = digitalRead(tlacitka[1]);
    }

    else if (stisk_3 == LOW && cil_f <= 59) {
      cil_f = cil_f + 1;
      delay(500);
      zobraz_f();
      //stisk_3 = digitalRead(tlacitka[2]);
    }

  }

}

void loop() {
  Serial.println("ahoj");
  delay(60000);
}
