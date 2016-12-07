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
bool lamp_switch;
String str = "";

void setup() {
  Serial.begin(9600);
  BTSerial.begin(bt_baud);
  BTSerial.setTimeout(200);
  pinMode(LED, OUTPUT);
  strip.begin(); //모든 LED off
  strip.show();
}

void loop() {
  if (lamp_switch) {
    rgbFadeInAndOut(red, green, blue, 10);
  }
  else {
    for (uint8_t i = 0; i < strip.numPixels(); i++) {
      strip.setPixelColor(i, 0, 0, 0);
    }
  }
  strip.show();
  GetBluetooth();
  Serial.print(red); Serial.print(", ");
  Serial.print(green); Serial.print(", ");
  Serial.println(blue);

}

void rgbFadeInAndOut(uint8_t red, uint8_t green, uint8_t blue, uint8_t wait) {
  for (uint8_t b = 40; b < 255; b++) {
    for (uint8_t i = 0; i < strip.numPixels(); i++) {
      strip.setPixelColor(i, red * b / 255, green * b / 255, blue * b / 255);
    }
    strip.show();
    delay(wait);
    GetBluetooth();
    if(lamp_switch == LOW)
      break;
  }
  for (uint8_t b = 255; b > 40; b--) {
    for (uint8_t i = 0; i < strip.numPixels(); i++) {
      strip.setPixelColor(i, red * b / 255, green * b / 255, blue * b / 255);
    }
    strip.show();
    delay(wait);
    GetBluetooth();
    if(lamp_switch == LOW)
      break;
  }
}

void GetBluetooth() {
  if (BTSerial.available()) {
    str = BTSerial.readString();
    if (str.charAt(0) == '<' and str.charAt(str.length() - 1) == '>') {     //delimited ',' string parse
      int first = str.indexOf(",");
      int second = str.indexOf(",", first + 1);
      int third = str.indexOf(",", second + 1);
      int fourth = str.indexOf(">", third);

      String str1 = str.substring(1, first);
      String str2 = str.substring(first + 1, second);
      String str3 = str.substring(second + 1, third);
      String str4 = str.substring(third + 1, fourth);

      if (str1 == "o")
        lamp_switch = HIGH;
      else
        lamp_switch = LOW;

      red = str2.toInt();
      green = str3.toInt();
      blue = str4.toInt();
    }
  }
}
