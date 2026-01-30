#include <Adafruit_GPS.h>

// NEO-7M GPS → Arduino RX0 (D0)
Adafruit_GPS GPS(&Serial);

void setup() {
  Serial.begin(9600);
  delay(2000);

  Serial.println("NEO-7M GPS (Adafruit GPS Library) Basladi...");
  
  GPS.begin(9600);  // GPS default baud
  GPS.sendCommand(PMTK_SET_NMEA_OUTPUT_RMCGGA);  // En önemli iki cümle
  GPS.sendCommand(PMTK_SET_NMEA_UPDATE_1HZ);     // 1 Hz güncelleme
}

void loop() {

  // GPS'ten ham veri oku
  char c = GPS.read();

  // Ham NMEA cümlelerini görmek istersen:
  if (c) {
    Serial.write(c);
  }

  // Yeni NMEA cümlesi bittiyse parse et
  if (GPS.newNMEAreceived()) {
    if (!GPS.parse(GPS.lastNMEA())) {
      return; 
    }

    // Parse başarılı → GPS verilerini yazdır
    Serial.print("Enlem: ");
    Serial.println(GPS.latitudeDegrees, 6);

    Serial.print("Boylam: ");
    Serial.println(GPS.longitudeDegrees, 6);

    Serial.print("Uydu sayisi: ");
    Serial.println(GPS.satellites);

    Serial.print("Yukseklik (m): ");
    Serial.println(GPS.altitude);

    Serial.println("-----------------------");
  }
}
