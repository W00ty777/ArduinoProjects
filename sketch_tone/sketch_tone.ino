const int speakerPin = 9;
const int pitchPin = 0;

void setup()
{
}
void loop()
{
  int sensor0Reading =analogRead(pitchPin);
  //map the analog reading to a meaningful range
  int frequency = map(sensor0Reading, 0, 1023, 100,5000); 
  int duration = 250;
  tone(speakerPin, frequency, duration);
  delay(1000);
}
