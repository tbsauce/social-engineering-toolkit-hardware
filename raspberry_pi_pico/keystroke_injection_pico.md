# Requirements

- **Raspberry Pi Pico**
- **Micro USB to USB-A adapter**
- *(Optional)* [Micro USB to USB-A dongle](https://thepihut.com/products/pico-dongle-lite)
- *(Optional)* Breadboard
- *(Optional)* Jumper wires

---

# Setup Guide

### Step 1: Prevent Accidental Execution

1. Connect **pin 1 (GP0) to pin 3 (GND)** on your Raspberry Pi Pico. 
    - This prevents the device from injecting payloads into your current machine.

### Step 2: Install CircuitPython

1. Download the appropriate `.uf2` firmware for your Raspberry Pi Pico:
   - [Raspberry Pi Pico](https://circuitpython.org/board/raspberry_pi_pico/)
   - [Raspberry Pi Pico W](https://circuitpython.org/board/raspberry_pi_pico_w/)
   - [Raspberry Pi Pico 2](https://circuitpython.org/board/raspberry_pi_pico2/)
   - [Raspberry Pi Pico 2W](https://circuitpython.org/board/raspberry_pi_pico2_w/)
2. Plug the Pico into your computer while holding the `BOOTSEL` button. A new drive named `RPI-RP2` should appear.
3. Copy the downloaded `.uf2` file onto the `RPI-RP2` drive. The Pico will reboot and reconnect as `CIRCUITPY`.

### Step 3: Install Required Libraries

1. Download the latest [Adafruit CircuitPython Bundle](https://github.com/adafruit/Adafruit_CircuitPython_Bundle/releases/).
2. Extract the ZIP file and navigate to the `lib` folder.
3. Copy the following folders and files to the `lib` folder on your Raspberry Pi Pico:
   - `adafruit_hid`
   - `adafruit_debouncer.mpy`
   - `adafruit_ticks.mpy`
   - `asyncio`
   - `adafruit_wsgi`

### Step 4: Install Pico-Ducky

1. Clone the [pico-ducky repository](https://github.com/dbisu/pico-ducky).
```
git clone https://github.com/dbisu/pico-ducky.git
```
2. Copy the following files to the root directory of your Raspberry Pi Pico:
   - `boot.py`
   - `ducky_in_python.py`
   - `code.py`
2. Create a file named `payload.dd` in the root directory.
3. Write a [Ducky Script](https://github.com/hak5/usbrubberducky-payloads) inside `payload.dd`.
4. If you prefer Python scripts instead of Ducky Script, modify the `code.py` file.

# Payloads

### Step 1: Set Up Reverse Shell Server

1. Follow the [Reverse Shell Server Setup Guide](https://github.com/tbsauce/social-engineering-hardware-toolkit/blob/main/server/reverseshell.md).
2. Generate a payload URL on the server.

### Step 2: Run payload

1. Run the reverse shell script to establish a connection.
    - [Ducky Script](https://github.com/tbsauce/social-engineering-hardware-toolkit/blob/main/raspberry_pi_pico/scripts/keystroke_duckyscript.dd)
    - [Python](https://github.com/tbsauce/social-engineering-hardware-toolkit/blob/main/raspberry_pi_pico/scripts/keystroke_pico.py)
