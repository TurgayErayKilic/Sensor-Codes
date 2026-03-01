#include <Wire.h>
#include <SPI.h>

#include <Adafruit_Sensor.h>
#include <Adafruit_BNO055.h>
#include <utility/imumaths.h>

#include <Adafruit_BME280.h>

#include "MedianFilter.h"   // bizim kütüphane (MedianFilter.h/.cpp aynı sketch klasöründe)

// ------------------- BNO055 (I2C) -------------------
Adafruit_BNO055 bno = Adafruit_BNO055(55, 0x28); // ADR=GND -> 0x28

// ------------------- BME280 (SPI) -------------------
const int BME_CS = 10;
Adafruit_BME280 bme(BME_CS); // HW SPI

// ------------------- Median Filters -----------------
MedianFilter mfHeading(5);   // window size
MedianFilter mfPressure(5);  // window size

void setup() {
  Serial.begin(115200);
  delay(500);

  Wire.begin();

  if (!bno.begin()) {
    Serial.println("BNO055 bulunamadi! Baglantilari kontrol edin.");
    while (1);
  }
  bno.setExtCrystalUse(true);

  SPI.begin();
  if (!bme.begin()) {
    Serial.println("BME280 (SPI) bulunamadi! CS/SPI pinlerini ve beslemeyi kontrol edin.");
    while (1);
  }

  Serial.println("BNO055(I2C) + BME280(SPI) + MedianFilter basladi.");
  Serial.println("Format: HeadingRaw,HeadingMedian,PressureRaw,PressureMedian");
}

void loop() {
  // ---- Raw readings ----
  imu::Vector<3> euler = bno.getVector(Adafruit_BNO055::VECTOR_EULER);
  float heading_deg = euler.x();

  float pressure_pa = bme.readPressure();

  // ---- Push to median filters ----
  mfHeading.push(heading_deg);
  mfPressure.push(pressure_pa);

  // ---- Print raw + filtered side-by-side ----
  Serial.print("Heading raw/med (deg): ");
  Serial.print(heading_deg, 2);
  Serial.print(" / ");
  if (mfHeading.available()) Serial.print(mfHeading.getMedian(), 2);
  else Serial.print("filling");

  Serial.print(" | Pressure raw/med (Pa): ");
  Serial.print(pressure_pa, 1);
  Serial.print(" / ");
  if (mfPressure.available()) Serial.println(mfPressure.getMedian(), 1);
  else Serial.println("filling");

  delay(50); // 20 Hz
}
