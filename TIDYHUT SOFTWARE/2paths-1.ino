//++++++++TWO PATHS++++++++++
void twoPaths(){
  switch (modeCase) {
 
 //---------------------case 1  PUBLIC----------------------- 
  case 1:
    // statements  PUBLIC:
   // Serial.println("Switchcase HIGH,Public, modeCase is 1");
   // delay (500);
    
//-----------------[ALERT]----------------------
  if (count_value <= minBag) {          //nominally "Bag Count is 0"
    digitalWrite(redLed, HIGH);
    digitalWrite(yellowLed, LOW);
    digitalWrite(greenLed, LOW);
    blinkit();
    DoorLock();                // check to make sure only  runs if door has opened
    digitalWrite(motorIsolate, HIGH);              //motor is isolated from digital lock
   // Serial.println("Red");
    }
  //---------------------[WARNING]------------------
  else if (count_value <= warnBag) {    //nominally "Bag Count is 60 or less"
        digitalWrite(redLed, LOW);
    digitalWrite(yellowLed, HIGH);
    digitalWrite(greenLed, LOW);
    digitalWrite(motorIsolate, HIGH);   //motor is isolated from digital lock
    //Serial.println("yellow");
  }
  //-------------------[NORMAL OPERATION]--------------
  else {                                //"Bag Count is greater than 60" 
    digitalWrite(redLed, LOW);
    digitalWrite(yellowLed, LOW);
    digitalWrite(greenLed, HIGH);
    digitalWrite(motorIsolate, HIGH);   //motor is isolated from digital lock
   // Serial.println("green");
  }
    break;

  //-----------------------case 2  PRIVATE--------------------------  
  case 2:
  // Serial.println ("Switchcase HIGH, Private, modeCase is 2");
  //  delay (1000);
 
  //-----------------[ALERT]----------------------
  if (count_value <= 0 || count_value >=500 ) {  //Serial.println("Bag Count is 0");
    digitalWrite(redLed, HIGH);
    digitalWrite(yellowLed, LOW);
    digitalWrite(greenLed, LOW);
    blinkit();
    DoorLock();
    digitalWrite(motorIsolate, HIGH);   //motor is isolated from digital lock
  }
  //---------------------[WARNING]------------------
  else if (count_value <= warnBag) {    //Serial.println ("Bag Count is 60 or less");
    digitalWrite(redLed, LOW);
    digitalWrite(yellowLed, HIGH);
    digitalWrite(greenLed, LOW);
    DoorLock();   
    digitalWrite(motorIsolate, LOW);    //motor is active
  }
  //-------------------[NORMAL OPERATION]--------------
  else {                               // Serial.println ("Bag Count is greater than 60") ;
    digitalWrite(redLed, LOW);
    digitalWrite(yellowLed, LOW);
    digitalWrite(greenLed, HIGH);
    DoorLock();    
    digitalWrite(motorIsolate, LOW);   //motor is active

  }
    break;
}}
