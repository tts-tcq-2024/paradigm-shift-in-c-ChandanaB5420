#include <stdio.h>
#include "warning_system.h"

float tolerance = 0.05;  // 5% tolerance

void printWarningMessage(const char* message) 
{
    if (message[0] != '\0') {
        printf("%s", message);
    }
}

void checkLowThreshold(float value, float min, float max, const char* lowWarningMessage) 
{
    float lowerWarningLimit = min + (tolerance * max);
    if (value > min && value <= lowerWarningLimit) {
        printWarningMessage(lowWarningMessage);
    }
}

void checkHighThreshold(float value, float max, const char* highWarningMessage) 
{
    float upperWarningLimit = max - (tolerance * max);
    if (value >= upperWarningLimit && value < max) {
        printWarningMessage(highWarningMessage);
    }
}
