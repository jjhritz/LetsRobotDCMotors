//
// Created by John J. Hritz on 2/13/2019.
//

#include "../include/IrLineEnforcement.h"

volatile bool IrLineEnforcement::override = false;

IrLineEnforcement::IrLineEnforcement()
/**
 * Default constructor for the Line Enforcement mechanism
 */
{
    this->IR = tcrt5000ir();

    populateIRHistory();

    attachInterrupt(digitalPinToInterrupt(this->IR.getDPin()), lineEncountered, FALLING);
}

IrLineEnforcement::IrLineEnforcement(uint8_t pinIRd, uint8_t pinIRa, uint8_t pinLED)
/**
 * Parameterized constructor for the Line Enforcement mechanism, allowing for custom pin assignment.
 * @param pinIRd The pin number connected to the IR sensor's digital output
 * @param pinIRa The pin number connected to the IR sensor's analog output
 * @param pinLED The pin number connected to the IR sensor's LED indicator
 */
{
    this->IR = tcrt5000ir(pinIRd, pinIRa, pinLED);

    populateIRHistory();

    attachInterrupt(digitalPinToInterrupt(this->IR.getDPin()), lineEncountered, FALLING);
}

void IrLineEnforcement::populateIRHistory()
/**
 * Takes sensor readings until the sample history is full, then determines the mean and standard deviation of the samples.
 * Used as a startup calibration, to determine the reflected light levels.
 */
{
    // Populate IR sensor history and calculate statistical data
    for (int i = 0; i < IRHistorySize; i++)
    {
        this->IRHistory[i] = this->IR.getIRa();
    }

    this->IRMean = mean(this->IRHistory, IRHistorySize);
    this->IRStdDev = stdev(this->IRHistory, IRHistorySize);
}

void IrLineEnforcement::lineEncountered()
/**
 * Interrupt service routine.  Run when the IR sensor detects what it considers a line.  Enables override behavior.
 */
{
    override = true;
}

int IrLineEnforcement::takeIRSample()
/**
 * Takes a sample from the IR sensor and stores it in the history list. Updates statistical data accordingly.
 */
{
    int val = this->IR.getIRa();

    this->IRHistory[this->next_sample] = val;

    if(++(this->next_sample) >= IRHistorySize)
    {
        this->next_sample = 0;
    }

    this->IRMean = mean(this->IRHistory, IRHistorySize);
    this->IRStdDev = stdev(this->IRHistory, IRHistorySize);

    return val;
}

float IrLineEnforcement::getIRMean()
{
    return this->IRMean;
}
float IrLineEnforcement::getIRStdDev()
{
    return this->IRStdDev;
}
int IrLineEnforcement::getIRHistorySize()
{
    return IRHistorySize;
}
int IrLineEnforcement::getNextSample()
{
    return this->next_sample;
}
int* IrLineEnforcement::getIRHistory()
{
    return this->IRHistory;
}
tcrt5000ir IrLineEnforcement::getIR()
{
    return this->IR;
}
bool IrLineEnforcement::getOverride()
{
    return override;
}

void IrLineEnforcement::setOverride(bool new_override)
{
    override = new_override;
}