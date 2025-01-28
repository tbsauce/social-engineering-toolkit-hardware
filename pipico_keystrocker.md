- follow instructions on the https://github.com/dbisu/pico-ducky
- if u want to use normla code and not ducky script after all the instructions remove the 3 last files for the code and add this 
```python
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

# Type 'notepad' to open Notepad
layout.write("notepad")
keyboard.press(Keycode.ENTER)
keyboard.release_all()

time.sleep(1)  # Wait for Notepad to open

# Now type the message in Notepad
layout.write("Hello, World!")
keyboard.press(Keycode.ENTER)
keyboard.release_all()
```


- make sure the file is names code.py
