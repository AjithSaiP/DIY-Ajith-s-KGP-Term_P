#include<Keypad.h> 
// KEYPAD LIBRARY FOR KEYPAD INTERFACING 
#include <LiquidCrystal.h>
#include<Servo.h>
// LIBRARY FOR SERVO MOTOR
//#include<String.h>

const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

char keys[4][4]={ 
 {'1','4','7','*'},
 {'2','5','8', '0'},
 {'3','6','9', '#'},
 {'A','B','C', 'D'}};
 
byte rowPin[4]={5,4,3,2}; // ROW PINS OF KEYPAD
byte colPin[4]={9,8,7,6}; // COLUMN
  

Servo servo_Motor; 
String password = "12347890";  // SETTING
  
int position = 0; // VARIABLE FOR DETERMINING THE POSITION.

int wrong = 0; // VARIABLE FOR CALCULATING THE WRONG INPUT.

int reset_pos = 0,i = 0;//for improvemnets later on
int reset_wrong = 0;
int reset_total = 0;

int redPin = 13; // DEFINING PIN FOR RED LED
  
int greenPin = 1; // DEFINING PIN FOR GREEN LED

void loop_custom();  

Keypad keypad=Keypad(makeKeymap(keys),rowPin,colPin,4,4);
// MAPPING THE KEYPAD NUMBERS

int total = 0; // VARIABLE TO DETERMINE THE NUMBER OF WRONG ATTEMPTS.

void setup()
{
 pinMode(redPin,OUTPUT);
 pinMode(greenPin,OUTPUT);
 lcd.begin(16,2);
 lcd.print("DOOR LOCK SYSTEM");
 lcd.setCursor(0,1);
 lcd.print("       BY:");
 delay(2000);
 lcd.clear();
 lcd.print("Creative");
 lcd.setCursor(0,2);
 lcd.print("Engineer");
 delay(2000);
 lcd.clear();
 setLocked(true);
 delay(1000);
}

void loop(){
  lcd.clear();
  lcd.print("Enter Password:");
  delay(100);
  
 char pressed=keypad.getKey();// TAKING
  
 String key[8];
  
  if(pressed){ 
   lcd.clear();
   lcd.print("Enter Password:");
   lcd.setCursor(position,2);
   lcd.print(pressed);
   delay(500);
     if(pressed == '*')

      {
          position = 0;
          setLocked(true);
          lcd.clear();
      }
   
    else if( pressed == '#'){
      	position--;
    	}
   //for resetting the password
    
    else if(pressed == password[position])
      {
          key[position]=pressed;
          position++;
      }
 
    else if (pressed != password[position])
      {// IN CASE OF WRONG INPUT INCREMENT BOTH WRONG AND POSITION.
          wrong++;
          position ++;
      }

    if(position == 8)
       {// WHEN POSITION == 3 THEN CHECK THE FOLLOWING
          if( wrong >0) // IF ANY WRONG INPUT IF GIVEN THEN INCREMENT TOTAL AND
          // SET WRONG AND POSITION TO ZERO.
            {
                total++;
                wrong = 0;
                position = 0;
                lcd.clear();
                lcd.print("WRONG");
                lcd.setCursor(5,2);
                lcd.print("PASSWORD");
                delay(1000);
                setLocked(true);
            }


          else if(position == 8 && wrong == 0)
            {// IF NO WRONG VALUE IS GIVEN THEN DISPLAY THE ACCEPTED PASSWORD AND
              // MOVE THE SERVO/MOTOR.
                position = 0;
                wrong = 0;
                lcd.clear();
                lcd.print("PASSWORD");
                lcd.setCursor(6,2);
                lcd.print("ACCEPTED");
                delay(2000);
                lcd.clear();
                lcd.print("Door Open");
                delay(2000);
                setLocked(false);

            }

          if(total == 3)// IF TOTAL OF 3 ATTEMPTS ARE DONE BY ENTERING WRONG PASS
            {
                total=0;
                delay(500);
            }
        }
   }
}

void setLocked(int locked)// FUNCTION TO CHANGE STATUS OF SERVO MOTOR.
  {
    if (locked)
      {
          digitalWrite(redPin, HIGH);
          digitalWrite(greenPin, LOW);
          delay(1000);
          servo_Motor.attach(10);
          servo_Motor.write(0);
          delay(1000);
          servo_Motor.detach();  
      }
    else
      {
          digitalWrite(redPin,LOW);
          digitalWrite(greenPin,HIGH);
          delay(1000);
          servo_Motor.attach(10);
          servo_Motor.write(90);
          delay(1000);
          servo_Motor.detach();
          delay(10000);
      	  digitalWrite(greenPin,LOW);
      }
  }

