#include <MFRC522v2.h>
#include <MFRC522DriverSPI.h>
#include <MFRC522DriverPinSimple.h>
#include <MFRC522Debug.h>
#include <Preferences.h>

Preferences preferences;

MFRC522DriverPinSimple ss_1_pin(10);
MFRC522DriverPinSimple ss_2_pin(8);

MFRC522DriverSPI driver_1{ss_1_pin};
MFRC522DriverSPI driver_2{ss_2_pin};

MFRC522 readers[]{driver_1, driver_2};

void setup() {
  Serial.begin(115200);
  while (!Serial);

  preferences.begin("rfid", false); // Initialize Preferences

  for (uint8_t i = 0; i < sizeof(readers)/sizeof(readers[0]); i++) {
    readers[i].PCD_Init();
    Serial.print(F("Reader "));
    Serial.print(i + 1);
    Serial.print(F(": "));
    MFRC522Debug::PCD_DumpVersionToSerial(readers[i], Serial);
  }
}

void loop() {
  for (uint8_t readerIndex = 0; readerIndex < sizeof(readers)/sizeof(readers[0]); readerIndex++) {
    MFRC522 &reader = readers[readerIndex];
    if (reader.PICC_IsNewCardPresent() && reader.PICC_ReadCardSerial()) {
      // Convert UID to hex string
      String uidStr;
      for (byte i = 0; i < reader.uid.size; i++) {
        if (reader.uid.uidByte[i] < 0x10) uidStr += "0";
        uidStr += String(reader.uid.uidByte[i], HEX);
      }
      uidStr.toUpperCase();

      // Get PICC type
      MFRC522::PICC_Type piccType = reader.PICC_GetType(reader.uid.sak);
      String typeStr = MFRC522Debug::PICC_GetTypeName(piccType);

      // Get and update entry count
      int entryCount = preferences.getInt("count", 0);
      String key = "entry" + String(entryCount);
      String logEntry = "Reader " + String(readerIndex + 1) + ", UID: " + uidStr + ", Type: " + typeStr;

      // Save to flash
      preferences.putString(key.c_str(), logEntry.c_str());
      entryCount++;
      preferences.putInt("count", entryCount);

      // Serial output for debugging
      Serial.print("Logged: ");
      Serial.println(logEntry);

      reader.PICC_HaltA();
      reader.PCD_StopCrypto1();
    }
  }
}
