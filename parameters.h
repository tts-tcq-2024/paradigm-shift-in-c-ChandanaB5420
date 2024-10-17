#define ERROR_TEMP "Temperature out of range!\n"
#define ERROR_SOC "State of Charge out of range!\n"
#define ERROR_CHARGE "Charge Rate out of range!\n"

#define WARNING_TEMP_LOW "Warning: Approaching lower temperature limit\n"
#define WARNING_TEMP_HIGH "Warning: Approaching upper temperature limit\n"

#define WARNING_SOC_LOW "Warning: Approaching discharge\n"
#define WARNING_SOC_HIGH "Warning: Approaching charge-peak\n"

#define WARNING_CHARGE_LOW "Warning: Approaching lower charge rate limit\n"
#define WARNING_CHARGE_HIGH "Warning: Approaching upper charge rate limit\n"

int checkParameter(float value, float min, float max, const char* errorMessage, const char* lowWarning, const char* highWarning);
