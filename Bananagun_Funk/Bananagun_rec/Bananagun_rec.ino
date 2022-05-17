#include <Servo.h>
#include <LiquidCrystal_I2C.h>
#include <RH_ASK.h>
#ifdef RH_HAVE_HARDWARE_SPI
#include <SPI.h>
#endif
#define SENSOR1 9
#define SENSOR2 10
#define SENSOR3 11
#define SENSOR4 12
#define SENSOR5 13

uint8_t star[8]  = {0x0, 0x0, 0x15, 0xe, 0x1f, 0xe, 0x15, 0x0};

RH_ASK driver(2000, 8, 5, 0);

Servo servo1;
Servo servo2;
Servo servo3;
Servo servo4;
Servo servo5;

int targets_hit = 0;
int shots = 0;
char hit = 2;
int message = 1;
String ans;

LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
  #ifdef RH_HAVE_SERIAL
      Serial.begin(9600);    // Debugging only
  #endif
      if (!driver.init())
  #ifdef RH_HAVE_SERIAL
           Serial.println("init failed");
  #else
    ;
  #endif
  Serial.begin(9600);

  lcd.begin();
  lcd.backlight();
  lcd.createChar(0, star);
  lcd.home();

  pinMode(SENSOR1, INPUT);
  pinMode(SENSOR2, INPUT);
  pinMode(SENSOR3, INPUT);
  pinMode(SENSOR4, INPUT);
  pinMode(SENSOR5, INPUT);

  servo1.attach(2);
  servo2.attach(3);
  servo3.attach(4);
  servo4.attach(5);
  servo5.attach(6);
  reset();
}

void loop() {
  uint8_t buf[RH_ASK_MAX_MESSAGE_LEN];
  uint8_t buflen = sizeof(buf);
  if (driver.recv(buf, &buflen)){
    message = int(char(buf[0]));
    if (message = 2) {
      reset();
    }
    else if(message=0){
      shots++;
    }
  }
  targetRun();
  lcd.clear();
  lcd.print("Shots fired:");
  lcd.print(shots);
  lcd.print("/5");
  lcd.setCursor(0,1);
  lcd.print("Targets hit:");
  lcd.print(targets_hit);
  lcd.print("/5");
  if(shots=5){
    lcd.clear();
    if (targets_hit = 5) {
      delay(1000);
      lcd.print("Fantastic run!");
      lcd.setCursor(3,1);
      lcd.write(0);
      lcd.print(" ");
      lcd.write(0);
      lcd.print(" ");
      lcd.write(0);
      lcd.print(" ");
      lcd.write(0);
      lcd.print(" ");
      lcd.write(0);
    }
    else if (targets_hit = 4) {
      delay(1000);
      lcd.print("Not too Bad!");
      lcd.setCursor(4,1);
      lcd.write(0);
      lcd.print(" ");
      lcd.write(0);
      lcd.print(" ");
      lcd.write(0);
      lcd.print(" ");
      lcd.write(0);
    }
    else if (targets_hit = 3) {
      delay(1000);
      lcd.print("Could be better.");
      lcd.setCursor(5,1);
      lcd.write(0);
      lcd.print(" ");
      lcd.write(0);
      lcd.print(" ");
      lcd.write(0);
    }
    else if (targets_hit = 2) {
      delay(1000);
      lcd.print("Hit the targets!");
      lcd.setCursor(6,1);
      lcd.write(0);
      lcd.print(" ");
      lcd.write(0);
    }
    else if (targets_hit = 1) {
      delay(1000);
      lcd.print("Quite bad!");
      lcd.setCursor(7,1);
      lcd.write(0);
    }
    else{
      delay(1000);
      lcd.print("Try again!");
    }
  }
  delay(10);
}
void reset() {
  servo1.write(0);
  servo2.write(0);
  servo3.write(0);
  servo4.write(0);
  servo5.write(0);
  targets_hit = 0;
}
void targetRun() {
  int temp_tar = targets_hit;
  if (digitalRead(SENSOR1)) {
    servo1.write(90);
    targets_hit++;
  }
  if (digitalRead(SENSOR2)) {
    servo2.write(90);
    targets_hit++;
  }
  if (digitalRead(SENSOR3)) {
    servo3.write(90);
    targets_hit++;
  }
  if (digitalRead(SENSOR4)) {
    servo4.write(90);
    targets_hit++;
  }
  if (digitalRead(SENSOR5)) {
    servo5.write(90);
    targets_hit++;
  }
  if(temp_tar > targets_hit){
    hit = "1";
    driver.send((uint8_t *)hit, strlen(hit));
    driver.waitPacketSent();
  }
  else if(message=0){
    hit = "0";
    driver.send((uint8_t *)hit, strlen(hit));
    driver.waitPacketSent();
  }
}
