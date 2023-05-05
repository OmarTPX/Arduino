#include <VarSpeedServo.h>
#include <Wire.h>
#include "ClosedCube_HDC1080.h"
#include <LiquidCrystal_I2C.h>

#define Servo_1 3
#define Servo_2 5
#define turnning_time 21600000
#define day 86400000
#define test 9000
#define day_print_delay 10000
#define Turn_print_delay 11000

unsigned long preMillis = 0, preMillis_2 = 0, preMillis_3 = 0, preMillis_4 = 0;

bool between(double number, double min, double max) {
  return number >= min && number <= max;
}

LiquidCrystal_I2C lcd(0x27, 16, 2);
ClosedCube_HDC1080 hdc1080;
VarSpeedServo servo_1;
VarSpeedServo servo_2;

int turnning_counts = 0;
int days = 0;
void setup() {
  servo_1.attach(Servo_1);
  servo_2.attach(Servo_2);
  Serial.begin(9600);
  hdc1080.begin(0x40);
  lcd.init();
  lcd.backlight();
  
}

void loop() {
  unsigned long ms = millis();
  if (ms - preMillis >= turnning_time) { // put test here to test the turning time 
    turnning_counts += 1;
    preMillis = ms;
    lcd.clear();
    lcd.print("Time For Turn");
    lcd.setCursor(0, 1);
    lcd.print(turnning_counts);
    lcd.print(" Total Turns");
    delay(1000);
    for (int x = 0; x < 270; x += 10) {
      servo_1.write(x, 10);
      servo_2.write(x, 10);
    }
    if (turnning_counts % 2 == 0) {
      for (int v = 270; v > 0; v -= 10) {
        servo_1.write(v, 10);
        servo_2.write(v, 10);
      }
    }
  }
  if (between(hdc1080.readTemperature(), 0, 37.50)) { 
    pinMode(8, OUTPUT);
    pinMode(9, OUTPUT);
  } else {
    pinMode(8, INPUT);
    pinMode(9, INPUT);
  }
  if (ms - preMillis_2 >= day) {
    days += 1;
    preMillis_2 = ms;
  }
  lcd.setCursor(0, 0);
  lcd.print("Temp=");
  lcd.print(hdc1080.readTemperature());
  lcd.print("C");
  lcd.setCursor(0, 1);
  lcd.print("Humidity=");
  lcd.print(hdc1080.readHumidity());
  lcd.println("%               ");
  if (ms - preMillis_3 >= day_print_delay) {
    preMillis_3 = ms;
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Days = ");
    lcd.print(days);
  }
  if (ms - preMillis_4 >= Turn_print_delay) {
    preMillis_4 = ms;
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Turns = ");
    lcd.print(turnning_counts);

  }
      delay(1000);

}
