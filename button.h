/*
Name:     button.h
Created:  04/15/2017 1:05:00 PM
Author:   Michael Dzura
Version: 2.4

Declaration of variables and functions
*/

#ifndef BUTTON_H
#define BUTTON_H

#include "Arduino.h"

/*********** INPUTS ***********/
#define INPUT_SWITCH	 20	   // Input Pin On Feather 32u4.
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

/********** DEBOUNCE **********/
#define DEBOUNCEDELAY	 20	   // Debounce Filter Time
long lastDebounceTime;		   // Previous Debounce Timestamp
/******************************/


int button(int input_pin, long short_Click);

#endif
