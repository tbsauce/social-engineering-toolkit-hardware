sudo apt install arp-scan
import subprocess

def get_connected_devices(interface="wlan1"):
    # Run arp-scan on the local network to find connected devices
    print(f"Scanning for devices on {interface}...")
    result = subprocess.run(
        ["sudo", "arp-scan", "--interface", interface, "192.168.50.0/24"],
        stdout=subprocess.PIPE, stderr=subprocess.PIPE
    )
    
    # Decode and split the output
    output = result.stdout.decode('utf-8')
    devices = output.splitlines()
    
    # Filter out the lines that contain device information
    connected_devices = []
    for device in devices:
        if "192.168.50" in device:  # Filter IP range of your local network
            connected_devices.append(device)
    
    return connected_devices

# Example of usage
devices = get_connected_devices()
print(f"Number of devices connected: {len(devices)}")
for device in devices:
    print(device)

