//
// Interface for TCRT 5000 IR Sensor Module
// Created by John J. Hritz on 2/4/2019.
//

#include "tcrt5000ir.h"

tcrt5000ir::tcrt5000ir()
{
    this->setPins();
}

tcrt5000ir::tcrt5000ir(int pinIRd, int pinIRa, int pinLED)
{
    this->pinIRd = pinIRd;
    this->pinIRa = pinIRa;
    this->pinLED = pinLED;

    this->setPins();
}

int tcrt5000ir::getIRa()
{
    return analogRead(this->pinIRa);
}


int tcrt5000ir::getIRd()
{
    return digitalRead(this->pinIRd);
}

int tcrt5000ir::getLEDval()
{
    return this->LEDval;
}

void tcrt5000ir::setLEDval(int val)
{
    digitalWrite(this->pinLED, val);
    this->LEDval = val;
}

void tcrt5000ir::setPins()
{
    pinMode(this->pinIRd,INPUT);
    pinMode(this->pinIRa,INPUT);
    pinMode(this->pinLED,OUTPUT);
}