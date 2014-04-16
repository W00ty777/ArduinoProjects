const int startByte    = 10;
const int endByte      = 13;
const int tagLength    = 10;
const int totalLength  = tagLength + 2;
char tag [tagLength + 1];
int bytesread = 0;

void setup()
{
   Serial.begin(2400);
   pinMode(2,OUTPUT);
   digitalWrite(2, LOW);
}

void loop()
{
  if(Serial.available() >= totalLength)
  {
    if(Serial.read() == startByte)
    {
      bytesread = 0;
      while(bytesread < tagLength) 
      {
        int val = Serial.read();
        if((val == startByte)||(val == endByte)) 
         break;
        tag[bytesread] = val;
         bytesread = bytesread + 1;
      }
      if( Serial.read() == endByte) 
      {
        tag[bytesread] = 0;
        long tagValue = atol(tag);
        Serial.print("RFID tag is: ");
        Serial.println(tagValue);
        Serial.println();
      }
    }
  }
}

