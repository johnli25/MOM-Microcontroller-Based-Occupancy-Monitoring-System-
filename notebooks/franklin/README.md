# Franklin's Lab Notebook
## Table of Contents
- [2022-09-13: Post-Meeting Notes](README.md#2022-09-13-post-meeting-notes)
- [2022-09-14: Parts Research](README.md#2022-09-14-parts-research)
- [2022-09-14: Quick note about our traffic monitoring method](README.md#2022-09-14-quick-note-about-our-traffic-monitoring-method)

## 2022-09-13: Post-Meeting Notes 
We just talked with our mentor TA about our initial block diagram, high-level and subsystem requirements, and about some of the parts that we are planning on using for the project. She had some great suggestions for us that we think would benefit our project, especially since she had a very similar project when she took the course. \
Here's the list of suggestions that she mentioned:
- Add the subcomponents for the cloud server in the block diagram.
- Put required voltages at each power line in the block diagram.
- Expand the high-level requirement involving power to include 24-hour availability while the board is plugged in.
- Don't bother making your own Wi-Fi module; just buy one since the budget is $150.

## 2022-09-14: Hardware Parts Research
Now that we kind of have our project idea fleshed out, we need to create an initial list of parts to create our prototype. All research will be done with the fact that the budget can only be used on Amazon, Digi-Key, and Mouser. Below is a list of all parts and components, sorted into subsystems, I have researched that should be purchased from the aforementioned sites, along with my thought process behind picking those parts.
- **Control Unit and Radio Scanner Suite**
  - [ESP32-S3-MINI-1](https://www.espressif.com/sites/default/files/documentation/esp32-s3-wroom-2_datasheet_en.pdf)
    - It's no question that the ESP32 family has a good track record with IoT projects. It's very inexpensive and it has a decently-sized community around it to provide support and answers should someone need it.
    - It's also approved and supported by AWS, which is a huge plus should we need help in the programming side of the project.
    - To make this easier for us to quickly build the prototype, we need an ESP32 SoC that has an integrated Bluetooth module as well as a Wi-Fi module to quickly integrate the ***Radio Scanner Suite***. This means we need to get an ESP32 with antennas.
    - As of right now, we aren't planning on integrating the 5 GHz frequency into the ***Radio Scanner Suite*** due to time constraints. The main issue is that if we were to also scan 5 GHz, we would need to purchase a separate Wi-Fi module and write the drivers for it, which would take too much time to integrate.
      - However, the ESP32 that we are getting has native USB support, so if we have the time to integrate the device drivers for the 5 GHz band, we would be able to do so.
      - On the bright side, Espressif is currently developing the ESP32-C5, which will have dual-band and Bluetooth LE capability. This would be the easiest upgrade to scan all Wi-Fi and Bluetooth frequencies, but the release date for this SoC is not currently known (as of 2022-09-14).
  - [USB-to-UART Bridge](http://esp32.net/usb-uart/)
    - We need a USB-to-UART bridge IC to actually program our ESP32. The link goes to a web page with a list of USB-to-UART ICs used in other ESP32 development boards, so we know picking one of those should work.
    - We are also planning on powering the board through USB when it is plugged in.
- **Power Supply**
  - LiPo battery
    - 18650 batteries are probably the better choice over choosing a LiPo pack when it comes to the price-to-capacity ratio. However, the ease and form factor of LiPo batteries are more suitable for our design since it's easier to tuck and keep hidden away.
  - [AP2112 Voltage Regulator](https://www.digikey.com/en/products/detail/diodes-incorporated/AP2112M-3-3TRG1/5305555) (3.3V)
    - The ESP32 series of SoCs all use 3.3 volts as their operating voltage. Since all USB types generally operating at or above 5 volts, we need to drop the voltage down. The AP2112 is a tried and true voltage regulator for 3.3 volts, so we'll use it in our design, too.
  - [MCP73831T Battery Charge Controller](https://www.digikey.com/en/products/detail/microchip-technology/MCP73831T-2DCI-OT/1979804)
    - It's very important to keep the battery from overcharging. This battery charge controller appears to be very popular with other boards that are based on ESP32.

## 2022-09-14: Quick note about our traffic monitoring method
So when our team initially talked about this idea, we were certain that we would need to purchase a separate Wi-Fi module to scan both bands of the 802.11 spectrum (2.4 GHz and 5 GHz). However, after a bit of research, and because of a hardware limitation of the ESP32 platform (as of 2022-09-14), we found that only scanning the 2.4 GHz frequency may be sufficient. This is because most Wi-Fi devices send probe requests after a certain event or a certain amount of time, which is dependent on the operating system used by the probing device. These probe requests are sent on both the 2.4 GHz and 5 GHz bands, since not all Wi-Fi networks utilize the 5 GHz band. 

The discovery phase of a Wi-Fi connection can be broken down to the following steps:
1. Wi-Fi client sends a (periodic) probe request to its general viscinity.
2. All Wi-Fi access points (APs) that have read the probe request frame generate and send a probe response to the client (unless the AP is configured otherwise).
3. Wi-Fi client received the probe response from the responding APs to generate the list of available Wi-Fi connections.  
  
Here are some good references to take a look at to learn more:
- [What are Passive and Active Scanning? - Wi-Fi Alliance](https://www.wi-fi.org/knowledge-center/faq/what-are-passive-and-active-scanning)
- [802.11 MAC Series – Basics of MAC Architecture – Part 3 of 3 - CWNP](https://www.cwnp.com/802.11-mac-series-ndash-basics-mac-architecture-ndash-part-3/)
- [Oliveira et al. 2019](https://ieeexplore.ieee.org/stamp/stamp.jsp?arnumber=8747391)
