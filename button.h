/*
Name:     button.h
Created:  09/10/2016 :11:00 PM
Author:   Michael Dzura
Version: 1.1

Declaration of variables and functions
*/

#ifndef BUTTON_H
#define BUTTON_H

#include "Arduino.h"

long buttonTime;

/*********** I/O PINS ***********/
#define INPUT_SWITCH 20
#define LED1		 5
#define LED2		 6
/********************************/

/****** SWITCH LOGIC ************/
int lastSwitchState;   // Variable For The Previous Reading From The Input Pin.
int pressTrigger;
int switchState;
/********************************/

/******** TIME VARIANTS *********/
#define SHORTHOLD 1000
#define LONGHOLD 2500
/********************************/

/********** DEBOUNCE ************/
#define DEBOUNCEDELAY 50
long lastDebounceTime;
/********************************/

int button(byte state, long s_Press, long l_Press);

#endif