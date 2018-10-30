/*
Name:     Multifunction_Button-v23.ino
Created:  04/12/2017 2:00:00 PM
Author:   Michael Dzura
Version: 2.3

Tests a 3 way button function through switch input to activate 1-3 LEDs/Relays.
Short Press (20ms-1000ms), Long Press(1000ms-2000ms), Longest Press(2000ms-4000ms).

**CHANGES:
- Removed Debounce Code.
*/

/*********** INPUTS ***********/
#define INPUT_SWITCH	 20	   // Input Pin On Feather 32u4.
/******************************/

/********** OUTPUTS ***********/
int LED[3] = {6,9,10};			 
//int RELAY[3] = {3,4,5};
/******************************/

/******** TIME VARIANTS *******/
#define CLICK_TIME		 500   // The Time Of A Single Switch Click. Only Adjust This. Will Multiply By 2.
/******************************/

/****** SWITCH LOGIC **********/
int lastSwitchState;		   // The Previous Reading From The Input Pin.
int pressTrigger;			   // Flag For Switch Press.
int switchState;			   // Value Of The Switch State.
long pressedTime;			   // Timestamp For When The Switch Is Pressed.
long releasedTime;			   // Timestamp For When The Switch Is Released.
long pressDuration;			   // Total Duration The Switch Was Pressed.
/******************************/


int button(int input_pin, long short_Click);

void setup() {
  pinMode(INPUT_SWITCH, INPUT);

  for (int i = 0; i <= 2; i++) {
	pinMode(LED[i], OUTPUT);
	//pinMode(RELAY[i], OUTPUT);
  }

  Serial.begin(9600);
}

void loop() { 

	switchState = digitalRead(INPUT_SWITCH);			// Gets The Realtime Switch State

	// Check to see if you just pressed the switch
	// (i.e. the input went from LOW to HIGH),  and you've waited
	// long enough since the last press to ignore any noise:

	// For each HIGH/LOW state a timestamp is stored representing
	// the rising and falling edge.
	if (switchState != lastSwitchState) {
		
		// Check If The Switch Is Being Pressed.
		if (switchState == LOW) {
			Serial.print("SwitchState = LOW, ");
			pressedTime = millis();						// Store The Time Of The Rising Edge.
			Serial.println(pressedTime);

		// Check If The Switch Is Released.
		} else if (switchState == HIGH) {
			Serial.print("SwitchState = HIGH, ");
			releasedTime = millis();					// Store The Time Of The Falling Edge.
			Serial.println(releasedTime);
			
			pressDuration = releasedTime - pressedTime;	// Calculate The Total Time The Switch Was Pressed
		
			Serial.println("");
			Serial.print("Switch Press For:  ");
			Serial.println(pressDuration);
		}
	}

		
	int state = button(INPUT_SWITCH, CLICK_TIME);			// Calls the button function and returns value of 1-3

	// Activated On Short Click.
	if (state == 1) {
		digitalWrite(LED[0], HIGH);
		//digitalWrite(RELAY[0], HIGH);
		delay(500);
		//digitalWrite(RELAY[0], LOW);
		digitalWrite(LED[0], LOW);

	// Activated On Long Click.
	} else if (state == 2) {
		digitalWrite(LED[1], HIGH);
		//digitalWrite(RELAY[1], HIGH);
		delay(1000);
		//digitalWrite(RELAY[1], LOW);
		digitalWrite(LED[1], LOW);

	// Activated On Longest Click.
	} else if (state == 3) {
		digitalWrite(LED[2], HIGH);
		//digitalWrite(RELAY[2], HIGH);
		delay(1000);
		//digitalWrite(RELAY[2], LOW);
		digitalWrite(LED[2], LOW);
	}

	// Save the switch value. Next time through the loop,
	// it'll be the lastButtonState:
	lastSwitchState = switchState;
}

/******************************** Button Function **********************
 * Listens for 3 different gestures from a single switch and outputs    *
 * to 3 Relays - Short Click, Long Click, Longest Click.				*
 * Change the short_Click variable to adjust the click timing.			*
 **********************************************************************/
int button(int input_pin, long short_Click) { 


	long long_Click, longest_Click, timeout;

/*********** Time Calculations *********************
 * Takes the Short Click value and multiplies by 2 *
 * assigning 3 units of time for switch clicks.	   *
 ***************************************************/
	short_Click = short_Click * 2;	
	long_Click = short_Click * 2;
	longest_Click = long_Click * 2;
	timeout = longest_Click * 1.5;


	// Checks If The Switch Is Pressed. If TRUE, Set The Flag.
	if (switchState == LOW) {
		pressTrigger = 1;		// 1 Indicates That The Switch Has Been Pressed.
	}


	// This is the primer for evaluating every switch press. 
	// It's only true if the button has been previously pressed, 
	// based on the pressTrigger flag, and then released.
	if (switchState == HIGH && pressTrigger == 1) {

		pressTrigger = 0;				 // Reset the press trigger back to zero, not pressed.

/**************************** Short Click Perameters****************************
 * Greater Than Debounce Filter, And Less Than Short Click Time.			   *
 *******************************************************************************/
		if ((pressDuration <= short_Click) && pressTrigger == 0) {
			Serial.println("Short Press!");
			pressTrigger = 0;			 // Reset the press trigger back to zero.
										 // Prevents Release From Activating.
			return 1;					 // Return If True.
		}

/**************************** Long Click Perameters ****************************
 * Greater Than Short Click Time, And Less Than Long Click Time.			   *
 *******************************************************************************/
		if ((pressDuration >= short_Click) && (pressDuration <= long_Click) && pressTrigger == 0) {
			Serial.println("Long Press!");
			pressTrigger = 0;			 // Reset the press trigger back to zero.
										 // Prevents Release From Activating.
			return 2;					 // Return If True.
		} 

/*************************** Longest Click Perameters **************************
 * Greater Than Long Click Time, And Less Than Longest Click Time.			   *
 * Timeout Is Included For Anything Else Greater.							   *
 *******************************************************************************/
		if ((pressDuration >= long_Click) && (pressDuration < longest_Click) && (pressDuration < timeout) && pressTrigger == 0) {
			Serial.println("Longest Press!");
			pressTrigger = 0;			 // Reset the press trigger back to zero.
										 // Prevents Release From Activating.
			return 3;					 // Return If True.
		}
	}
	
	return 0; // No Action Returns Nothing.
}