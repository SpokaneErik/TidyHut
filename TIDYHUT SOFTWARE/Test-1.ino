//++++++++++++++++++++ Test Sequence ++++++++++++++++++++++++
void startTest() {
     digitalWrite(redLed, HIGH);
     digitalWrite(yellowLed, HIGH);
     digitalWrite(greenLed, HIGH);
     digitalWrite(alertLed, HIGH);     // energizes mosfet, ( test strobe connected to power)
     delay (10000);
 
  digitalWrite(motorIsolate, HIGH); // energizes relay, (contacts open, motor isolated)
  delay(1000);                      // test relay connection
  digitalWrite(motorIsolate, LOW);  // connects motor to digital lock ( allows unlock)

 // digitalWrite(doorLock, HIGH);     // energizes relay, (contacts shut, shut signal sent)
 // delay(1000);                      // test relay connection
 // digitalWrite(doorLock, LOW);      // de-energizes relay, (contacts open, normal keypad operation)

  digitalWrite(flushMotor, HIGH);   // energizes relay, ( contact shut, motor on)
  delay(1000);                      // test flush relay
  digitalWrite(flushMotor, LOW);    // de-energized relay( contact open, motor off)

    digitalWrite(redLed, LOW);
    digitalWrite(yellowLed, LOW);
    digitalWrite(greenLed, LOW);
    digitalWrite(alertLed, LOW);      // de-energized mosfet ( stobe disconnected from power)

}
