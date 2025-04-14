# Requirements

- Raspberry Pi 5
- Micro USB to USB-A adapter
- WiFi dongle

---
# setup

```
curl -sSL https://raw.githubusercontent.com/tbsauce/social-engineering-toolkit-hardware/main/raspberry_pi_5/scripts/setup_rogue_router.py | sudo python3
```

# Manual Setup: AP 

### Step 1: Update and Install Necessary Packages

```
sudo apt update && sudo apt upgrade -y
sudo apt install -y hostapd dnsmasq iptables wireless-tools
```

### Step 2: Disable Services Temporarily

```
sudo systemctl stop hostapd
sudo systemctl stop dnsmasq
```

### Step 3: Verify WiFi Interfaces

- Ensure that two WiFi interfaces are available:
```
iw dev
```
- Check for Access Point support:
```
iw list | grep -A 10 "Supported interface modes"
```

### Step 4: Configure the Rogue Access Point

1. Open the hostapd configuration file:
```
sudo vim /etc/hostapd/hostapd.conf
```
2. Add the following configuration:
```
interface=wlan1
driver=nl80211
ssid=RogueAP
hw_mode=g
channel=6
auth_algs=1
wpa=2
wpa_passphrase=Rogue12345
wpa_key_mgmt=WPA-PSK
rsn_pairwise=CCMP
```

### Step 5: Configure hostapd Service

1. Edit the default hostapd file:
```
sudo vim /etc/default/hostapd
```
2. Modify the line to:
```
DAEMON_CONF="/etc/hostapd/hostapd.conf"
```

### Step 6: Configure DHCP

1. Backup existing configuration:
```
sudo mv /etc/dnsmasq.conf /etc/dnsmasq.conf.bak
```
2. Create a new configuration file:
```
sudo vim /etc/dnsmasq.conf
```
3. Add the following lines:
```
interface=wlan1
dhcp-range=192.168.50.10,192.168.50.100,255.255.255.0,24h
```

### Step 7: Enable Internet Sharing

1. Verify if `dhcpcd` is installed:
```
dpkg -l | grep dhcpcd
```
2. If not installed, install and restart:
```
sudo apt install dhcpcd5 -y
sudo systemctl enable dhcpcd
sudo systemctl restart dhcpcd
```
3. Configure a static IP for `wlan1`:
```
sudo vim /etc/dhcpcd.conf
```
4. Add:
```
interface wlan1
    static ip_address=192.168.50.1/24
    nohook wpa_supplicant
```
5. Restart `dhcpcd`:
```
sudo service dhcpcd restart
```

### Step 8: Set Up NAT with iptables

1. Enable IP forwarding:
```
sudo vim /etc/sysctl.conf
```
2. Uncomment the line:
```
net.ipv4.ip_forward=1
```
3. Apply the change immediately:
```
sudo sysctl -w net.ipv4.ip_forward=1
```
4. Add NAT rules:
```
sudo iptables -t nat -A POSTROUTING -o wlan0 -j MASQUERADE
sudo iptables -A FORWARD -i wlan1 -o wlan0 -j ACCEPT
sudo iptables -A FORWARD -i wlan0 -o wlan1 -j ACCEPT
```
5. Save the rules:
```
sudo sh -c "iptables-save > /etc/iptables.ipv4.nat"
```
6. Configure persistence:
```
sudo vim /etc/rc.local
```
7. Add:
```
iptables-restore < /etc/iptables.ipv4.nat
exit 0
```
8. Make `rc.local` executable:
```
sudo chmod +x /etc/rc.local
```
9. Restore iptables:
```
sudo iptables-restore < /etc/iptables.ipv4.nat
```

### Step 9: Start Services

```
sudo systemctl unmask hostapd
sudo systemctl start hostapd
sudo systemctl start dnsmasq
sudo systemctl enable hostapd
sudo systemctl enable dnsmasq
```

### Step 10: Verify Setup

```
sudo iw dev wlan1 info
```

### Step 11: Run the Script

1. Execute your [script](https://github.com/tbsauce/social-engineering-hardware-toolkit/blob/main/raspberry_pi_5/scripts/device_logs.py) to finalize the setup.
