#include <SoftwareSerial.h>
#include <Adafruit_NeoPixel.h>

#define LED 6
#define BT_RX 2
#define BT_TX 3

Adafruit_NeoPixel strip = Adafruit_NeoPixel(40, LED, NEO_GRB + NEO_KHZ800); //(led개수,제어핀번호,타입flag)
SoftwareSerial BTSerial(BT_RX, BT_TX);

void colorWipe(uint32_t c, uint8_t wait);

int c;

void setup() {
  BTSerial.begin(9600);
  strip.begin();
  strip.show();
}

void loop() {
//    for (int a = 5; a < 255 ; a++) {
//      colorWipe(strip.Color(255, 255, 0), 1);
//      delay(5);
//    }
//    for (int a = 255; a > 5 ; a--) {
//      colorWipe(strip.Color(255, 255, 0), 1);
//      delay(5);
//    }

  if (BTSerial.available()) {
    c = BTSerial.read();
  }

  if (c == 'r') {
    colorWipe(strip.Color(255, 0, 0), 50); 
  }
  if (c == 'g') {
    colorWipe(strip.Color(0, 255, 0), 50); 
  }
  if (c == 'b') {
    colorWipe(strip.Color(0, 0, 255), 50); 
  }
  if (c == 'y') {
    colorWipe(strip.Color(255, 255, 0), 50);
  }

}

void colorWipe(uint32_t c, uint8_t wait) {
  for (uint16_t i = 0; i < strip.numPixels(); i++) {
    strip.setPixelColor(i, c);
    strip.show();
    delay(wait);
  }
}
