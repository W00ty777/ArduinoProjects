// zoomkat 9-11-12 serial servo detach test
// type servo position in serial monitor
// use writeMicroseconds >500 to control servo
// use writeMicroseconds <500 to detach servo
// for IDE 0022 and later
// Powering a servo from the arduino usually DOES NOT WORK.

String readString;
#include <Servo.h> 
Servo myservo;  // create servo object to control a servo 

void setup() {
  Serial.begin(9600);
  myservo.writeMicroseconds(2000); //set initial servo position if desired
  //myservo.attach(7);  //the pin for the servo control 
  Serial.println("servo-detach-test"); // so I can keep track of what is loaded
}

void loop() {
  while (Serial.available()) {
    char c = Serial.read();  //gets one byte from serial buffer
    readString += c; //makes the string readString
    delay(2);  // allow buffer to fill with next character
    }

  if (readString.length() >0) {
    Serial.println(readString);  //so you can see the captured string 
    int n = readString.toInt();

    if (n < 500) {
      myservo.detach(); 
    }
    else {
       myservo.attach(7);
       myservo.writeMicroseconds(n); //convert readString to number for servo
    }
    readString=""; //empty for next input
  } 
}

