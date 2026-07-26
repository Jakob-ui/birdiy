#include "CO2.h"

SensirionI2cScd4x sensor;
bool setupRan = false;
uint16_t co2 = 0;
float temperature = 0.0f;
float humidity = 0.0f;
unsigned long lastCo2Read = 0;
const unsigned long co2ReadInterval = 5000;

unsigned long lastTempRead = 0;
const unsigned long tempReadInterval = 5000;

bool initSensor()
{
    Wire.end();
    Wire.begin();
    Wire.setClock(100000);
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

    bool dataReady = false;
    while (!dataReady)
    {
        error = sensor.getDataReadyStatus(dataReady);
        if (error)
        {
            Serial.print("Fehler beim Abfragen des Status: ");
            Serial.println(error);
            return false;
        }

        delay(500);
    }

    Serial.println("CO2 Sensor ist bereit und hat Daten!");
    return true;
}

bool readMeasurementData()
{
    if (millis() - lastCo2Read < co2ReadInterval)
    {
        return true;
    }

    bool dataReady = false;

    uint16_t error = sensor.getDataReadyStatus(dataReady);
    if (error)
    {
        Serial.print("Sensor I2C error: ");
        Serial.println(error);
        Wire.end();
        delay(50);
        initSensor();
        return false;
    }

    if (dataReady)
    {
        error = sensor.readMeasurement(co2, temperature, humidity);
        if (!error)
        {
            Serial.print("CO2: ");
            Serial.print(co2);
            Serial.print(" ppm, Temp: ");
            Serial.println(temperature);
            lastCo2Read = millis();
            return true;
        }

        Serial.print("Measurement error: ");
        Serial.println(error);
        Wire.end();
        delay(50);
        initSensor();
        return false;
    }
    return false;
}

uint16_t getCO2()
{
    if (readMeasurementData())
    {
        return co2;
    }
    else
        return 1;
}

float getTemp()
{
    if (readMeasurementData())
    {
        return temperature;
    }
    else
        return 1;
}