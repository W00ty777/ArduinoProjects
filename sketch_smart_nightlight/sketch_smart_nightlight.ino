const int ledPin = 13;
const int sensorPin = 0;

void setup()

{
  Serial.begin(9600);
  pinMode(ledPin, OUTPUT);
}

void loop()
{
  int rate = analogRead(sensorPin);
  digitalWrite(ledPin, LOW);
  while(analogRead(sensorPin)<450)
  {
   digitalWrite(ledPin, HIGH);
  }
}

  
