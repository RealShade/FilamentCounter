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
  unsigned long uuid;

  // Ожидание
  if (!rider.PICC_IsNewCardPresent())
    return;
  // чтение
  if (!rider.PICC_ReadCardSerial()) {
    Serial.println("UUID no found");
    return;
  }
  // вывод данных

  memcpy(&uuid, rider.uid.uidByte, 4);
  if (spool != NULL && spool->getUuid() == uuid) {
    return;
  }

  if (DEBUG_MODE == 1) {
    Serial.print("Rfid UUID: ");
    Serial.println(uuidAsString(uuid));
  }

  if (spool != NULL) {
    // if (spool->getSpent() > 0) {
      spool->write();
    // }
    free(spool);
  }
  spool = new Spool(uuid);
  menu->setMode(Menu::Mode::spent);
}
