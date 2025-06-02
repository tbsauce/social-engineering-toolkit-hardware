# Requirements

- Raspberry Pi 5
- Micro USB to USB-A adapter
- WiFi dongle

---

# Setup: Server

### Step 1: Create a Server
1. Set up a server with either a **public IP** or an **IP available on the local network**.

### Step 2: Download APScavenge
1. Clone the Repository [APScavenge](https://github.com/xL1fer/APScavenge) 
```
git clone --recursive https://github.com/xL1fer/APScavenge.github
cd APScavenge/APServer
```

### Step 3: Configure Server Settings
1. Get the Server's IP
```
ip a
```
2. Modify the following files to match your server’s configuration. 
    - In `approject/.env.local` **only add a port if it's not the default (80).**

#### `docker-compose.yml`
```
nginx:
  build: ./nginx
  volumes:
    - static:/static
  ports:
    - "{port}:{port}"
```

#### `nginx/default.conf`
```
server {
  listen {port};
}
```

#### `approject/.env.local`
```
DJANGO_CSRF_TRUSTED_ORIGINS='http://127.0.0.1,http://0.0.0.0,http://{ip}:{port}'
```

### Step 4: Start the Server
1. Launch the server:
```
./docker_run.sh
```

### Step 5: Create a Superuser
1. Get the name of the running container:
   ```sh
   docker ps
   ```
2. Create a superuser inside the container:
   ```sh
   sudo docker exec -it [container_name] python manage.py createsuperuser
   ```

---

# Setup: Access Point (AP)

### Step 1: Install Raspberry Pi OS
1. Download and install [Raspberry Pi Imager](https://www.raspberrypi.com/software/).
2. Use the **Raspberry Pi Imager** to flash the OS onto an SD card.
3. Insert the SD card into the Raspberry Pi.

### Step 2: Connect and Setup Network
1. Find the Raspberry Pi's IP address by checking your router's domain settings.
2. SSH into the device:
   ```sh
   ssh pi@<Raspberry_Pi_IP>
   ```
3. Insert the WiFi dongle.

### Step 3: Verify Wireless Interfaces
1. Check if two **wlan** interfaces are detected:
```
iw dev
```

2. Ensure support for **Access Point (AP) mode**:
```
iw list | grep -A 10 "Supported interface modes"
```

### Step 4: Download APScavenge
1. Clone the Repository [APScavenge](https://github.com/xL1fer/APScavenge) 
```
git clone --recursive https://github.com/xL1fer/APScavenge.github
cd APScavenge/APAgent
```

### Step 5: Get the Agent's IP Address

### Step 6: Configure the Agent
1. Get the Server's IP
```sh
ip a
```
2. Modify the following files to set up the **central server IP** and **agent IP**.
    - **`COM_IFACE`**: The interface **with internet access**.
    - **`AP_IFACE`**: The interface **creating the access point (WiFi dongle)**.

#### `docker-compose.yml`
```
nginx:
  build: ./nginx
  volumes:
    - static:/static
  ports:
    - "{port}:{port}"
```

#### `nginx/default.conf`
```
server {
  listen {port};
}
```

#### `approject/.env.local`
```
COM_IFACE={interface}
AP_IFACE={interface}
CENTRAL_IP='{central_server_ip}:{central_server_port}'
AGENT_IP='{ip}:{port}'
```

#### `entrypoint.sh`
```
gunicorn --bind {ip}:8000 resolver:app #--log-level debug
```

#### `nginx/default.conf`
```
upstream flask {
  server {ip}:8000;
}
```

### Step 7: Start the Agent
1. Launch the agent:
```
./docker_run.sh
```

