#include "simple_hbridge.h"

int fspeed= 255;
int hspeed = 125;
int bufferSize = 0;
long finishCommandTimestamp = 0;
long currentTimestamp = 0;

void setup() {
  Serial.begin(9600);
  init_motors(); 
  finishCommandTimestamp = millis();
  currentTimestamp = millis();
}

void loop() {
  currentTimestamp = millis();
  if (currentTimestamp > finishCommandTimestamp) {
        left_motor(0);
        right_motor(0);    
  }
  if (Serial.available()) {
    char inByte = Serial.read();
    delay(2);
    if (Serial.available()) Serial.println("still stuff in the serial stream");  
    else Serial.println("stream empty");  
    while (Serial.available()) {
      char tempByte = Serial.read();
      delay(2);
      if (tempByte != 10 && tempByte != 13) inByte = tempByte;  // Keep reading bytes until you have the last one.
    }
    Serial.println("Last data read: "+(String)inByte);
    switch (inByte) {
      //______________Motors______________
      case 'f': // forward
        Serial.println("Forward!");
        left_motor(fspeed);
        right_motor(fspeed);
        reset_ending_timestamp();
        break;
      case 'b': // back
        Serial.println("Back!");
        left_motor(-fspeed);
        right_motor(-fspeed);
        reset_ending_timestamp();
        break;
      case 'r': // right
        Serial.println("Right!");
        left_motor(fspeed);
        right_motor(hspeed);
        reset_ending_timestamp();
        break;
      case 'l': // left
        Serial.println("Left!");
        left_motor(hspeed);
        right_motor(fspeed);
        reset_ending_timestamp();
        break;
      case 's': // stop
        Serial.println("Stop!!"); // For debugging only. The pi does not send this.
        left_motor(0);
        right_motor(0);
        reset_ending_timestamp();
        break;
      default:
        delay(10);
    }
  }
}    

void reset_ending_timestamp() {
  finishCommandTimestamp = millis()+500;
}
  
