# Requirements

- Raspberry Pi with Wi-Fi capability

---

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

