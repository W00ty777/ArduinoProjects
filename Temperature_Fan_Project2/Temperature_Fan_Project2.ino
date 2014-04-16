/*
In this project we have modified the original temperature sketch
to include:
Print temperature on screen
Turn on Fan when temp above 75 
But we have smoothed out the spikes in temp to take an avaerage 
of 4 temperatures to prevent the fan from turning on and off 
serveral times when the temperature is near the threshold.
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
int fan = 10;
float f;
float f1=0;
float f2=0;
float f3=0;
float f4=0;

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
}

void loop()
{
  int value = analogRead(inPin);
  float millivolts = (value / 1024.0) * 5000;
  float celsius = millivolts / 10;  // sensor output is 10mV per degree Celsius
  float ferinheight = (celsius * 9)/ 5 + 32; //  converts to fahrenheit
  lcd.setCursor(5,1); //sets cursor
  lcd.print(celsius);// prints temperature
  lcd.printByte(223);//degrees symbol
  lcd.print("C");
  delay(5000); // wait for 5 second
  lcd.setCursor(5,1);
  lcd.print(ferinheight);// prints temperature
  lcd.printByte(223);//degrees symbol
  lcd.print("F");
  f4=f3;
  f3=f2;
  f2=f1;
  f1=ferinheight;
  f=(f1+f2+f3+f4)/4;
  Serial.print("F1 ");
  Serial.println(f1);
  Serial.print("F2 ");  
  Serial.println(f2);
  Serial.print("F3 ");
  Serial.println(f3);
  Serial.print("F4 ");
  Serial.println(f4);
  Serial.print("Avg ");
  Serial.println(f);
  Serial.println();
  if(f > 75){
    digitalWrite(fan, HIGH);
  }else{
    digitalWrite(fan, LOW);
  }
  delay(5000); // wait for 5 seconds
  lcd.setCursor(5,1); //sets curso
  lcd.print(celsius);// prints temperature
  lcd.printByte(223);//degrees symbol
  lcd.print("C");
  delay(5000); // wait for 5 second
  lcd.setCursor(5,1);
  lcd.print(ferinheight);// prints temperature
  lcd.printByte(223);//degrees symbol
  lcd.print("F");
  delay(5000); // wait for 5 second
}


