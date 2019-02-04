#include "simple_hbridge.h"

int fspeed= 220;                        /// The "full" speed the motors are allowed to run at normally.
int hspeed = 75;                       /// The "half" speed the motors will run at.
int bspeed = fspeed + 15;               /// The "boost" speed the motors will run at under special circumstances.
int cspeed = fspeed;                    /// The current speed the motors are set to run at.
int bufferSize = 0;
long finishCommandTimestamp = 0;        /// The program time at which the motors will stop on their own.
long finishBoostTimestamp = 0;          /// The program time at which the speed boost will expire.
long currentTimestamp = 0;              /// The current program time.

void setup() {
    Serial.begin(9600);
    init_motors();
    finishCommandTimestamp = millis();
    currentTimestamp = millis();
}

void loop()
{
    currentTimestamp = millis();

    if (currentTimestamp >= finishCommandTimestamp)
    {
        left_motor(0);
        right_motor(0);
    }

    if (currentTimestamp >= finishBoostTimestamp)
    {
        cspeed = fspeed;
    }

    if (Serial.available())
    {
        char inByte = Serial.read();
        delay(2);

        //if (Serial.available()) Serial.println("still stuff in the serial stream");
        //else Serial.println("stream empty");

        while (Serial.available()) {
            char tempByte = Serial.read();
            delay(2);
            if (tempByte != 10 && tempByte != 13) inByte = tempByte;  // Keep reading bytes until you have the last one.
        }

        //Serial.println("Last data read: "+(String)inByte);

        switch (inByte)
        {
            //______________Motors______________
            case 'f': // forward
                //Serial.println("Forward!");
                left_motor(cspeed);
                right_motor(cspeed);
                reset_ending_timestamp();
                break;
            case 'b': // back
                //Serial.println("Back!");
                left_motor(-cspeed);
                right_motor(-cspeed);
                reset_ending_timestamp();
                break;
            case 'r': // right
                //Serial.println("Right!");
                left_motor(cspeed);
                right_motor(-hspeed);
                reset_ending_timestamp();
                break;
            case 'l': // left
                //Serial.println("Left!");
                left_motor(-hspeed);
                right_motor(cspeed);
                reset_ending_timestamp();
                break;
            case 's': // stop
                //Serial.println("Stop!!"); // For debugging only. The pi does not send this.
                left_motor(0);
                right_motor(0);
                reset_ending_timestamp();
                break;
            case 't': // BOOST!
                //Serial.println("BOOST!!!");
                cspeed = bspeed;
                set_boost_timestamp(60);
                break;
            default:
                delay(10);
        }
    }
}

void reset_ending_timestamp()
/**
 * Sets how time at which the motors will stop on their own, if no command is received.
 */
{
    finishCommandTimestamp = millis() + 500;
}

void set_boost_timestamp(int sec)
/**
 * Sets the time at which the speed boost will expire.
 * @param sec The number of seconds the speed boost will run.
 */
{
    finishBoostTimestamp = millis() + sec * 1000;
}
