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
    }

    error = sensor.startPeriodicMeasurement();
    if (error)
    {
        Serial.println("Error starting measurement");
        return false;
    }

    Serial.println("CO2 Sensor started! Waiting 5s for first reading...");
    return true;
}

int getCO2()
{
    uint16_t co2 = 0;
    float temperature = 0.0f;
    float humidity = 0.0f;
    bool dataReady = false;

    uint16_t error = sensor.getDataReadyStatus(dataReady);
    if (error)
    {
        return 0;
    }

    if (dataReady)
    {
        error = sensor.readMeasurement(co2, temperature, humidity);
        if (!error)
        {
            Serial.print("CO2: ");
            Serial.println(co2);
            return co2;
        }
    }
    return 0;
}