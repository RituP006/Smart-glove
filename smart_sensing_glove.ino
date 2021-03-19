
#include "FlexLibrary.h"
#include <Servo.h>
#include <LiquidCrystal.h>
#include "ADXL335.h"
#define USE_ARDUINO_INTERRUPTS true    // Set-up low-level interrupts for most acurate BPM math.
#include <PulseSensorPlayground.h>     // Includes the PulseSensorPlayground Library.   

const int PulseWire = 7;       // PulseSensor PURPLE WIRE connected to ANALOG PIN 0
const int LED13 = 13;          // The on-board Arduino LED, close to PIN 13.
int Threshold = 550;           // Determine which Signal to "count as a beat" and which to ignore.
                            
Servo  thumbS, middleS, indexS, ringS, pinkyS;

PulseSensorPlayground pulseSensor; 

String debug = "";

int fin4 = 5; // ring
int fin5 = 9;  // pinky
int fin1 = 2; // thumb
int fin3 = 11; // middle
int fin2 = 3; // index

int maxRing = 580;
int maxPinky = 620;
int maxThumb = 600;
int maxMiddle = 570;
int maxIndex = 575;

int minRing = 420;
int minPinky = 420;
int minThumb = 440;
int minMiddle = 440;            
int minIndex = 450;

// Flex(int SensorPin, int minInput, int maxInput, int numReadings, int smoothingType, int weight)  
Flex ring(A3, minRing, maxRing, 10, RUN_AVG, 0);
Flex pinky(A4, minPinky, maxPinky, 10, RUN_AVG, 0);
Flex thumb(A0, minThumb, maxThumb, 10, RUN_AVG, 0);
Flex middle(A2, minMiddle, maxMiddle, 10, RUN_AVG, 0);
Flex index(A1, minIndex, maxIndex, 10, RUN_AVG, 0);

const int xpin = A5;                  // x-axis 
const int ypin = A6;                  // y-axis

const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

void setup(){
  Serial.begin(9600);
  ringS.attach(fin4);
  pinkyS.attach(fin5);
  thumbS.attach(fin1);
  middleS.attach(fin3);
  indexS.attach(fin2);

  ringS.write(2);
  pinkyS.write(2);
  thumbS.write(2);
  middleS.write(2);
  indexS.write(2);

  
  delay(1000);


// pulse sensor--------------------------
     Serial.begin(9600);          // For Serial Monitor

  // Configure the PulseSensor object, by assigning our variables to it. 
  pulseSensor.analogInput(PulseWire);   
  pulseSensor.blinkOnPulse(LED13);       //auto-magically blink Arduino's LED with heartbeat.
  pulseSensor.setThreshold(Threshold);   

  // Double-check the "pulseSensor" object was created and "began" seeing a signal. 
   if (pulseSensor.begin()) {
    Serial.println("PulseSensor Object activated");  //This prints one time at Arduino power-up,  or on Arduino reset.  
  }
}

void loop(){
  thumb.updateVal();
  middle.updateVal();
  index.updateVal();
  ring.updateVal();
  pinky.updateVal();

  int ringPos = map(ring.getSensorValue(), minRing, maxRing, 180, 0);
  ringPos = constrain(ringPos, 0, 180);
  int pinkyPos = map(pinky.getSensorValue(), minPinky, maxPinky, 0, 180);
  pinkyPos = constrain(pinkyPos, 0, 180);
  int thumbPos = map(thumb.getSensorValue(), minThumb, maxThumb, 180, 0);
  thumbPos = constrain(thumbPos, 0, 180);
  int middlePos = map(middle.getSensorValue(), minMiddle, maxMiddle, 0, 180);
  middlePos = constrain(middlePos, 0, 180);
  int indexPos = map(index.getSensorValue(), minIndex, maxIndex, 0, 180);
  indexPos = constrain(indexPos, 0, 180);
 // Serial.println(thumbPos);
  
  //Tells servos to move by the amount specified in the "pos" variables
  ringS.write(ringPos);
  pinkyS.write(pinkyPos);
  thumbS.write(thumbPos);
  middleS.write(middlePos);
  indexS.write(indexPos);

  //debug = ((String)"Thumb: " + thumbPos + "\tIndex: " + indexPos + "\tMiddle: " + middlePos + "\tRing: " + ringPos + "\tPinky: " + pinkyPos);
  debug = ((String)"Thumb: " + thumb.getSensorValue() + "\tIndex: " + index.getSensorValue() + "\tMiddle: " + middle.getSensorValue() + "\tRing: " + ring.getSensorValue() + "\tPinky: " + pinky.getSensorValue());
  Serial.println(debug);
 
 // Serial.print(analogRead(xpin));
 // Serial.print("\t");
 // Serial.print(analogRead(ypin));
 // Serial.print("\t");
 // Serial.println();

  int rv = ring.getSensorValue();
  int pv = pinky.getSensorValue();
  int tv = thumb.getSensorValue();
  int mv = middle.getSensorValue();
  int iv = index.getSensorValue();

  int x = analogRead(xpin);
  int y = analogRead(ypin);

delay(5000);


if(((tv >= 240) && (tv<=280)) && ((iv >= 40) && (iv<=100)) && ((mv >= 120) && (mv<=160)) && ((rv >= 80) && (rv<=120)) && ((pv >= 200) && (pv<=250))){
  Serial.print("\nHello");
  Serial.println();
  Serial.println();
}  
else if (((tv >= 160) && (tv<=220)) && ((iv >= 40) && (iv<=100)) && ((mv >= 50) && (mv<=120)) && ((rv >= 30) && (rv<=80)) && ((pv >= 180) && (pv<=220))){
  Serial.print("\nIneed help");
  Serial.println();
    Serial.println();
}  
else if (((tv >= 175) && (tv<=210)) && ((iv >= 40) && (iv<=80)) && ((mv >= 120) && (mv<=160)) && ((rv >= 80) && (rv<=120)) && ((pv >= 190) && (pv<=230))){
  Serial.print("\nI want to use rest room");
  Serial.println();
    Serial.println();
}  
else if (((tv >= 220) && (tv<=270)) && ((iv >= 40) && (iv<=90)) && ((mv >= 80) && (mv<=120)) && ((rv >= 50) && (rv<=100)) && ((pv >= 150) && (pv<=230))){
  Serial.print("\nI am not well");
  Serial.println();
    Serial.println();
}
else if (((tv >= 230) && (tv<=270)) && ((iv >= 30) && (iv<=80)) && ((mv >=80) && (mv<=120)) && ((rv >= 40) && (rv<=80)) && ((pv >= 190) && (pv<=240))){
  Serial.print("\nI am good");
    Serial.println();
  Serial.println();
}

  
 
//---------pulse sensor-----------------
 int myBPM = pulseSensor.getBeatsPerMinute();  // Calls function on our pulseSensor object that returns BPM as an "int".
                                               // "myBPM" hold this BPM value now. 

if (pulseSensor.sawStartOfBeat()) {            // Constantly test to see if "a beat happened". 
 Serial.println("♥  A HeartBeat Happened ! "); // If test is "true", print a message "a heartbeat happened".
 Serial.print("BPM: ");                        // Print phrase "BPM: " 
 Serial.println(myBPM);                        // Print the value inside of myBPM. 
}

  delay(20);                    // considered best practice in a simple sketch.

}
