/*
Name:     Multifunction_Button-v1.ino
Created:  09/09/2016 7:00:00 PM
Author:   Michael Dzura
Version: 1.0

Tests a simplified button function through switch input to activate one Relay
on Short Press and another Relay on Long Press.
*/

/*********** INPUTS ***********/
#define INPUT_SWITCH 20
/******************************/

/******** TIME VARIANTS *******/
#define SHORTHOLD 1000
#define LONGHOLD 2500
#define BUTTON3 4000
/******************************/

long buttonTime;

/****** SWITCH LOGIC *********/
int lastSwitchState;   // Variable For The Previous Reading From The Input Pin.
int pressTrigger;
int switchState;
/*****************************/

/********** DEBOUNCE *********/
#define DEBOUNCEDELAY 50
long lastDebounceTime;
/****************************/


int button(int input_pin, long s_Press, long l_Press);

void setup() {
  pinMode(INPUT_SWITCH, INPUT);
  pinMode(6, OUTPUT);
  pinMode(9, OUTPUT);

  Serial.begin(9600);
}

void loop() { 

	switchState = digitalRead(INPUT_SWITCH);

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
		int state = button(INPUT_SWITCH, SHORTHOLD, LONGHOLD);
		if (state == 1) {
			digitalWrite(6, HIGH);
			delay(1500);
			digitalWrite(6, LOW);
		} else if (state == 2) {
			digitalWrite(9, HIGH);
			delay(1500);
			digitalWrite(9, LOW);
		}
	}
	// Save the switch value. Next time through the loop,
	// it'll be the lastButtonState:
	lastSwitchState = switchState;
}


int button(int input_pin, long s_Press, long l_Press) { 

	// Loop Keeps Checking Switch Status
	// Reads in current state of button as HIGH/Off or LOW/On.
	//switchState = digitalRead(input_pin);

	if (switchState == LOW) { // When Pressed.
		Serial.println("SwitchState = LOW");

		pressTrigger = 1; // Acknowledge button has been pressed.
		// This is the primer for the release action.
	}
	// This is the long press for the second function.
	// Checks if the button is pressed within the predefined duration.
	if ((millis() - buttonTime) > s_Press && (millis() - buttonTime) <= l_Press && pressTrigger == 1) {
		lastDebounceTime = millis(); // Reset Debounce Timer.
		Serial.println("Long Hold!");
		pressTrigger = 0;   // Reset the press trigger back to zero.
		// Prevents Release from activating.
		return 2; // Return If True
	}

	// This is the primer for the first function.
	// Is only true if button has been previously pressed.
	if (switchState == HIGH && pressTrigger == 1) {
		Serial.println("SwitchState = HIGH");
		pressTrigger = 0;		// Reset the press trigger back to zero.

		// Checks if the button is released within the predefined duration.
		if ((millis() - buttonTime) > DEBOUNCEDELAY && (millis() - buttonTime) <= s_Press && pressTrigger == 0) {
			lastDebounceTime = millis(); // Reset Debounce Timer.
			Serial.println("Short Press!");
			pressTrigger = 0;   // Reset the press trigger back to zero.
			// Prevents Release from activating.
			return 1; // Return If True
		} 
	}

	return 0; // No Action Returns Nothing.
}