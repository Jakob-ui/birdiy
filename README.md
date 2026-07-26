# Bir*DIY*

This project aims to recreate the beautiful air quality monitor from [Birdie Design](https://birdie.design/) at a lower cost, while adding smart home integration via Zigbee.

This little bird actively monitors your room's CO2 levels and physically drops down when it's time to open a window, while simultaneously sending the exact measurements to your smart home hub.

## Features

*   **Visual Air Quality Indicator:** The bird automatically drops down when CO2 levels exceed 1000 ppm and returns to its upright position when the air is fresh again.
*   **Zigbee Integration:** Acts as a Zigbee End Device, publishing CO2 and temperature data to your smart home network every 2 minutes.
*   **Smart Error Handling:** The bird rotates to specific angles to visually indicate hardware issues (e.g., sensor failure or Zigbee connection loss).

## Required hardware

* [Seed Studio esp32-c6](https://www.seeedstudio.com/Seeed-Studio-XIAO-ESP32C6-p-5884.html)
* [28BYJ-48 4-Phase Stepper Motor with 5V Drive Board](https://www.amazon.de/Heevhas-28BYJ-48-Schrittmotor-Treiberplatine-Testmodul/dp/B0CW9ST4XM?__mk_de_DE=%C3%85M%C3%85%C5%BD%C3%95%C3%91&sr=8-1)
* [SCD41 Sensor Module](https://www.amazon.de/dp/B0FK53SJHB)
* and a button of some sort :)

## Wiring Diagramm

Picture coming soon

## Software & Installation

This project is built using [PlatformIO](https://platformio.org/). 
Make sure you have PlatformIO installed in VS Code. Clone this repository, open the folder in VS Code, and PlatformIO will automatically download the required libraries defined in the `platformio.ini` file (such as `AccelStepper` and the `Sensirion I2C SCD4x` library).

## 3D Printed Parts

*(Coming soon!)* 
All STL files required to build the bird and the housing will be available here: [Link to 3D files]()