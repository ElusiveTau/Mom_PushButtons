/** 
 Example demonstrating how to use the Mom_PushButton library to 
 control LED brightness (PWM)
 
 Modulus *must* be greater than 0. 
 Mode *must* be greater than or equal to 0. 
 **/

#include <Mom_PushButton.h>

int LED_Pin = 3; //Pin 3 is PWMed 
int BUT_Pin = 4; //Button pin
int modulus = 5; //Number of brightness division

Mom_PushButton ledButton(BUT_Pin, 2, modulus); //Mode 2

void setup()
{
  Serial.begin(9600); 
  pinMode(LED_Pin, OUTPUT);  
}

void loop()
{ 
  ledButton.debounceRead(); //Get button state
  Serial.println(ledButton.getState()); //Print to Console
  analogWrite(LED_Pin, map(ledButton.getState(),0, modulus,0,255)); //Map to a brightness 
}
