#include <msp430.h>
#include <LiquidCrystal.h>

//LCD pins assignment
//Power pins: A,VDD connected to VCC; VO, RW, VSS, K connected to GND
//Signal pins: (RS,   E,    D4,   D5,   D6,   D7)
LiquidCrystal lcd (P2_0, P2_1, P2_2, P2_3, P2_4, P2_5); 

//Variables for checking the alarm states
int alarmStatus = 0;
int alarmActive = 0;

const String password = "1234"; //Constant Pin code
String input_password; //Pin to check against the real pin

//Variables for declaring Pinouts
const int buzzer = P1_1;
int pirPin1 = P1_0;
int pirPin2 = P1_2;
int redLED = P1_3;
int greenLED = P1_4;
int blueLED = P2_7;


void setup() {
  Serial.begin(9600);
  lcd.begin(16, 2); //We are using a 16*2 LCD display
  delay(100);       //Wait a 100 ms

  displayScreen(); //Call the home splash screen
  
  //Declare the pinModes for each pin used
  pinMode(pirPin1, INPUT);
  pinMode(pirPin2, INPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(redLED, OUTPUT);
  pinMode(greenLED, OUTPUT);
  pinMode(blueLED, OUTPUT);

  //Inital states for the LEDs
  digitalWrite(redLED, LOW);
  digitalWrite(greenLED, HIGH);
  digitalWrite(blueLED, LOW);
}

void loop() {
  int adc_val = analogRead(P1_7); /* Read input from keypad */

  if (adc_val>186  && adc_val<259) { //Constantly check if the 'A' key was pressed
    tone(buzzer,1000);
    delay(100);
    noTone(buzzer);
    enterPassword(); //Call the password function
  }
  
  //Checking if the alarm is armed
  if(alarmActive == 1){
    if(digitalRead(pirPin1) == HIGH) //PIR motion sensor for the back room
    {
      alarmTriggered(); //Call alarmTriggered function
    }
    
    if(digitalRead(pirPin2) == HIGH)//PIR motion sensor for the front room
    {
      alarmTriggered(); //Call alarmTriggered function
    }
  }
}

//============================================================================

//Function for declaring what happens when the alarm was tripped
void alarmTriggered(){ 
  alarmStatus = 1;
  tone(buzzer,1000); //Activate the buzzer
  lcd.clear();
  lcd.print("Motion Detected");

  while(alarmStatus == 1){
	  int adc_val = analogRead(P1_7); /* Read input from keypad */

	  if ( adc_val>=110  && adc_val<=120)//Check if the 'B' key was pressed
	  {
		  enterPassword(); //Call enterPassword function
	  }

	  //Blue light flicker
	  digitalWrite(blueLED, HIGH);
	  delay(80);
	  digitalWrite(blueLED, LOW);
	  delay(80);
  }
}

//Function for arming the alarm system
void activate(){ 
  digitalWrite(redLED, HIGH); //Set the red LED on
  digitalWrite(greenLED, LOW); //Set the green LED off
  
  lcd.clear();
  lcd.setCursor(2,0);
  lcd.print("SYSTEM ARMED");
  alarmActive = 1; //Set the alarm to the active state
  delay(2000);
}

//Function for disarming the alarm system
void deactivate(){
  digitalWrite(blueLED, LOW); //Set the blue LED off
  digitalWrite(redLED, LOW); //Set the red LED off
  digitalWrite(greenLED, HIGH); //Set the green LED on
  noTone(buzzer); //Turn the buzzer off
  
  alarmStatus = 0;//Clear the alarmStatus state
  lcd.clear();
  lcd.print("SYSTEM DISARMED");
  alarmActive = 0; //Clear the alarmActive state
  delay(2000);
  displayScreen(); //Display the main splash screen
}

//Function for checking whether to arm or disarm the system
void checkAlarm(){
  if(alarmActive == 0 && alarmStatus == 0)
    {
      activate();
    } 
    else if( alarmActive == 1 || alarmStatus == 1) {
      deactivate();
    }
}

//Function for entering/checking the pin entered
void enterPassword() {
  bool passcorrect = false;
  lcd.clear();
  lcd.print("Enter Pin:");
  
  while (passcorrect == false) { //Loop to keep taking input until the pin is correct
     if (alarmStatus == 1){ 
      digitalWrite(blueLED, HIGH);
      delay(30);
      digitalWrite(blueLED, LOW);
      delay(30);
    }  
    
    int adc_val = analogRead(P1_7); /* Read input from keypad */
    if (adc_val>850) //Key 1
    {
      if (alarmStatus == 0){ 
        tone(buzzer,1000);
        delay(100);
        noTone(buzzer); 
      }
      input_password += "1"; 
      lcd.print("1");
      delay(100);
    }
    else if ( adc_val>450  && adc_val<550) //Key 2
    {
      if (alarmStatus == 0){
        tone(buzzer,1000);
        delay(100);
        noTone(buzzer); 
      }
      input_password += "2"; 
      lcd.print("2");
      delay(100);
    }
    else if ( adc_val>300  && adc_val<370) //Key 3
    {
      if (alarmStatus == 0){
        tone(buzzer,1000);
        delay(100);
        noTone(buzzer); 
      }
      input_password += "3"; 
      lcd.print("3");
      delay(100);
    }
    else if ( adc_val>165  && adc_val<185) //Key 4
    {
      if (alarmStatus == 0){
        tone(buzzer,1000);
        delay(100);
        noTone(buzzer); 
      }
      input_password += "4"; 
      lcd.print("4");
      delay(100);
    }
    else if ( adc_val>147  && adc_val<164) //Key 5
    {
      if (alarmStatus == 0){
        tone(buzzer,1000);
        delay(100);
        noTone(buzzer); 
      }
      input_password += "5"; 
      lcd.print("5");
      delay(100);
    }
    else if ( adc_val>125  && adc_val<131) //Key 6
    {
      if (alarmStatus == 0){
        tone(buzzer,1000);
        delay(100);
        noTone(buzzer); 
      }
      input_password += "6"; 
      lcd.print("6");
      delay(100);
    }
    else if ( adc_val>=93  && adc_val<=105) //Key 7
    {
      if (alarmStatus == 0){
        tone(buzzer,1000);
        delay(100);
        noTone(buzzer); 
      }
      input_password += "7"; 
      lcd.print("7");
      delay(100);
    }
    else if ( adc_val>=86  && adc_val<=91) //Key 8
    {
      if (alarmStatus == 0){
        tone(buzzer,1000);
        delay(100);
        noTone(buzzer); 
      }
      input_password += "8"; 
      lcd.print("8");
      delay(100);
    }
    else if( adc_val>=74  && adc_val<=84) //Key 9
    {
      if (alarmStatus == 0){
        tone(buzzer,1000);
        delay(100);
        noTone(buzzer); 
      }
      input_password += "9"; 
      lcd.print("9");
      delay(100);
    }
    else if ( adc_val>=61  && adc_val<=63) //Key 0
    {
      if (alarmStatus == 0){
        tone(buzzer,1000);
        delay(100);
        noTone(buzzer); 
      }
      input_password += "0"; 
      lcd.print("0");
      delay(100);
    }
    else if ( adc_val>=66  && adc_val<=70) //Key *
    {
      if (alarmStatus == 0){
        tone(buzzer,1000);
        delay(100);
        noTone(buzzer); 
      }
      input_password = "";
      lcd.clear();
      lcd.print("Enter Pin:");;
      delay(100);
    }
    else if ( adc_val>=58  && adc_val<=60) //Key #
    {
      if (alarmStatus == 0){
        tone(buzzer,1000);
        delay(100);
        noTone(buzzer); 
      }

      if (password == input_password) { //When password is correct
        passcorrect = true;
        input_password = "";
        checkAlarm(); 
      } 
      else { //When password is incorrect
        input_password = "";
        lcd.clear();
        lcd.print("WRONG CODE!!");
        lcd.setCursor(0,1);
        lcd.print("TRY AGAIN!");
        delay(2000);
        lcd.clear();
        lcd.print("Enter Pin:");
      }
      delay(100);
    }
    else
    {
    }
    delay(100);
  }
}

//Function for displaying the main splash screen
void displayScreen() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Security System");
  lcd.setCursor(0, 1);
  lcd.print("Press A to Arm");
}
