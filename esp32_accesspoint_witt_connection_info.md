#include <WiFi.h>
#include "esp_wifi.h"

// SSID and Password for the Access Point
const char* ssid = "ESP32-Access-Point";
const char* password = "12345678"; // Minimum 8 characters

void setup() {
  Serial.begin(115200);
  Serial.println("Setting up Access Point...");

  // Start the Access Point
  WiFi.softAP(ssid, password);

  // Display the IP Address of the Access Point
  IPAddress IP = WiFi.softAPIP();
  Serial.print("Access Point IP Address: ");
  Serial.println(IP);

  // Wait for some time to let stations connect
  delay(5000);
}

void loop() {
  // Get the list of connected stations
  wifi_sta_list_t station_list;
  esp_wifi_ap_get_sta_list(&station_list);  // Get list of connected stations
  
  // Display the number of connected devices
  int num_stations = station_list.num;
  Serial.print("Number of devices connected: ");
  Serial.println(num_stations);

  // Loop through the connected stations
  for (int i = 0; i < num_stations; i++) {
    // Print the MAC address of the connected station
    Serial.print("MAC Address: ");
    Serial.println(MacToStr(station_list.sta[i].mac));
  }

  delay(5000);  // Update every 5 seconds
}

// Helper function to convert MAC address to string
String MacToStr(const uint8_t *mac) {
  String macStr = "";
  for (int i = 0; i < 6; i++) {
    macStr += String(mac[i], HEX);
    if (i < 5) macStr += ":";
  }
  return macStr;
}

