#include <stdio.h>
#include <assert.h>

// Function declaration
int batteryIsOk(float temperature, float soc, float chargeRate);

// Test cases for valid scenarios
void testValidCases() {
    assert(batteryIsOk(25, 70, 0.7));
    assert(batteryIsOk(0, 20, 0.0));
    assert(batteryIsOk(45, 80, 0.8));
}

// Test cases for invalid temperature
void testInvalidTemperature() {
    assert(!batteryIsOk(-1, 70, 0.7));
    assert(!batteryIsOk(46, 70, 0.7));
}

// Test cases for invalid SoC
void testInvalidSoC() {
    assert(!batteryIsOk(25, 19, 0.7));
    assert(!batteryIsOk(25, 81, 0.7));
}

// Test cases for invalid charge rate
void testInvalidChargeRate() {
    assert(!batteryIsOk(25, 70, 0.9));
}

// Test cases for combinations of invalid values
void testInvalidCombinations() {
    assert(!batteryIsOk(-1, 19, 0.9));
    assert(!batteryIsOk(46, 81, 0.9));
    assert(!batteryIsOk(25, 70, 1.0));
}

// Edge cases
void testEdgeCases() {
    assert(!batteryIsOk(0, 19, 0.7));
    assert(!batteryIsOk(45, 81, 0.8));
    assert(batteryIsOk(25, 70, 0.8));
    assert(batteryIsOk(25, 70, 0.0));
}

// Test Temperature Warnings
void testTemperatureWarnings() {
    assert(batteryIsOk(1.0, 50, 0.5));  // Should trigger lower temperature warning
    assert(batteryIsOk(44.0, 50, 0.5));  // Should trigger upper temperature warning
}

// Test SoC Warnings
void testSoCWarrnings() {
    assert(batteryIsOk(25, 21.0, 0.5));  // Should trigger lower SoC warning
    assert(batteryIsOk(25, 79.0, 0.5));  // Should trigger upper SoC warning
}

// Test Charge Rate Warnings
void testChargeRateWarnings() {
    assert(batteryIsOk(25, 50, 0.02));  // Should trigger lower charge rate warning
    assert(batteryIsOk(25, 50, 0.78));  // Should trigger upper charge rate warning
}

// Function to run all tests
void runTests() {
    testValidCases();
    testInvalidTemperature();
    testInvalidSoC();
    testInvalidChargeRate();
    testInvalidCombinations();
    testEdgeCases();
    testTemperatureWarnings();
    testSoCWarrnings();
    testChargeRateWarnings();
}
