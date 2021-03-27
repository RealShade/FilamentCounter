#include "header.h"

// *****************************************************************************

Rfid::Rfid() {
  if (DEBUG_MODE == 1) {
    Serial.println("Rfid init");
  }
  rider.PCD_Init();
}

// *****************************************************************************

void Rfid::check() {
  // Ожидание
  if (!rider.PICC_IsNewCardPresent())
    return;
  // чтение
  if (!rider.PICC_ReadCardSerial()) {
    Serial.println("UUID no found");
    return;
  }
  // вывод данных

  if (spool != NULL && memcmp(spool->getUUID(), rider.uid.uidByte, 4) == 0) {
    return;
  }

  if (DEBUG_MODE == 1) {
    Serial.print("Rfid UUID: ");
    Serial.print(rider.uid.uidByte[0], HEX);
    Serial.print(rider.uid.uidByte[1], HEX);
    Serial.print(rider.uid.uidByte[2], HEX);
    Serial.println(rider.uid.uidByte[3], HEX);
  }

  if (spool != NULL) {
    // if (spool->getSpent() > 0) {
      spool->write();
    // }
    free(spool);
  }
  spool = new Spool(rider.uid.uidByte);
  menu->setMode(Menu::Mode::spent);
}
