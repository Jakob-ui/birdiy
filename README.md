# Bir*DIY*

This project aims to recreate the beautiful air quality monitor from [Birdie Design](https://birdie.design/) at a lower cost, while adding smart home integration via Zigbee.

This little bird actively monitors your room's CO2 levels and physically drops down when it's time to open a window, while simultaneously sending the exact measurements to your smart home hub.

## Features

*   **Visual Air Quality Indicator:** The bird automatically drops down when CO2 levels exceed 1000 ppm and returns to its upright position when the air is fresh again.
*   **Zigbee Integration:** Acts as a Zigbee End Device, publishing CO2 and temperature data to your smart home network every 2 minutes.
*   **Smart Error Handling:** The bird rotates to specific angles to visually indicate hardware issues (e.g., sensor failure or Zigbee connection loss).

## Required Hardware

| Component | Notes |
|---|---|
| [Seeed Studio XIAO ESP32-C6](https://www.seeedstudio.com/Seeed-Studio-XIAO-ESP32C6-p-5884.html) | Microcontroller with Zigbee support |
| [28BYJ-48 4-Phase Stepper Motor + 5V driver board](https://www.amazon.de/Heevhas-28BYJ-48-Schrittmotor-Treiberplatine-Testmodul/dp/B0CW9ST4XM) | Drives the bird's tilting motion |
| [SCD41 Sensor Module](https://www.amazon.de/dp/B0FK53SJHB) | CO₂, temperature & humidity sensor |
| A button of some sort | e.g. for manual reset/calibration :) |

## Software & Installation

This project is built with [PlatformIO](https://platformio.org/).

1. Install the [PlatformIO extension](https://platformio.org/install/ide?install=vscode) for VS Code.
2. Clone this repository:
   ```bash
   https://github.com/Jakob-ui/birdiy.git
   ```
3. Open the folder in VS Code — PlatformIO will automatically download the required libraries listed in `platformio.ini`, including:
   - [`AccelStepper`](https://www.arduino.cc/reference/en/libraries/accelstepper/)
   - [`Sensirion I2C SCD4x`](https://github.com/Sensirion/arduino-i2c-scd4x)
4. Build and flash the firmware to your ESP32-C6 via PlatformIO.

## 3D Printed Parts

*(Coming soon!)* 
All STL files required to build the bird and the housing will be available here: [Link to 3D files]()