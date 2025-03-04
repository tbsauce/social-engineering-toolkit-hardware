#include <WiFi.h>
#include "esp_wifi.h"
#include <Preferences.h>

// SSID and Password for the Access Point
const char* ssid = "ESP32-Access-Point";
const char* password = "";

// Preferences object for non-volatile memory storage
Preferences preferences;

// Helper function to convert MAC address to string
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

  // Initialize Preferences
  preferences.begin("wifi", false);

  // Retrieve the stored count from Preferences
  int stored_count = preferences.getInt("connected_count", 0); // Default to 0 if not found
  Serial.print("Stored connected count: ");
  Serial.println(stored_count);

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

  // Retrieve the stored list of connected MAC addresses from Preferences
  String stored_macs = preferences.getString("mac_addresses", "");
  int old_count = preferences.getInt("connected_count", 0);
  Serial.print("Total connected MACs: ");
  Serial.println(stored_macs);
  Serial.print("Total connected count: ");
  Serial.println(old_count);

  
  // Loop through the connected stations
  for (int i = 0; i < num_stations; i++) {
    String macStr = MacToStr(station_list.sta[i].mac);
    
    // Check if the MAC address is already stored
    if (stored_macs.indexOf(macStr) == -1) {
      // New device connected, update the count
      int new_count = old_count + 1;
      preferences.putInt("connected_count", new_count); // Store the updated count
      
      // Add the new MAC address to the stored list
      stored_macs += macStr + ",";
      preferences.putString("mac_addresses", stored_macs); // Store the updated MAC list
    }
  }
  delay(5000);  // Update every 5 seconds
}
