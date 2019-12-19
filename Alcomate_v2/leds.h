#include <Adafruit_NeoPixel.h>


static uint16_t i, j;
static int br = 100;
static int pix = 0;
static bool up = false;
static bool down = true;


Adafruit_NeoPixel pixels(9, 12, NEO_RGB + NEO_KHZ800); // define neopixel (12 = digital_in) amount=30 delay = 500

// -------------------------------------------------------------------------------------------------------------------------------
// -----------------------------------------------------  HELPING FUNCTIONS ------------------------------------------------------
// -------------------------------------------------------------LEDS--------------------------------------------------------------

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

  for (j = 0; j < 256 * 1; j++) { // 5 cycles of all colors on wheel
    for (i = 0; i < pixels.numPixels(); i++) {
      pixels.setPixelColor(i, Wheel(((i * 256 / pixels.numPixels()) + j) & 255));
    }
    pixels.show();
    delay(wait);
  }
}

void colorWipe(uint32_t color, int wait) {
  for (int i = 0; i < pixels.numPixels(); i++) { // For each pixel in strip...
    pixels.setPixelColor(i, color);         //  Set pixel's color (in RAM)
    pixels.show();                          //  Update strip to match
    delay(wait);                           //  Pause for a moment
  }
}

void ledstrip() {
  pixels.begin();
  pixels.setBrightness(100);
  //rainbowCycle(0);
}

void colorFlow() {
  if (j == 256) {
    j = 0;
  } else {
    j++;
  }

  if (i == pixels.numPixels()) {
    i = 0;
  } else {
    i++;
  }


  delay(10);
  pixels.setPixelColor(i, Wheel((i + j) & 255));
  pixels.show();
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

  for (int pix = 0; pix < pixels.numPixels(); pix++)
  {
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
