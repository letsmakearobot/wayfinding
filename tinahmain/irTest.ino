void IRTest() {
  while (!stopbutton()) {
    LCD.clear();
    LCD.setCursor(0,0);
    LCD.print("L:");
    labelPrint("L", analogRead(IRFRONTLEFT),"R", analogRead(IRFRONTRIGHT),"S", analogRead(IRFRONT));
    LCD.setCursor(0,1);
    LCD.print("PU ");
    labelPrint("L", analogRead(IRLEFT),"R", analogRead(IRRIGHT),"",0);
  }
  LCD.clear();
  LCD.setCursor(0,0);
  LCD.print("START to test, hold");
  LCD.setCursor(0,1);
  LCD.print("STOP&START to cont");
  while (!startbutton()) {
    // just chilling
  }
}

