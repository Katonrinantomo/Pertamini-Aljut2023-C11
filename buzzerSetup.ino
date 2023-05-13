

const int buzzer = 9; //masukkan pin arduino yang terpasang buzzer

void setup(){
  pinMode(buzzer, OUTPUT); // Set buzzer - pin 9 sebagai output
}

void loop(){
  tone(buzzer, 1000); // Send 1KHz sound signal...
  delay(1000);        // ...for 1 sec
  noTone(buzzer);     // Stop sound...
  delay(1000);        // ...for 1sec