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

- [Raspberry Pi Pico](https://mauser.pt/catalog/product_info.php?products_id=096-9421) 
- [Raspberry Pi Zero](https://mauser.pt/catalog/product_info.php?products_id=095-1561)
- [Raspberry Pi 5](https://mauser.pt/catalog/product_info.php?products_id=095-5008) 
- [ESP32](https://mauser.pt/catalog/product_info.php?products_id=096-7620) 
- [ESP8266](https://mauser.pt/catalog/product_info.php?products_id=096-8518) 
- [Arduino Nano ESP32](https://mauser.pt/catalog/product_info.php?products_id=095-2097)
- [RC522](https://mauser.pt/catalog/product_info.php?products_id=096-8517) 
- [TP-Link Antena AC1300 Mini](https://www.tp-link.com/pt/home-networking/adapter/archer-t3u/) 
- [Alfa Antena](https://alfa-network.eu/awus036ach-c) 


---

# Attack Techniques

Below are the primary attack methodologies supported by this toolkit:

## Keystroke Injection

This technique uses hardware to simulate a keyboard or mouse, allowing for automated execution of malicious payloads, such as reverse shells, to infiltrate a target machine.
- **Setup:**
  - [Raspberry Pi Pico](https://github.com/tbsauce/social-engineering-toolkit-hardware/tree/main/raspberry_pi_pico_keystroke_injection)
  - [Raspberry Pi Zero](https://github.com/tbsauce/social-engineering-toolkit-hardware/tree/main/raspberry_pi_zero_keystroke_injection)

## Evil Twin Attack

This attack creates a rogue Wi-Fi access point that mimics a legitimate network. When users connect, their credentials are intercepted and stored. The stolen passwords can later be cracked using tools like Hashcat.

- **Setup:**
  - [Raspberry Pi 5](https://github.com/tbsauce/social-engineering-toolkit-hardware/tree/main/raspberry_pi_5_evil_twin)
  
## Rogue Router

This attack involves setting up a rogue router, which can be either public or private, to monitor connection attempts from nearby devices. It collects important data, such as the number of devices trying to connect, allowing the ethical hacker to analyze connection statistics and gather intelligence on the devices attempting to use the network.

- **Setup:**
  - [ESP32](https://github.com/tbsauce/social-engineering-toolkit-hardware/tree/main/esp32_rogue_router)
  - [ESP8266](https://github.com/tbsauce/social-engineering-toolkit-hardware/tree/main/esp8266_rogue_router)
  - [Raspberry Pi 5](https://github.com/tbsauce/social-engineering-toolkit-hardware/tree/main/raspberry_pi_5_rogue_router)

## Deauthentication Attack

This technique forcefully disconnects users from Wi-Fi access points, causing network disruption and opening opportunities for further exploitation.

- **Setup:**
  - [ESP32](https://github.com/tbsauce/social-engineering-toolkit-hardware/tree/main/esp32_deauther)

## RFID Attack

This attack reads the unique identifiers (UIDs) of scanned RFID cards. By replicating these cards, the ethical hacker can gain unauthorized access to physical locations or systems that rely on RFID-based authentication.

- **Setup:**
  - [Arduino-nano](https://github.com/tbsauce/social-engineering-toolkit-hardware/tree/main/arduino_nano_rfid_attack)

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

2. Add the following:

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

+ **Linux:**

```
sudo ip addr add 192.168.1.1/24 dev eth0
```

+ **Windows:**

  1. Go to Control Panel → Network and Sharing Center → Change adapter settings

  2. Right-click Ethernet → Properties → IPv4 → Use the following IP address:

    + IP: `192.168.1.1`
    + Subnet mask: `255.255.255.0`
    + Gateway: (leave blank)


### Step 7: Test the Connection

1. SSH into the Raspberry Pi:

```
ssh sauce@192.168.1.2
```



