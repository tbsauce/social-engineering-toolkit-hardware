#include <WiFi.h>
#include "esp_wifi.h"
#include <Preferences.h>

// SSID and Password for the Access Point
const char* ssid = "ESP32-Access-Point";
const char* password = ""; // "" -> no password

// Preferences object to store data on flash memory
Preferences preferences;

// Function to convert MAC address to string
String MacToStr(const uint8_t *mac) {
  String macStr = "";
  for (int i = 0; i < 6; i++) {
    macStr += String(mac[i], HEX);
    if (i < 5) macStr += ":";
  }
  return macStr;
}

void setup() {
  Serial.begin(115200);
  Serial.println("Setting up Access Point...");

  // Start the Access Point
  WiFi.softAP(ssid, password);

  // Initialize Preferences as read/write(false) mode
  preferences.begin("wifi", false);

  // Retrieve the stored count from Preferences
  int stored_count = preferences.getInt("connected_count", 0); 
  Serial.print("Stored connected count: ");
  Serial.println(stored_count);

  // Display the IP Address of the Access Point
  IPAddress IP = WiFi.softAPIP();
  Serial.print("Access Point IP Address: ");
  Serial.println(IP);

  delay(5000); // 5 seconds
}

void loop() {
  // Get the list of connected stations
  wifi_sta_list_t station_list;
  esp_wifi_ap_get_sta_list(&station_list); 
  
  // Display the number of connected devices
  int num_stations = station_list.num;
  Serial.print("Number of devices currently connected: ");
  Serial.println(num_stations);

  // Retrieve the stored list of connected MAC addresses from Preferences
  String stored_macs = preferences.getString("mac_addresses", "");
  int old_count = preferences.getInt("connected_count", 0);
  Serial.println("Total connected MACs: ");
  Serial.println(stored_macs);
  Serial.print("Total connected count: ");
  Serial.println(old_count);

  
  // Loop through the connected stations
  for (int i = 0; i < num_stations; i++) {
      String macStr = MacToStr(station_list.sta[i].mac);
      
      // Check if the MAC address is already stored
      if (stored_macs.indexOf(macStr) == -1) {
          // Update the count
          int new_count = old_count + 1;
          preferences.putInt("connected_count", new_count); 
          
          // Add new MAC address
          stored_macs += macStr + ",";
          preferences.putString("mac_addresses", stored_macs); 
      }
  }
  delay(5000);  // 5 seconds
}
