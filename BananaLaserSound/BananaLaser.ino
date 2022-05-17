#define PIN 12
void setup() {
  pinMode(PIN, OUTPUT);

}

void loop() {
  for (int i = 2000; i > 500; i--) {
    tone(PIN, i, 1);
  }
  noTone(PIN);
  delay(20);
  for (int i = 2000; i > 31; i--) { //shot
    tone(PIN, i, 1);
  }
  noTone(PIN);
  delay(200);
  for (int i = 2000; i > 1000; i--) {
    tone(PIN, i, 1);
  }
  noTone(PIN);
  delay(20);
  for (int i = 2000; i > 1000; i--) {
    tone(PIN, i, 1);
  }
  noTone(PIN);
  delay(20);
  for (int i = 2000; i > 31; i--) {
    tone(PIN, i, 1);
  }
  noTone(PIN);
  noTone(PIN);
  delay(200);
  for (int i = 2000; i > 1000; i--) {
    tone(PIN, i, 1);
  }
  noTone(PIN);
  delay(20);
  for (int i = 2000; i > 1000; i--) {
    tone(PIN, i, 1);
  }
  noTone(PIN);
  delay(20);
  for (int i = 2000; i > 1000; i--) {
    tone(PIN, i, 1);
  }
  noTone(PIN);
  delay(20);
  for (int i = 2000; i > 1000; i--) {
    tone(PIN, i, 1);
  }
  noTone(PIN);
  delay(20);
  for (int i = 2000; i > 1000; i--) {
    tone(PIN, i, 1);
  }
  noTone(PIN);
  delay(20);
  for (int i = 2000; i > 1000; i--) {
    tone(PIN, i, 1);
  }
  noTone(PIN);
  delay(20);
  for (int i = 2000; i > 1000; i--) {
    tone(PIN, i, 1);
  }
  noTone(PIN);
  delay(20);
  for (int i = 2000; i > 1000; i--) {
    tone(PIN, i, 1);
  }
  noTone(PIN);
  delay(20);
  for (int i = 2000; i > 1000; i--) {
    tone(PIN, i, 1);
  }
  noTone(PIN);
  delay(20);
  for (int i = 2000; i > 1000; i--) {
    tone(PIN, i, 1);
  }
  noTone(PIN);
  delay(20);
  for (int i = 2000; i > 1000; i--) {
    tone(PIN, i, 1);
  }
  noTone(PIN);
  delay(20);
  for (int i = 2000; i > 31; i--) {
    tone(PIN, i, 1);
  }
  noTone(PIN);
  delay(1000);
  
  tone(PIN, 120, 300);  //failed
  delay(370);
  tone(PIN, 60, 500);
  delay(500);
  noTone(PIN);
  delay(1000);

  tone(PIN, 500, 100);  //success
  delay(100);
  tone(PIN, 800, 200);
  delay(200);
  noTone(PIN);


  delay(10000);
}
