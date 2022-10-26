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

## MAC Address Filtering
In addition, we have a list of MAC address prefixes (also known as Organizationally Unique Identifiers, or OUIs) that belong to Aruba Networks, the company who manufactures the access points used for UIUC networks, and other devices which we believe are not student devices. We use this list to ignore MAC addresses that are a part of the building and improve accuracy of our readings. To get this list, we used the [https://maclookup.app](https://maclookup.app) database, which is derived from the official IEEE database of OUIs [here](https://standards-oui.ieee.org/oui/oui.csv), and put it in this repo [here](MOM/mac-vendors-export-2022-10-25.csv). The repo's snapshot of the database is up to date as of 2022-10-25. 

The list of OUIs can be scraped using the Python3 script [get_ouis.py](MOM/oui_lists/get_ouis.py). The script is used to find all OUIs of a specified company. The script has an argument of the company to find OUIs for. It is case insensitive as it will force all names to lowercase. An example usage is `python3 get_ouis.py aruba` to search for Aruba in the database. It will then output 2 files, one where it directly lists the OUIs in formatted hexadecimal form (`<COMPANY_NAME>-ouis.txt`), and one where the OUI is converted to unsigned integers (`<COMPANY_NAME>-ouis-uints.txt`).