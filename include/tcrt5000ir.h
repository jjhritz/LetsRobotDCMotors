//
// Interface for TCRT 5000 IR Sensor Module
// Based on code by mybotic: https://www.instructables.com/id/How-to-Use-TCRT5000-IR-Sensor-Module-With-Arduino-/
// Created by John J. Hritz on 2/4/2019.
//

#include <Arduino.h>

#ifndef LETSROBOTDCMOTORS_TCRT5000IR_H
#define LETSROBOTDCMOTORS_TCRT5000IR_H


class tcrt5000ir
{
    uint8_t pinIRd = 2;
    uint8_t pinIRa = A0;
    uint8_t pinLED = 9;
    byte LEDval = 0;

    public:
        tcrt5000ir();
        tcrt5000ir(uint8_t pinIRd, uint8_t pinIRa, uint8_t pinLED);

        int getIRa();
        int getIRd();
        uint8_t getDPin();
        uint8_t getAPin();

        int getLEDval();
        void setLEDval(byte val);

        void testRead();


    private:
        void setPins();
};


#endif //LETSROBOTDCMOTORS_TCRT5000IR_H
