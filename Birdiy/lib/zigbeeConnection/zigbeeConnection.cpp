#include "zigbeeConnection.h"

ZigbeeCarbonDioxideSensor CO2Sensor(1);
ZigbeeTempSensor TempSensor(2);
bool zigbeSetupRan = false;

bool initZigbee()
{
    Zigbee.setTimeout(90000);
    Zigbee.setScanDuration(3);
    if (!zigbeSetupRan)
    {
        Serial.println("Try initialising Sensor");
        //TempSensor.setManufacturerAndModel("Birdiy", "Birdiy_Temp_Sensor");
        //TempSensor.setMinMaxValue(-100, 100);
        //TempSensor.setDefaultValue(0);
        CO2Sensor.setManufacturerAndModel("Birdiy", "Birdiy_CO2_Sensor");
        CO2Sensor.setMinMaxValue(0, 5000);
        CO2Sensor.setDefaultValue(0);

        bool co2Ok = Zigbee.addEndpoint(&CO2Sensor);
        //bool tempOk = Zigbee.addEndpoint(&TempSensor);
        if (!co2Ok)
        {
            Serial.println("Endpoint registration failed");
            return false;
        }
        Serial.println("Starte Zigbee...");
        zigbeSetupRan = true;
        if (!Zigbee.begin(ZIGBEE_END_DEVICE))
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

    //TempSensor.setTemperature(temp);
    //TempSensor.reportTemperature();
}