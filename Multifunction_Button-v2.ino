/*
Name:     Multifunction_Button-v2.ino
Created:  04/11/2017 2:00:00 PM
Author:   Michael Dzura
Version: 2.0

Tests a simplified button function through switch input to activate one Relay
on Short Press and another Relay on Long Press.
*/

/*********** INPUTS ***********/
#define INPUT_SWITCH 20
/******************************/

/******** TIME VARIANTS *******/
#define CLICK		 700
#define LONGCLICK	 1000
#define LONGESTCLICK 2000
#define TIMEOUT		 3000
long current_Time;
/******************************/

long buttonTime;

/****** SWITCH LOGIC *********/
int lastSwitchState;   // Variable For The Previous Reading From The Input Pin.
int pressTrigger;
int switchState;
long pressedTime;
long releasedTime;
long pressDuration;
/*****************************/

/********** DEBOUNCE *********/
#define DEBOUNCEDELAY 20
long lastDebounceTime;
/****************************/


int button(int input_pin, long s_Press, long l_Press, long longest_Press);

void setup() {
  pinMode(INPUT_SWITCH, INPUT);
  pinMode(6, OUTPUT);
  pinMode(9, OUTPUT);

  pinMode(10, OUTPUT);

  Serial.begin(9600);
}

void loop() { 

	switchState = digitalRead(INPUT_SWITCH);
	current_Time = millis();

	// check to see if you just pressed the button
	// (i.e. the input went from LOW to HIGH),  and you've waited
	// long enough since the last press to ignore any noise:

	// If the switch changed, due to noise or pressing:
	if (switchState != lastSwitchState) {
		// Reset The Debouncing Timer.
		lastDebounceTime = millis();

		if (switchState == LOW) {
			Serial.print("SwitchState = LOW, ");
			pressedTime = millis();
			Serial.println(pressedTime);

		} else if (switchState == HIGH) {
			Serial.print("SwitchState = HIGH, ");
			releasedTime = millis();
			Serial.println(releasedTime);
			
			pressDuration = releasedTime - pressedTime;
		
			Serial.println("");
			Serial.print("Switch Press For:  ");
			Serial.println(pressDuration);
		}

		// Current Button Timestamp.
		//buttonTime = millis();
	}
	if ((millis() - lastDebounceTime) > DEBOUNCEDELAY) {
		// whatever the reading is at, it's been there for longer
		// than the debounce delay, so take it as the actual current state:
		int state = button(INPUT_SWITCH, CLICK, LONGCLICK, LONGESTCLICK);
		if (state == 1) {
			digitalWrite(6, HIGH);
			delay(1000);
			digitalWrite(6, LOW);
		} else if (state == 2) {
			digitalWrite(9, HIGH);
			delay(1000);
			digitalWrite(9, LOW);
		} else if (state == 3) {
			digitalWrite(10, HIGH);
			delay(1000);
			digitalWrite(10, LOW);
		} /*else if (state == 0) {
			Serial.println("TIMEOUT!");
		}*/
	}
	// Save the switch value. Next time through the loop,
	// it'll be the lastButtonState:
	lastSwitchState = switchState;
}


int button(int input_pin, long s_Click, long l_Click, long longest_Click) { 

	if (switchState == LOW) {

		pressTrigger = 1;

	}

	// This is the primer for the first function.
	// Is only true if button has been previously pressed.
	if (switchState == HIGH && pressTrigger == 1) {
		//Serial.println("SwitchState = HIGH");
		pressTrigger = 0;				// Reset the press trigger back to zero.

		// Checks if the button is released within the predefined duration.
		if ((pressDuration > DEBOUNCEDELAY) && (pressDuration <= l_Click) && pressTrigger == 0) {
			lastDebounceTime = millis(); // Reset Debounce Timer.
			Serial.println("Short Press!");
			pressTrigger = 0;			// Reset the press trigger back to zero.
										// Prevents Release from activating.
			return 1;					// Return If True
		}

		if ((pressDuration >= l_Click) && (pressDuration <= longest_Click) && pressTrigger == 0) {
			lastDebounceTime = millis(); // Reset Debounce Timer.
			Serial.println("Long Press!");
			pressTrigger = 0;			// Reset the press trigger back to zero.
										// Prevents Release from activating.
			return 2;					// Return If True
		} 

		if ((pressDuration >= longest_Click) && (pressDuration < TIMEOUT) && pressTrigger == 0) {
			lastDebounceTime = millis(); // Reset Debounce Timer.
			Serial.println("Longest Press!");
			pressTrigger = 0;			// Reset the press trigger back to zero.
										// Prevents Release from activating.
			return 3;					// Return If True
		} else {
			return 0;
		}
	}
	
	return 0; // No Action Returns Nothing.
}