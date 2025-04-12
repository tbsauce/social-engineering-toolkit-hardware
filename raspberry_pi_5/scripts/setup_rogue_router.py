import subprocess
import sys

AP_SSID = "MyRogueAP"        
AP_PASSWORD = "MyPassword123"  
wlanInternet = "wlan0"        # WLAN interface connected to the internet 
wlanAP = "wlan1"              # WLAN interface for the rogue access point

def run_command(command, check=True):
    """Run shell command and handle errors."""
    try:
        print(f"Running command: {command}")
        result = subprocess.run(command, shell=True, check=check, text=True, capture_output=True)
        print(result.stdout)
        return result
    except subprocess.CalledProcessError as e:
        print(f"Error: {e.stderr}")
        sys.exit(1)

def setup_rogue_ap():
    # Step 1: Update and install necessary packages
    run_command("sudo apt update && sudo apt upgrade -y")
    run_command("sudo apt install -y hostapd dnsmasq iptables wireless-tools")

    # Step 2: Stop hostapd and dnsmasq services
    run_command(f"sudo systemctl stop hostapd")
    run_command(f"sudo systemctl stop dnsmasq")

    # Step 3: Verify wlan interfaces
    run_command(f"iw dev")

    # Step 4: Ensure AP support
    run_command("iw list | grep -A 10 'Supported interface modes'")

    # Step 5: Configure Rogue Access Point
    with open('/etc/hostapd/hostapd.conf', 'w') as f:
        f.write(f"""interface={wlanAP}
driver=nl80211
ssid={AP_SSID}
hw_mode=g
channel=6
auth_algs=1
wpa=2
wpa_passphrase={AP_PASSWORD}
wpa_key_mgmt=WPA-PSK
rsn_pairwise=CCMP
""")

    # Step 6: Configure hostapd Service
    with open('/etc/default/hostapd', 'w') as f:
        f.write(f'DAEMON_CONF="/etc/hostapd/hostapd.conf"\n')

    # Step 7: Backup and modify dnsmasq.conf
    run_command("sudo mv /etc/dnsmasq.conf /etc/dnsmasq.conf.bak")
    with open('/etc/dnsmasq.conf', 'w') as f:
        f.write(f"""interface={wlanAP}
                dhcp-range=192.168.50.10,192.168.50.100,255.255.255.0,24h
                """)

    # Step 8: Ensure dhcpcd is installed
    run_command("dpkg -l | grep dhcpcd", check=False)
    run_command("sudo apt install dhcpcd5 -y")
    run_command("sudo systemctl enable dhcpcd")
    run_command("sudo systemctl restart dhcpcd")

    # Step 9: Configure static IP for wlanAP 
    with open('/etc/dhcpcd.conf', 'a') as f:
        f.write(f"""interface {wlanAP}
                static ip_address=192.168.50.1/24
                nohook wpa_supplicant
                """)
    run_command("sudo service dhcpcd restart")

    # Step 10: Set up NAT with iptables
    with open('/etc/sysctl.conf', 'a') as f:
        f.write("net.ipv4.ip_forward=1\n")

    run_command("sudo sysctl -w net.ipv4.ip_forward=1")

    # Add NAT rules
    run_command(f"sudo iptables -t nat -A POSTROUTING -o {wlanInternet} -j MASQUERADE")
    run_command(f"sudo iptables -A FORWARD -i {wlanAP} -o {wlanInternet} -j ACCEPT")
    run_command(f"sudo iptables -A FORWARD -i {wlanInternet} -o {wlanAP} -j ACCEPT")

    # Save iptables rules to persist
    run_command("sudo sh -c 'iptables-save > /etc/iptables.ipv4.nat'")

    # Set up rc.local to restore iptables rules on boot
    with open('/etc/rc.local', 'w') as f:
        f.write("""#!/bin/sh -e
                iptables-restore < /etc/iptables.ipv4.nat
                exit 0
                """)
    
    # Make rc.local executable
    run_command("sudo chmod +x /etc/rc.local")
    run_command("sudo iptables-restore < /etc/iptables.ipv4.nat")

    # Step 11: Start hostapd and dnsmasq services
    run_command("sudo systemctl unmask hostapd")
    run_command("sudo systemctl start hostapd")
    run_command("sudo systemctl start dnsmasq")

    # Step 12: Enable services to start on boot
    run_command("sudo systemctl enable hostapd")
    run_command("sudo systemctl enable dnsmasq")

    # Step 13: Verify setup
    run_command(f"sudo iw dev {wlanAP} info")

if __name__ == "__main__":
    setup_rogue_ap()
