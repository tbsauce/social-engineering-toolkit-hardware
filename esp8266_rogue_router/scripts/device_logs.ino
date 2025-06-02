#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <EEPROM.h>

// SSID and Password for the Access Point
const char* ssid = "McDonald’s Wi-Fi";
const char* password = ""; // "" -> no password

IPAddress IP;
const int interval = 1; // seconds loop again
ESP8266WebServer server(80);

#define EEPROM_SIZE 512
#define COUNT_ADDR 0
#define MACS_ADDR 4

String MacToStr(const uint8_t *mac) {
  String macStr = "";
  for (int i = 0; i < 6; i++) {
    if (mac[i] < 0x10) macStr += "0";
    macStr += String(mac[i], HEX);
    if (i < 5) macStr += ":";
  }
  return macStr;
}

void handleRoot() {
  struct station_info *station_list = wifi_softap_get_station_info();
  int currentConnected = 0;
  
  // Count connected stations
  struct station_info *station = station_list;
  while (station) {
    currentConnected++;
    station = station->next.stqe_next;
  }
  
  if (station_list) {
    wifi_softap_free_station_info();
  }

  int totalCount = 0;
  EEPROM.get(COUNT_ADDR, totalCount);
  unsigned long uptime = millis() / 1000;

  String html = "<!DOCTYPE html><html><head>";
  html += "<meta http-equiv='refresh' content='5'>";
  html += "<title>ESP8266 Status</title>";
  html += "<style>body {font-family: Arial; text-align: center; margin-top: 50px;}";
  html += "h1 {color: #444;} .data {font-size: 24px; margin: 20px;}</style></head>";
  html += "<body><h1>ESP8266 Connection Statistics</h1>";
  html += "<div class='data'>Current connected devices: " + String(currentConnected) + "</div>";
  html += "<div class='data'>Total unique devices: " + String(totalCount) + "</div>";
  html += "<div class='data'>Uptime: " + String(uptime) + " seconds</div>";
  html += "</body></html>";

  server.send(200, "text/html", html);
}

void GetLogs() {
  char macs_buffer[EEPROM_SIZE - MACS_ADDR];
  memset(macs_buffer, 0, sizeof(macs_buffer));
  for (int i = 0; i < sizeof(macs_buffer); ++i) {
    macs_buffer[i] = EEPROM.read(MACS_ADDR + i);
    if (macs_buffer[i] == 0) break;
  }
  String stored_macs = macs_buffer;
  
  int old_count = 0;
  EEPROM.get(COUNT_ADDR, old_count);
  
  Serial.println("===== Logs =====");
  Serial.println("Stored MAC Addresses:");
  Serial.println(stored_macs);
  Serial.print("Total Count: ");
  Serial.println(old_count);
  Serial.println("================");
}

void ClearLogs() {
  char empty_buffer[EEPROM_SIZE - MACS_ADDR] = {0};
  for (int i = 0; i < sizeof(empty_buffer); ++i) {
    EEPROM.write(MACS_ADDR + i, empty_buffer[i]);
  }
  int zero = 0;
  EEPROM.put(COUNT_ADDR, zero);
  EEPROM.commit();
  Serial.println("Logs cleared from memory.");
}

void setup() {
  Serial.begin(115200);
  Serial.println("Setting up Access Point...");

  EEPROM.begin(EEPROM_SIZE);
  
  // Initialize count if invalid
  int stored_count = 0;
  EEPROM.get(COUNT_ADDR, stored_count);
  if (stored_count < 0 || stored_count > 1000) {
    stored_count = 0;
    EEPROM.put(COUNT_ADDR, stored_count);
    EEPROM.commit();
  }

  WiFi.softAP(ssid, password);

  IP = WiFi.softAPIP();
  Serial.print("Access Point IP Address: ");
  Serial.println(IP);

  server.on("/", handleRoot);
  server.begin();
  Serial.println("HTTP server started");

  delay(interval * 1000);
}

void loop() {
  struct station_info *station_list = wifi_softap_get_station_info();
  int num_stations = 0;
  
  // Count connected stations
  struct station_info *station = station_list;
  while (station) {
    num_stations++;
    station = station->next.stqe_next;
  }

  // Read stored data from EEPROM
  char macs_buffer[EEPROM_SIZE - MACS_ADDR];
  memset(macs_buffer, 0, sizeof(macs_buffer));
  for (int i = 0; i < sizeof(macs_buffer); ++i) {
    macs_buffer[i] = EEPROM.read(MACS_ADDR + i);
    if (macs_buffer[i] == 0) break;
  }
  String stored_macs = macs_buffer;
  
  int old_count = 0;
  EEPROM.get(COUNT_ADDR, old_count);

  // Handle serial commands
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

  // Print menu
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

  // Check for new MAC addresses
  bool updated = false;
  station = station_list;
  while (station) {
    String macStr = MacToStr(station->bssid);
    if (stored_macs.indexOf(macStr) == -1) {
      stored_macs += macStr + ",";
      old_count++;
      updated = true;
    }
    station = station->next.stqe_next;
  }

  // Update EEPROM if needed
  if (updated) {
    EEPROM.put(COUNT_ADDR, old_count);
    memset(macs_buffer, 0, sizeof(macs_buffer));
    strncpy(macs_buffer, stored_macs.c_str(), sizeof(macs_buffer) - 1);
    for (int i = 0; i < sizeof(macs_buffer); ++i) {
      EEPROM.write(MACS_ADDR + i, macs_buffer[i]);
    }
    EEPROM.commit();
  }

  if (station_list) {
    wifi_softap_free_station_info();
  }

  server.handleClient();
  delay(interval * 1000);
}
