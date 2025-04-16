sudo apt install wpasupplicant wireless-tools
sudo rfkill unblock wifi
sudo vim /etc/wpa_supplicant/wpa_supplicant.conf

ctrl_interface=DIR=/var/run/wpa_supplicant GROUP=netdev
update_config=1
country=US  # or your 2-letter country code

network={
    ssid="eduroam"
    key_mgmt=WPA-EAP
    eap=PEAP
    identity="your_username@your_university.edu"
    password="your_password"
    phase1="peaplabel=0"
    phase2="auth=MSCHAPV2"
}



sudo ip addr flush dev wlan0    
sudo pkill wpa_supplicant
sudo wpa_supplicant -B -i wlan0 -c /etc/wpa_supplicant/wpa_supplicant.conf
sleep 5
sudo dhclient -v wlan0
