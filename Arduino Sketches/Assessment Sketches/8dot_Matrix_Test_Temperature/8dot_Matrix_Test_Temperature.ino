#include <LedControl.h>

const int DIN_PIN = 20;
const int CS_PIN = 19;
const int CLK_PIN = 18;

const uint64_t IMAGES[] = {
 0x00105438ee385410,
  0x000010386c381000,
  0x0000001028100000,
  0x000010386c381000
};
const int IMAGES_LEN = sizeof(IMAGES)/8;


LedControl display = LedControl(DIN_PIN, CLK_PIN, CS_PIN);


void setup() {
  display.clearDisplay(0);
  display.shutdown(0, false);
  display.setIntensity(0, 10);
}

void displayImage(uint64_t image) {
  for (int i = 0; i < 8; i++) {
    byte row = (image >> i * 8) & 0xFF;
    for (int j = 0; j < 8; j++) {
      display.setLed(0, i, j, bitRead(row, j));
    }
  }
}

int i = 0;

void loop() {
  displayImage(IMAGES[i]);
  if (++i >= IMAGES_LEN ) {
    i = 0;
  }
  delay(200);
}