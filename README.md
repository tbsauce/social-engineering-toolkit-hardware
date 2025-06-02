# Social Engineering Toolkit Hardware 

Welcome to the **Social Engineering Toolkit Hardware**, a comprehensive resource for documenting penetration testing tools, payloads, and attack techniques related to physical social engineering threats. This repository explores hardware-based attack vectors such as keyloggers, rogue routers, and other physical intrusion methods.

## Purpose
The goal of this toolkit is to provide an open and accessible platform for security researchers, ethical hackers, and cybersecurity enthusiasts to:
- Understand and explore various physical attack vectors.
- Simulate real-world scenarios to identify security vulnerabilities.
- Develop practical defenses against hardware-based social engineering attacks.

By experimenting with these tools and techniques, users can enhance their security awareness and improve their ability to defend against physical threats.

## Disclaimer
This toolkit is intended for educational and ethical testing purposes only. Unauthorized use of these tools for malicious activities is strictly prohibited.

---

# Supported Hardware
The toolkit supports various hardware devices, each capable of executing different attack techniques:

- [Raspberry Pi Pico](https://github.com/tbsauce/social-engineering-hardware-toolkit/tree/main/raspberry_pi_pico) 
- [Raspberry Pi Zero](https://github.com/tbsauce/social-engineering-hardware-toolkit/tree/main/raspberry_pi_zero)
- [Raspberry Pi 5](https://github.com/tbsauce/social-engineering-hardware-toolkit/tree/main/raspberry_pi_5) 
- [ESP32](https://github.com/tbsauce/social-engineering-hardware-toolkit/tree/main/esp32) 

---

# Attack Techniques
Below are the primary attack methodologies supported by this toolkit:

## Keystroke Injection
This technique uses hardware to simulate a keyboard or mouse, allowing for automated execution of malicious payloads, such as reverse shells, to infiltrate a target machine.
- **Hardware:**
  - [Raspberry Pi Pico](https://github.com/tbsauce/social-engineering-hardware-toolkit/blob/main/raspberry_pi_pico/keystroke_injection_pico.md)
  - [Raspberry Pi Zero](https://github.com/tbsauce/social-engineering-hardware-toolkit/blob/main/raspberry_pi_zero/keystroke_injection_zero.md)

## Evil Twin Attack
This attack creates a rogue Wi-Fi access point that mimics a legitimate network. When users connect, their credentials are intercepted and stored. The stolen passwords can later be cracked using tools like Hashcat.

- **Hardware:**
  - [Raspberry Pi 5](https://github.com/tbsauce/social-engineering-hardware-toolkit/blob/main/raspberry_pi_5/evil_twin.md)

## Rogue Router (With Internet Access)
This attack involves setting up a rogue router that users unknowingly connect to. The attacker can monitor network traffic, analyze connection statistics, and gather intelligence on connected devices.

- **Hardware:**
  - [Raspberry Pi 5](https://github.com/tbsauce/social-engineering-hardware-toolkit/blob/main/raspberry_pi_5/rougue_router.md)

## Rogue Router (Without Internet Access)
This attack sets up a rogue router (public or private) for monitoring connection attempts. It helps collect important data, such as the number of devices attempting to connect, without providing actual internet access.

- **Hardware:**
  - [ESP32](https://github.com/tbsauce/social-engineering-hardware-toolkit/blob/main/esp32/rogue_router_no_internet.md)

## Deauthentication Attack
This technique forcefully disconnects users from Wi-Fi access points, causing network disruption and opening opportunities for further exploitation.

- **Hardware:**
  - [ESP32](https://github.com/tbsauce/social-engineering-hardware-toolkit/blob/main/esp32/wifi_deauth_attack.md)
---

# Raspberry Pi Conf

## Connction to WPA2-Enterprise on Raspberry Pi

### Step 1: Install Required Packages
```
sudo apt update
sudo apt install wpasupplicant wireless-tools
sudo rfkill unblock wifi
```

### Step 2: Configure `wpa_supplicant`

1. Edit the configuration file:

```
sudo vim /etc/wpa_supplicant/wpa_supplicant.conf
```

2. Add the following and replace placeholders with your actual credentials:

```
ctrl_interface=DIR=/var/run/wpa_supplicant GROUP=netdev
update_config=1
country=US  # Replace with your 2-letter country code

network={
    ssid="eduroam"
    key_mgmt=WPA-EAP
    eap=PEAP
    identity="your_username@your_university.edu"
    password="your_password"
    phase1="peaplabel=0"
    phase2="auth=MSCHAPV2"
}
```

### Step 3: Connect to eduroam

```
sudo ip addr flush dev wlan0
sudo pkill wpa_supplicant
sudo wpa_supplicant -B -i wlan0 -c /etc/wpa_supplicant/wpa_supplicant.conf
sudo dhclient -v wlan0
```

## SSH via ethernet cable on Raspberry Pi 5

### Step 1: Check if `dhcpcd` is Installed

```
which dhcpcd
# or
dhcpcd --version
```

### Step 2: Install `dhcpcd` (If Missing)

```
sudo apt update && sudo apt install dhcpcd5 -y
```


### Step 3: Enable and Start `dhcpcd`

```
sudo systemctl enable dhcpcd
sudo systemctl start dhcpcd
```

Check status:

```
sudo systemctl status dhcpcd
```

### Step 4: Apply Static IP Configuration

1. Edit the configuration file:

```
sudo vim /etc/dhcpcd.conf
```

2. Add the following (for a direct Ethernet connection):

```ini
interface eth0
static ip_address=192.168.1.2/24
static routers=192.168.1.1
static domain_name_servers=8.8.8.8
```

3. Restart the service:

```
sudo systemctl restart dhcpcd
```

### Step 5: Verify the IP Address

```
ip a show eth0
```

---

### Step 6: Configure Your Laptop’s Ethernet Port

* **Linux:**

```
sudo ip addr add 192.168.1.1/24 dev eth0
```

* **Windows:**

  1. Go to Control Panel → Network and Sharing Center → Change adapter settings
  2. Right-click Ethernet → Properties → IPv4 → Use the following IP address:

     * IP: `192.168.1.1`
     * Subnet mask: `255.255.255.0`
     * Gateway: (leave blank)

---

### Step 7: Test the Connection

1. SSH into the Raspberry Pi:

```
ssh sauce@192.168.1.2
```



