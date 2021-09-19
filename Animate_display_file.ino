
/*
 RETRO
 Space Invader Game
 Author: Stuff 
 */

// include the library code:
#include <LiquidCrystal.h>

// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
LiquidCrystal lcd(7, 8, 9, 10, 11, 12);

//current laser position
int laserColumn, dir;
int speed_delay;

void setup() {
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);

  //initialize laser position
  laserColumn = 0;
  dir = 1;
  speed_delay = 250;
}

void loop() {
  
  //Erase old frame
  lcd.setCursor(laserColumn,1);
  lcd.print(' ');
  
  //Calculate new frame
  if (laserColumn == 15 or laserColumn == 0) {
    dir = -dir;
  }
  
  laserColumn = (laserColumn + dir) % 16;
  
  // put your main code here, to run repeatedly:
  // set the cursor to column 0, line 1
  // (note: line 1 is the second row, since counting begins with 0):
  lcd.setCursor(laserColumn,1);
  lcd.print('^');

  //Delay loop
  delay(speed_delay);
  
}
  
