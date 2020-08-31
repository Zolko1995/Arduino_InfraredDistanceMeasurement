#include <SharpIR.h> //A SHARP 2Y0A21 szenzor használatához szükséges könyvtár beillesztése
#include<Wire.h> //Wire könyvtár beillesztése az I2C busz használatához
#include<LiquidCrystal_I2C.h> //Az I2C Folyékony kristályos LCD kijelző kezelő könyvtára
LiquidCrystal_I2C lcd(0x27, 16, 2); //Az általunk használt kijelző karakterkészlete 16 karakter és 2 sor

#define IR A0 //A szenzor adat pinjének a definiálása
#define model 1080 //Pontos típus beállítása

SharpIR SharpIR(IR, model); //A könytárból használt objektum

void setup()
{
  lcd.init(); //Az LCD kijelző inicializálása
  lcd.backlight(); //Az LCD kijelző háttérvilágításának bekapcsolása
  Serial.begin(9600); //A soros porton történő kommunikáció bitrátája
}

void loop() //ciklus
{
  delay(500);
  lcd.clear(); //Az LCD kijelző tartalmának a törlése
  lcd.setCursor(0, 0); //Kurzor pozicionálás ez esetben 0. karakter az 0. sorban
  lcd.print("A TAVOLSAG:"); //Megadott karakterlánc kiíratása
  unsigned long kezdet = millis(); // 32 bites változó deklarálása a kezdettől számított idő tárolására
  int tav = SharpIR.distance(); // this returns the distance to the object you're measuring
  lcd.setCursor(12, 0); //Kurzor pozicionálás ez esetben 12. karakter az 0. sorban
  lcd.print(tav); //A távolság értékenek kiíratása
  lcd.setCursor(14, 0); //Kurzor pozicionálás ez esetben 14. karakter az 0. sorban
  lcd.print("CM"); //Megadott karakterlánc kiíratása
  Serial.print("Tavolsag: "); //Megadott karakterlánc kiíratása a soros portra
  Serial.println(tav); //A távolság értékenek kiíratása a soros portra
  Serial.println(analogRead(A0)); //A szenzorból kapott nem átalakított jel kiíratása a soros portra
  unsigned long veg = millis() - kezdet; //32 bites változó deklarálása a vegző időpont tárolására
  Serial.print("Eltelt ido (ms): "); //Megadott karakterlánc kiíratása a soros portra
  Serial.println(veg); //A távolság értékenek kiíratása a soros portra
}
