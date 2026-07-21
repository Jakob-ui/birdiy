#include <CO2.h>
#include <Zigbee.h>

ZigbeeCarbonDioxideSensor CO2Sensor(1);
SensirionI2cScd4x sensor;
bool setupRan = false;
uint16_t co2 = 0;
float temperature = 0.0f;
float humidity = 0.0f;
unsigned long lastCo2Read = 0;
const unsigned long co2ReadInterval = 5000;

bool initSensor(){
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
}

bool initZigbee(){
    if (!setupRan)
    {
        Serial.println("Try initialising Sensor");
        CO2Sensor.setManufacturerAndModel("Birdiy", "Birdiy-CO2-Sensor");

        CO2Sensor.setMinMaxValue(0, 5000);
        CO2Sensor.setDefaultValue(0);
        Zigbee.addEndpoint(&CO2Sensor);
        Serial.println("Starte Zigbee...");
        if (!Zigbee.begin(ZIGBEE_END_DEVICE))
        {
            Serial.println("Zigbee konnte nicht gestartet werden!");
            ESP.restart();
            return false;
        }
        Serial.println("Zigbee läuft! (Pairing)...");
        setupRan = true;
    }
    return true;
}

int getCO2()
{
    if (millis() - lastCo2Read < co2ReadInterval)
    {
        return co2;
    }

    bool dataReady = false;

    uint16_t error = sensor.getDataReadyStatus(dataReady);
    if (error)
    {
        Serial.print("CO2 sensor I2C error: ");
        Serial.println(error);
        Wire.end();
        delay(50);
        initSensor();
        CO2Sensor.setCarbonDioxide(co2);
        return 0;
    }

    if (dataReady)
    {
        error = sensor.readMeasurement(co2, temperature, humidity);
        if (!error)
        {
            Serial.print("CO2: ");
            Serial.println(co2);
            CO2Sensor.setCarbonDioxide(co2);
            lastCo2Read = millis();
            return co2;
        }

        Serial.print("CO2 measurement error: ");
        Serial.println(error);
        Wire.end();
        delay(50);
        initSensor();
    }
    CO2Sensor.setCarbonDioxide(co2);
    return 0;
}