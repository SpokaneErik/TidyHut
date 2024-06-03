void blinkit(){
 int interval = (on)? strobeOn*1000 : strobeOff*1000;
 if (millis() > lastchange + interval){
on = !on;
lastchange = millis();
digitalWrite(alertLed, on);
}
}
