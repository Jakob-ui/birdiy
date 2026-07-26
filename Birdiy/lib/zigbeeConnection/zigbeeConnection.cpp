#include "zigbeeConnection.h"

#define CO2_SENSOR_ENDPOINT 1
#define TEMP_SENSOR_ENDPOINT 2

ZigbeeCarbonDioxideSensor CO2Sensor(CO2_SENSOR_ENDPOINT);
ZigbeeTempSensor TempSensor(TEMP_SENSOR_ENDPOINT);
bool zigbeSetupRan = false;

bool initZigbee()
{
    esp_zb_cfg_t zigbeeConfig = ZIGBEE_DEFAULT_ED_CONFIG();
    zigbeeConfig.nwk_cfg.zed_cfg.keep_alive = 6000000;

    Zigbee.setTimeout(90000);
    Zigbee.setScanDuration(3);

    if (!zigbeSetupRan)
    {
        Serial.println("Try initialising Sensor");
        CO2Sensor.setManufacturerAndModel("Birdiy", "Birdiy_Air_Monitor");
        CO2Sensor.setMinMaxValue(0, 5000);
        CO2Sensor.setDefaultValue(0);

        TempSensor.setMinMaxValue(-100, 100);
        TempSensor.setDefaultValue(0);

        bool co2Ok = Zigbee.addEndpoint(&CO2Sensor);
        delay(50);
        bool tempOk = Zigbee.addEndpoint(&TempSensor);
        delay(50);
        if (!co2Ok || !tempOk)
        {
            Serial.println("Endpoint registration failed");
            return false;
        }
        Serial.println("Starte Zigbee...");
        zigbeSetupRan = true;
        if (!Zigbee.begin(&zigbeeConfig, false))
        {
            Serial.println("Zigbee konnte nicht gestartet werden!");
            return false;
        }
        Serial.println("Zigbee läuft! (Pairing)...");
        return true;
    }
    return true;
}

void publishData(uint16_t co2, float temp)
{
    if (!Zigbee.connected())
        return;

    CO2Sensor.setCarbonDioxide(co2);
    CO2Sensor.report();

    TempSensor.setTemperature(temp);
    TempSensor.reportTemperature();
}
