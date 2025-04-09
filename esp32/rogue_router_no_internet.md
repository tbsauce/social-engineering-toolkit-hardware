# Requirements  

- ESP32  
- Micro USB to USB-A adapter  

---

# Setup Guide  

### Step 1: Install Arduino IDE  

1. Download and install [Arduino IDE](https://www.arduino.cc/en/software).  

### Step 2: Add ESP32 Board Support  

1. Open **Arduino IDE** and navigate to `File > Preferences`.  
2. In the `Additional Board Manager URLs` field, add the following URL:  
    - https://dl.espressif.com/dl/package_esp32_index.json

### Step 3: Install ESP32 Board Package  

1. Go to `Tools > Board > Boards Manager`.  
2. Search for `ESP32` and install the package by **Espressif Systems**.  

### Step 4: Configure the Board  

1. Open `Tools > Board` and select your **ESP32 model**.  
2. Go to `Tools > Port` and select the port associated with your ESP32.  
- If your board doesn't appear, you may need to install the **CP210x drivers** from [Silicon Labs](https://www.silabs.com/developers/usb-to-uart-bridge-vcp-drivers).  

### Step 5: Upload Code  

1. Add the ESP32 [code](https://github.com/tbsauce/social-engineering-hardware-toolkit/blob/main/esp32/scripts/device_logs.ino) to the Arduino IDE.  
2. Click **Upload** to flash the code to your ESP32.

### Step 6: Get Ouput

1. Open `Tools > Serial Monitor`.  
2. Select the baudrate of `115200`.    
