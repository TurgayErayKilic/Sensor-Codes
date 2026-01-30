#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BNO055.h>
#include <utility/imumaths.h>

// ADR pini GND ise adres 0x28, VCC ise 0x29
Adafruit_BNO055 bno = Adafruit_BNO055(55, 0x28);

void setup() {
  Serial.begin(9600);
  delay(1000);

  Serial.println("BNO055 baslatiliyor...");

  if (!bno.begin()) {
    Serial.println("BNO055 bulunamadi! Baglantilari kontrol edin.");
    while (1); // Hata durumunda burada kal
  }

  // Harici kristal kullan (çoğu breakout için öneriliyor)
  bno.setExtCrystalUse(true);

  Serial.println("BNO055 baslatildi!");
  delay(1000);
}

void loop() {
  // Euler acilari (derece cinsinden)
  imu::Vector<3> euler = bno.getVector(Adafruit_BNO055::VECTOR_EULER);
  Serial.print("Heading: "); Serial.print(euler.x());
  Serial.print("  Pitch: "); Serial.print(euler.y());
  Serial.print("  Roll: ");  Serial.println(euler.z());

  // Lineer ivme (m/s^2)
  imu::Vector<3> accel = bno.getVector(Adafruit_BNO055::VECTOR_LINEARACCEL);
  Serial.print("Accel X: "); Serial.print(accel.x());
  Serial.print("  Y: ");     Serial.print(accel.y());
  Serial.print("  Z: ");     Serial.println(accel.z());

  // Gyro (deg/s)
  imu::Vector<3> gyro = bno.getVector(Adafruit_BNO055::VECTOR_GYROSCOPE);
  Serial.print("Gyro X: "); Serial.print(gyro.x());
  Serial.print("  Y: ");    Serial.print(gyro.y());
  Serial.print("  Z: ");    Serial.println(gyro.z());

  // Kalibrasyon durumu
  uint8_t sys, gyroC, accelC, magC;
  bno.getCalibration(&sys, &gyroC, &accelC, &magC);
  Serial.print("Calib - SYS: "); Serial.print(sys);
  Serial.print("  G: ");         Serial.print(gyroC);
  Serial.print("  A: ");         Serial.print(accelC);
  Serial.print("  M: ");         Serial.println(magC);

  Serial.println("------------------------");
  delay(2000);
}
