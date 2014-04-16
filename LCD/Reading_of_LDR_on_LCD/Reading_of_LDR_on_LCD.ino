/*
Reading of LDR on LCD
*/

#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

#if defined(ARDUINO) && ARDUINO >= 100
#define printByte(args)  write(args);
#else
#define printByte(args)  print(args,BYTE);
#endif

LiquidCrystal_I2C lcd(0x27,16,2);  // set the LCD address to 0x27 for a 16 chars and 2 line display
const int inPin = 0;  // sensor connected to this analog pin

void setup()
{
  Serial.begin(9600);
  lcd.init();                      // initialize the lcd 
  lcd.backlight();
  lcd.setCursor(0,0);
  lcd.print(" LDR Number is");
  lcd.setCursor(0,1);
  lcd.print("");
  delay(3000);
}

void loop()
{
  int value = analogRead(inPin);
  lcd.setCursor(5,1);
  lcd.print(inPin);
}
