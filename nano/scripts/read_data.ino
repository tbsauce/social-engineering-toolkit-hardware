#include <WiFi.h>
#include <WebServer.h>
#include <Preferences.h>
#include <MFRC522v2.h>
#include <MFRC522DriverSPI.h>
#include <MFRC522DriverPinSimple.h>
#include <MFRC522Debug.h>

// WiFi Access Point
const char* ssid = "ESP32-Access-Point";
const char* password = "";

Preferences preferences;

MFRC522DriverPinSimple ss_1_pin(10);
MFRC522DriverSPI driver_1{ss_1_pin};
MFRC522 reader{driver_1};

WebServer server(80);
IPAddress IP;

unsigned long lastMenuTime = 0;
const unsigned long menuInterval = 1 * 1000; // 1 second

void setup() {
  Serial.begin(115200);

  // Start Access Point
  WiFi.softAP(ssid, password);
  IP = WiFi.softAPIP();
  Serial.print("Access Point IP Address: ");
  Serial.println(IP);

  // Init Preferences
  preferences.begin("rfid", false);

  // Init RFID reader
  reader.PCD_Init();
  Serial.print(F("Reader: "));
  MFRC522Debug::PCD_DumpVersionToSerial(reader, Serial);

  // Start Web Server
  server.on("/", handleRoot);
  server.begin();
  Serial.println("Web server started.");
}

void loop() {
  // RFID reading
  if (reader.PICC_IsNewCardPresent() && reader.PICC_ReadCardSerial()) {
    String uidStr;
    for (byte i = 0; i < reader.uid.size; i++) {
      if (reader.uid.uidByte[i] < 0x10) uidStr += "0";
      uidStr += String(reader.uid.uidByte[i], HEX);
    }
    uidStr.toUpperCase();

    MFRC522::PICC_Type piccType = reader.PICC_GetType(reader.uid.sak);
    String typeStr = MFRC522Debug::PICC_GetTypeName(piccType);

    int count = preferences.getInt("count", 0);
    bool exists = false;

    // Check if UID already exists
    for (int i = 0; i < count; i++) {
      String uidKey = "uid" + String(i);
      String storedUid = preferences.getString(uidKey.c_str(), "");
      if (storedUid == uidStr) {
        exists = true;
        break;
      }
    }

    if (!exists) {
      String uidKey = "uid" + String(count);
      String typeKey = "type" + String(count);
      preferences.putString(uidKey.c_str(), uidStr);
      preferences.putString(typeKey.c_str(), typeStr);
      preferences.putInt("count", count + 1);
      Serial.print("New UID logged: ");
      Serial.println(uidStr);
    } else {
      Serial.print("UID already logged: ");
      Serial.println(uidStr);
    }

    reader.PICC_HaltA();
    reader.PCD_StopCrypto1();
  }

  // Serial input handling
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

  // Print menu every X seconds
  if (millis() - lastMenuTime > menuInterval) {
    Serial.println("===== Menu =====");
    Serial.print("WebServer IPAddress: ");
    Serial.println(IP);
    Serial.println("1: Show Logs");
    Serial.println("2: Clear Logs");
    Serial.print("Total Cards Logged: ");
    Serial.println(preferences.getInt("count", 0));
    Serial.print("Uptime (s): ");
    Serial.println(millis() / 1000);
    Serial.println("===== Menu =====");
    lastMenuTime = millis();
  }

  server.handleClient();
}

// Serve logs via web interface
void handleRoot() {
  int count = preferences.getInt("count", 0);
  unsigned long uptime = millis() / 1000;

  String html = "<!DOCTYPE html><html><head>";
  html += "<meta http-equiv='refresh' content='5'>";
  html += "<title>RFID Logs</title>";
  html += "<style>";
  html += "body {font-family: Arial; text-align: center; margin-top: 50px;}";
  html += "h1 {color: #444;}";
  html += ".data {font-size: 24px; margin: 20px;}";
  html += "table {margin: 0 auto; border-collapse: collapse; width: 80%;}";
  html += "th, td {border: 1px solid #ccc; padding: 10px; font-size: 18px;}";
  html += "th {background-color: #f2f2f2;}";
  html += "</style></head><body>";

  html += "<h1>RFID Card Logs</h1>";
  html += "<div class='data'>Total Cards Read: " + String(count) + "</div>";
  html += "<div class='data'>Uptime: " + String(uptime) + " seconds</div>";

  html += "<table>";
  html += "<tr><th>#</th><th>UID</th><th>Card Type</th></tr>";

  for (int i = 0; i < count; i++) {
    String uid = preferences.getString(("uid" + String(i)).c_str(), "");
    String type = preferences.getString(("type" + String(i)).c_str(), "");
    html += "<tr><td>" + String(i + 1) + "</td><td>" + uid + "</td><td>" + type + "</td></tr>";
  }

  html += "</table></body></html>";

  server.send(200, "text/html", html);
}

// Serial log display
void GetLogs() {
  int count = preferences.getInt("count", 0);
  Serial.println("===== RFID Logs =====");
  Serial.print("Total Cards Logged: ");
  Serial.println(count);

  for (int i = 0; i < count; i++) {
    String uid = preferences.getString(("uid" + String(i)).c_str(), "");
    String type = preferences.getString(("type" + String(i)).c_str(), "");
    Serial.print(i + 1);
    Serial.print(": UID = ");
    Serial.print(uid);
    Serial.print(" | Type = ");
    Serial.println(type);
  }
  Serial.println("===== RFID Logs =====");
}

// Clear all logs
void ClearLogs() {
  preferences.clear();  // Clear all keys in the namespace
  preferences.putInt("count", 0);  // Reset count explicitly
  Serial.println("RFID logs cleared.");
}

