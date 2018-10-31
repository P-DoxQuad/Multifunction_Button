/*
Name:     button.c
Created:  04/15/2017 1:05:00 PM
Author:   Michael Dzura
Version: 2.4

Definition of button function. Passes input state and press
durations. Activate Short Press (20ms-1000ms), 
Long Press(1000ms-2000ms), Longest Press(2000ms-4000ms).

**TODO
- Double Press functionality.
*/

#include "Arduino.h" // Needs to include Arduino Library. Only Needed When Not Main File.
#include "button.h"  // Includes Variable And Function Declarations.


/************************ Button Function *******************************
 * Listens for 3 different gestures from a single switch and outputs    *
 * to 3 Relays - Short Click, Long Click, Longest Click.				*
 * Change the short_Click variable to adjust the click timing.			*
 ************************************************************************/
int button(int input_pin, long short_Click) { 

	switchState = digitalRead(input_pin);			// Gets The Realtime Switch State

	long long_Click, longest_Click, timeout;

/*********** Time Calculations *********************
 * Takes the Short Click value and multiplies by 2 *
 * assigning 3 units of time for switch clicks.	   *
 ***************************************************/
	short_Click = short_Click * 2;	
	long_Click = short_Click * 2;
	longest_Click = long_Click * 2;
	timeout = longest_Click * 1.5;



/**************** Edge Detection ********************
 * Check to see if you just pressed the switch		*
 * (i.e. the input went from LOW to HIGH), and		*
 * you've waited long enough since the last press to* 
 * ignore any noise:								*
 *													*
 * For each HIGH/LOW state a timestamp is stored	*
 * representing the rising and falling edge.		*
 ****************************************************/
	if (switchState != lastSwitchState) {

		lastDebounceTime = millis();					// Reset The Debouncing Timer.

		// Check If The Switch Is Being Pressed. If TRUE, Set The Flag.
		if (switchState == LOW) {
			//Serial.print("SwitchState = LOW, ");
			pressedTime = millis();						// Store The Time Of The Rising Edge.
			//Serial.println(pressedTime);
			
			pressTrigger = 1;							// 1 Indicates That The Switch Has Been Pressed.


		// This is the primer for evaluating every switch press. 
		// It's only true if the button has been previously pressed, 
		// based on the pressTrigger flag, and then released.
		} else if (switchState == HIGH && pressTrigger == 1) {
			//Serial.print("SwitchState = HIGH, ");
			releasedTime = millis();					// Store The Time Of The Falling Edge.
			//Serial.println(releasedTime);

			pressDuration = releasedTime - pressedTime;	// Calculate The Total Time The Switch Was Pressed

			//Serial.println("");
			//Serial.print("Switch Press For:  ");
			//Serial.println(pressDuration);

			pressTrigger = 0;							// Reset the press trigger back to zero, not pressed.

			/**************************** Short Click Perameters****************************
			* Greater Than Debounce Filter, And Less Than Short Click Time.			   *
			*******************************************************************************/
			if ((pressDuration > DEBOUNCEDELAY) && (pressDuration <= short_Click) && pressTrigger == 0) {
				lastDebounceTime = millis();			// Reset Debounce Timer.
				//Serial.println("Short Press!");
				pressTrigger = 0;						// Reset the press trigger back to zero.
														// Prevents Release From Activating.
				return 1;								// Return If True.
			}

			/**************************** Long Click Perameters ****************************
			* Greater Than Short Click Time, And Less Than Long Click Time.			   *
			*******************************************************************************/
			if ((pressDuration >= short_Click) && (pressDuration <= long_Click) && pressTrigger == 0) {
				lastDebounceTime = millis();			// Reset Debounce Timer.
				//Serial.println("Long Press!");
				pressTrigger = 0;						// Reset the press trigger back to zero.
														// Prevents Release From Activating.
				return 2;								// Return If True.
			} 

			/*************************** Longest Click Perameters **************************
			* Greater Than Long Click Time, And Less Than Longest Click Time.			   *
			* Timeout Is Included For Anything Else Greater.							   *
			*******************************************************************************/
			if ((pressDuration >= long_Click) && (pressDuration < longest_Click) && (pressDuration < timeout) && pressTrigger == 0) {
				lastDebounceTime = millis();			// Reset Debounce Timer.
				//Serial.println("Longest Press!");
				pressTrigger = 0;						// Reset the press trigger back to zero.
														// Prevents Release From Activating.
				return 3;								// Return If True.
			}
		}
	}

	// Save the switch value. Next time through the loop,
	// it'll be the lastButtonState:
	lastSwitchState = switchState;

	return 0; // No Action Returns Nothing.
}
