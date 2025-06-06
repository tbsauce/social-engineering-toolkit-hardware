# Introduction

This document aims to present the planning and execution of an awareness program designed to educate employees and evaluate their cybersecurity preparedness. The campaign will be conducted ethically, in a controlled manner, and in compliance with internal guidelines and applicable legislation.

---
# Scope and Objectives

The security assessment will be conducted exclusively within the University of Aveiro campus, with priority given to high-traffic user zones and areas accessible to privileged personnel.  All simulated engagements will immediately terminate upon participant identification to ensure ethical compliance and prevent unnecessary operational impact. The assessment has the following objectives:

- Identify gaps in staff awareness and procedural adherence.
- Test the detection and response capabilities of IT/security teams.
- Measure reporting rates for suspicious devices and activities.
- Quantify victimization rates from simulated attacks.
- Assess baseline security awareness among staff.
- Evaluate the detection capabilities of the monitoring system.

---
# Attack Methodologies

## Phishing Attack

This social engineering attack simulates a phishing campaign using GoPhish, an open-source phishing toolkit, to test the awareness and resilience of University of Aveiro staff and students. The phishing emails will imitate trusted institutional communication, such as an urgent message about a lost ID card, academic penalty, or a course registration issue, creating a sense of urgency and increase interations. To carry out the attack, a realistic email template must be created to replicate the look of official university correspondence. An identical login page should be developed to mirror the University’s authentication portal, where victims may be tricked into entering their credentials. Finally, a server is required to host the GoPhish application, allowing the attacker to manage the campaign, send the emails, and collect any submitted data.

### Attack Plan Steps

1. Create a realistic phishing email template.
2. Create a authentication forms of the institution.
2. Configure GoPish and launch the fake login page of the institution. 
3. Deploy phishing campaign.
4. Evaluate Staff Response:
	- Do staff report any phishing emails?
	- Do they open the email?
	- Do they click the link?
	- Do they enter credentials?

### Impact Mapping

- **T1531 - Account Access Removal:** If stolen credentials are used to access an administrator account, the attacker can remove accounts. Additionally, if no second-factor authentication is in place, a hacker with user credentials can easily change the password, locking the legitimate user out of the account.  

- **T1486 - Data Encrypted for Impact:** If the phishing payload includes ransomware, it can encrypt the victim's data to extort payment.  

- **T1485/T1561 - Data Destruction/Disk Wipe:** The phishing payload may contain a virus designed to delete data or perform a full disk wipe.  

- **T1496.001 - Compute Hijacking:** The payload may contain malware that runs in the background of a compromised computer, consuming its resources for malicious purposes.  

---
## Deauthentication Attack

This attack involves creating a deauthentication device using an ESP32 to disconnect users from a specific network. On the University of Aveiro campus, this can be executed by deploying the attack near the library to target random users or positioning it close to the AP of a specific target. The primary goal of this attack is to create a DDoS by continuously disconnecting users while monitoring their response to assess the impact and effectiveness of the disruption. This type of disruption allows researchers to observe how users and IT personnel react to persistent connectivity issues, evaluate detection capabilities, and assess the institution’s incident response procedures. Furthermore, the deauthentication attack can be combined with more advanced tactics such as an Evil Twin or rogue access point. By forcefully disconnecting users from legitimate routers, the attack increases the likelihood that devices will automatically reconnect to the malicious network, thereby amplifying the potential impact and effectiveness of credential theft or traffic interception.

### Attack Plan Steps

1. Acquire and configure the ESP32-Deauther.
2. Move to a discreet location close to the target.
3. Turn on the deauthentication device.
4. Evaluate the reaction of the staff:
    - Will the staff notice the abnormal disconnections?
    - Will they react?
    - Will they report the incident?
    - Do they know the response protocols?
    - How fast do they react?

### Impact Mapping

- **T1498 - Network Denial of Service:** Disrupts network availability by sending deauthentication frames, preventing legitimate users from connecting.

---
## Evil Twin

This attack involves creating a rogue AP with an identical SSID to the institution's trusted network. The goal is to attract users to connect, potentially exposing their usernames and hashed passwords if their devices are misconfigured. The attack can be executed on campus or in a nearby building outside the reach of the institution's trusted network. The setup requires a Raspberry Pi 5, a server, an external Wi-Fi dongle or an Alpha Access Point, and optionally, a deauthentication device. Once deployed, the attacker can attempt to crack the credentials of users who connect to the rogue AP.

### Attack Plan Steps

1. Obtain and configure an evil twin.
2. Deploy it on campus close to a critical location or outside the campus range.
3. Activate the router with the same SSID as the institution's trusted network.
4. If necessary, use a deauthentication device to force clients to connect to the rogue AP.
5. Monitor devices connecting to the rogue router.
6. Attempt to crack hashed passwords from connected users.
7. Evaluate the reaction of the staff:
    - Is the rogue AP detected as an Evil Twin?
    - Will users connect to it?
    - Are user passwords secure?
    - Do users report the issue and know the reporting procedure?

### Impact Mapping

- **T1531 - Account Access Removal:** If stolen credentials are used to access an administrator account, the attacker can remove accounts. Additionally, if no second-factor authentication is in place, a hacker with user credentials can easily change the password, locking the legitimate user out of the account.  

- **T1485 - Data Destruction:** If stolen credentials are used to access an account, they can be leveraged to delete data.    

- **T1565.002 - Transmitted Data Manipulation:**  Intercepts and alters unencrypted traffic, potentially modifying or injecting malicious data.  

- **T1491.002 - External Defacement:** Redirects users to fake login pages, undermining trust in services.

