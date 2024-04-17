#include "LiquidCrystal_I2C.h"
#include <SD.h>

#define I2C_SDA A4
#define I2C_SCL A5
#define SD_CS 7

String s = "";

const int tlacitka[] = {3,2,5,4};
bool stisk[] = {0, 0, 0, 0};

bool pomoc = false;
int n = 0;

int vlhkost = 0;
int cilova = 5;
int cil_f = 0;  //počet dnů

const int Rele = 9;
const int kolikrat = 144;
unsigned long cas = 0;

LiquidCrystal_I2C lcd(0x27, 16, 2);

void(* resetFunc) (void) = 0;

void reset(){
  cti_stisk(1);
  cti_stisk(3);
  if (stisk[1] == LOW && stisk[3] == LOW) {
    napis_radek(0, "OH NO, RESET!", true);
    delay(1000);
    resetFunc();
  }
}

void cti_stisk(int cislo) {
  stisk[cislo] = digitalRead(tlacitka[cislo]);
}

void cti_vlhkost(){
  vlhkost = analogRead(A0);
  vlhkost = -0.3 * vlhkost + 157.1;
}

void zobraz_hum() {
  napis_radek(0, "Humidity: " + (String) vlhkost + "%", true);
  napis_radek(1, "Desired: " + (String) cilova + "%", false);
}

void zobraz_freq() {
  napis_radek(0, "Set frequency:", true);
  napis_radek(1, "    " + (String) cil_f + " days", false);
}

void napis_radek(byte cislo_radku, String text, bool clear) {
  if (clear) {
    lcd.clear();
  }
  lcd.setCursor(0, cislo_radku);
  lcd.print(text);
}

String pomocnik[] = {
  "At beginning",
  "set 2 things:",
  "1. humidity",
  "2. frequency",
  "< to set lower",
  "> to set higher",
  "OK to confirm",
  "< + OK to reset",
};

void help(){
  cti_stisk(0);
  if (stisk[0] == LOW){
    n = 0;
    napis_radek(0, pomocnik[0], true);
    napis_radek(1, pomocnik[1], false);
    while (stisk[0] == LOW){
      cti_stisk(0);
    }
    while (stisk[0] == HIGH){
      cti_stisk(1);
      cti_stisk(2);
      if (stisk[1] == LOW && n >= 2){
        n = n - 2;
        delay(300);
        napis_radek(0, pomocnik[n], true);
        napis_radek(1, pomocnik[n+1], false);
      }
      else if (stisk[2] == LOW && n <= 5){
        n = n + 2;
        delay(300);
        napis_radek(0, pomocnik[n], true);
        napis_radek(1, pomocnik[n+1], false);
      }
      cti_stisk(0);
    }
    if (cil_f == 0){
      zobraz_hum();
    }

    else {
      zobraz_freq();
    }
    delay(500);
  }
}

void setup() {
  Serial.begin(9600);

  pinMode(Rele, OUTPUT);
  digitalWrite(Rele, HIGH);

  lcd.begin();
  napis_radek(0, "Rehor sees you.", true);
  napis_radek(1, "HELP - press ?", false);
  delay(2000);
  
  while (!SD.begin(SD_CS)) {
    Serial.println("SD karta neni pripojena nebo je vadna!");
  }

  File sd = SD.open("data.txt", FILE_WRITE);
  while (!sd) sd = SD.open("data.txt", FILE_WRITE);
  sd.println("Novy experiment zacal.\nData:");
  sd.close();

  napis_radek(0, "SD card is OK.", true);
  delay(1000);

  for(int x=0; x<4; x++)
  {
    pinMode(tlacitka[x], INPUT_PULLUP);
  }

  cti_vlhkost();
  zobraz_hum();

  cti_stisk(3);

  while (stisk[3] == HIGH) {
    help();
    cti_stisk(1);
    cti_stisk(2);

    if (stisk[1] == LOW && cilova >= 10) {
      cilova = cilova - 5;
      zobraz_hum();
      delay(300);
    }

    else if (stisk[2] == LOW && cilova <= 95) {
      cilova = cilova + 5;
      zobraz_hum();
      delay(300);
    }

    cti_stisk(3);
    reset();
  }
  
  cil_f = 1;
  zobraz_freq();

  delay(2000);

  cti_stisk(3);

  while (stisk[3] == HIGH) {
    help();
    cti_stisk(1);
    cti_stisk(2);

    if (stisk[1] == LOW && cil_f >= 2) {
      cil_f = cil_f - 1;
      delay(300);
      zobraz_freq();
    }

    else if (stisk[2] == LOW && cil_f <= 59) {
      cil_f = cil_f + 1;
      delay(300);
      zobraz_freq();
    }
    cti_stisk(3);
    reset();
  }

  napis_radek(0, "Rest in piece.", true);
  delay(3000);

  reset();
  help();

  napis_radek(0, "  Set values:  ", true);
  napis_radek(1, "  " + (String) cilova + "%  " + (String) cil_f + " days", false);
  delay(1000);
}

void loop() {
  cti_vlhkost();

  while ((vlhkost + 5) < cilova) {
    reset();
    digitalWrite(Rele, LOW);
    delay(4000);
    digitalWrite(Rele, HIGH);
    delay(10000);
    cti_vlhkost();
  }

  for (int i = 0; i < cil_f * kolikrat; i++) {
    cti_vlhkost();
    cas = millis();
    s = (String) cas + "\t" + (String) vlhkost;
    File sd = SD.open("data.txt", FILE_WRITE);

    if (sd) {
      sd.println(s);
      sd.close();
    }

    for (int i = 0; i < 600; i++){
      reset();
      delay(1000);
    }
  }
}
