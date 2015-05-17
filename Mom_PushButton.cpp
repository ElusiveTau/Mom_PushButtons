#include "Arduino.h"
#include "Mom_PushButton.h" 

#define DEBOUNCE_TIME 5

Mom_PushButton::Mom_PushButton(uint8_t input_pin, bool mode_number)
{
    _pin = input_pin;	//Set pin 
    pinMode(input_pin, INPUT);	//Set pinmode
	if(mode_number == 1 || mode_number == 0)	//Set mode
		_mode = mode_number; 
	m1_counter = 0;	//Reset counter
 	
} 

Mom_PushButton::Mom_PushButton(uint8_t input_pin, int mode_number, int modulus)
{
    _pin = input_pin; 
	pinMode(input_pin, INPUT);
	if(mode_number == 2 && (modulus >= 1) ) 
	{
		_mode = mode_number; 
		_modulus = modulus+1;	//Modifies modulus so it counts the number of button presses up to and including the value of "modulus" 
	} 
 	m2_counter = 0;
}

int Mom_PushButton::getState()
{
	switch(_mode)
	{
		case 0: return m0_counter; 
			break;
		case 1: return m1_counter; 
			break;
		case 2: return m2_counter; 
			break;
		default: 
			Serial.println("Can't get button state. Button mode invalid.");
			break; 
	}
}

void Mom_PushButton::debounceRead()
{
	_nextState = digitalRead(_pin); 	//Take a sample from input pin
	switch(_mode)
	{
		case 0: 
		    if(_prevState != _nextState)    	//If in that instance, a change of state is detected
			{
				delay(DEBOUNCE_TIME);			//Wait a bit (ms)
				_nextState = digitalRead(_pin); //Read again, presumably after signal stability
				m0_counter = _nextState;		//Counter does not change value unless there is a change of state 
			}
			break; 

		case 1: 
			if(_prevState != _nextState)
			{
				delay(DEBOUNCE_TIME); 
				_nextState = digitalRead(_pin); 
			}	
			if(_prevState == 1 && _nextState == 0) 
				m1_counter = (m1_counter+1)%2; 	
			break; 

		case 2: 
			if(_prevState != _nextState)
			{
				delay(DEBOUNCE_TIME); 
				_nextState = digitalRead(_pin); 
			}
			if(_prevState == 1 && _nextState == 0)
				m2_counter = (m2_counter+1)%(_modulus); 	
			break; 

		default: 
			Serial.print("Warning: Button at pin "); 
			Serial.print(_pin); 
			Serial.println(" has undefined mode. Check that mode parameter is valid."); 
			break; 
	}
	_prevState = _nextState; 
} 
