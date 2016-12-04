#include <SoftwareSerial.h>
#include <Adafruit_NeoPixel.h>

#define LED 6
#define BT_RX 2
#define BT_TX 3

Adafruit_NeoPixel strip = Adafruit_NeoPixel(40, LED, NEO_GRB + NEO_KHZ800); //(led개수,제어핀번호,타입flag)
SoftwareSerial BTSerial(BT_RX, BT_TX);

void colorWipe(uint32_t c, uint8_t wait);

char c;
int bt_baud = 9600;
int red;
int green;
int blue;

String readString;

void setup() {
  Serial.begin(9600);
  BTSerial.begin(bt_baud);
  strip.begin();
  strip.show();
}

void loop() {

  if (BTSerial.available()) {
    c = BTSerial.read();
    if (c == ',') {       //delimited ',' string parse
      if (readString.length() > 1) { //reads characters into a string
        int n = readString.toInt();  //convert readString into a number

        if (readString.indexOf('r') > 0) {
          red = n;
        }
        if (readString.indexOf('g') > 0) {
          green = n;
        }
        if (readString.indexOf('b') > 0) {
          blue = n;
        }
        readString = ""; //clears variable for new input
      }
    }
    else {
      readString += c; //makes the string readString
    }
  }
  Serial.print("red = " + String(red) + "\n");
  Serial.print("green = " + String(green) + "\n");
  Serial.print("blue = " + String(blue) + "\n");
  
 // colorWipe(strip.Color(red, green, blue), 50);

}

void colorWipe(uint32_t c, uint8_t wait) {
  for (uint16_t i = 0; i < strip.numPixels(); i++) {
    strip.setPixelColor(i, c);
    strip.show();
    delay(wait);
  }
}
