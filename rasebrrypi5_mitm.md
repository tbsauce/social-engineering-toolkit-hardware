- create AP with wifi
```
sudo apt update
sudo apt install bettercap -y
```

```
sudo bettercap -iface wlan1
```

```
net.probe on
arp.spoof on
```

```
net.sniff on
```