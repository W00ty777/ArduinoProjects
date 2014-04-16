/*
Reading of LDR on LCD
*/

const int inPin = 0;  // sensor connected to this analog pin
int fan = 10;    //fan initialized

void setup()
{
  pinMode(fan, OUTPUT);  
  Serial.begin(9600);
  delay(3000);
}

void loop()
{
  int value = analogRead(inPin);
  if(value > 750){
    digitalWrite(fan, HIGH);
  }else{
    digitalWrite(fan, LOW);
  }
  delay(10000);
}
