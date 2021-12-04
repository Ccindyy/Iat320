//Code adapted from Adafruit Neopixels striptest example

#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
#include <avr/power.h> // Required for 16 MHz Adafruit Trinket
#endif

//Parameter 1: Number of pixels in a strip
//Parameter 2: Pin number
//Parameter 3: Pixel type
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)

//Created 2 strips on pin 6 and 9
Adafruit_NeoPixel strip1 = Adafruit_NeoPixel(8, 6, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel strip2 = Adafruit_NeoPixel(8, 9, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel floraStrip = Adafruit_NeoPixel(8+++, 8, NEO_GRB + NEO_KHZ800);


//Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ400);


void setup() {

#if defined(__AVR_ATtiny85__) && (F_CPU == 16000000)
  clock_prescale_set(clock_div_1);
#endif


  strip1.begin();           // INITIALIZE NeoPixel strip object (REQUIRED)
  strip1.show();            // Turn OFF all pixels ASAP
  strip1.setBrightness(50); // Set BRIGHTNESS to about 1/5 (max = 255)

  strip2.begin();
  strip2.show();
  strip2.setBrightness(50);

  floraStrip.begin();
  floraStrip.show();
  floraStrip.setBrightness(50);
}

void loop() {

  colorWipe3(floraStrip.Color(255, 102, 255), 500); // Pink
  colorWipe1(strip1.Color(255, 102, 255), 500); // Pink
  colorWipe2(strip2.Color(0, 255, 0), 500); // Green

  colorWipe3(floraStrip.Color(255, 128, 0), 500); // Pink
  colorWipe1(strip1.Color(255, 128, 0), 500); // Orange
  colorWipe2(strip2.Color(50, 50, 255), 500); // White


}

//Color wipe for strip1
void colorWipe1(uint32_t color, int wait) {
  for (int i = 0; i < strip1.numPixels(); i++) { // For each pixel in strip...
    strip1.setPixelColor(i, color);         //  Set pixel's color (in RAM)
    strip1.show();                          //  Update strip to match
    delay(wait);                           //  Pause for a moment
  }
}

//Color wipe for strip2
void colorWipe2(uint32_t color, int wait) {
  for (int i = 0; i < strip2.numPixels(); i++) { // For each pixel in strip...
    strip2.setPixelColor(i, color);         //  Set pixel's color (in RAM)
    strip2.show();                          //  Update strip to match
    delay(wait);                           //  Pause for a moment
  }
}



//Color wipe for the Flora neopixel
void colorWipe3(uint32_t color, int wait) {
  for (int i = 0; i < floraStrip.numPixels(); i++) { // For each pixel in strip...
    floraStrip.setPixelColor(i, color);         //  Set pixel's color (in RAM)
    floraStrip.show();                          //  Update strip to match
    delay(wait);                           //  Pause for a moment
  }
}
