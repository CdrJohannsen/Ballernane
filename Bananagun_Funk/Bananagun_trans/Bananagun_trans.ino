#include <RH_ASK.h>
#ifdef RH_HAVE_HARDWARE_SPI
#include <SPI.h>
#endif
#define BUTTON 12
#define LASER 11
#define PIN 10

RH_ASK driver(2000, 4, 2, 0);

int button = 1;
int tries = 5;
int hit = 2;
char message;
String ans;

void setup() {
  pinMode(BUTTON, INPUT_PULLUP);
  pinMode(LASER, OUTPUT);
  #ifdef RH_HAVE_SERIAL
      Serial.begin(9600);    // Debugging only
  #endif
      if (!driver.init())
  #ifdef RH_HAVE_SERIAL
           Serial.println("init failed");
  #else
    ;
  #endif
  reset();
}

void loop() {
  uint8_t buf[RH_ASK_MAX_MESSAGE_LEN];
  uint8_t buflen = sizeof(buf);
  button = digitalRead(BUTTON);
  if (button = LOW) {
    digitalWrite(LASER,HIGH);
    message = char(button);
    driver.send((uint8_t *)message, strlen(message));
    driver.waitPacketSent();
    delay(100);
    digitalWrite(LASER,LOW);
    for (int i = 2000; i > 31; i--) { //shot
      tone(PIN, i, 1);
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
    message = char(button);
    driver.send((uint8_t *)message, strlen(message));
    driver.waitPacketSent();
  }
  else {
    tries--;
  }
  if (driver.recv(buf, &buflen)){
  ans = char(buf[0]);
  hit = ans.toInt();
    if (hit == 1) {
      tone(PIN, 500, 100);  //success
      delay(100);
      tone(PIN, 800, 200);
      delay(200);
      noTone(PIN);
    }
    else if(hit==0) {
      tone(PIN, 120, 300);  //failed
      delay(370);
      tone(PIN, 60, 500);
      delay(500);
      noTone(PIN);
    }
    hit = 2;
  }
}

void reset() {
  tries = 5;
}