---
## Rogue Router

This attack is similar to the Evil Twin but does not require a password to access the rogue network. The goal is to provide an open, unprotected access point for attackers to perform a MITM attack or launch a DNS spoofing attack. The necessary materials include a Raspberry Pi 5, a server, an external Wi-Fi dongle, or an Alpha Access Point.

### Attack Plan Steps

1. Configure the rogue AP with a public SSID and ensure internet access is available.
2. Deploy the AP on campus or nearby, close to critical areas.
3. Activate the AP.
4. Monitor devices connecting to the rogue router.
5. Create a DNS spoofing attack or monitor the traffic of a specific victim.
6. Evaluate the reaction of the staff:
    - Is the rogue AP detected?
    - Will users connect to a known public or unknown SSID?
    - Will they identify the risk?
    - Are users using VPNs or other protection systems?
    - Do users report the issue and know the reporting procedure?

### Impact Mapping

- **T1531 - Account Access Removal:** If stolen credentials are used to access an administrator account, the attacker can remove accounts. Additionally, if no second-factor authentication is in place, a hacker with user credentials can easily change the password, locking the legitimate user out of the account.  

- **T1485 - Data Destruction:** If stolen credentials are used to access an account, they can be leveraged to delete data.    

- **T1565.002 - Transmitted Data Manipulation:**  Intercepts and alters unencrypted traffic, potentially modifying or injecting malicious data.  

- **T1491.002 - External Defacement:** Redirects users to fake login pages, undermining trust in services.

---
## Keystroke Attack

The Bad USB attack exploits human curiosity by leveraging malicious USB devices. An attacker strategically drops a compromised USB drive in a public area, hoping a target picks it up and connects it to their computer. Once plugged in, the device executes preconfigured scripts that can establish a reverse shell, steal credentials, or exfiltrate data. To conduct this attack, a Raspberry Pi Zero or Pico can be configured as a USB HID emulating a keyboard and a micro USB to USB-A adapter.

### Attack Plan Steps

1. Prepare a malicious USB device with a preloaded attack script.
2. Leave the device in a strategic and visible location.
3. Configure the payload to execute automatically upon connection.
4. Monitor whether the device is plugged into a system.
5. Assess staff responses:
    - Do employees recognize the USB as a potential security threat?
    - Will someone plug it into a system?
    - Does the individual report the suspicious device?
    - Are staff familiar with the organization's security protocols for handling unknown USB devices?
    - If plugged in, do staff members respond appropriately to mitigate the threat?

### Impact Mapping  

- **T1485/T1561 - Data Destruction/Disk Wipe:** The keystroke device may contain a virus designed to delete data or perform a full disk wipe.  

- **T1486 - Data Encrypted for Impact:** A payload may include ransomware that encrypts the victim's data to extort payment.  

- **T1565.001 - Stored Data Manipulation:** The keystroke device may contain a script to modify files on victim systems.  

- **T1490 - Inhibit System Recovery:** The keystroke device may disable backup services, delete restore points, or corrupt recovery partitions to prevent system restoration.  

- **T1496.001 - Compute Hijacking:** The payload may contain malware that runs in the background of a compromised computer, consuming its resources for malicious purposes.  

--- 
## Keylogging Attack

The keylogging attack involves inserting a Raspberry Pi Pico between a keyboard and a computer to intercept and log keystrokes. The Pico acts as a stealthy man-in-the-middle, capturing sensitive input while transparently relaying keystrokes to a log file. The logged data is later retrieved by the attacker for exploitation.

### Attack Plan Steps

1. Prepare a malicious USB keylogging device.
2. Deploy the device in a strategic location.
3. Ensure automatic keystroke logging upon connection.
4. Monitor whether the device is plugged into a system.
5. Assess staff responses
    - Do employees notice the modified hardware?
    - Does anyone report the suspicious device?
    - If detected, how quickly is the threat mitigated?

### Impact Mapping

- **T1531 - Account Access Removal:** If stolen credentials are used to access an administrator account, the attacker can remove accounts. Additionally, if no second-factor authentication is in place, a hacker with user credentials can easily change the password, locking the legitimate user out of the account.  

- **T1485 - Data Destruction:** If stolen credentials are used to access an account, they can be leveraged to delete data.    

- **T1565.001 - Stored Data Manipulation:** If stolen credentials are used to modify files on victim systems.  

## RFID Attack

This attack exploits vulnerabilities in RFID-based access control systems. Using an RC522 reader and writer, an attacker can clone legitimate access cards to gain unauthorized entry to secured areas. The attack involves capturing RFID signals, replicating them onto a blank card, and testing access within the institution.

### Attack Plan Steps

1. Setup an RC522 RFID to  read cards.
2. Scan an RFID access card to capture its signal.
3. Clone the captured signal onto a blank RFID card.
4. Test the cloned card on institution access points.
5. Evaluate security measures:
    - Do RFID systems detect cloned cards?
    - Are additional authentication mechanisms in place?
    - Do security staff monitor for unauthorized access attempts?

### Impact Mapping

- **T1489 - Service Stop:** An attacker gains unauthorized access to a restricted area and manually disrupts critical services by unplugging devices, cutting power, or disabling key infrastructure.  

- **T1529 - System Shutdown/Reboot:** Physically access workstations, servers, or control panels, and force immediate shutdowns or reboots by pressing power buttons, disconnecting cables, or triggering hardware resets, potentially causing service disruptions or data loss.  

# Authorization and Approvals  

By signing below, the authorized parties confirm their approval of this assessment, and testers acknowledge their understanding of and compliance with all testing protocols and boundaries.

**Signatures:**  

