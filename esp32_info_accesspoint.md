#include <WiFi.h>

void setup() {
  Serial.begin(115200);
  Serial.println("Starting Wi-Fi scan...");

  // Set ESP32 to Station Mode
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  delay(100);
}

void loop() {
  Serial.println("Scanning for nearby networks...");
  
  // Perform the Wi-Fi scan
  int networkCount = WiFi.scanNetworks();

  // Display the results
  if (networkCount == 0) {
    Serial.println("No networks found.");
  } else {
    Serial.printf("Found %d networks:\n", networkCount);
    Serial.println("--------------------------------------------------------------------------");
    Serial.println("Index | SSID                     | Signal  | Encryption   | MAC Address         ");
    Serial.println("--------------------------------------------------------------------------");

    for (int i = 0; i < networkCount; i++) {
      // Print details for each network
      Serial.printf("%5d | %-25s | %7ddBm | %-12s | %s\n",
                    i,
                    WiFi.SSID(i).c_str(),
                    WiFi.RSSI(i),
                    encryptionType(WiFi.encryptionType(i)).c_str(),
                    macToString(WiFi.BSSID(i)).c_str());
    }

    Serial.println("--------------------------------------------------------------------------");
  }

  // Wait for 10 seconds before scanning again
  delay(10000);
}

// Convert encryption type to readable string
String encryptionType(wifi_auth_mode_t type) {
  switch (type) {
    case WIFI_AUTH_OPEN:
      return "Open";
    case WIFI_AUTH_WEP:
      return "WEP";
    case WIFI_AUTH_WPA_PSK:
      return "WPA_PSK";
    case WIFI_AUTH_WPA2_PSK:
      return "WPA2_PSK";
    case WIFI_AUTH_WPA_WPA2_PSK:
      return "WPA/WPA2_PSK";
    case WIFI_AUTH_WPA3_PSK:
      return "WPA3_PSK";
    case WIFI_AUTH_WPA2_ENTERPRISE:
      return "WPA2_Enterprise";
    default:
      return "Unknown";
  }
}

// Convert MAC address to readable string
String macToString(const uint8_t *mac) {
  char macStr[18];
  sprintf(macStr, "%02X:%02X:%02X:%02X:%02X:%02X", mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);
  return String(macStr);
}

