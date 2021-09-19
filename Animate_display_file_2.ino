
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

//current laser position and direction
int laserColumn, dir;
//Set speed by setting time delay
int speed_delay;
//Invader string
String invaders;

void setup() {
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  
  //initialize laser position
  laserColumn = 0;
  dir = 1;
  speed_delay = 150;

  invaders = "** * **   *   **";
  lcd.setCursor(0,0);
  lcd.print(invaders);

  //Set up laser button
  pinMode(13, INPUT_PULLUP);

}

void loop() {
  
  while (invaders != "                ") {
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
    
      //Check button and zap invaders
    
      if (digitalRead(13) == LOW) {
        lcd.setCursor(laserColumn,0);
        lcd.print(' ');
        invaders[laserColumn] = ' ';
      }
    
      //Delay loop
      delay(speed_delay);
  }

  lcd.setCursor(0,0);
  lcd.print('All invaders');
  lcd.setCursor(0,1);
  lcd.print('zapped!!!');
  
  
}
  
