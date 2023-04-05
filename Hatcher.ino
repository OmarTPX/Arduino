#include<VarSpeedServo.h>
#include <Wire.h>
#include "ClosedCube_HDC1080.h"
#include<LiquidCrystal_I2C.h>

#define Servo_1 10
#define Servo_2 11
#define turnning_time 21600
#define test 5000
unsigned long preMillis = 0;

LiquidCrystal_I2C lcd(0x27 , 16,2);
ClosedCube_HDC1080 hdc1080;
VarSpeedServo servo_1;
VarSpeedServo servo_2;

int turnning_counts = 0;

void setup()
{
  servo_1.attach(Servo_1);
  servo_2.attach(Servo_2);
	Serial.begin(9600);
	hdc1080.begin(0x40);
  lcd.init();
  lcd.backlight();
}

void loop()
{
  unsigned long ms = millis();
  if(ms - preMillis>=test){
    turnning_counts +=1;
    preMillis = ms;
    lcd.clear();
    lcd.print("Time For Turn");
    lcd.setCursor(0,1);
    lcd.print(turnning_counts);
    lcd.print(" Total Turns");
    delay(1000);
  }
  lcd.clear();
  lcd.setCursor(0,0);
	lcd.print("Temp=");
	lcd.print(hdc1080.readTemperature());
  lcd.print("C");
  lcd.setCursor(0,1);
  lcd.print("Humidity=");
	lcd.print(hdc1080.readHumidity());
	lcd.println("%               ");
	delay(1000);
} 
