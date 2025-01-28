- Prepare the Raspberry Pi
- install packages 
'''
sudo apt update && sudo apt upgrade -y
sudo apt install -y hostapd dnsmasq iptables wireless-tools
'''
- Disable hostapd and dnsmasq
'''
sudo systemctl stop hostapd
sudo systemctl stop dnsmasq
'''
- veify that u have 2 wlan

'''
iw dev
'''
- ensure support for AP

'''
iw list | grep -A 10 "Supported interface modes"
'''
- Configure the Rogue Access Point
'''
sudo vim /etc/hostapd/hostapd.conf
'''

'''
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
'''

- Configure hostapd Service

'''
sudo vim /etc/default/hostapd
'''
- change a line to
'''
DAEMON_CONF="/etc/hostapd/hostapd.conf"
'''

- sudo mv /etc/dnsmasq.conf /etc/dnsmasq.conf.bak
- sudo vim /etc/dnsmasq.conf

- add 
'''
interface=wlan1
dhcp-range=192.168.50.10,192.168.50.100,255.255.255.0,24h
'''
-  Enable Internet Sharing
	
	- Verify if dhcpcd is installed:
	'''
	dpkg -l | grep dhcpcd
	'''
	- if not 
	'''
	sudo apt install dhcpcd5 -y
	sudo systemctl enable dhcpcd
	sudo systemctl restart dhcpcd
	'''

'''
sudo vim /etc/dhcpcd.conf
'''
'''
interface wlan1
    static ip_address=192.168.50.1/24
    nohook wpa_supplicant
'''
'''
sudo service dhcpcd restart
'''


- Set Up NAT with iptables

'''
sudo vim /etc/sysctl.conf
'''

- uncomment 
'''
net.ipv4.ip_forward=1
'''

- Apply the change immediately:

'''
sudo sysctl -w net.ipv4.ip_forward=1
'''


- Add NAT rules for forwarding:
'''
sudo iptables -t nat -A POSTROUTING -o wlan0 -j MASQUERADE
sudo iptables -A FORWARD -i wlan1 -o wlan0 -j ACCEPT
sudo iptables -A FORWARD -i wlan0 -o wlan1 -j ACCEPT
'''

- Save the rules to persist:
'''
sudo sh -c "iptables-save > /etc/iptables.ipv4.nat"
'''

- sudo vim /etc/rc.local
'''
iptables-restore < /etc/iptables.ipv4.nat

exit 0
'''
'''
sudo chmod +x /etc/rc.local
'''

'''
iptables-restore < /etc/iptables.ipv4.nat
'''

- sudo systemctl start hostapd
- sudo systemctl start dnsmasq
'''
sudo systemctl enable hostapd
sudo systemctl enable dnsmasq
'''

- verify setup
'''
sudo iw dev wlan1 info
'''
