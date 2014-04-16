/* KnightRider
 */

const int NbrLEDs = 6;
const int ledPins[] = {2, 3, 4, 5, 6, 7};
const int sensorPin = 0;
const int wait = 30;

void setup(){
  Serial.begin(9600);
  for (int led = 0; led < NbrLEDs; led++)
  {
    pinMode(ledPins[led], OUTPUT);
  }
}

void loop() {
    int rate = analogRead(sensorPin);
    Serial.write("LDR read out: ");
    Serial.write(rate);`
  for (int led = 0; led < NbrLEDs; led++)
  {
    digitalWrite(ledPins[led], LOW);
  }
 while(analogRead(sensorPin)<450){
  for (int led = 0; led < NbrLEDs-1; led++){
    digitalWrite(ledPins[led], HIGH);
	delay(wait);
	digitalWrite(ledPins[led + 1], HIGH);
	delay(wait);
	digitalWrite(ledPins[led], LOW);
	delay(wait*2);
  }
  for (int led = NbrLEDs-1; led > 0; led--) {
	digitalWrite(ledPins[led], HIGH);
	delay(wait);
	digitalWrite(ledPins[led - 1], HIGH);
	delay(wait);
	digitalWrite(ledPins[led], LOW);
	delay(wait*2);
  }
 }
}
