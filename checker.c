#include <stdio.h>
#include <assert.h>

// Helper function to check the range and print error message
int checkRange(float value, float min, float max, const char *message) {
    if (value < min || value > max) {
        printf("%s\n", message);
        return 0;
    }
    return 1;
}

// Main function to check battery status
int batteryIsOk(float temperature, float soc, float chargeRate) {
    // Consolidate all checks into a single return statement
    return checkRange(temperature, 0, 45, "Temperature out of range!") &&
           checkRange(soc, 20, 80, "State of Charge out of range!") &&
           checkRange(chargeRate, -1, 0.8, "Charge Rate out of range!");
}

int main() {
    assert(batteryIsOk(25, 70, 0.7));  // Should pass: All values are within range
    assert(!batteryIsOk(50, 85, 0));   // Should fail: Temperature and State of Charge out of range

    return 0;
}
