/*
Name:     button.c
Created:  09/09/2016 7:00:00 PM
Author:   Michael Dzura
Version: 1.1

Definition of button function. Passes input pin and press
durations. Outputs 1 for short press and 2 for long hold. 

**TODO
- Pouble Press functionality.
*/

#include "Arduino.h" // Needs to include Arduino Library. Only Needed When Not Main File.
#include "button.h"  // Includes Variable And Function Declarations.

int button(byte state, long s_Press, long l_Press) { 
	
	// Loop Keeps Checking Switch Status
	// Reads in current state of button as HIGH/Off or LOW/On.
	//do {
		if (state == LOW) { // When Pressed.
			//Serial.println("SwitchState = LOW");

			pressTrigger = 1; // Acknowledge button has been pressed.
			// This is the primer for the release action.
		}
		// This is the long press for the second function.
		// Checks if the button is pressed within the predefined duration.
		if ((millis() - buttonTime) > s_Press && (millis() - buttonTime) <= l_Press && pressTrigger == 1) {
			lastDebounceTime = millis(); // Reset Debounce Timer.
			//Serial.println("Switch Press = Long Hold!, Will Return 2");
			pressTrigger = 0;   // Reset the press trigger back to zero.
			// Prevents Release from activating.
			return 2; // Return If True
		}

		// This is the primer for the first function.
		// Is only true if button has been previously pressed.
		if (state == HIGH && pressTrigger == 1) {
			//Serial.println("SwitchState = HIGH");
			pressTrigger = 0;		// Reset the press trigger back to zero.

			// Checks if the button is released within the predefined duration.
			if ((millis() - buttonTime) > DEBOUNCEDELAY && (millis() - buttonTime) <= s_Press && pressTrigger == 0) {
				lastDebounceTime = millis(); // Reset Debounce Timer.
				//Serial.println("Switch Press = Short Hold!, Will Return 1");
				pressTrigger = 0;   // Reset the press trigger back to zero.
				// Prevents Release from activating.
				return 1; // Return If True
			} 
		}
	//} while (digitalRead(INPUT_SWITCH) == LOW );
	return 0; // No Action Returns Nothing.
}
