int redPIN = 9;
int greenPIN = 10;
int bluePIN = 11;

void setup() {

  pinMode(redPIN, OUTPUT);
  pinMode(greenPIN, OUTPUT);
  pinMode(bluePIN, OUTPUT);
  Serial.begin(9600);
}

void loop() {

  int REDpotentiometerValue = analogRead(A3);
  int GREENpotentiometerValue = analogRead(A2);
  int BLUEpotentiometerValue = analogRead(A1);

  int REDbrightness = REDpotentiometerValue / 4; 
  int GREENbrightness = GREENpotentiometerValue / 4; 
  int BLUEbrightness = BLUEpotentiometerValue / 4; 

  Serial.print("\n");
  Serial.print("RED: " + String(REDbrightness) + " GREEN: " + String(GREENbrightness) + " BLUE: " + String(BLUEbrightness));

  analogWrite(redPIN, 255 - REDbrightness);
  analogWrite(greenPIN, 255 - GREENbrightness);
  analogWrite(bluePIN, 255 - BLUEbrightness);

}
