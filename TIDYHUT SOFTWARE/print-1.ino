void printLogo() {
  String Version = (__FILE__);
  display.clearDisplay();
  display.setTextSize(2);             // The fontsize
  display.setTextColor(WHITE);        // Draw white text
  display.setCursor(20, 0);           // Start at top-left corner
  display.print("TIDYHUT");
  display.setCursor(30, 20);
  display.setTextSize(2);             // The fontsize
  //display.print("Ver ");
  display.print(ver);
  display.setCursor(30, 45);
  display.setTextSize(1);             // The fontsize
  display.print(micro);
  display.display();                  //call to display
}

void printText() {
  display.clearDisplay();
  display.setTextColor(WHITE);        // Draw white text
 //   (line 1)
  display.setCursor(25, 0);           // Start at top-left corner  
  display.setTextSize(2);             // The fontsize
    if (modeState == HIGH) {
    display.print("PUBLIC");       //the text
  }
  else {
    display.print("PRIVATE");
  }

  
  //  (line 2)
  display.setCursor(35, 20);           
  display.setTextSize(3);             // The fontsize
  display.print(count_value);
  
  //display.setTextSize(2);             // The fontsize
 // display.print(beginBag);

 
 //  (line 3)
  display.setCursor(15, 45); 
  display.setTextSize(2);             // The fontsize
  display.print("bags left");
  //display.setCursor(45, 45);           
  //display.setTextSize(1);             // The fontsize
 // display.print(ver);
  //call to display
  display.display();                  
}
