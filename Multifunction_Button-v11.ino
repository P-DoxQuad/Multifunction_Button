/*
Name:     Multifunction_Button-v11.ino
Created:  09/09/2016 7:00:00 PM
Author:   Michael Dzura
Version: 1.1

Tests a simplified button function through switch input to activate one LED
on Short Press and another on Long Press.
*/

#include "button.h" 
#include "button.c" // NEVER INCLUDE YOUR IMPLEMENTATION! ONLY FOR ARDUINO!!

void setup() {
  pinMode(INPUT_SWITCH, INPUT);
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);

  Serial.begin(9600);
}

void loop() { 

	switchState = digitalRead(INPUT_SWITCH);

	Serial.println(switchState);
	// check to see if you just pressed the button
	// (i.e. the input went from LOW to HIGH),  and you've waited
	// long enough since the last press to ignore any noise:

	// If the switch changed, due to noise or pressing:
	if (switchState != lastSwitchState) {
		// Reset The Debouncing Timer.
		lastDebounceTime = millis();

		// Current Button Timestamp.
		buttonTime = millis();
	}
	if ((millis() - lastDebounceTime) > DEBOUNCEDELAY) {
		// whatever the reading is at, it's been there for longer
		// than the debounce delay, so take it as the actual current state:
		int state = button(switchState, SHORTHOLD, LONGHOLD);
		if (state == 1) {
			digitalWrite(LED1, HIGH);
			delay(1500);
			digitalWrite(LED1, LOW);
		} else if (state == 2) {
			digitalWrite(LED2, HIGH);
			delay(1500);
			digitalWrite(LED2, LOW);
		}
	}
	// Save the switch value. Next time through the loop,
	// it'll be the lastButtonState:
	lastSwitchState = switchState;
}
