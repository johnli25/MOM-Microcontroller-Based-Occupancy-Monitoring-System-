# Arduino Code
This folder contains Arduino code for the ESP32-S3 microcontroller. This includes all code used for testing, verification, and project code.
## Setting up the Arduino IDE
- Install the Arduino IDE [from the Arduino website](https://www.arduino.cc/en/software).
- If the `hardware/espressif/esp32` folder is empty, run the below command:
  - `git submodule update --init --recursive`
- Run `get.exe` in the `hardware/espressif/esp32` folder.
- Plug in the board, open the Arduino IDE, and open the IDE preferences (from the topbar: `File->Preferences`).
- Change the Sketchbook location to this folder.
- Copy and paste the below line to the `Additional boards manager URLs`:
  - `https://arduino.esp8266.com/stable/package_esp8266com_index.json,https://dl.espressif.com/dl/package_esp32_index.json`
- Restart the IDE. You should now be able to communicate with the board.
- NOTE: If the IDE throws an error saying it couldn't get the FQDN, you will need to select the board from the topbar: `Tools->Board->ESP32 Arduino (in Sketchbook)