#include <Adafruit_GFX.h>
#include <Adafruit_ST7789.h>
#include <SPI.h>

#define TFT_CS     6
#define TFT_RST    8
#define TFT_DC     7
#define TFT_BLK    5

Adafruit_ST7789 tft = Adafruit_ST7789(TFT_CS, TFT_DC, TFT_RST);

int redPIN = 9;
int greenPIN = 10;
int bluePIN = 3;

void setup() {

  pinMode(redPIN, OUTPUT);
  pinMode(greenPIN, OUTPUT);
  pinMode(bluePIN, OUTPUT);

  Serial.begin(9600);

  pinMode(TFT_BLK, OUTPUT);
  analogWrite(TFT_BLK, 255);

  tft.init(240, 240);
  tft.setRotation(2);
  tft.fillScreen(ST77XX_BLACK);
  tft.setTextSize(7);
}

void loop() {

  int REDpotentiometerValue = analogRead(A3);
  int GREENpotentiometerValue = analogRead(A2);
  int BLUEpotentiometerValue = analogRead(A1);

  int REDbrightness = REDpotentiometerValue / 4; 
  int GREENbrightness = GREENpotentiometerValue / 4; 
  int BLUEbrightness = BLUEpotentiometerValue / 4;

  Serial.println("R: " + String(REDbrightness) + " G: " + String(GREENbrightness) + " B: " + String(BLUEbrightness));

  analogWrite(redPIN, 255 - REDbrightness);
  analogWrite(greenPIN, 255 - GREENbrightness);
  analogWrite(bluePIN, 255 - BLUEbrightness);

  tft.fillRect(0, 0, 240, 240, ST77XX_BLACK);

  tft.setCursor(0, 0);
  tft.setTextColor(ST77XX_RED);
  tft.print(String(REDbrightness));

  tft.setCursor(0, 80);
  tft.setTextColor(ST77XX_GREEN);
  tft.print(String(GREENbrightness));

  tft.setCursor(0, 160);
  tft.setTextColor(ST77XX_BLUE);
  tft.print(String(BLUEbrightness));

  delay(80);
}
