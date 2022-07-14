#include<LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27 , 16,2);  //if lcd doesn't work use 0x3F instide of 0x27
int pina = A0;
int read;
float volt;
int led = 3;
int value;

void setup(){
  pinMode(read, INPUT);
  pinMode(led , OUTPUT);
  Serial.begin(9600);
  lcd.init();
  lcd.backlight();
}

void loop(){
    lcd.setCursor(0,0);
    value = analogRead(A0);
    analogWrite(led , value * 255. / 1023.);
  read = analogRead(pina);
  volt = read * 5. / 1023. ;
  lcd.print(volt);
}
