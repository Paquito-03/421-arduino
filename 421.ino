#include <SevSeg.h>
SevSeg sevseg; 

// Tilt Ball switch sensor
int sensor = A4; // define the tilt switch sensor interfaces
int val ;// define numeric variables val

// bouton
const int boutonPins[] = {A0, A1, A2, A3};

// games
int diceRoll = 0;
int digit1 = 0;
int digit2 = 0;
int digit3 = 0;

// block digit
bool blockDigit1 = false;
bool blockDigit2 = false;
bool blockDigit3 = false;

void setup() {

  // DEBUG
  pinMode(13, OUTPUT);
  digit2 = 4;
  blockDigit2 = true;
  
  //set all segments & digits as outputs

  byte numDigits = 4;
  byte digitPins[] = {12,9,8,6};
  byte segmentPins[] = {11,7,4,2,1,10,5};

  bool resistorsOnSegments = false; 
  bool updateWithDelaysIn = false;
  byte hardwareConfig = COMMON_ANODE; 
  sevseg.begin(hardwareConfig, numDigits, digitPins, segmentPins, resistorsOnSegments);
  sevseg.setBrightness(100);

  // Tilt Ball switch sensor
  pinMode (sensor, INPUT) ;//define the output interface tilt switch sensor

  // button
  for (int i = 0; i < sizeof(boutonPins) / sizeof(boutonPins[0]); i++) {
    pinMode(boutonPins[i], INPUT); // Configure les broches des boutons en entrée
  }

}

void loop() {
  val = digitalRead (sensor) ;// digital interface will be assigned a value of 3 to read val

  if (val == HIGH) //When the tilt sensor detects a signal when the switch, LED flashes
  {
    if (!blockDigit1)
      digit1 = random(1,6);
    if (!blockDigit2)
      digit2 = random(1,6);
    if (!blockDigit3)
      digit3 = random(1,6);


    diceRoll = (digit1 * 100) + (digit2 * 10) + digit3;
  }

  if (digitalRead(boutonPins[0]) == HIGH)
  {
      blockDigit1 = true;
      digitalWrite(13, HIGH); 
  }
      
  if (digitalRead(boutonPins[1]) == HIGH)
  {
    blockDigit2 = true;
      digitalWrite(13, HIGH);
  }
      
  if (digitalRead(boutonPins[2]) == HIGH)
  {
      blockDigit3 = true;
      digitalWrite(13, HIGH);
  }
      

  if (digitalRead(boutonPins[3]) == HIGH)
  {
    unlockAllDigit();
    digitalWrite(13, HIGH);
  }
      


  sevseg.setNumber(diceRoll, 0);
  sevseg.refreshDisplay();
}

void unlockAllDigit()
{
  blockDigit1 = false;
  blockDigit2 = false;
  blockDigit3 = false;
}

