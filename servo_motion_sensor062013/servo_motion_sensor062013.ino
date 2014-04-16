/* ir-distance sketch
 * prints distance and changes LED flash rate based on distance from IR sensor
 */
#include <Servo.h>

Servo myservo;  // create servo object to control a servo
const int ledPin    = 13; // the pin connected to the LED to flash
int pwr = 10;
const int sensorPin = 0;  // the analog pin connected to the sensor
const long referenceMv = 5000; // long int to prevent overflow when multiplied
const int TABLE_ENTRIES = 12;
const int firstElement = 250; // first entry is 250 mV
const int INTERVAL  = 250; // millivolts between each element
static int distance[TABLE_ENTRIES] = {150,140,130,100,60,50,40,35,30,25,20,15};

int getDistance(int mV)
{
   if( mV >  INTERVAL * TABLE_ENTRIES-1 )
      return distance[TABLE_ENTRIES-1];
   else
   {
      int index = mV / INTERVAL;
      float frac = (mV % 250) / (float)INTERVAL;
      return distance[index] - ((distance[index] - distance[index+1]) * frac);
   }
}

void setup()
{
  Serial.begin(9600);
  pinMode(ledPin, OUTPUT);
  myservo.attach(9);  // attaches the servo on pin 9 to the servo object
}

void loop()
{
  int val = analogRead(sensorPin);
  int mV = (val * referenceMv) / 1023;
  Serial.print(mV);
  Serial.print(",");
  int cm = getDistance(mV);
  Serial.println(cm);
  val = cm  ;
  val = map(val, 0, 1023, 0, 90);     // scale it to use it with the servo
  
  digitalWrite(ledPin, HIGH);
//  delay(cm * 10 ); // each centimeter adds 10 milliseconds delay
//  digitalWrite(ledPin, LOW);
//  delay( cm * 10);

  if(cm<=100){
    Serial.println("Open");
    digitalWrite(pwr, HIGH);
    myservo.write(90);                  // sets position to the 90 deg
    delay(15);
    Serial.println("Open2");
    myservo.write(0);                  // sets position to the 90 deg
    delay(15);
    digitalWrite(pwr, LOW);
  }
  else {
    Serial.println("Closed");  
    myservo.write(0);                  // sets position to the 90 deg
    delay(15);
  }
 digitalWrite(ledPin, LOW);
}
