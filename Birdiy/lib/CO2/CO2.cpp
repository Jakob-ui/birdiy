#include "CO2.h"

SensirionI2cScd4x sensor;
bool setupRan = false;
uint16_t co2 = 0;
float temperature = 0.0f;
float humidity = 0.0f;
unsigned long lastRead = 0;
const unsigned long readInterval = 60000;

bool tryInitSensor(int retries)
{
    if (!setupRan)
    {
        for (int i = 0; i < retries; i++)
        {
            Wire.end();
            Wire.begin();
            Wire.setClock(100000);
            sensor.begin(Wire, 0x62);
            Serial.println("Try initialising CO2 Sensor " + String(i) + "x");

            uint16_t error = sensor.stopPeriodicMeasurement();
            if (error)
            {
                Serial.println("Error stopping measurement");
                continue;
            }

            error = sensor.startPeriodicMeasurement();
            if (error)
            {
                Serial.println("Error starting measurement");
                continue;
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
                    continue;
                }

                delay(500);
            }

            Serial.println("CO2 Sensor ist bereit und hat Daten!");
            setupRan = true;
            return true;
        }
        return false;
    }
    return true;
}

bool readMeasurementData()
{
    if (millis() - lastRead < readInterval)
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
        tryInitSensor(2);
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
            lastRead = millis();
            return true;
        }

        Serial.print("Measurement error: ");
        Serial.println(error);
        Wire.end();
        delay(50);
        tryInitSensor(3);
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
        return 0;
}

float getTemp()
{
    if (readMeasurementData())
    {
        return temperature;
    }
    else
        return 0;
}