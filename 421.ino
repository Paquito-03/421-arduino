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

void setup() {
  
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
    digit1 = random(1,6);
    digit2 = random(1,6);
    digit3 = random(1,6);
    diceRoll = (digit1 * 100) + (digit2 * 10) + digit3;
  }
  sevseg.setNumber(diceRoll, 0);
  sevseg.refreshDisplay();

}

