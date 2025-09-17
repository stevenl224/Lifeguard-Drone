#include <RadioLib.h>

// Pin mapping (RP2040 Pico -> SX1262MB2CAS)
#define NSS_PIN    5   // Chip Select
#define DIO1_PIN   6   // IRQ
#define RESET_PIN  8   // Reset
#define BUSY_PIN   7   // Busy

// Create SX1262 radio instance
SX1262 radio = new Module(NSS_PIN, DIO1_PIN, RESET_PIN, BUSY_PIN);

void setup() {
  Serial1.begin(115200);   // Use Serial1 on Pico (TX=GPIO0, RX=GPIO1 by default)
  delay(1500);             // Wait for serial to initialize

  Serial1.println("Starting SX1262...");

  // Initialize the radio
  int state = radio.begin();
  if (state == RADIOLIB_ERR_NONE) {
    Serial1.println("SX1262 successfully initialized!");
  } else {
    Serial1.print("SX1262 initialization failed, code ");
    Serial1.println(state);
    while (true); // Stop here if failed
  }
}

void loop() {
}
