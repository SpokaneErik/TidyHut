//=============Begin Count==================================
//++Set count to saved value from before restart or power out++++
void lastCount() {
//----open flash memory-----false>read&write,  true> read only
   p.begin("test-1", false);
   q.begin("test-2", true);

//------read flash memory--------------
   unsigned int counter1 = p.getUInt("counter", 0);
   unsigned int counter2 = q.getUInt("counter", 0);

   raw_count = counter2;     // last recorded value of raw_count
   Serial.printf("raw_count recovered is: %u\n", raw_count);
   count_value= counter1;    // last recorded value of count_value
   Serial.printf("count_value is: %u\n", count_value);

//------save to flash memory (not used)------
   // p.putUInt("counter", counter1);
   // q.putUInt("counter", counter2);

//----close flash memory-------
   p.end();
   q.end();
 
   Buzzer1();
   
}
//---------End set Counts to saved value----------------------------------------------

//=====================Save Count==================
//+++saves count when it is changed+++(false>read&write,  true> read only)
void saveCount() {
   //----open flash memory-----
   p.begin("test-1", false);
   q.begin("test-2", false);

//------read flash memory (not used) --------------
  unsigned int counter1 = p.getUInt("counter", 0);
  unsigned int counter2 = q.getUInt("counter", 0);

//-----do stuff-------------
   counter1 = count_value;
   counter2 = raw_count;
   Serial.printf("Current counter1 value: %u\n", counter1);
   Serial.printf("Current counter2 value: %u\n", counter2);

//------save to flash memory------
   p.putUInt("counter", counter1);
   q.putUInt("counter", counter2);

//----close flash memory-------
   p.end();
   q.end();
 
   Buzzer4();
}
//-----------End Save Count-----------------------

//============Reset Count==================
//+++reset raw_count and count_value to begining value +++(false>read&write,  true> read only)
void resetCount() {
   //----open flash memory-----
   p.begin("test-1", false);
   q.begin("test-2", false);

//------read flash memory (not used) --------------
   unsigned int counter2 = q.getUInt("counter", 0);   
   unsigned int counter1 = p.getUInt("counter", 0);

//-----do stuff-------------
   count_value = count_value;
   raw_count = reset_raw_count;
   Serial.printf("Current counter1 value: %u\n", counter1);
   Serial.printf("Current counter2 value: %u\n", counter2);

///------save to flash memory------
   p.putUInt("counter", count_value);
   q.putUInt("counter", reset_raw_count);

//----close flash memory-------
   p.end();
   q.end();
 
   Buzzer4();
   esp_restart();
}
//-------------End Reset Count--------------------


/*//=============Begin Count==============================
//+++++++Sets count from before restart or power out++++++++
void lastCount() {

  p.begin("test-1", false);
  q.begin("test-2", true);
  unsigned int counter1 = p.getUInt("counter", 0);
  unsigned int counter2 = q.getUInt("counter", 0);

  counter1 = counter1 + 1;
  beginCount = counter2;
  count_value = counter2;
  Serial.printf("Current counter1 value: %u\n", counter1);
  Serial.printf("Current counter2 value: %u\n", counter2);
  Serial.printf("Current beginCount value: %u\n", beginCount);


  // p.putUInt("counter", counter1);
  // q.putUInt("counter", counter2);

  p.end();
  q.end();
}
//-------------------------------------------------------

//=====================Save Count==================
//+++++++++++saves count when it is changed+++++++++++
void saveCount() {
  p.begin("test-1", false);
  q.begin("test-2", false);
  unsigned int counter1 = p.getUInt("counter", 0);
  unsigned int counter2 = q.getUInt("counter", 0);

  counter1 = counter1 + 1;
  counter2--;
  count_value = counter2;
  Serial.printf("Current counter1 value: %u\n", counter1);
  Serial.printf("Current counter2 value: %u\n", counter2);


  p.putUInt("counter", counter1);
  q.putUInt("counter", counter2);

  p.end();
  q.end();
}
//---------------------------------------------------

//============Reset Count==================
//+++++++used to reset count to 115++++++++++++++++++
void resetCount() {
  q.begin("test-2", false);
  q.putUInt("counter", 115);
  q.end();
  //BuzzerA();
  //BuzzerBx2();
}
//----------------------------------------------------------*/
