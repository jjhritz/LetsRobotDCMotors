//
// Created by John J. Hritz on 2/13/2019.
//

#include "tcrt5000ir.h"
#include "statistics.h"
#include <Arduino.h>

#ifndef LETSROBOTDCMOTORS_IRLINEENFORCEMENT_H
#define LETSROBOTDCMOTORS_IRLINEENFORCEMENT_H


class IrLineEnforcement
{
    protected:
        tcrt5000ir IR;                          /// Object representation of a TCRT5000 IR sensor.
        static const int IRHistorySize = 8;     /// The length of sample history from the IR sensor
        int IRHistory[IRHistorySize];           /// Sample history from the IR sensor
        float IRMean = 0;                       /// Mean value of the IR sample history
        float IRStdDev = 0;                     /// Standard deviation of the IR sample history
        int next_sample = 0;                    /// Tracks where the next sample will be placed in the history.
        static volatile bool override;          /// Flag set when a line is encountered.

    public:
        IrLineEnforcement();
        IrLineEnforcement(uint8_t pinIRd, uint8_t pinIRa, uint8_t pinLED);

        float getIRMean();
        float getIRStdDev();
        int getIRHistorySize();
        int getNextSample();
        int* getIRHistory();
        tcrt5000ir getIR();
        bool getOverride();

        void setOverride(bool override);

        int takeIRSample();

    private:
        static void lineEncountered();
        void populateIRHistory();
};

#endif //LETSROBOTDCMOTORS_IRLINEENFORCEMENT_H
