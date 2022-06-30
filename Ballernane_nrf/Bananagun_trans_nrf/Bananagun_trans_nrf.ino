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
#define AIM_BUTTON 9
#define LASER 6
#define TONEPIN 5

RF24 radio(7, 8); // CE, CSN

const byte addresses[][6] = {"00001", "00002"};
int button = 1;
int tries = 2;
int hit = 2;

void setup() {
  Serial.begin(9600);
  if (!radio.begin()) {
    Serial.println("[DEBUG] Radio hardware is not responding!");
  }
  radio.openWritingPipe(addresses[1]); // 00002
  radio.openReadingPipe(1, addresses[0]); // 00001
  radio.setPALevel(RF24_PA_MIN);
  pinMode(BUTTON, INPUT_PULLUP);
  pinMode(LASER, OUTPUT);
  reset();
}

void send_message(int send_message, String serial_send_message = "Sending...") {
  radio.stopListening();
  Serial.println(serial_send_message);
  radio.write(&send_message, sizeof(send_message));
  radio.startListening();
}

void loop() {
  while (true) {

    while (true) {
      button = digitalRead(BUTTON);
      if (button == LOW) {
        Serial.println("press");
        delay(500);
        digitalWrite(LASER, HIGH);
        send_message(button);
        delay(100);
        digitalWrite(LASER, LOW);
        for (int i = 2000; i > 31; i--) { //shot
          tone(TONEPIN, i, 1);
        }
        break;
      }
      delay(10);
    }
    if (tries == 0) {
      Serial.println("Shots fired...");
      delay(500);

      button = 1;
      while (button == 1) {
        delay(50);
        button = digitalRead(BUTTON);
      }

      delay(500);
      reset();
      continue;
    }
    else {
      tries--;
    }
    Serial.print("Tries: ");
    Serial.println(tries);
    /*
      radio.startListening();
      delay(10);
      Serial.println(radio.available());
      long temp_time = millis();
      while (!radio.available()) {
      Serial.println("Waiting for answer");
      if (temp_time + 1000 < millis()) {
        Serial.println("No answer");
        break;
      }
      }
      Serial.println(radio.available());
      radio.read(&hit, sizeof(hit));
      radio.stopListening();
      if (hit == 1) {
      tone(TONEPIN, 500, 100);  //success
      delay(100);
      tone(TONEPIN, 800, 200);
      delay(200);
      noTone(TONEPIN);
      }
      else if (hit == 0) {
      Serial.println("Failed shot");
      tone(TONEPIN, 120, 300);  //failed
      delay(370);
      tone(TONEPIN, 60, 500);
      delay(500);
      noTone(TONEPIN);
      }
    */
    hit = 2;
  }
}

void reset() {
  Serial.println("[DEBUG] Reset");
  tries = 2;
  for (int t = 32; t < 250; t++) {
    tone(TONEPIN, t);
    delay(5);
  }
  tone(TONEPIN, 250, 200);
  delay(200);
  noTone(TONEPIN);
  send_message(2,"[DEBUG] Send request to reset");
}
