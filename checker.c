#include <stdio.h>
#include <assert.h>

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

// Function to check for low warnings
void checkLowWarning(float value, float min, float max, const char* warnLow) {
    float lowerWarningLimit = min + (tolerance * max);
    if (value > min && value <= lowerWarningLimit) {
        printWarning(warnLow);
    }
}

// Function to check for high warnings
void checkHighWarning(float value, float min, float max, const char* warnHigh) {
    float upperWarningLimit = max - (tolerance * max);
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

    // Check for low and high warnings separately
    checkLowWarning(value, min, max, warnLow);
    checkHighWarning(value, min, max, warnHigh);

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

int main() {
    // Valid cases
    assert(batteryIsOk(25, 70, 0.7));
    assert(batteryIsOk(0, 20, 0.0));     
    assert(batteryIsOk(45, 80, 0.8));    

    // Test cases for invalid temperature
    assert(!batteryIsOk(-1, 70, 0.7));   
    assert(!batteryIsOk(46, 70, 0.7));   

    // Test cases for invalid SOC
    assert(!batteryIsOk(25, 19, 0.7));  
    assert(!batteryIsOk(25, 81, 0.7));  

    // Test cases for invalid charge rate
    assert(!batteryIsOk(25, 70, 0.9));   

    // Test cases for invalid combinations
    assert(!batteryIsOk(-1, 19, 0.9));   
    assert(!batteryIsOk(46, 81, 0.9));  
    assert(!batteryIsOk(25, 70, 1.0));   

    // Edge cases
    assert(!batteryIsOk(0, 19, 0.7)); 
    assert(!batteryIsOk(45, 81, 0.8));
    assert(batteryIsOk(25, 70, 0.8));    
    assert(batteryIsOk(25, 70, 0.0)); 

    return 0;
}
