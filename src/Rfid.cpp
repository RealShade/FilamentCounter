#include "header.h"

Rfid::Rfid() { rider.PCD_Init(); }

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

  spool = new Spool(rider.uid.uidByte);
  menu.setMode(Menu::Mode::spent);
  menu.show();
}
