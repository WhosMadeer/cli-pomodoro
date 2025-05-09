#ifndef INPUTHANDLER_H
#define INPUTHANDLER_H
#include "pomodoro.h"

// * helper functions
void handleInput(stringstream& ss);
bool getInteger(stringstream& ss, int& x);
bool getString(stringstream& ss, string& s);
bool getBoolean(stringstream& ss, bool& f);


// * handler function
void handleStart();
void handleSet(stringstream& ss);
void handleStop();
void handlePause();
void handleContinue();
void handleStatus();
void handleReset();

#endif