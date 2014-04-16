byte ledPin = 10;

void setup()
{
}

void fadeLED(){
 for (int brightness = 0; brightness < 255; brightness++) {
   analogWrite(ledPin, brightness);
   delay(10);
 }
 delay(100);
 for (int brightness = 255; brightness >= 0; brightness--) {
    analogWrite(ledPin, brightness);
    delay(10);
 }
}
void loop()
{
  fadeLED();
}
      
    
