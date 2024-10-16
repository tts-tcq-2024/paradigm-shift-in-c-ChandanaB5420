#include <stdio.h>
#include <assert.h>
#include "parameters.h"

int batteryIsOk(float temperature, float soc, float chargeRate) 
{
    int temperatureStatus = checkParameter(temperature, 0, 45, ERROR_TEMP, WARNING_TEMP_LOW, WARNING_TEMP_HIGH);
    int socStatus = checkParameter(soc, 20, 80, ERROR_SOC, WARNING_SOC_LOW, WARNING_SOC_HIGH);
    int chargeRateStatus = checkParameter(chargeRate, 0, 0.8, ERROR_CHARGE, WARNING_CHARGE_LOW, WARNING_CHARGE_HIGH);

    return temperatureStatus && socStatus && chargeRateStatus;
}

int main() {
    runTests();
}
