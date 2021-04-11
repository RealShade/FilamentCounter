#include "header.h"

// *****************************************************************************

Rfid::Rfid()
{
  if (DEBUG_MODE == 1)
  {
    Serial.println("Rfid init");
  }
  rider.PCD_Init();
  Serial.println(rider.PCD_PerformSelfTest() ? "ok" : "error");
  rider.PCD_Init();
}

// *****************************************************************************

void Rfid::check()
{
  unsigned long uuid;

  // Ожидание
  if (!rider.PICC_IsNewCardPresent())
    return;
  // чтение
  if (!rider.PICC_ReadCardSerial())
  {
    Serial.println("UUID no found");
    //   rider.PCD_Reset();
    //   delay(500);
    // rider.PCD_Init();
    return;
  }
  // вывод данных
  memcpy(&uuid, rider.uid.uidByte, 4);
  // rider.PCD_Reset();
  //   delay(500);
  // rider.PCD_Init();
  if (spool != NULL && spool->getUuid() == uuid)
  {
    Serial.println("UUID already read");
    return;
  }

  buzzer->clickStart();

  if (DEBUG_MODE == 1)
  {
    Serial.print("Rfid UUID: ");
    Serial.println(uuidAsString(uuid));
  }

  if (spool != NULL)
  {
    // if (spool->getSpent() > 0) {
    spool->write();
    // }
    free(spool);
  }
  spool = new Spool(uuid);
  menu->setMode(Menu::Mode::spent);
}
