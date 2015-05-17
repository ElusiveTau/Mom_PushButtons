#include <Mom_PushButton.h>

/* This library is designed to work with a pull-down momentary pushbutton
   Setup: 
     Connect a current-limiting resistor to ground. Connect a wire between the end of the resistor
     that isn't connected to ground and the MCU's input pin. Then connect a 2-terminal pushbutton 
     between the resistor-wire connection and 5V.
     
   This library enables you to use a push button as a simple switch with some features: 
   - MODE 0: Operate as a momentary on-off switch. MCU input reads HIGH when button is depressed and LOW when button is released.  
   - MODE 1: Operates as a toggle on-off switch. *LED feedback to user is strongly recommended with this mode*. Call a single depress & release a "button cycle".
     If a button cycle occurs and the state of the switch is off, then the state of the switch changes to on. If it occurs and state of switch is on, then
     the state of the switch changes to off. 
   - MODE 2: Operates as a counter that counts to some value and resets. Basically MODE 1 but with user-specified number of states. 

 */

/* CHOOSE A TEST */
//Test 1 checks for changes in button state and prints only when button state changes
//Test 2 Spams serial print to demonstrate that states remain the same when button isn't pressed
//Use EITHER test 1 or test 2 but NOT both. 
#define TEST1 1 
#define TEST2 0

//Variables used for testing
int _prev1 = 0;  //Button 1's next/prev state; used to prevent flooding of Console with a bunch of prints
int _curr1 = 0; 
int _prev2 = 0;  //Button 2's nex/prev state
int _curr2 = 0; 

/* DEFINE BUTTON PINS */
int button_Pin_1 = 3; 
int button_Pin_2 = 4; 
int modulus = 5; //The button will count to this number and then reset to 0. 


//Mom_PushButton button1(button_Pin_1, 0);     //Declare & initalized a button, mode 0; Mode 0 and Mode 1 has same parameter signature 
Mom_PushButton button1(button_Pin_1, 1);     //Testing Mode 1
Mom_PushButton button2(button_Pin_2, 2, 5);  //Mode 2 has 3 parameters: pin #, mode #, modulus

void setup() {
  Serial.begin(9600); //Button state will be output to Serial
  Serial.println("Press buttons when ready."); 
}

void loop() {
  button1.debounceRead(); 
  button2.debounceRead(); 
  
  #if TEST1
  _curr1 = button1.getState(); 
  _curr2 = button2.getState(); 
  if((_prev1 != _curr1) || (_prev2 != _curr2)) 
  {
    Serial.print("Button1: "); 
    Serial.print(_curr1);
    Serial.print("      Button2: "); 
    Serial.println(_curr2); 
  }
  _prev1 = _curr1; 
  _prev2 = _curr2; 
  #endif
  
  #if TEST2
  Serial.print("Button1: ");
  Serial.print(button1.getState()); 
  Serial.print("      Button2: "); 
  Serial.println(button2.getState()); 
  #endif
  
}  
