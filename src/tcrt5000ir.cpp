//
/// Interface for TCRT 5000 IR Sensor Module
// Created by John J. Hritz on 2/4/2019.
//

#include "../include/tcrt5000ir.h"

tcrt5000ir::tcrt5000ir()
/**
 * Default constructor for the TCRT 5000 IR sensor object
 */
{
    this->setPins();
}

tcrt5000ir::tcrt5000ir(uint8_t pinIRd, uint8_t pinIRa, uint8_t pinLED)
/**
 * Parameterized constructor for the TCRT 5000 IR sensor object, allowing customized pin assignment.
 */
{
    this->pinIRd = pinIRd;
    this->pinIRa = pinIRa;
    this->pinLED = pinLED;

    this->setPins();
}

int tcrt5000ir::getIRd()
{
    return digitalRead(this->pinIRd);
}

int tcrt5000ir::getIRa()
{
    return analogRead(this->pinIRa);
}

int tcrt5000ir::getLEDval()
{
    return this->LEDval;
}

void tcrt5000ir::setLEDval(byte val)
{
    digitalWrite(this->pinLED, val);
    this->LEDval = val;
}

void tcrt5000ir::setPins()
/**
 * Sets the Arduino GPIO pins attached to the analog and digital reporting pins on the IR sensor to input and the LED
 * control pint to output.
 */
{
    pinMode(this->pinIRd, INPUT);
    pinMode(this->pinIRa, INPUT);
    pinMode(this->pinLED, OUTPUT);
}

void tcrt5000ir::testRead()
/**
 * Performs a read of the IR sensor and writes the results to the serial port.
 */
{
    Serial.print("Analog Reading=");
    Serial.print(getIRa());
    Serial.print("\t Digital Reading=");
    Serial.println(getIRd());
}

uint8_t tcrt5000ir::getDPin()
{
    return this->pinIRd;
}

uint8_t tcrt5000ir::getAPin()
{
    return this->pinIRa;
}