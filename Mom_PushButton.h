/*
 Mom_PushButtons.h - Library for Momentary push buttons 
 Created by Minh Tran in May 2015

 Hardware Setup: You need a momentary pushbutton switch, a resistor, and GND/5V (LOW/HIGH, respectively)
 1) Connect end A of the resistor to GND. This is a current limiting resistor, choose resistor value carefully.   
 2) Connect end B of the resistor to end A of the pushbutton. 
 3) Connect end B of the pushbutton to 5V. 
 4) Connect a wire to which one end goes to the MCU and the other goes to resistor-pushbutton node (end B/end A, respectively)

 This library enables you to use a push button as a simple switch with some features: 
 - MODE 0: Operate as a momentary on-off switch. MCU input reads HIGH when button is depressed and LOW when button is released.  
 - MODE 1: Operates as a toggle on-off switch. *LED feedback to user is strongly recommended with this mode*. Call a single depress & release a "button cycle".
   If a button cycle occurs and the state of the switch is off, then the state of the switch changes to on. If it occurs and state of switch is on, then
   the state of the switch changes to off. 
 - MODE 2: Operates as a counter that counts to some value and resets. Basically MODE 1 but with user-specified number of states. 

*/
#ifndef Mom_PushButton_h
#define Mom_PushButton_h

#include <Arduino.h>

class Mom_PushButton
{
	public: 
	Mom_PushButton(uint8_t input_pin, bool mode_number); 				  //Initialize button in MODE 0 or MODE 1 
    Mom_PushButton(uint8_t input_pin, int mode_number, int modulus);      //Initalize button in MODE 0, MODE 1, MODE 2 
	~Mom_PushButton(){}; 
   
    inline int getPin(){return _pin;}
    inline int getMode(){return _mode;}
 	inline int getModulus(){return _modulus;}
	
	int getState(); 		//Returns the button state (a value from the range, below). If mode 0, m0_counter is returned, if mode 1 then m1_counter, etc.
	void debounceRead(); 	//Call this function to poll buttons for change of state.  

    private:
	int _pin = -1;  
 	int _mode = -1; 
 	int _modulus = -1;

	bool _prevState = 0; 
	bool _nextState = 0; 

	int m0_counter; // Range: 0 or 1 
	int m1_counter; // Range: 0 or 1
	int m2_counter; // Range: 0 to "modulus"  **Note** Unlike m0,m1,m2 counts up to and INCLUDING the value, "modulus".   

};

#endif
