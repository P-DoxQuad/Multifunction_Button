/*
Name:     Multifunction_Button-v25-Debounce.ino
Created:  09/04/2017 7:19:00 PM
Updated:  09/26/2017 11:38:00 PM
Author:   Michael Dzura
Version: 2.6

Tests a 3 way button through switch input to activate 1-3 LEDs/Relays.
Short Press (20ms-1000ms), Long Press(1000ms-2000ms), Longest Press(2000ms-4000ms).

**CHANGES:
- Debounce And Edge Detection Are All Included Inside Button Function. 
- Decreased Wait Time For Faster Response.
*/

#include "button.h"      // Custom Multifunction Button!
#include "button.c"
#include "TimeWait.h"
#include "TimeWait.c"

/********** OUTPUTS ***********/
int LED[3] = {13,9,11};			 
//int RELAY[3] = {3,4,5};
/******************************/

void setup() {
	pinMode(INPUT_SWITCH, INPUT_PULLUP);

	for (int i = 0; i <= 2; i++) {
		pinMode(LED[i], OUTPUT);
		//pinMode(RELAY[i], OUTPUT);
	}

	Serial.begin(9600);
	digitalWrite(LED[1], HIGH);
	wait(500);
	digitalWrite(LED[1], LOW);
	//Serial.println("READY!!");

}

void loop() { 

	int state = button(INPUT_SWITCH, CLICK_TIME);			// Calls the button function and returns value of 1-3

	// Activated On Short Click.
	if (state == 1) {
		Serial.println("Short Press!");
		for (int i = 0; i < state; i++) {
			digitalWrite(LED[1], HIGH);
			//digitalWrite(RELAY[1], HIGH);
			wait(125);
			//digitalWrite(RELAY[1], LOW);
			digitalWrite(LED[1], LOW);
			wait(125);
		}


		// Activated On Long Click.
	} else if (state == 2) {
		Serial.println("Long Press!");
		for (int i = 0; i < state; i++) {
			digitalWrite(LED[1], HIGH);
			//digitalWrite(RELAY[1], HIGH);
			wait(125);
			//digitalWrite(RELAY[1], LOW);
			digitalWrite(LED[1], LOW);
			wait(125);
		}

		// Activated On Longest Click.
	} else if (state == 3) {
		Serial.println("Longest Press!");
		for (int i = 0; i < state; i++) {
			//digitalWrite(RELAY[1], HIGH);
			digitalWrite(LED[1], HIGH);
			wait(125);
			//digitalWrite(RELAY[1], LOW);
			digitalWrite(LED[1], LOW);
			wait(125);
		}
	} 
}
