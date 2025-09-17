#include <Arduino.h>
#include <RadioLib.h>

// Pin mapping (RP2040 Pico -> SX1262MB2CAS)
#define NSS_PIN    5   // Chip Select
#define DIO1_PIN   6   // IRQ
#define RESET_PIN  8   // Reset
#define BUSY_PIN   7   // Busy

SX1262 radio = new Module(NSS_PIN, DIO1_PIN, RESET_PIN, BUSY_PIN);

void setup() {
  Serial.begin(115200);
  delay(1000);

  Serial.println("LoRa Transmitter init...");

  // Start the radio on 915.0 MHz (use 868.0 in EU)
  int state = radio.begin(915.0);
  if (state != RADIOLIB_ERR_NONE) {
    Serial.print("Radio init failed, code ");
    Serial.println(state);
    while (true);
  }

  Serial.println("Radio init success!");
}

void loop() {
  String msg = "Hello World!";

  int state = radio.transmit(msg);
  if (state == RADIOLIB_ERR_NONE) {
    Serial.println("Sent: " + msg);
  } else {
    Serial.print("TX failed, code ");
    Serial.println(state);
  }

  delay(5000); // wait 5 seconds
}
