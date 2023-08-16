#include <SevSeg.h>
SevSeg sevseg; 

// Hit sensor
int sensor = A4; // define the tilt switch sensor interfaces
int val ;// define numeric variables val

// boutons
const int boutonPins[] = {A0, A1, A2, A3};

// variable for the game
int diceRoll = 0;
byte digit1 = 0;
byte digit2 = 0;
byte digit3 = 0;

// block the digit
bool blockDigit1 = false;
bool blockDigit2 = false;
bool blockDigit3 = false;

void setup() {
  
  //set all segments & digits as outputs

  byte numDigits = 4;
  byte digitPins[] = {12,9,8,6};
  byte segmentPins[] = {11,7,4,2,1,10,5};

  // go see documentation of SevSeg.h for the configuration
  bool resistorsOnSegments = false; 
  bool updateWithDelaysIn = false;
  byte hardwareConfig = COMMON_ANODE; 
  sevseg.begin(hardwareConfig, numDigits, digitPins, segmentPins, resistorsOnSegments);
  sevseg.setBrightness(100);

  // Tilt Ball switch sensor
  pinMode (sensor, INPUT) ; // define the output interface tilt switch sensor

  // buttons
  for (int i = 0; i < sizeof(boutonPins) / sizeof(boutonPins[0]); i++) {
    pinMode(boutonPins[i], INPUT); // Configure pins of the buttons at INPUT
  }

}

void loop() {
  val = digitalRead (sensor) ; // read hit sensor

  if (val == LOW) // if the tilt sensor detects a signal
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
      blockDigit1 = true;
      
  if (digitalRead(boutonPins[1]) == HIGH)
    blockDigit2 = true;
      
  if (digitalRead(boutonPins[2]) == HIGH)
      blockDigit3 = true;
      

  if (digitalRead(boutonPins[3]) == HIGH)
    unlockAllDigit();

  // For more details, see the documentation of sevgev.h
  sevseg.setNumber(diceRoll, 0); // 
  sevseg.refreshDisplay(); 
}

/**
 * Unlocks all digit changes after dice are rolled.
 *
 * This function resets the flags that prevent changing the digits
 * after the dice are rolled. This allows the digits to be changed
 * again for the next roll.
 */
void unlockAllDigit()
{
  blockDigit1 = false;
  blockDigit2 = false;
  blockDigit3 = false;
}

