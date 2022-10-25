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
- NOTE: If the IDE throws an error saying it couldn't get the FQDN, you will need to select the board from the topbar: `Tools->Port`

## MAC Address Mapping
In addition, we have a list of MAC address prefixes (also known as Organizationally Unique Identifiers, or OUIs) that belong to Aruba Networks, the company who manufactures the access points used for UIUC networks. To get this list, we used the database from the official IEEE database of OUIs and put it in this repo [here as oui.csv, which is up to date as of 2022-10-25](MOM/oui.csv). If you would like to download it yourselfwhich can be downloaded as a CSV [here](https://standards-oui.ieee.org/oui/oui.csv)). The list of Aruba OUIs was scraped using the Python3 script [get_aruba_ouis.py](MOM/get_aruba_ouis.py). We can use these OUIs to prevent overcounting should our microcontrollers read traffic from the university access points instead of from student devices.