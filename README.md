# LetsRobot DC Motors
A simple Arduino sketch designed to control a pair of DC motors through an h-bridge.

## Wiring
The motors are controlled through an H-bridge, which makes it easier to run them forwards and backwards.

When wiring your H-bridge, make sure it (and your motors) is rated for your battery voltage.  If it's not, you're going to need to use a stepdown converter to make sure you don't fry the electronics.

| H-bridge Pin | Arduino Pin |
|--------------|-------------|
| ENA          | 3           |
| IN1          | 8           |
| IN2          | 4           |
| IN3          | 5           |
| IN4          | 6           |
| ENB          | 11          |

## Configuring LetsRobot
Start by following the instructions on the LetsRobot Github [here](https://github.com/letsRobot/letsrobot).

When you get to the *Configure the controller* part of the instructions, you'll start setting options in `letsrobot.conf`.  In this case, the Arduino is considered a `serial_board` type, so there are only a few settings you need to worry about:
1. Under the `[robot]` section, set `type` to `serial_board`.
2. Under the `[serial]` section, set `serial_device` to the name of the serial port the Arduino is connected as.
    * You can get a list of the connected serial ports by entering `ls /dev/tty*` into the command line.  This will bring up a lot of entries; Arduinos and similar boards generally get names like `ttyACM0`, but the list of possibilities should be short.
3. Set `baud_rate` to `9600`.  If you change the baud rate in this Arduino code, be sure to use that new baud rate here.

## IR Line Enforcement
There is an alternate version of this sketch (`HankyPankyTanky.ino`) that includes a simple area enforcement mechanism using an IR proximity sensor.  It uses a TCRT 5000 IR sensor to look out for areas of high contrast (usually tape).  When it encounters such an area, it turns reverses direction and moves away.  

The sensor should be connected to the Arduino as follows.

| Sensor Pin | Arduino Pin |
|------------|-------------|
| D0         | 2           |
| A0         | A0          |

It should be relatively easy to modify this mechanism to use a different IR sensor.