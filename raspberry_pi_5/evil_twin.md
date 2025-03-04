# Requirements

- Raspberry Pi 5
- Micro usb to usb A adapter
- Wifi dongle

# Setup Server

- Create a Server with a public or ip availble on the local network
- clone the repo and acess the server folder
```
git clone --recursive https://github.com/xL1fer/APScavenge.github
cd APScavenge/APServer
```
- Get the servers ip
```
ip a
```
- Modify the following values to work with your server
    - the .env.local only add port if its not the 80 deafault
```
docker-compose.yml
		|
		|  nginx:
		|	build: ./nginx
		|	volumes:
		|	  - static:/static
		|	ports:
		|	  - "{port}:{port}"
		|
	
	nginx/default.conf
		|
		|	server {
		|		listen {port};
		|
	
	approject/.env.local
		|
		|	DJANGO_CSRF_TRUSTED_ORIGINS='http://127.0.0.1,http://0.0.0.0,http://{ip}:{port}'
		|
```
- Run the docker compose to launch the server
```
docker_run.sh
```
- Get the containers name and create a super user for it
```
docker ps
```
- Create the Super User
```
sudo docker exec -it [container_name] python manage.py createsuperuser
```
# Setup AP 

- Install [Raspberry Pi Imager](https://www.raspberrypi.com/software/)
- Flash the OS into a SD card using Raspberry Pi Imager
- Insert the SD card into the PI
- Get the Pi's ip by accessing the routers domain and ssh into the device 
- Insert wifi dongle
- veify that u have 2 wlan
``` 
iw dev
``` 
- ensure support for AP
``` 
iw list | grep -A 10 "Supported interface modes"
``` 
- clone the repo and acess the Agent folder
```
git clone --recursive https://github.com/xL1fer/APScavenge.github
cd APScavenge/APAgent
```
- Get the agent ip
```
ip a
```
- Modify the following values to work with your server(centeral_server_ip) and agent(ip), the COM_IFACE should be the interface with internet connection and apinterface the device that will create the ap in this case the wifi dongle 
```
docker-compose.yml
		|
		|  nginx:
		|	build: ./nginx
		|	volumes:
		|	  - static:/static
		|	ports:
		|	  - "{port}:{port}"
		|
	
	nginx/default.conf
		|
		|	server {
		|		listen {port};
		|
	
	approject/.env.local
		|   
        |   COM_IFACE={interface}
        |   AP_IFACE={interface}
        |   CENTRAL_IP='{centeral_server_ip}:{centeral_server_port}'
		|	AGENT_IP='{ip}:{port}'
		|
	
    entrypoint.sh
        |
        |	gunicorn --bind {ip}:8000 resolver:app #--log-level debug
        |
    
    nginx/default.conf
        |
        |	upstream flask {
        |		server {ip}:8000;
        |	}
        |
```
- Run the Agent
```
docker_run.sh
```
