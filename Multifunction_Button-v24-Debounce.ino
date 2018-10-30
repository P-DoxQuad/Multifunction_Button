/*
Name:     Multifunction_Button-v24-Debounce.ino
Created:  04/13/2017 1:05:00 PM
Author:   Michael Dzura
Version: 2.4

Tests a 3 way button through switch input to activate 1-3 LEDs/Relays.
Short Press (20ms-1000ms), Long Press(1000ms-2000ms), Longest Press(2000ms-4000ms).

**CHANGES:
- Debounce And Edge Detection Are All Included Inside Button Function. 
*/

#include "button.h"      // Custom Multifunction Button!
#include "button.c"
#include "TimeWait.h"
#include "TimeWait.c"

/********** OUTPUTS ***********/
int LED[3] = {6,9,10};			 
//int RELAY[3] = {3,4,5};
/******************************/

void setup() {
  pinMode(INPUT_SWITCH, INPUT);

  for (int i = 0; i <= 2; i++) {
	pinMode(LED[i], OUTPUT);
	//pinMode(RELAY[i], OUTPUT);
  }

  Serial.begin(9600);
}

void loop() { 
		
		int state = button(INPUT_SWITCH, CLICK_TIME);			// Calls the button function and returns value of 1-3

		// Activated On Short Click.
		if (state == 1) {
			digitalWrite(LED[0], HIGH);
			//digitalWrite(RELAY[0], HIGH);
			wait(500);
			//digitalWrite(RELAY[0], LOW);
			digitalWrite(LED[0], LOW);

		// Activated On Long Click.
		} else if (state == 2) {
			digitalWrite(LED[1], HIGH);
			//digitalWrite(RELAY[1], HIGH);
			wait(1000);
			//digitalWrite(RELAY[1], LOW);
			digitalWrite(LED[1], LOW);

		// Activated On Longest Click.
		} else if (state == 3) {
			digitalWrite(LED[2], HIGH);
			//digitalWrite(RELAY[2], HIGH);
			wait(1000);
			//digitalWrite(RELAY[2], LOW);
			digitalWrite(LED[2], LOW);
		} 
}