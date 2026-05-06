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
int toggleBTN = 12;

int mode = LOW;
int lastButtonState = HIGH;

void setup() {

  pinMode(redPIN, OUTPUT);
  pinMode(greenPIN, OUTPUT);
  pinMode(bluePIN, OUTPUT);
  pinMode(toggleBTN, INPUT_PULLUP);

  Serial.begin(9600);

  pinMode(TFT_BLK, OUTPUT);
  analogWrite(TFT_BLK, 255);

  tft.init(240, 240);
  tft.setRotation(2);
  tft.fillScreen(ST77XX_BLACK);
}

void loop() {
  int currentButtonState = digitalRead(toggleBTN);
  int masterBrightness = analogRead(A4);
  int REDpotentiometerValue = analogRead(A3);
  int GREENpotentiometerValue = analogRead(A2);
  int BLUEpotentiometerValue = analogRead(A1);
  int light = analogRead(A0);
  float lightcalc = ((float)light /1023);

  int REDbrightness = REDpotentiometerValue / 4; 
  int GREENbrightness = GREENpotentiometerValue / 4; 
  int BLUEbrightness = BLUEpotentiometerValue / 4;

  Serial.print("R: " + String(int(((float)REDbrightness / 255) * 100)));
  Serial.print(" G: " + String(int(((float)GREENbrightness / 255) * 100)));
  Serial.print(" B: " + String(int(((float)BLUEbrightness / 255) * 100)));
  Serial.print(" W: " + String(int(((float)masterBrightness / 1023) * 100)));
  Serial.print(" L: " + String(lightcalc * 100));
  Serial.print("\n");

  if (currentButtonState == LOW && lastButtonState == HIGH) {
    mode = !mode;
    delay(50);
  }

  lastButtonState = currentButtonState;
  String modeDPL = "P";

  if (mode == HIGH) {
    analogWrite(redPIN, 255 - (REDbrightness * lightcalc));
    analogWrite(greenPIN, 255 - (GREENbrightness * lightcalc));
    analogWrite(bluePIN, 255 - (BLUEbrightness * lightcalc));
    modeDPL = "L";
  } else {
    analogWrite(redPIN, 255 - (REDbrightness * ((float)masterBrightness / 1023)));
    analogWrite(greenPIN, 255 - (GREENbrightness * ((float)masterBrightness / 1023)));
    analogWrite(bluePIN, 255 - (BLUEbrightness * ((float)masterBrightness / 1023)));
    modeDPL = "P";
  }

  tft.setTextSize(6.5);

  char buffer[7];

  tft.setCursor(60, 0);
  tft.setTextColor(ST77XX_RED, ST77XX_BLACK);
  sprintf(buffer, "%3d", int(((float)REDbrightness / 255) * 100));
  tft.print(buffer);

  tft.setCursor(60, 48);
  tft.setTextColor(ST77XX_GREEN, ST77XX_BLACK);
  sprintf(buffer, "%3d", int(((float)GREENbrightness / 255) * 100));
  tft.print(buffer);

  tft.setCursor(60, 96);
  tft.setTextColor(ST77XX_BLUE, ST77XX_BLACK);
  sprintf(buffer, "%3d", int(((float)BLUEbrightness / 255) * 100));
  tft.print(buffer);

  tft.setCursor(60, 144);
  tft.setTextColor(ST77XX_WHITE, ST77XX_BLACK);
  sprintf(buffer, "%3d", int(((float)masterBrightness / 1023) * 100));
  tft.print(buffer);

  tft.setCursor(60, 192);
  tft.setTextColor(ST77XX_WHITE, ST77XX_BLACK);
  sprintf(buffer, "%3d", int(lightcalc * 100));
  tft.print(buffer);

  tft.setCursor(0, 0);
  tft.setTextColor(ST77XX_WHITE, ST77XX_BLACK);
  tft.print(modeDPL);
}


