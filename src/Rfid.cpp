#include "header.h"

void view_data(byte *buf, byte size) {
  for (byte j = 0; j < size; j++) {
    Serial.print(buf[j]);
    Serial.print(buf[j], HEX);
  }
}

Rfid::Rfid(){
  rider.PCD_Init();
}

void Rfid::check() {
  // Ожидание
  if ( ! rider.PICC_IsNewCardPresent())
  return;
  // чтение
  if ( ! rider.PICC_ReadCardSerial()) {
    Serial.println("UUID no found");
  return;
}
  // вывод данных
  Serial.print("UID=");
  view_data(rider.uid.uidByte,rider.uid.size);
  Serial.println();
  Serial.print("type=");
  byte piccType = rider.PICC_GetType(rider.uid.sak);
  Serial.print(rider.PICC_GetTypeName(piccType));
  Serial.println();
}
