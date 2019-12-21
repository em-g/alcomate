// -------------------------------------------------------------------------------------------------------------------------------
// -----------------------------------------------------  HELPING FUNCTIONS ------------------------------------------------------
// -------------------------------------------------------------LEDS--------------------------------------------------------------

#include <Adafruit_NeoPixel.h>


static uint16_t i, j;
static int br = 100;
static int pix = 0;
static bool up = false;
static bool down = true;
unsigned long previousLedMillis = 0;

Adafruit_NeoPixel pixels(9, 12, NEO_RGB + NEO_KHZ800);

uint32_t Wheel(byte WheelPos) {
  WheelPos = 255 - WheelPos;
  if (WheelPos < 85) {
    return pixels.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  }
  if (WheelPos < 170) {
    WheelPos -= 85;
    return pixels.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
  WheelPos -= 170;
  return pixels.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
}

void rainbowCycle(uint8_t wait) {
  uint16_t i, j;

  for (j = 0; j < 256 * 1; j++) {
    for (i = 0; i < pixels.numPixels(); i++) {
      pixels.setPixelColor(i, Wheel(((i * 256 / pixels.numPixels()) + j) & 255));
    }
    pixels.show();
    delay(wait);
  }
}

void colorWipe(uint32_t color, int wait) {
  for (int i = 0; i < pixels.numPixels(); i++) {
    pixels.setPixelColor(i, color);
    pixels.show();
    delay(wait);
  }
}

void ledstrip() {
  pixels.begin();
  pixels.setBrightness(100);
}

void colorFlow(int ledInterval) {
  if (millis() - previousLedMillis >= ledInterval) {
    previousLedMillis = millis();
    String aaa = "current = " + String(millis()) + ", interval = " + String(ledInterval) + ", previous = " + String(previousLedMillis);
    Serial.println(aaa);
    if (j == 256) j = 0;
    else j++;

    pixels.setPixelColor(0, Wheel((0 + j) & 255));
    pixels.setPixelColor(1, Wheel((1 + j) & 255));
    pixels.setPixelColor(2, Wheel((2 + j) & 255));
    pixels.setPixelColor(3, Wheel((3 + j) & 255));
    pixels.setPixelColor(4, Wheel((4 + j) & 255));
    pixels.setPixelColor(5, Wheel((5 + j) & 255));
    pixels.setPixelColor(6, Wheel((6 + j) & 255));
    pixels.setPixelColor(7, Wheel((7 + j) & 255));
    pixels.setPixelColor(8, Wheel((8 + j) & 255));
    pixels.show();
  }
}

void pulse(int r, int g, int b) {
  if (br < 30) {
    up = true;
    down = false;
  }
  if (br > 98) {
    up = false;
    down = true;
  }
  if (up && !down) br++;
  if (down && !up) br--;
  delay(10);

  for (int pix = 0; pix < pixels.numPixels(); pix++) {
    pixels.setPixelColor(pix, b, r, g);
  }

  pixels.setBrightness(br);
  pixels.show();
}

void shortPulse(int r, int g, int b) {
  for (int pix = 0; pix < pixels.numPixels(); pix++) {
    pixels.setPixelColor(pix, b, r, g);
    pixels.show();
  }
}
