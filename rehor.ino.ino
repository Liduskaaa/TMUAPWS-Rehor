#define I2C_SDA A4
#define I2C_SCL A5
#include "LiquidCrystal_I2C.h"

LiquidCrystal_I2C lcd(0x27, 16, 2);

const int tlacitka[] = {3,2,5,4};
int stisk = 0;
int vlhkost = 0;
int tlac = 0;
const int Rele = 6;

void setup() {
  Serial.begin(9600);
  Serial.println("");
  Serial.println("NOVÉ TESTOVÁNÍ");
  lcd.begin();
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("aaa");
  for(int x=0; x<4; x++)
  {
    // zapojení tlačítek jako vstup s pull-up odporem
    pinMode(tlacitka[x], INPUT_PULLUP);
  } 

  pinMode(Rele, OUTPUT);
}

void loop() {
  Serial.println("chacha");
  lcd.setCursor(0, 0);
  lcd.print("Joooo :)");

  digitalWrite(Rele, LOW);
  delay(2000);
  Serial.println("zapnuto?");
  delay(2000);
  digitalWrite(Rele, HIGH);

  vlhkost = analogRead(A0);
  Serial.print("Vlhkost: ");
  Serial.println(vlhkost);
  delay(1000);

  for(int x=0; x<4; x++)
  {
    //načtení stavu tlačítka a uložení do proměnné stisk
    stisk = digitalRead(tlacitka[x]);

    // pokud je tlačítko stisknuto
    // vykonej následující
    if (stisk == LOW) {    
      // vytiskni pres sériovou linku číslo tlačítka a zprávu
      tlac = x+1;
      Serial.print(tlac);
      Serial.println(" stisknuto");
      // vyčkej 500 ms kvůli zbytečnému množství tisknutých znaků
      delay(500);
    }
  }
}
