
/*
 RETRO
 Space Invader Game
 Author: Stuff 
 */

//Symbolic Parameters (Sketch settings)
const char LASER_SYMBOL = '^';

// include the library code:
#include <LiquidCrystal.h>

// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
LiquidCrystal lcd(7, 8, 9, 10, 11, 12);



//current laser position and direction
int laserColumn, dir;
//Invader string and no of invaders
String invaders;
int no_of_inv;

//Timer variables
unsigned long timerStart;
unsigned long timerInterval;
unsigned long currentTime;

//Button debouncing variables
int currentReading;
int newReading;

//Edge detection variable
int previousReading;

void setup() {
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);

  Serial.begin(9600);//Initialization of Serial Port
  delay(1000);
  
  //initialize laser position
  laserColumn = 0;
  dir = 2;

  //Initialise timer
  timerStart = millis();
  timerInterval = 250;

  invaders = "** * **   *   **";
  no_of_inv = 8;

  //Set up laser button
  pinMode(4, INPUT_PULLUP);
  
  //Initialize debouncing
  currentReading = digitalRead(4);

  while (currentReading != LOW) {
    lcd.print("Zap invaders!!!");
    lcd.setCursor(0,1);
    lcd.print("Press button... ");
    currentReading = digitalRead(4);
  }
  
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print(invaders);

}

int debounce(int pin, int pinState, int interval) {
  //Debounce button input
  int newValue = digitalRead(pin);
  if (newValue != pinState) {
    delay(interval);
    newValue = digitalRead(pin);
    if (newValue != pinState) {
      pinState = newValue;
    }
  }
  return pinState;
}

void loop() {

    //Set current time
    currentTime = millis();
    if ((currentTime-timerStart) > timerInterval) {

        //Reset timer
        timerStart = currentTime;

        
        //Erase old frame
        lcd.setCursor(laserColumn,1);
        lcd.print(' ');
        
        //Calculate new frame
        if (dir == 2) {
          dir = 1;
        }
        else if (laserColumn == 15 || laserColumn == 0) {
          dir = -dir;
        }
        
        laserColumn = (laserColumn + dir) % 16;
        
        // put your main code here, to run repeatedly:
        // set the cursor to column 0, line 1
        // (note: line 1 is the second row, since counting begins with 0):
        lcd.setCursor(laserColumn,1);
        lcd.print(LASER_SYMBOL);

        //Save the current button reading
        previousReading = currentReading;

        //Debounce button
        currentReading = debounce(4,currentReading,4);
      
        //Check button and zap invaders
        if ((previousReading == HIGH)&&(currentReading == LOW)) {
          //if invader is hit, deactivate it
          if (invaders[laserColumn] == '*') {
            Serial.print("hi");
            Serial.print('\n');
            lcd.setCursor(laserColumn,0);
            lcd.print('+');
            no_of_inv = no_of_inv - 1;
            invaders[laserColumn] = '+';
            Serial.print("ha");
            Serial.print('\n');
            Serial.print(invaders);
            Serial.print('\n');
          }

          //if deactivated invader hit, reactivate it
          else if (invaders[laserColumn] == '+'){
            lcd.setCursor(laserColumn,0);
            lcd.print('*');
            no_of_inv = no_of_inv + 1;
            invaders[laserColumn] = '*';
          }

          else {
            ;
          }
          
        }
    
        if (no_of_inv == 0) {
            lcd.clear();
            lcd.print("All invaders");
            lcd.setCursor(0,1);
            lcd.print("zapped!!!");
            while (true);
        }

    }
  
}
  
