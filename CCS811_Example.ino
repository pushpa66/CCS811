
#include "CCS811.h"

#define ADDR      0x5A
//#define ADDR      0x5B
#define WAKE_PIN  14

CCS811 sensor;

void setup()
{
  Serial.begin(9600);
  Serial.println("CCS811 test");
  //Wire.setClock(400000);
  configure();
}

void configure() {
  int count = 0;
  while (count < 100) {
    count++;
    if (!sensor.begin(uint8_t(ADDR), uint8_t(WAKE_PIN))) {
      Serial.println("Initialization failed.");
    } else {
      Serial.println("Success in " + String(count));
      break;
    }
    delay(100);
  }
}

void loop()
{
  sensor.getData(ADDR, WAKE_PIN);
  float co2 = sensor.readCO2();
  float tvoc = sensor.readTVOC();
  if (co2 >= 65021) {
    configure();
  } else if (co2 < 1) {
    Serial.println("Correction");
    co2 = 400;
    tvoc = 0;
  }
  Serial.print("CO2 concentration  : "); Serial.print(co2); Serial.println(" ppm");
  Serial.print("TVOC concentration : "); Serial.print(tvoc); Serial.println(" ppb");
  Serial.println();
  delay(2000);
}
