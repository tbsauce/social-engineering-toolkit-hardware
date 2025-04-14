#include <Preferences.h>

Preferences preferences;

void setup() {
  Serial.begin(115200);
  while (!Serial);  // Wait for Serial Monitor
  
  preferences.begin("rfid", true);  // Read-only mode
  
  int entryCount = preferences.getInt("count", 0);
  Serial.print("Total Entries: ");
  Serial.println(entryCount);

  for (int i = 0; i < entryCount; i++) {
    String key = "entry" + String(i);
    String entry = preferences.getString(key.c_str(), "");
    if (entry != "") {
      Serial.print(i);
      Serial.print(": ");
      Serial.println(entry);
    } else {
      Serial.print("Entry ");
      Serial.print(i);
      Serial.println(" is empty or corrupted.");
    }
  }
  
  preferences.end();
}

void loop() {
  // Nothing here
}
