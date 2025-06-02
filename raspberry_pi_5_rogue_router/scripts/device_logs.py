import subprocess
import time
import json
import os

# Path to store the device connection data
data_file = "device_connections.json"

def load_device_data():
    """Load the existing device connection data from a file (if it exists)."""
    if os.path.exists(data_file):
        with open(data_file, 'r') as f:
            return json.load(f)
    return {}

def save_device_data(data):
    """Save the device connection data to a file."""
    with open(data_file, 'w') as f:
        json.dump(data, f)

def get_connected_devices(interface="wlan1"):
    # Load existing device data
    connected_devices = load_device_data()
    
    # Run arp-scan on the local network to find connected devices
    print(f"Scanning for devices on {interface}...")
    result = subprocess.run(
        ["sudo", "arp", "-a"],
        stdout=subprocess.PIPE, stderr=subprocess.PIPE
    )

    # Decode and split the output
    output = result.stdout.decode('utf-8')
    devices = output.splitlines()

    # Process each device
    for device in devices:
        if "192.168.50" in device:  # Filter IP range of your local network
            mac = device.split()[3]
            
            # Check if the device already exists in the dictionary
            if mac in connected_devices:
                # Update the device's connection data
                connected_devices[mac]["connected_times"] += 1
                connected_devices[mac]["connteted_time"] += time.time() - connected_devices[mac]["start_time"]
            else:
                # Add new device with initial stats
                connected_devices[mac] = {
                    "connected_times": 1,
                    "connteted_time": 0,
                    "start_time": time.time()
                }

    # Save updated data back to file
    save_device_data(connected_devices)

    return connected_devices

# Loop to keep scanning for devices continuously
try:
    while True:
        # Get connected devices
        devices = get_connected_devices()

        # Print the number of connected devices
        print(f"Number of devices connected: {len(devices)}")

        # Print the connection details for each device
        for mac, stats in devices.items():
            total_connected_time = stats["connteted_time"]
            print(f"MAC: {mac}, Connected Times: {stats['connected_times']}, Total Connected Time: {total_connected_time:.2f} seconds")
        
        # Sleep for a while before scanning again
        print("\nWaiting for the next scan...\n")
        time.sleep(10)  # Sleep for 10 seconds before the next scan

except KeyboardInterrupt:
    print("\nProgram terminated by user.")

