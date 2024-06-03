//==================checkSwitch===================    
void checkSwitch() {            // Check status of mode switch
 if (digitalRead(modePin) == LOW) {
    // Switch is on,   Mode is Private
    modeState = LOW;
    modeCase = 2;
   // Serial.println ("Mode is private,modeState is LOW, modeCase is 2");
  }
  else   {
    // Switch is off; Mode is Public
    modeState = HIGH;
    modeCase =1;
  //  Serial.println ("Mode is  public, modeState is HIGH, modeCase is 1");
  }
}
