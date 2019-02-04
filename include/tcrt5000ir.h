//
// Interface for TCRT 5000 IR Sensor Module
// Based on code by mybotic: https://www.instructables.com/id/How-to-Use-TCRT5000-IR-Sensor-Module-With-Arduino-/
// Created by John J. Hritz on 2/4/2019.
//

#include <Arduino.h>

#ifndef LETSROBOTDCMOTORS_TCRT5000IR_H
#define LETSROBOTDCMOTORS_TCRT5000IR_H


class tcrt5000ir {
    int pinIRd = 8;
    int pinIRa = A0;
    int pinLED = 9;
    int LEDval = 0;

    public:
        tcrt5000ir();
        tcrt5000ir(int pinIRd, int pinIRa, int pinLED);

        int getIRa();
        int getIRd();

        int getLEDval();
        void setLEDval(int val);

    private:
        void setPins();
};


#endif //LETSROBOTDCMOTORS_TCRT5000IR_H
