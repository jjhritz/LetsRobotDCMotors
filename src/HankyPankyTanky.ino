#include "../include/simple_hbridge.h"
#include "../include/IrLineEnforcement.h"


int fspeed= 220;                        /// The "full" speed the motors are allowed to run at normally.
int hspeed = 75;                        /// The "half" speed the motors will run at.
int bspeed = fspeed + 15;               /// The "boost" speed the motors will run at under special circumstances.
int cspeed = fspeed;                    /// The current speed the motors are set to run at.

long finishCommandTimestamp = 0;        /// The program time at which the motors will stop on their own.
long finishBoostTimestamp = 0;          /// The program time at which the speed boost will expire.
long currentTimestamp = 0;              /// The current program time.
long lastSensorRead = 0;                /// The program time at which the IR sensor was last read.

char last_dir;

IrLineEnforcement irle;                 /// Line enforcement

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

void drive_motors(char control)
/**
 * Sets the speed and direction of the motors based on the
 * @param control
 */
{
    switch (control)
    {
        //______________Motors______________
        case 'f': // forward
            last_dir = control;
            left_motor(cspeed);
            right_motor(cspeed);
            reset_ending_timestamp();
            break;
        case 'b': // back
            last_dir = control;
            left_motor(-cspeed);
            right_motor(-cspeed);
            reset_ending_timestamp();
            break;
        case 'r': // right
            last_dir = control;
            left_motor(hspeed);
            right_motor(-hspeed);
            reset_ending_timestamp();
            break;
        case 'l': // left
            last_dir = control;
            left_motor(-hspeed);
            right_motor(hspeed);
            reset_ending_timestamp();
            break;
        case 'a': // left forward
            last_dir = control;
            left_motor(hspeed);
            right_motor(cspeed);
            reset_ending_timestamp();
            break;
        case 'd': // right forward
            last_dir = control;
            left_motor(cspeed);
            right_motor(hspeed);
            reset_ending_timestamp();
            break;
        case 'z': // left back
            last_dir = control;
            left_motor(-hspeed);
            right_motor(-cspeed);
            reset_ending_timestamp();
            break;
        case 'c': // right back
            last_dir = control;
            left_motor(-cspeed);
            right_motor(-hspeed);
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

void setup()
{
  Serial.begin(9600);
  init_motors();
  irle = IrLineEnforcement();

  finishCommandTimestamp = millis();
  currentTimestamp = millis();
}

void loop()
{
    currentTimestamp = millis();

    if (currentTimestamp > finishCommandTimestamp)
    {
        left_motor(0);
        right_motor(0);
    }

    if (currentTimestamp >= finishBoostTimestamp)
    {
        cspeed = fspeed;
    }

    /**
     * When the IR sensor detects an object (tape, usually), the Override flag is set. The robot should stop and go back
     * in the direction it came from.
     */
    if(irle.getOverride())
    {
        left_motor(0);
        right_motor(0);

        char reverse_char;

        switch (last_dir)
        {
            //______________Motors______________
            case 'f': // forward
                reverse_char = 'b';
                break;
            case 'b': // back
                reverse_char = 'f';
                break;
            case 'r': // right
                reverse_char = 'l';
                break;
            case 'l': // left
                reverse_char = 'r';
                break;
            case 'a': // left forward
                reverse_char = 'c';
                break;
            case 'd': // right forward
                reverse_char = 'z';
                break;
            case 'z': // left back
                reverse_char = 'd';
                break;
            case 'c': // right back
                reverse_char = 'a';
                break;
            default:
                delay(10);
                break;
        }

        drive_motors(reverse_char);
        irle.setOverride(false);
    }
    else
    {
        if (currentTimestamp > (lastSensorRead + 1000))
        {
            irle.takeIRSample();
            lastSensorRead = millis();
        }

        if (Serial.available())
        {
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

            while (Serial.available())
            {
                char tempByte = Serial.read();
                delay(2);       // See note above about why we need to wait for characters to be completed.
                if (tempByte != 10 && tempByte != 13) inByte = tempByte;  // Keep reading bytes until you have the last one.
            }

            drive_motors(inByte);
        }
    }
}
