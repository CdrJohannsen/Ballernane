#define TONEPIN 5
void setup() {


}

void loop() {
  for(int i = 32;i<250;i++){
    tone(TONEPIN, i);  //success
    delay(5);
  }
  tone(TONEPIN, 250,200);
  delay(200);
  noTone(TONEPIN);
  delay(10000);
}
