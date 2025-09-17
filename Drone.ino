#include <Arduino.h>
#include <RadioLib.h>

// wiring for LoRa module to RP2040 Pico
#define NSS_PIN    5   // Chip Select
#define DIO1_PIN   6   // IRQ
#define RESET_PIN  8   // Reset
#define BUSY_PIN   7   // Busy

SX1262 radio = new Module(NSS_PIN, DIO1_PIN, RESET_PIN, BUSY_PIN);

void setup() {
  Serial.begin(115200);
  delay(1000);

  Serial.println("LoRa Receiver init...");

  int state = radio.begin(915.0);
  if (state != RADIOLIB_ERR_NONE) {
    Serial.print("Radio init failed, code ");
    Serial.println(state);
    while (true);
  }

  Serial.println("Radio init success, waiting for packets...");
}

void loop() {
  String str;
  int state = radio.receive(str);

  if (state == RADIOLIB_ERR_NONE) {
    Serial.print("Received: ");
    Serial.println(str);

    // Also show signal quality
    Serial.print("RSSI: ");
    Serial.print(radio.getRSSI());
    Serial.print(" dBm  |  SNR: ");
    Serial.println(radio.getSNR());
  }
}
