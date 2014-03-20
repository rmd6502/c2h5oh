#include <math.h>

void setup()
{
  pinMode(A0,INPUT);
  pinMode(3,OUTPUT);
  pinMode(5,OUTPUT);
  pinMode(6,OUTPUT);
  Serial.begin(9600);
}

void loop()
{
  static uint8_t redVal=0, greenVal=0, blueVal=0;
  int16_t angle = 0;

  uint16_t reading = analogRead(A0);
  Serial.print("reading "); Serial.print(reading);
  angle = map(reading, 130, 700, 120, 0);
  Serial.print(" angle "); Serial.println(angle);
  
  angleToRGB(angle, redVal, greenVal, blueVal);
  analogWrite(6,redVal);
  analogWrite(5,greenVal);
  analogWrite(3,blueVal);
  
//  Serial.print("angle "); Serial.print(angle);
//  Serial.print(" r "); Serial.print(redVal);
//  Serial.print(" g "); Serial.print(greenVal);
//  Serial.print(" b "); Serial.println(blueVal);
  
//  ++angle;
//  if (angle == 360) {
//    angle = 0;
//  }
  
  delay(20);
}

void angleToRGB(int16_t angle, uint8_t &red, uint8_t &green, uint8_t &blue)
{
  red = (stepCos(angle) * 255);
  blue = (stepCos(angle + 120) * 255);
  green = (stepCos(angle + 240) * 255);
}

double stepCos(int16_t angle)
{
  if (angle < 0) {
    angle += 360;
  }
  if (angle > 360) {
    angle -= 360;
  }
  double adjusted = angle * 1.5f;
  if (adjusted >= 180.0f && adjusted < 360.0f) {
    return 0.0f;
  }
  if (adjusted >= 360.0f) {
    adjusted -= 180.0f;
  }
  return cos(adjusted * M_PI / 180.0f) / 2.0f + 0.5f;
}
  


