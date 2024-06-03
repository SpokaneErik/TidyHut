 //================= doorState==============================    
 void checkdoorState () {
 doorState = digitalRead(doorSwitch);  //magnetic switch
  if (doorState == LOW) {
    Serial.println ("door is shut");
    //lastdoorState = LOW;
    digitalWrite(doorLed, LOW); //LED OFF WHEN DOOR IS SHUT
    //delay (100);
  }
  else {
    //Serial.println ("door is open");
    digitalWrite(doorLed, HIGH);  //LED ON WHEN DOOR OPEN
    doorState = HIGH;  //door was opened, therefore unlocked
    lastdoorState = HIGH;
  }}
 
//=========================doorLock============================
 void DoorLock() {
  //doorState = digitalRead(doorSwitch);     //read value of doorSwitch to make sure it can lock 
   if (doorState == LOW && lastdoorState == HIGH) {  
    digitalWrite(doorLed, LOW);  // TURN LED OFF ONCE CYCLE STARTS, 
    delay(lockDelaytime);                   // makes sure door is staying shut
    digitalWrite (motorIsolate, LOW);       // relay is not energized  (wired for NC)
    digitalWrite (doorLock, HIGH);          // relay is energized to signal door lock (wired for NO)
    Serial.println("Digital Lock is signaled");
    delay (1000);                            // wait for half second
    digitalWrite(doorLock, LOW);            // turnoff  relay (signal to door lock)
    Serial.println("Digital signal off");
    delay(5000);                            // wait for 5 second
    lastdoorState = LOW;
    delay (50);
  }}
