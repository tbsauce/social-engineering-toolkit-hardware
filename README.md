# Social Engineering Hardware Toolkit

Welcome to the **Social Engineering Hardware Toolkit**, a comprehensive resource for documenting penetration testing tools, payloads, and attack techniques related to physical social engineering threats. This repository explores hardware-based attack vectors such as keyloggers, rogue routers, and other physical intrusion methods.

## Purpose
The goal of this toolkit is to provide an open and accessible platform for security researchers, ethical hackers, and cybersecurity enthusiasts to:
- Understand and explore various physical attack vectors.
- Simulate real-world scenarios to identify security vulnerabilities.
- Develop practical defenses against hardware-based social engineering attacks.

By experimenting with these tools and techniques, users can enhance their security awareness and improve their ability to defend against physical threats.

---

## Supported Hardware
The toolkit supports various hardware devices, each capable of executing different attack techniques:

- [Raspberry Pi Pico](https://github.com/tbsauce/social-engineering-hardware-toolkit/tree/main/raspberry_pi_pico) 
- [Raspberry Pi Zero](https://github.com/tbsauce/social-engineering-hardware-toolkit/tree/main/raspberry_pi_zero)
- [Raspberry Pi 5](https://github.com/tbsauce/social-engineering-hardware-toolkit/tree/main/raspberry_pi_5) 
- [ESP32](https://github.com/tbsauce/social-engineering-hardware-toolkit/tree/main/esp32) 

---

# Attack Techniques
Below are the primary attack methodologies supported by this toolkit:

## Keystroke Injection
This technique uses hardware to simulate a keyboard or mouse, allowing for automated execution of malicious payloads, such as reverse shells, to infiltrate a target machine.
- **Hardware:**
  - [Raspberry Pi Pico](https://github.com/tbsauce/social-engineering-hardware-toolkit/blob/main/raspberry_pi_pico/keystroke_injection_pico.md)
  - [Raspberry Pi Zero](https://github.com/tbsauce/social-engineering-hardware-toolkit/blob/main/raspberry_pi_zero/keystroke_injection_zero.md)

## Evil Twin Attack
This attack creates a rogue Wi-Fi access point that mimics a legitimate network. When users connect, their credentials are intercepted and stored. The stolen passwords can later be cracked using tools like Hashcat.

- **Hardware:**
  - [Raspberry Pi 5](https://github.com/tbsauce/social-engineering-hardware-toolkit/blob/main/raspberry_pi_5/evil_twin.md)

### Rogue Router (With Internet Access)
This attack involves setting up a rogue router that users unknowingly connect to. The attacker can monitor network traffic, analyze connection statistics, and gather intelligence on connected devices.

- **Hardware:**
  - Raspberry Pi 5

### Rogue Router (Without Internet Access)
This attack sets up a rogue router (public or private) for monitoring connection attempts. It helps collect important data, such as the number of devices attempting to connect, without providing actual internet access.

- **Hardware:**
  - [ESP32](https://github.com/tbsauce/social-engineering-hardware-toolkit/blob/main/esp32/rogue_router_no_internet.md)

### Deauthentication Attack
This technique forcefully disconnects users from Wi-Fi access points, causing network disruption and opening opportunities for further exploitation.

- **Hardware:**
  - [ESP32](https://github.com/tbsauce/social-engineering-hardware-toolkit/blob/main/esp32/wifi_deauth_attack.md)
---

# Disclaimer
This toolkit is intended for educational and ethical testing purposes only. Unauthorized use of these tools for malicious activities is strictly prohibited.



