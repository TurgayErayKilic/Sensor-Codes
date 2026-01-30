#include <LoRa_E22.h> 
#include <string.h> // memcpy için
#include <SoftwareSerial.h>

SoftwareSerial MySerial(10,11);

LoRa_E22 E22(&MySerial);

struct Veriler { float alt; } data; 
uint8_t buffer[sizeof(Veriler)]; 
void setup() {

Serial.begin(9600);
MySerial.begin(9600);
///// LoRa E22 Başlatma ///// 
E22.begin();
}

void loop() { 
data.alt=500; 
  // Struct → Byte diziye kopyala
memcpy(buffer, &data, sizeof(Veriler));
    // Veriyi sabit adrese gönder (örnek: 0,2,18)
E22.sendFixedMessage(0, 3, 2, buffer, sizeof(buffer));
delay(50); // Bekleme süresi 
Serial.println("Gönderildi");
       }