#include <stdio.h>

#define ERROR_TEMP "Temperature out of range!\n"
#define ERROR_SOC "State of Charge out of range!\n"
#define ERROR_CHARGE "Charge Rate out of range!\n"
#define WARNING_TEMP_LOW "Warning: Approaching lower temperature limit\n"
#define WARNING_TEMP_HIGH "Warning: Approaching upper temperature limit\n"
#define WARNING_SOC_LOW "Warning: Approaching discharge\n"
#define WARNING_SOC_HIGH "Warning: Approaching charge-peak\n"
#define WARNING_CHARGE_LOW "Warning: Approaching lower charge rate limit\n"
#define WARNING_CHARGE_HIGH "Warning: Approaching upper charge rate limit\n"

float tolerance = 0.05;  // 5% tolerance

// Function to print warning messages
void printWarning(const char* message) {
    if (message[0] != '\0') {  // Only print non-empty messages
        printf("%s", message);
    }
}

// Function to check both low and high warnings
void checkWarnings(float value, float min, float max, const char* warnLow, const char* warnHigh) {
    float lowerWarningLimit = min + (tolerance * (max - min));
    float upperWarningLimit = max - (tolerance * (max - min));
    
    if (value > min && value <= lowerWarningLimit) {
        printWarning(warnLow);
    }
    if (value >= upperWarningLimit && value < max) {
        printWarning(warnHigh);
    }
}

// Function to check range and print errors/warnings
int checkAndWarn(float value, float min, float max, const char* errorMessage, const char* warnLow, const char* warnHigh) {
    if (value < min || value > max) {
        printf("%s", errorMessage);
        return 0;  // Out of range
    }
    
    // Check for warnings
    checkWarnings(value, min, max, warnLow, warnHigh);
    return 1;  // Within range
}

int batteryIsOk(float temperature, float soc, float chargeRate) {
    // Perform checks for all parameters
    int temperatureStatus = checkAndWarn(temperature, 0, 45, ERROR_TEMP, WARNING_TEMP_LOW, WARNING_TEMP_HIGH);
    int socStatus = checkAndWarn(soc, 20, 80, ERROR_SOC, WARNING_SOC_LOW, WARNING_SOC_HIGH);
    int chargeRateStatus = checkAndWarn(chargeRate, 0, 0.8, ERROR_CHARGE, WARNING_CHARGE_LOW, WARNING_CHARGE_HIGH);

    // Return the overall status
    return temperatureStatus && socStatus && chargeRateStatus;
}
