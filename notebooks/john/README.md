# John's Lab Notebook
## Table of Contents
---
- [2022-09-13: Meeting Notes](README.md#2022-09-13-meeting-notes)
- [2022-09-14: Hardware Components Research](README.md#2022-09-14-Hardware-Components-research)
- [2022-09-16: Meeting with Jack Kilby](README.md#2022-09-14-Meeting-With-Jack-Kilby)

## 2022-09-13: Meeting-Notes

Discussed with TA regarding our project proposal and our system and subsystem designs. Some things and suggestions to take note of:
- Add subcomponents for the cloud server for block diagram.
- Label necessary voltages at each power line for block diagram.
- Expand high-level requirement involving power to include 24-hour availability while the board is plugged in.
- Don't bother making your own Wi-Fi module; just buy one since budget is $150.

## 2022-09-14: Hardware-Components-research

Since we have a limited $150 budget, all of our purchases will most likely be limited to Amazon, Digikey, and Mouser. Parts we are leaning toward using:

**Control Unit and Radio Scanner Suite**
  - [ESP32-S3-MINI-1](https://www.espressif.com/sites/default/files/documentation/esp32-s3-wroom-2_datasheet_en.pdf)
- This ESP32 is versatile, not super expensive, offers various functionalities, and is used in many IoT projects, both hobbyist and professional.
- Furthermore, this microcontroller has been proven to be compatible with AWS. 
- Currently, we aren't planning on integrating the 5 GHz frequency into the Radio Scanner Suite due to time constraints. The primary issue is that if we were to also scan 5 GHz, we would need to purchase a separate Wi-Fi module and write the drivers for it, which would take too much time and effort to integrate. So we plan on settling for 2.4 GHz frequency for our Wi-Fi module for now
- [USB-to-UART Bridge](http://esp32.net/usb-uart/): We need to make use of this bridge and attach it to our ESP-32. 

**Power Supply**
- LiPo battery
- 18650 batteries are probably the better choice over choosing a LiPo pack when it comes to the price-to-capacity ratio. However, the ease and form factor of LiPo batteries are more suitable for our design since it's easier to tuck and keep hidden away.
- [AP2112 Voltage Regulator](https://www.digikey.com/en/products/detail/diodes-incorporated/AP2112M-3-3TRG1/5305555) (3.3V)
- The ESP32 series of SoCs all use 3.3 volts as their operating voltage. Since all USB types generally operating at or above 5 volts, we need to drop the voltage down. The AP2112 is a tried and true voltage regulator for 3.3 volts, so we'll use it in our design, too.
- [MCP73831T Battery Charge Controller](https://www.digikey.com/en/products/detail/microchip-technology/MCP73831T-2DCI-OT/1979804)
- It's very important to keep the battery from overcharging. This battery charge controller appears to be very popular with other boards that are based on ESP32.
