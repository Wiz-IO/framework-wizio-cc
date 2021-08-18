
EEPROM MAX SIZE 8192 !!!

EXAMPLE
```C
#include <Arduino.h>
#include <EEPROM.h>

extern "C" int _start_eeprom; // only for debug
void eeprom_test()
{
  { // only for debug
    printf("[EEPROM] ADDRESS: %p\n", &_start_eeprom);
  }

  EEPROM.begin(512);
  printf("[EEP] read: %u\n", (int)EEPROM.read(0));

  EEPROM.write(0, 41);
  EEPROM.write(1, 42);
  EEPROM.write(2, 43);
  EEPROM.write(3, 44);
  if (EEPROM.commit()) // save to flash
  {
    printf("[EEP] read: %u\n", (int)EEPROM.read(0));
    printf("[EEP] read: %u\n", (int)EEPROM.read(1));
    printf("[EEP] read: %u\n", (int)EEPROM.read(2));
    printf("[EEP] read: %u\n", (int)EEPROM.read(3));
  }

  { // only debug
    uint32_t *p = (uint32_t *)&_start_eeprom;
    printf("[EEPROM] value: %X\n", (int)*p); // 2C2B2A29
  }
}

void setup()
{
  Serial.begin(115200, true);
  Serial.printf("\n[APP] TI CC2652 2021 Georgi Angelov\n");
  pinMode(LED_GREEN, OUTPUT);
  eeprom_test();
}

void loop()
{
  blink(LED_GREEN, 100);
}

/*
[APP] TI CC2652 2021 Georgi Angelov
[EEPROM] ADDRESS: 0xa000
[EEP] read: 255
[EEP] read: 41
[EEP] read: 42
[EEP] read: 43
[EEP] read: 44
[EEPROM] value: 2C2B2A29
*/
```
