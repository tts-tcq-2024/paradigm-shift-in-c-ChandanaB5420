extern float tolerance;

void printWarningMessage(const char* message);

void checkLowThreshold(float value, float min, float max, const char* lowWarningMessage);
void checkHighThreshold(float value, float max, const char* highWarningMessage);
