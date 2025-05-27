# Requirements  

- ESP8266  
- Micro USB to USB-A adapter  

---

# Setup Guide  

### Step 1: Install Arduino IDE  

1. Download and install [Arduino IDE](https://www.arduino.cc/en/software).  

### Step 2: Add ESP8266 Board Support  

1. Open **Arduino IDE** and navigate to `File > Preferences`.  
2. In the `Additional Board Manager URLs` field, add the following URL:  
    - http://arduino.esp8266.com/stable/package_esp8266com_index.json

### Step 3: Install ESP8266 Board Package  

1. Go to `Tools > Board > Boards Manager`.  
2. Search for `ESP8266` and install the package by **Espressif Systems**.  

### Step 4: Configure the Board  

1. Open `Tools > Board` and select your **ESP8266 model**.  
2. Go to `Tools > Port` and select the port associated with your ESP8266.  
- If your board doesn't appear, you may need to install the **CP210x drivers** from [Silicon Labs](https://www.silabs.com/developers/usb-to-uart-bridge-vcp-drivers).  

### Step 5: Upload Code  

1. Add the ESP8266 [code](https://github.com/tbsauce/social-engineering-hardware-toolkit/blob/main/esp8266/scripts/device_logs.ino) to the Arduino IDE.  
2. Click **Upload** to flash the code to your ESP8266.

### Step 6: View Ouput

#### Option 1:
1. Open `Tools > Serial Monitor`.  
2. Select the baudrate of `115200`.    

#### Option 2:
1. Connect to the Wi-Fi network created by the device.
2. Open a web browser and go to `http://192.168.4.1`.
