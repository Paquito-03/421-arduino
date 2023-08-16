#include <SevSeg.h>
SevSeg sevseg; 

// digitCodeMap indicate which segments must be illuminated to display
// each number. FROM SevSeg.cpp
static const uint8_t digitCodeMap[] = {
  // GFEDCBA  ID             7-segment map:
  0b00111111, // 0   "0"          AAA
  0b00000110, // 1   "1"         F   B
  0b01011011, // 2   "2"         F   B
  0b01001111, // 3   "3"          GGG
  0b01100110, // 4   "4"         E   C
  0b01101101, // 5   "5"         E   C
  0b01111101, // 6   "6"          DDD
  0b00000111, // 7   "7"
  0b01111111, // 8   "8"
  0b01101111, // 9   "9"
  0b01110111, // 10  'A'
  0b01111100, // 11  'b'
  0b00111001, // 12  'C'
  0b01011110, // 13  'd'
  0b01111001, // 14  'E'
  0b01110001, // 15  'F'
  0b00000000, // 16  ''        BLANK
  0b00000001, // 17  '-'       FIRST THROW
  0b01000001, // 18  '--'      SECOND THROW
  0b01001001, // 19  '---'     THIRD THROW
};

// Hit sensor
int sensor = A4; // define the tilt switch sensor interfaces
int val ;// define numeric variables val

// boutons
const int boutonPins[] = {A0, A1, A2, A3};

// variable for the game
byte digits[] = {0, 0, 0};
byte nbThrow = 0;

// block the digit
bool blockDigit1 = false;
bool blockDigit2 = false;
bool blockDigit3 = false;

void setup() {
  
  //set all segments & digits as outputs

  byte numDigits = 4;

  // order is important !!!
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

  if (val == LOW && nbThrow < 3) // if the tilt sensor detects a signal 
  {
    if (!blockDigit1)
      digits[0] = random(1,6);
    if (!blockDigit2)
      digits[1] = random(1,6);
    if (!blockDigit3)
      digits[2] = random(1,6);
    delay(200);
    nbThrow++;
  }


  if (digitalRead(boutonPins[0]) == HIGH)
      blockDigit1 = true;
      
  if (digitalRead(boutonPins[1]) == HIGH)
    blockDigit2 = true;
      
  if (digitalRead(boutonPins[2]) == HIGH)
      blockDigit3 = true;
      

  if (digitalRead(boutonPins[3]) == HIGH)
    unlockAllDigit();

  // For more details, see the documentation of SevSeG.h
  // Set the segments for every digit on the display
  uint8_t segs[4] = {digitCodeMap[16 + nbThrow], digitCodeMap[digits[0]], digitCodeMap[digits[1]], digitCodeMap[digits[2]]};
  sevseg.setSegments(segs);

  sevseg.refreshDisplay(); 
}

/**
 * Unlocks all digit changes after dice are rolled and set nbThrow to 0.
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

  nbThrow = 0;
}

