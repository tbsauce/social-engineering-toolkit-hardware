Step 1: Check if dhcpcd is Installed

Run:
bash

which dhcpcd

or
bash

dhcpcd --version

If it's not installed, you'll see command not found.
Step 2: Install dhcpcd (If Missing)
bash

sudo apt update && sudo apt install dhcpcd5 -y

Step 3: Enable and Start dhcpcd
bash

sudo systemctl enable dhcpcd
sudo systemctl start dhcpcd

Now check its status:
bash

sudo systemctl status dhcpcd

(You should see active (running).)
Step 4: Apply Static IP Configuration

Re-edit /etc/dhcpcd.conf:
bash

sudo vim /etc/dhcpcd.conf

Add (for a direct Ethernet connection to your laptop):
ini

interface eth0
static ip_address=192.168.1.2/24
static routers=192.168.1.1
static domain_name_servers=8.8.8.8

Save (:wq in Vim) and restart:
bash

sudo systemctl restart dhcpcd

Step 5: Verify the IP Address

Check if eth0 got the static IP:
bash

ip a show eth0

You should see:

inet 192.168.1.2/24 ...

Step 6: Configure Your Laptop’s Ethernet Port

Assign a static IP on the same subnet (e.g., 192.168.1.1) on your laptop:

    Linux:
    bash

sudo ip addr add 192.168.1.1/24 dev eth0

Windows:
Go to Control Panel > Network and Sharing Center > Change adapter settings → Right-click Ethernet → Properties → IPv4 → Use:

IP: 192.168.1.1  
Subnet: 255.255.255.0  
Gateway: (leave blank)  

Step 7: Test the Connection

From your laptop, ping the Pi:
bash

ping 192.168.1.2

Then SSH:
bash

ssh sauce@192.168.1.2
