void Buzzer1() {
  tone(buzzer, 1000); // Send 1KHz sound signal...
  Serial.println ("Buzz1");
  delay(500);        // ...for 1 sec
  noTone(buzzer);     // Stop sound...
  delay(50);        // ...for 1sec
}
void Buzzer2(){
  tone(buzzer, 2000); // Send 1KHz sound signal...
  Serial.println ("Buzz2");
  delay(500);        // ...for 1 sec
  noTone(buzzer);     // Stop sound...
  delay(50);        // ...for 1sec
}
void Buzzer3() {
  tone(buzzer, 3000); // Send 1KHz sound signal...
  Serial.println ("Buzz3");
  delay(1000);        // ...for 1 sec
  noTone(buzzer);     // Stop sound...
  delay(50);        // ...for 1sec
}
void Buzzer4(){
  tone(buzzer, 500); // Send 1KHz sound signal...
  Serial.println ("Buzz4");
  delay(100);        // ...for 1 sec
  noTone(buzzer);     // Stop sound...
  delay(50);        // ...for 1sec
}
