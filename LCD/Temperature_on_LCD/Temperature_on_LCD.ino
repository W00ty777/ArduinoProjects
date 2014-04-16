/*
Print temperature on screen

///              ______________                    _ Gnd
///             |              |           LM35 ( |_ A0 
///             |              |                ( |_ 5v
///             |              |
///             |         AREF |--
///             |          GND |--
///             |           13 |--
///           --| IORef     12 |--    
///           --| Reset     11 |--
///           --| 3.3V      10 |--
/// VCC&LM35 X--| 5V         9 |--
///           --| GND        8 |--
///           --| GND          |
///           --| Vin        7 |--
///             |            6 |--
///     LM35 X--| A0         5 |--
///           --| A1         4 |--
///           --| A2         3 |--
///           --| A3         2 |--
///      SDA X--| A4         1 |--
///      SCL X--| A5         0 |--
///             |______________|
///                  
///
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
  lcd.print("Current Temp is:");
  lcd.setCursor(0,1);
  lcd.print("");
  delay(3000);
}

void loop()
{
  int value = analogRead(inPin);
  float millivolts = (value / 1024.0) * 5000;
  float celsius = millivolts / 10;  // sensor output is 10mV per degree Celsius
  float fahrenheit = (celsius * 9)/ 5 + 32; //  converts to fahrenheit
  lcd.setCursor(5,1);
  lcd.print(fahrenheit);
  lcd.printByte(223);//degrees symbol
  lcd.print("F");
  delay(5000); // wait for five second
  lcd.setCursor(5,1);
  lcd.print(celsius);
  lcd.printByte(223);//degrees symbol
  lcd.print("C");
  delay(5000); // wait for five second
}
