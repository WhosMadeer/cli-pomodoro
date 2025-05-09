#ifndef POMODORO_H
#define POMODORO_H

#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>
#include <thread>
#include <chrono>
#include <atomic>

using namespace std;

#include "inputHandlers.h"
#include "timer.h"

/* Global Variables */

extern int focusTime;
extern int breakTime;
// default options 

extern thread timer; // only need one thread


extern bool isRunning;
extern bool isFocusMode; // true is focus, false is break
extern bool automaticSwitch; // true means that the timer goes to next mode after

extern atomic<bool> stopTimer;

extern volatile int currentFocusTime;
extern volatile int currentBreakTime;



/* string array */

extern string commandOptions[];

extern string commandOptionsShorthand[];


extern string errorArray[];

extern string timerErrorArray[];

#endif