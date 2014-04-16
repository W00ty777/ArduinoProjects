//*****************************************************************************
/// @file
/// @brief
///   Arduino SmartThings Shield LED Example 
/// @note
///              ______________
///             |              |
///             |         SW[] |
///             |[]RST         |
///             |         AREF |--
///             |          GND |--
///             |           13 |--
///             |           12 |--
///             |           11 |--
///           --| 3.3V      10 |--X Fan Switch
///           --| 5V         9 |--
///           --| GND        8 |--X TV Switch
///           --| GND          |
///           --| Vin        7 |--
///             |            6 |--
///      LDR X--| A0         5 |--
///           --| A1    ( )  4 |--
///           --| A2         3 |--X THING_RX
///           --| A3  ____   2 |--X THING_TX
///           --| A4 |    |  1 |--
///           --| A5 |    |  0 |--
///             |____|    |____|
///                  |____|
///
//*****************************************************************************
#include <SoftwareSerial.h>   //TODO need to set due to some weird wire language linker, should we absorb this whole library into smartthings
#include <SmartThings.h>

//*****************************************************************************
// Pin Definitions    | | | | | | | | | | | | | | | | | | | | | | | | | | | | |
//                    V V V V V V V V V V V V V V V V V V V V V V V V V V V V V
//*****************************************************************************
#define PIN_TV          8
#define PIN_THING_RX    3
#define PIN_THING_TX    2

//*****************************************************************************
// Global Variables   | | | | | | | | | | | | | | | | | | | | | | | | | | | | |
//                    V V V V V V V V V V V V V V V V V V V V V V V V V V V V V
//*****************************************************************************
SmartThingsCallout_t messageCallout;    // call out function forward decalaration
SmartThings smartthing(PIN_THING_RX, PIN_THING_TX, messageCallout);  // constructor

bool isDebugEnabled;    // enable or disable debug in this example
int stateLED;           // state to track last set value of LED
const int inPin = 0;  // sensor connected to this analog pin
int fan = 10;    //fan initialized
String State= ""; // State of TV initialized
String Mesh="";



//*****************************************************************************
// Local Functions  | | | | | | | | | | | | | | | | | | | | | | | | | | | | | |
//                  V V V V V V V V V V V V V V V V V V V V V V V V V V V V V V
//*****************************************************************************
void on(){
  stateLED = 1;                 // save state as 1 (on)
  smartthing.send("on");        // send message to cloud
  smartthing.shieldSetLED(0, 0, 1); // Colors are (Red,Green,Blue) intensity {0=off to 9=max}
}

void off(){
  stateLED = 0;                 // set state to 0 (off)
  smartthing.send("off");       // send message to cloud
  smartthing.shieldSetLED(0, 0, 0); // Colors are (Red,Green,Blue) intensity {0=off to 9=max}
}

void tv(){                      // TV momentary switch
  digitalWrite(PIN_TV, HIGH);  
  delay(300);
  digitalWrite(PIN_TV, LOW);
}

void LampCheck(){
  int value = analogRead(inPin);
  if(value > 750){
    digitalWrite(fan, HIGH);
    State="on";
  }else{
    digitalWrite(fan, LOW);
    State="off";
  }
}


//*****************************************************************************
// API Functions    | | | | | | | | | | | | | | | | | | | | | | | | | | | | | |
//                  V V V V V V V V V V V V V V V V V V V V V V V V V V V V V V
//*****************************************************************************
void setup()
{
  // setup default state of global variables
  isDebugEnabled = false;
  stateLED = 0;                  // matches state of hardware pin set below
  
  // setup hardware pins 
  pinMode(PIN_TV, OUTPUT);      // define PIN_TV as an output
  pinMode(fan, OUTPUT);  
    
  if (isDebugEnabled)
  { // setup debug serial port
    Serial.begin(9600);         // setup serial with a baud rate of 9600
    Serial.println("setup..");  // print out 'setup..' on start
  }
}

//*****************************************************************************
void loop()
{
  // run smartthing logic
  LampCheck();
  smartthing.run();
}

//*****************************************************************************
void messageCallout(String message)
{
  Mesh = message;
  tv();
  // if debug is enabled print out the received message
  if (isDebugEnabled)
  {
    Serial.print("Received message: '");
    Serial.print(Mesh);
    Serial.print("' ");
    Serial.print("State: '");
    Serial.print(State);
    Serial.println("' ");
  }

  // if message contents equals to 'on' then call on() function
  // else if message contents equals to 'off' then call off() function
  if (message.equals("on"))
  {
    on();
  }
  else if (message.equals("off"))
  {
    off();
  }
  delay(60000);
  LampCheck();
  Check();
}

void Check(){
   if (Mesh==State)
  {
    Serial.println("They are equal");    
    Serial.print(Mesh);
    Serial.print(State);
  }
  else 
  {
    tv();
  }
}
