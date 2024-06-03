
//TidyHut231019 6Bd

// code written by Kraig Lysek
// April 2024
// all rights reserved
// Use board 'ESP32 WROOM DA module' in ide
/*
   count and reset interupts
   persistance for retaining last count
   count interupt removed and replaced by state change detection.
   will consider for reset also in next version.

*/

//-------------------LIBRARIES------------------------
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Preferences.h>

//-----Setup for PERSISTANT COUNT over restart and power out----
Preferences p;
Preferences q;

//-------------reset button  and count lever interupt----------
struct Button {
  const uint8_t PIN;
  uint32_t numberKeyPresses;
  bool pressed;
};

Button button = {15, 0, false};
unsigned long button_time = 0;
unsigned long last_button_time = 0;
unsigned long reset_time = 0;
unsigned long last_reset_time = 0;

void IRAM_ATTR reset_isr() {
  button_time = millis();
  if (button_time - last_button_time > 250 )
  {
    button.numberKeyPresses++;
    button.pressed = true;
    last_button_time = button_time;
  }
}
//---------------end interrupt---------------------------------

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//-------Setup Variables-change these for testing or modification---------
const int minBag = 0;             // count that locks tidyhut (nominal 0 left)
const int warnBag = 60;           // count that turns on warning lights (nominal 60 left)
const int beginBag = 115;
const int clicks_per_bag = 4;           //2 count per rotation,  2 count per lever pull, 2 rotations per bag
const int lockDelaytime = 1500;   // set time from door shut to door lock (nominal 1500, 1.5 seconds; )

const int strobeOn = 15;          // seconds strobe blinks
const int strobeOff = 15;         // seconds strobe is not blinking
long int lastchange = millis();   // used for alert strobe blink subroutine
bool on = false;                  // used for alert strobe blink subroutine
unsigned long currentMillis;
unsigned long interval = 1000; // start value set to 1 second

String ver = "Ver 6Be";           // version # installed
String micro = "ESP32-WROOM-DA";  // microcontroller in use
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//-------------OLED--------------------[GPIO21-(SDA), GPIO22-(SCL)]
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

//----------------define names to pin numbers-------------------------------------------
#define buzzer  4          // Output -  LOCAL set buzzer; (reset notification)
#define motorIsolate  13   // Output -  D9A GREEN Relay 1; isolates power to motor (NC)
#define doorLock  14       // Output -  D9A BROWN Relay 2; key bypass to lock door (NO)
#define flushMotor  19     // Output -  D9B BLUE Relay 3; power to  12V flush motor
#define greenLed  25       // Output -  D9A BLUE
#define yellowLed  26      // Output -  D9A YELLOW
#define redLed  27         // Output -  D9A ORANGE
#define alertLed  2        // Output -  D9A YELLOW TIP120 base pin w/5K resistor (norm LOW)
#define doorLed 12         // Output -  D9A PURPLE  (on when door OPEN)

#define flushButton 5      // Input -   D9B PURPLE; starts flush motor time sequence
#define leverPin  18       // Input -   D9B GRAY Opto switch; 8 slots/rev-lever pulled,(NO)
#define modePin  23        // Input -   LOCAL RED Sw1 Shut (high == public), Open (low == private)
#define doorSwitch  33     // Input -   D9A GRAY; door open or shut (NC)

// +++++variables and states will change:++++
//int leverState = 0;            // variable for reading the pushbutton status
//int prestate = 0;               // used in count debounce
unsigned int raw_count = beginBag * clicks_per_bag;   //used with multiple clicks per bag (currently 4)
unsigned int reset_raw_count = 460; //(beginBag * clicks_per_bag);   //used with multiple clicks per bag (currently 4)

