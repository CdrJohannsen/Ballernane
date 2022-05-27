/*
Copyright (C) 2022  Cdr_Johannsen
This program is free software; you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation; either version 3 of the License, or (at your option) any later version.
This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.
You should have received a copy of the GNU General Public License along with this program; if not, see <http://www.gnu.org/licenses/>. 
 */
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#define BUTTON 10
#define LASER 6
#define TONEPIN 5

RF24 radio(7, 8); // CE, CSN

const byte addresses[][6] = {"00001", "00002"};
int button = 1;
int tries = 3;
int hit = 2;

void setup() {
  radio.begin();
  radio.openWritingPipe(addresses[1]); // 00002
  radio.openReadingPipe(1, addresses[0]); // 00001
  radio.setPALevel(RF24_PA_MIN);
  pinMode(BUTTON, INPUT_PULLUP);
  pinMode(LASER, OUTPUT);
  reset();
}

void loop() {
  button = digitalRead(BUTTON);
  if (button = LOW) {
    digitalWrite(LASER,HIGH);
    radio.stopListening();
    radio.write(&button, sizeof(button)); //damit das Ziel auch was machen kann (blinken oder so)
    radio.startListening();
    delay(100);
    digitalWrite(LASER,LOW);
    for (int i = 2000; i > 31; i--) { //shot
      tone(TONEPIN, i, 1);
    }
  }
  delay(5);
  if (tries = 0) {
    delay(500);

    reset();
    button = digitalRead(BUTTON);
    while(button=1){
      delay(50);
       button = digitalRead(BUTTON);
    }
    button = 2;
    radio.stopListening();
    radio.write(&button, sizeof(button));
    radio.startListening();
  }
  else {
    tries--;
  }
  while (!radio.available());
  radio.read(&hit, sizeof(hit));
  if (hit == 1) {
    tone(TONEPIN, 500, 100);  //success
    delay(100);
    tone(TONEPIN, 800, 200);
    delay(200);
    noTone(TONEPIN);
  }
  else if(hit==0) {
    tone(TONEPIN, 120, 300);  //failed
    delay(370);
    tone(TONEPIN, 60, 500);
    delay(500);
    noTone(TONEPIN);
  }
  hit = 2;
}

void reset() {
  tries = 3;
}
