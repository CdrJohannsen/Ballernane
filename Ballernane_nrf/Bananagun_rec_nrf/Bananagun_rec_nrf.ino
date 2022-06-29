/*
  Copyright (C) 2022  Cdr_Johannsen
  This program is free software; you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation; either version 3 of the License, or (at your option) any later version.
  This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.
  You should have received a copy of the GNU General Public License along with this program; if not, see <http://www.gnu.org/licenses/>.
*/
#include <Servo.h>
#include <SPI.h>
#include <LiquidCrystal_I2C.h>
#include <nRF24L01.h>
#include <RF24.h>
#define SENSOR1 9
#define SENSOR2 10
#define SENSOR3 11
#define SINGLE_TARGET false

uint8_t star[8]  = {0x0, 0x0, 0x15, 0xe, 0x1f, 0xe, 0x15, 0x0};

RF24 radio(7, 8); // CE, CSN ← ich weiß nicht ob ich die pins ändern kann...

const byte addresses[][6] = {"00001", "00002"};

Servo servo1;
Servo servo2;
Servo servo3;

int targets_hit = 0;
int shots = 0;
int hit = 2;
int message = 1;

LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
  Serial.begin(9600);
  radio.begin();
  radio.openWritingPipe(addresses[0]); // 00001
  radio.openReadingPipe(1, addresses[1]); // 00002
  radio.setPALevel(RF24_PA_MIN);
  radio.startListening();

  lcd.begin();
  lcd.backlight();
  lcd.createChar(0, star);
  lcd.home();
  lcd.clear();

  pinMode(53, OUTPUT);
  digitalWrite(53, LOW);

  pinMode(SENSOR1, INPUT);
  pinMode(SENSOR2, INPUT);
  pinMode(SENSOR3, INPUT);

  servo1.attach(2);
  servo2.attach(3);
  servo3.attach(4);
  reset();
  lcd.clear();
  lcd.print("Welcome!");
  delay(2000);
}

void loop() {
  message = 1;
  if (radio.available() == true) {
    radio.read(&message, sizeof(message));
    Serial.print("Radio avaliable: ");
    Serial.println(message);
    if (message == 2) {
      reset();
    }
    else if (message == 0) {
      shots++;
      hit = 1;
      Serial.println("Shot");
    }
  }

  targetRun();
  if (hit != 0 || message == 0) {
    Serial.println("clearing");
    lcd.clear();
    lcd.print("Shots fired:");
    lcd.print(shots);
    lcd.print("/3");
    lcd.setCursor(0, 1);
    lcd.print("Targets hit:");
    lcd.print(targets_hit);
    lcd.print("/3");
    hit = 0;
  }

  if (shots >= 3) {
    Serial.println("shots == 3");
    delay(2000);
    lcd.clear();
    if (targets_hit == 3) {
      lcd.print("Fantastic run!");
      lcd.setCursor(5, 1);
      lcd.write(0);
      lcd.print(" ");
      lcd.write(0);
      lcd.print(" ");
      lcd.write(0);
    }
    else if (targets_hit == 2) {
      lcd.print("Could be better.");
      lcd.setCursor(5, 1);
      lcd.write(0);
      lcd.print(" ");
      lcd.write(0);
      lcd.print(" ");
      lcd.write(0);
    }
    else {
      lcd.print("Try again!");
    }
    bool reseted = false;
    while (!reseted) {
      if (radio.available()) {
        radio.read(&message, sizeof(message));
        if (message == 2) {
          reset();
          reseted = true;
        }
      }
    }
  }
}
void reset() {
  Serial.println("resetting");
  servo1.write(0);
  servo2.write(0);
  servo3.write(0);
  targets_hit = 0;
  shots = 0;
  hit = 2;
  Serial.println("resetted");
}
void targetRun() {
  int temp_tar = targets_hit;
  if (SINGLE_TARGET) {
    if (digitalRead(SENSOR1)) {
      servo1.write(90);
      targets_hit++;
      servo1.write(0);
    }
    return;
  }
  if (true) {// ----------------------------NUR ZUM TESTEN!!!

  }
  else if (digitalRead(SENSOR1)) {
    servo1.write(90);
    targets_hit++;
  }
  else if (digitalRead(SENSOR2)) {
    servo2.write(90);
    targets_hit++;
  }
  else if (digitalRead(SENSOR3)) {
    servo3.write(90);
    targets_hit++;
  }
  /*
    if (temp_tar < targets_hit) {
    radio.stopListening();
    hit = 1;
    radio.write(&hit, sizeof(hit));
    radio.startListening();
    }

    else if(message==0){
    radio.stopListening();
    hit = 0;
    radio.write(&hit, sizeof(hit));
    radio.startListening();
    }
  */
}