unsigned int count_value = beginBag;     // starting count for bags
int lastdoorState = LOW;        // used in verifing if door opened since doorLock run
int doorState;                  // stores current state of door(0-shut, 1-open)
int modeState = LOW;            // Starts mode in (LOW-Private, HIGH-Public)
int modeCase = 2;               // Switch Case for mode selection (2-Private, 1-Public)
int test = 0;
int leverPullCounter = beginBag * clicks_per_bag;   // counter for the number of button presses
int leverState = 0;         // current state of the button
int lastLeverState = 0;     // previous state of the button
//--------------------------[SETUP]-----------------------
void setup() {
  Serial.begin(115200);
  Serial.println ("starting");
  delay (1000);
  //++++initialize the output pins:+++++
  pinMode(buzzer, OUTPUT);        // 04Pin
  pinMode(motorIsolate, OUTPUT);  // 13Pin  relay 1
  pinMode(doorLock, OUTPUT);      // 14Pin  relay 2
  pinMode(flushMotor, OUTPUT);    // 19Pin  relay 3
  pinMode(greenLed, OUTPUT);      // 25Pin
  pinMode(yellowLed, OUTPUT);     // 26Pin
  pinMode(redLed, OUTPUT);        // 27Pin
  pinMode(alertLed, OUTPUT);      // 32Pin  TIP120 base
  pinMode(doorLed, OUTPUT);       // 12Pin

  //++++initialize the input pins:++++++
  pinMode(flushButton, INPUT_PULLUP);  //  5Pin
  pinMode(leverPin, INPUT_PULLUP);    // 18Pin
  pinMode(modePin, INPUT_PULLUP);      // 23Pin
  pinMode(doorSwitch, INPUT_PULLUP);   // 33Pin
  pinMode(button.PIN, INPUT_PULLUP);   // 15Pin //INTERUPT BUTTON BUTTON
  //+++++++Interrupt Pins++++++++++++++
  attachInterrupt(button.PIN, reset_isr, FALLING);

  startTest();  //---------[TEST]----------

  //---------------------[print LOGO and version info]------------------------
  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;); // Don't proceed, loop forever
  }
  // Clear the buffer
  printLogo();
  delay(2000);
  lastCount();
  Buzzer1();        // run Buzzer subroutine to indicate reset complete
  Serial.print("raw_count, count_value...");
  Serial.print (raw_count);
  Serial.println (count_value);
  Serial.println ("SETUP IS DONE");
}

//---------------------------[LOOP]-------------------------------

void loop() {
  // Serial.printf("Raw Count  is now  %u \n", raw_count);
 // Serial.printf("Bags left is now  %u bagsLeft \n", count_value);

  checkdoorState();  //---[check door open or shut] >> set modeState-------
  checkSwitch();  //---[check public/private switch] >> set modeState and modeCase-----------
  twoPaths();

  // read the flushlever input pin:
  leverState = digitalRead(leverPin);

  // compare the leverState to its previous state
  if (leverState != lastLeverState) {
    // if the state has changed, increment the counter
    if (leverState == HIGH) {
      // if the current state is HIGH then the button went from off to on:
      leverPullCounter--;
      Serial.println("on");
      Serial.print("number of lever pulls: ");
      Serial.println(leverPullCounter);
      //raw_count =  leverPullCounter;
      raw_count--;
      Serial.printf("clicks per bag is: %u  clicks. \n", clicks_per_bag);
      Serial.printf("Raw Count left is now:  %u  \n", raw_count);
      count_value = raw_count / clicks_per_bag;
      Serial.printf("Bags left is now  %u bagsLeft \n", count_value);
      saveCount();
    } else {
      // if the current state is LOW then the button went from on to off:
      Serial.println("off");
    }
    // Delay a little bit to avoid bouncing
    delay(50);
  }
  // save the current state as the last state, for next time through the loop
  lastLeverState = leverState;
  
  //-----reset Button timeout----------------
  if (reset_time - last_reset_time > 3000) {
    button.numberKeyPresses = 0;
    Serial.printf("Excellent,  reset Button has been reset to %u times\n", button.numberKeyPresses);
    last_reset_time = reset_time;
    Buzzer4();
  }

  // ----------Update Display * Clear the buffer ---------------
  display.clearDisplay();
  printText();

  //--------------reset interrupt----------------
  if (button.pressed) {
    Serial.printf("Button has been pressed %u times\n", button.numberKeyPresses);
    button.pressed = false;
    reset_time = millis();

    if (button.numberKeyPresses >= 2) {
      resetCount();
      button.numberKeyPresses = 0;
      Serial.println("Really Smart Kraig, raw_count and count_value will be RESET");
      last_reset_time = reset_time;
    }
    delay(1000);
  }          //-----------reset interrupt finish-------------
}   //----------------------------[END LOOP]-------------------
