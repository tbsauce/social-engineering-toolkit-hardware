#!/bin/bash

# Create the systemd service file
sudo tee /etc/systemd/system/rogue_router.service > /dev/null <<'EOF'
[Unit]
Description=Rogue AP Setup Script
After=network-online.target sys-subsystem-net-devices-wlan1.device
Requires=sys-subsystem-net-devices-wlan1.device
Wants=network-online.target

[Service]
Type=simple
Restart=always  
RestartSec=30s
ExecStartPre=/bin/bash -c 'while fuser /var/lib/dpkg/lock >/dev/null 2>&1; do sleep 5; done'
ExecStartPre=/bin/bash -c 'sudo dpkg --configure -a || true'
# Use a loop to keep the service active
ExecStart=/bin/bash -c 'while true; do /usr/bin/curl -sSL https://raw.githubusercontent.com/tbsauce/social-engineering-toolkit-hardware/main/raspberry_pi_5/scripts/setup_rogue_router.py | /usr/bin/sudo /usr/bin/python3; sleep 10; done'
StandardOutput=file:/var/log/rogue_router.log
StandardError=file:/var/log/rogue_router.log
TimeoutStartSec=300
Environment="PYTHONUNBUFFERED=1"

[Install]
WantedBy=multi-user.target
EOF

# Reload systemd and enable service
sudo systemctl daemon-reload
sudo systemctl enable --now rogue_router.service

# Verify service status
echo -e "\nService created. Status:"
systemctl status rogue_router.service --no-pager
echo -e "\nLogs will be written to: /var/log/rogue_router.log"
