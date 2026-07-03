#include <CO2.h>

SensirionI2cScd4x sensor;

bool initSensor(){
    Wire.begin();
    sensor.begin(Wire, 0x62);
    uint16_t error = sensor.stopPeriodicMeasurement();
    if (error)
    {
        Serial.println("Error stopping measurement");
        return false;
    } else {
        return true;
    }
}

int getCO2(){
    uint16_t co2 = 0;
    float temperature = 0.0f;
    float humidity = 0.0f;
    bool dataReady = false;

    uint16_t error = sensor.startPeriodicMeasurement();
    if (error)
    {
        Serial.println("Error starting measurement");
        return 0;
    }
    Serial.println("Waiting for first measurement...");
    error = sensor.getDataReadyStatus(dataReady);
    if (error)
    {
        Serial.println("Error checking data ready status");
        return 0;
    }
    else if (dataReady)
    {
        error = sensor.readMeasurement(co2, temperature, humidity);
        if (!error)
        {
            Serial.print("CO2: ");
            Serial.println(co2);
            return co2;
        } else {
            return 0;
        }
    } else {
        return 0;
    }
}