# Requirements

- Raspberry Pi Zero
- Micro USB to USB-A adapter
- Reverse Shell Server
- (Optional) [Micro USB to USB-A dongle](https://52pi.com/collections/raspberry-pi-zero/products/52pi-usb-dongle-for-raspberry-pi-zero-zero-w)

---

# Setup Guide

### Step 1: Install Raspberry Pi OS
1. Download and install [Raspberry Pi Imager](https://www.raspberrypi.com/software/).
2. Use Raspberry Pi Imager to flash the OS onto an SD card.
3. Insert the SD card into the Raspberry Pi Zero.

### Step 2: Connect and Access the Pi
1. Find the Raspberry Pi's IP address by checking your router's domain settings.
2. SSH into the device:
   ```
   ssh pi@<Raspberry_Pi_IP>
   ```

### Step 3: Install Dependencies
1. Update package lists and install required dependencies:
   ```
   sudo apt-get update
   sudo apt-get install -y git vim python3-pip python3-venv
   ```

### Step 4: Set Up USB Gadget Mode
1. Clone the required repository:
   ```
   git clone https://github.com/thewh1teagle/zero-hid
   ```
2. Navigate to the `usb_gadget` directory and run the installer:
   ```
   cd zero-hid/usb_gadget
   sudo ./installer
   ```
3. Add `sudo` to the file line added by the script for proper execution.

### Step 5: Create a Virtual Environment
1. Set up a Python virtual environment and install `zero-hid`:
   ```
   python3 -m venv ~/venv
   source ~/venv/bin/activate
   pip3 install zero-hid
   sudo reboot
   ```

---

# Reverse Shell Attack

### Step 1: Set Up Reverse Shell Server
1. Follow the [Reverse Shell Server Setup Guide](https://github.com/tbsauce/social-engineering-hardware-toolkit/blob/main/server/reverseshell.md).
2. Generate a payload link on the server.

### Step 2: Initialize rc.local
1. Set up the `rc.local` file:
   ```
   sudo bash -c 'echo "#!/bin/bash" > /etc/rc.local'
   sudo bash -c 'echo "exit 0" >> /etc/rc.local'
   sudo chmod +x /etc/rc.local
   sudo systemctl daemon-reload
   sudo systemctl enable rc-local
   sudo systemctl start rc-local
   ```

### Step 3: Run Payload

1. Run the reverse shell [script](https://github.com/tbsauce/social-engineering-hardware-toolkit/blob/main/raspberry_pi_zero/scripts/keystroke_zero.py) to establish a connection.

### Step 4: Make payload run on boot

1. Finish after
