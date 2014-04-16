/*
Print temperature on screen
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
int fan = 13;


void setup()
{
  pinMode(fan, OUTPUT);  
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
  float ferinheight = (celsius * 9)/ 5 + 32; //  converts to fahrenheit
  lcd.setCursor(5,1);
  lcd.print(ferinheight);
  lcd.printByte(223);//degrees symbol
  lcd.print("F");
  delay(5000); // wait for five second
  lcd.setCursor(5,1);
  lcd.print(celsius);
  lcd.printByte(223);//degrees symbol
  lcd.print("C");
  if(ferinheight > 75){
    digitalWrite(fan, HIGH);
  }else{
    digitalWrite(fan, LOW);
  }
  delay(5000); // wait for five second
}


