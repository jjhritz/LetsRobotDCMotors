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
    /* It takes just over 1 millisecond for a character to be delivered   
     * via the serial connection. We wait for 2ms after each character to 
     * allow another character to come in on the line. We then respond to 
     * only the last command received, throwing the rest away.
     * 
     * This overcomes an issue in how the web interface handles desktop
     * vs. mobile users. 
     */
    delay(2);
    while (Serial.available()) {
      char tempByte = Serial.read();
      delay(2);       // See note above about why we need to wait for characters to be completed.
      if (tempByte != 10 && tempByte != 13) inByte = tempByte;  // Keep reading bytes until you have the last one.
    }
    switch (inByte) {
      //______________Motors______________
      case 'f': // forward
        left_motor(fspeed);
        right_motor(fspeed);
        reset_ending_timestamp();
        break;
      case 'b': // back
        left_motor(-fspeed);
        right_motor(-fspeed);
        reset_ending_timestamp();
        break;
      case 'r': // right
        left_motor(fspeed);
        right_motor(hspeed); //for tank or chassis that turns poorly in place, otherwise use -fspeed
        reset_ending_timestamp();
        break;
      case 'l': // left
        left_motor(hspeed); //for tank or chassis that turns poorly in place, otherwise use -fspeed
        right_motor(fspeed);
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
  
