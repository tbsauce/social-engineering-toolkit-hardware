- install arduino IDE
- Go to File > Preferences
- Add the following URL in the "Additional Board Manager URLs" field:
``` 
https://dl.espressif.com/dl/package_esp32_index.json
``` 
- Tools > Board > Boards Manager, search for "ESP32", and install the package
- add the following code to the IDE
``` 
#include <WiFi.h>

// SSID and Password for the Access Point
const char* ssid = "ESP32-Access-Point";
const char* password = "12345678"; // Minimum 8 characters

void setup() {
  Serial.begin(115200);
  Serial.println("Setting up Access Point...");

  // Start the Access Point
  WiFi.softAP(ssid, password);

  // Display the IP Address
  IPAddress IP = WiFi.softAPIP();
  Serial.print("Access Point IP Address: ");
  Serial.println(IP);
}

void loop() {
  // Nothing to do here
}

``` 
- Go to Tools > Board, and select your ESP32
- Tools > Port and select the port associated with your ESP32	
	- if the board doesnt appear maybe its necessary to install the CP210x drivers

