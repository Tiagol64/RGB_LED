#include <Adafruit_GFX.h>
#include <Adafruit_ST7789.h>
#include <SPI.h>

#define TFT_CS     4
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
  pinMode(6, OUTPUT);

  Serial.begin(9600);

  pinMode(TFT_BLK, OUTPUT);
  analogWrite(TFT_BLK, 255);

  tft.init(240, 240);
  tft.setRotation(2);
  tft.fillScreen(ST77XX_BLACK);
}

void loop() {

  int masterBrightness = analogRead(A4);
  int REDpotentiometerValue = analogRead(A3);
  int GREENpotentiometerValue = analogRead(A2);
  int BLUEpotentiometerValue = analogRead(A1);

  int REDbrightness = REDpotentiometerValue / 4; 
  int GREENbrightness = GREENpotentiometerValue / 4; 
  int BLUEbrightness = BLUEpotentiometerValue / 4;

  Serial.print("R: " + String(REDbrightness));
  Serial.print(" G: " + String(GREENbrightness));
  Serial.print(" B: " + String(BLUEbrightness));
  Serial.print(" W: " + String((float)masterBrightness / 1023));
  Serial.print("\n");

  analogWrite(redPIN, 255 - (REDbrightness * ((float)masterBrightness / 1023)));
  analogWrite(greenPIN, 255 - (GREENbrightness * ((float)masterBrightness / 1023)));
  analogWrite(bluePIN, 255 - (BLUEbrightness * ((float)masterBrightness / 1023)));

  tft.setTextSize(7);

  char buffer[4];

  tft.setCursor(0, 0);
  tft.setTextColor(ST77XX_RED, ST77XX_BLACK);
  sprintf(buffer, "%3d", REDbrightness);
  tft.print(buffer);

  tft.setCursor(0, 80);
  tft.setTextColor(ST77XX_GREEN, ST77XX_BLACK);
  sprintf(buffer, "%3d", GREENbrightness);
  tft.print(buffer);

  tft.setCursor(0, 160);
  tft.setTextColor(ST77XX_BLUE, ST77XX_BLACK);
  sprintf(buffer, "%3d", BLUEbrightness);
  tft.print(buffer);
}
