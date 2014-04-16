const int ledPin = 13;
const int sensorPin = 0;

void setup()

{
  pinMode(ledPin, OUTPUT);
}

void loop()
{
  int rate = analogRead(sensorPin);
  digitalWrite(ledPin, HIGH);
  delay(rate);
  digitalWrite(ledPin, LOW);
  delay(rate);
}

  
