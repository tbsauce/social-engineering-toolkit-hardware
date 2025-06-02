#include <WiFi.h>
#include <WebServer.h>
#include "esp_wifi.h"
#include <Preferences.h>

// SSID and Password for the Access Point
const char* ssid = "McDonald’s Wi-Fi";
const char* password = ""; // "" -> no password

IPAddress IP;
const int interval = 1; //seconds loop again
WebServer server(80);
Preferences preferences;

String MacToStr(const uint8_t *mac) {
  String macStr = "";
  for (int i = 0; i < 6; i++) {
    macStr += String(mac[i], HEX);
    if (i < 5) macStr += ":";
  }
  return macStr;
}

void handleRoot() {
  wifi_sta_list_t station_list;
  esp_wifi_ap_get_sta_list(&station_list);
  int currentConnected = station_list.num;
  int totalCount = preferences.getInt("connected_count", 0);
  unsigned long uptime = millis() / 1000;

  String html = "<!DOCTYPE html><html><head>";
  html += "<meta http-equiv='refresh' content='5'>";
  html += "<title>ESP32 Status</title>";
  html += "<style>body {font-family: Arial; text-align: center; margin-top: 50px;}";
  html += "h1 {color: #444;} .data {font-size: 24px; margin: 20px;}</style></head>";
  html += "<body><h1>ESP32 Connection Statistics</h1>";
  html += "<div class='data'>Current connected devices: " + String(currentConnected) + "</div>";
  html += "<div class='data'>Total unique devices: " + String(totalCount) + "</div>";
  html += "<div class='data'>Uptime: " + String(uptime) + " seconds</div>";
  html += "</body></html>";

  server.send(200, "text/html", html);
}

void GetLogs() {
  String stored_macs = preferences.getString("mac_addresses", "");
  int old_count = preferences.getInt("connected_count", 0);
  Serial.println("===== Logs =====");
  Serial.println("Stored MAC Addresses:");
  Serial.println(stored_macs);
  Serial.print("Total Count: ");
  Serial.println(old_count);
  Serial.println("================");
}

void ClearLogs() {
  preferences.putString("mac_addresses", "");
  preferences.putInt("connected_count", 0);
  Serial.println("Logs cleared from memory.");
}

void setup() {
  Serial.begin(115200);
  Serial.println("Setting up Access Point...");

  WiFi.softAP(ssid, password);
  preferences.begin("wifi", false);

  IP = WiFi.softAPIP();
  Serial.print("Access Point IP Address: ");
  Serial.println(IP);

  server.on("/", handleRoot);
  server.begin();
  Serial.println("HTTP server started");

  delay(interval * 1000);
  
}

void loop() {
  wifi_sta_list_t station_list;
  esp_wifi_ap_get_sta_list(&station_list);
  int num_stations = station_list.num;
  String stored_macs = preferences.getString("mac_addresses", "");
  int old_count = preferences.getInt("connected_count", 0);

  if (Serial.available()) {
    char option = Serial.read();
    switch (option) {
      case '1':
        GetLogs();
        break;
      case '2':
        ClearLogs();
        break;
      default:
        Serial.println("Invalid option. Use 1 or 2.");
        break;
    }
  }

  Serial.println("===== Menu =====");
  Serial.print("WebServer IPAddress ");
  Serial.println(IP);
  Serial.println("1: Show Logs");
  Serial.println("2: Clear Logs");
  Serial.print("Number of devices currently connected: ");
  Serial.println(num_stations);
  Serial.print("Total number of devices connected: ");
  Serial.println(old_count);
  Serial.print("Uptime (s): ");
  Serial.println(millis() / 1000);
  Serial.println("===== Menu =====");
  
  for (int i = 0; i < num_stations; i++) {
      String macStr = MacToStr(station_list.sta[i].mac);
      if (stored_macs.indexOf(macStr) == -1) {
          int new_count = old_count + 1;
          preferences.putInt("connected_count", new_count); 
          stored_macs += macStr + ",";
          preferences.putString("mac_addresses", stored_macs); 
      }
  }
  
  server.handleClient();
  delay(interval * 1000);
}
