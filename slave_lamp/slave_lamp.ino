#include <SoftwareSerial.h>
#include <Adafruit_NeoPixel.h>

#define LED 6
#define BT_RX 2
#define BT_TX 3

Adafruit_NeoPixel strip = Adafruit_NeoPixel(59, LED, NEO_GRB + NEO_KHZ800); //(led개수,제어핀번호,타입flag)
SoftwareSerial BTSerial(BT_RX, BT_TX);

void colorWipe(uint32_t c, uint8_t wait);

int bt_baud = 9600;
int red;
int green;
int blue;
int lamp_action;
int start_flag;
String readString;

void setup() {
  Serial.begin(9600);
  BTSerial.begin(bt_baud);
  pinMode(LED, OUTPUT);
  strip.begin(); //모든 LED off
  strip.show();
}

void loop() {
  lamp_action = 0;
  for (uint8_t i = 0; i < strip.numPixels(); i++) {
    strip.setPixelColor(i, 0, 0, 0);
  }
  strip.show();
  GetBluetooth();

  Serial.print(red); Serial.print(", ");
  Serial.print(green); Serial.print(", ");
  Serial.print(blue); Serial.print(", ");
  Serial.println(lamp_action);

  while (lamp_action == 1) {
    rgbFadeInAndOut(red, green, blue, 10);
  }
}

void rgbFadeInAndOut(uint8_t red, uint8_t green, uint8_t blue, uint8_t wait) {
  for (uint8_t b = 40; b < 255; b++) {
    for (uint8_t i = 0; i < strip.numPixels(); i++) {
      strip.setPixelColor(i, red * b / 255, green * b / 255, blue * b / 255);
    }
    strip.show();
    delay(wait);
    GetBluetooth();
  }
  for (uint8_t b = 255; b > 40; b--) {
    for (uint8_t i = 0; i < strip.numPixels(); i++) {
      strip.setPixelColor(i, red * b / 255, green * b / 255, blue * b / 255);
    }
    strip.show();
    delay(wait);
    GetBluetooth();
  }
}

void GetBluetooth() {
  if (BTSerial.available()) {
    char c = BTSerial.read();

    if (c == ',') {       //delimited ',' string parse
      if (readString.length() > 1) { //reads characters into a string
        int n = readString.toInt();  //convert readString into a number

        if (readString.indexOf('r') > 0) {
          red = n;
        }
        else if (readString.indexOf('g') > 0) {
          green = n;
        }
        else if (readString.indexOf('b') > 0) {
          blue = n;
        }
        if (readString.indexOf('f') > 0) {
          lamp_action = n;
        }
        readString = ""; //clears variable for new input
      }
    }
    else {
      readString += c; //makes the string readString
    }
  }
}
