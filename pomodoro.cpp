#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>
#include <thread>
#include <chrono>
#include <atomic>

using namespace std;

/* Function Declaration */

// * helper functions
void handleInput(stringstream& ss);
bool getInteger(stringstream& ss, int& x);
bool getString(stringstream& ss, string& s);


// * handler function
void handleStart(stringstream& ss);
void handleSet(stringstream& ss);
void handleStop(stringstream& ss);
void handlePause(stringstream& ss);
void handleContinue(stringstream& ss);
void handleStatus(stringstream& ss);
void handleReset(stringstream& ss);




void runFocusTimer();
void runBreakTimer();


/* Global Variables */

// ? TODO: convert into an object
int focusTime = 25 * 60;
int breakTime = 5 * 60;
// default options 

thread timer; // only need one thread


bool isRunning = false;
bool isFocusMode = false; // true is focus, false is break

atomic<bool> stopTimer(false);

volatile int currentFocusTime = 0;
volatile int currentBreakTime = 0;

string commandOptions[] = {
    "help",
    "start",
    "set",
    "stop",
    "continue",
    "pause",
    "status",
    "reset",
};

string commandOptionsShorthand[] = {
    "-h"
};


string errorArray[] = {
    "invalid command",                                  // 0
    "invalid argument",                                 // 1
    "too few arguments",                                // 2
};

string timerErrorArray[] = {
    "timer is not running",
    "timer is not paused"
};

/*
    argc is number of arguments
    argv is an array of strings containing all the arguments
    argv[0] is the filename
*/
int main(int argc, char* argv[]) {
    string line = "";
    if (argc < 1) {
        cout << "missing argv[0]: " << argv[0] << endl;
        return 1;
    }
    if (argc == 1) { // default app start

    }

    // logic loop
    while (!cin.eof()) {
        cout << "> ";
        cout.flush();
        getline(cin, line);
        stringstream ss(line);

        if (ss.fail() || cin.eof()) { // * check if ss failed before calling other functions
            ss.clear();
            ss.ignore(1000, ' ');
        }
        else {
            handleInput(ss);
        }
    }

    if (timer.joinable()) {
        timer.join();
    }

    this_thread::sleep_for(chrono::seconds(1));


    return 0;
}

// Function Implemenetation
bool getInteger(stringstream& ss, int& x) { // * returns true if successful
    ss >> x;
    if (ss.fail()) {
        ss.clear();
        ss.ignore(1000, '\n');
        return false;
    }
    return true;
}

bool getString(stringstream& ss, string& s) { // * returns true if successful
    ss >> s;
    if (ss.fail()) {
        ss.clear();
        ss.ignore(1000, '\n');
        return false;
    }
    return true;
}


void handleInput(stringstream& ss) {
    string command;
    if (!getString(ss, command)) {
        ss.clear();
        cout << "Error: " << errorArray[0] << endl;
    }
    else {
        // cout << command << endl;
        // cout << commandOptions[5] << endl;

        // start
        if (command == commandOptions[1]) { //TODO: add shorthand for start
            handleStart(ss);
        }
        // set
        else if (command == commandOptions[2]) {
            handleSet(ss);
        }
        // stop
        else if (command == commandOptions[3]) {
            handleStop(ss);
        }
        // continue
        else if (command == commandOptions[4]) {
            handleContinue(ss);
        }
        // pause
        else if (command == commandOptions[5]) {
            handlePause(ss);
        }
        // status
        else if (command == commandOptions[6]) {
            handleStatus(ss);
        }
        // reset
        else if (command == commandOptions[7]) {
            handleReset(ss);
        }
        else {
            cout << "Error: " << errorArray[0] << endl;
        }
    }
}


/*
    if the thread doesn't already exist, then it should start a new thread that does the counting
    if the thread exists, then it hsould display an error
*/
void handleStart(stringstream& ss) {
    isRunning = true;
    isFocusMode = !isFocusMode;

    if (isFocusMode) {
        timer = thread(runFocusTimer); // while on a seperate thread, the code will enter a new input setup that would be used pause or stop the focus session
        timer.detach();
        cout << "focus pomodoro started" << endl;

    }
    else {
        timer = thread(runBreakTimer);
        timer.detach();
        cout << "break pomodoro started" << endl;
    }
}

/*
    When the user requests the pomodoro timer to be stopped, the timer should reset the current time to zero and move to the next state (focus -> break, break -> focus)
*/

void handleStop(stringstream& ss) { // run after pausing
    if (stopTimer == false) {
        cout << timerErrorArray[1] << endl;
        return;
    }
    if (isFocusMode) {
        currentFocusTime = 0;
    }
    else {
        currentBreakTime = 0;
    }
    stopTimer = false;
    cout << "pomodoro stopped" << endl;
}


void handlePause(stringstream& ss) {
    if (isRunning == false) {
        cout << timerErrorArray[0] << endl;
        return;
    }
    isRunning = false;
    string command;

    stopTimer = true;
    if (timer.joinable()) {
        timer.join();
    }

    this_thread::sleep_for(chrono::seconds(1));




    // cout << "pomodoro paused" << endl;

}


void handleContinue(stringstream& ss) { // run after pausing
    if (stopTimer == false) {
        cout << timerErrorArray[1] << endl;
        return;
    }

    isRunning = true;
    stopTimer = false;

    cout << "pomodoro continued" << endl;


    if (isFocusMode) {
        timer = thread(runFocusTimer); // while on a seperate thread, the code will enter a new input setup that would be used pause or stop the focus session
        timer.detach();
    }
    else {
        timer = thread(runBreakTimer);
        timer.detach();
    }
}

/*
    this function sets up the length of the focus and break periods
    -f: change focus time
    -b: change break time

    the input will be in minutes and the code should convert it to seconds
*/
void handleSet(stringstream& ss) { // this ss doesn't have "set"
    string args;
    int value;
    if (ss.str() == "set") {
        cout << "Error: " << errorArray[2] << endl;
        return;
    }
    while (ss >> args) {
        if (args == "-f") {
            if (!getInteger(ss, value)) {
                ss.clear();
                ss.ignore(1000, ' ');
            }
            else {
                focusTime = value * 60;
                cout << focusTime << endl;
            }
        }
        else if (args == "-b") {
            if (!getInteger(ss, value)) {
                ss.clear();
                ss.ignore(1000, ' ');
            }
            else {
                breakTime = value * 60;
                cout << breakTime << endl;

            }
        }
    }
}

void handleStatus(stringstream& ss) {
    if (isFocusMode) {
        cout << "current focus time: " << currentFocusTime / 60 << ":" << setfill('0') << setw(2) << currentFocusTime % 60 << endl;
        cout << "total focus time: " << focusTime / 60 << endl;
        cout << "completed %: " << (currentFocusTime * 100) / focusTime << endl;
    }
    else {
        cout << "current break time: " << currentBreakTime / 60 << ":" << setfill('0') << setw(2) << currentBreakTime % 60 << endl;
        cout << "total break time: " << breakTime / 60 << endl;
        cout << "completed %: " << (currentBreakTime * 100) / breakTime << endl;
    }
}


void handleReset(stringstream& ss) {
    currentFocusTime = 0;
    currentBreakTime = 0;
    focusTime = 25 * 60;
    breakTime = 5 * 60;
    isRunning = false;
    stopTimer = true;

    if (timer.joinable()) {
        timer.join();
    }
    stopTimer = false;
    isFocusMode = false;
    cout << "timer reset" << endl;
}



void runFocusTimer() {
    for (; currentFocusTime <= focusTime; currentFocusTime++) {
        if (stopTimer) {
            cout << "focus timer stopped" << endl;
            return;
        }
        this_thread::sleep_for(chrono::seconds(1));
    }
    cout << endl;
    cout << "! focus timer finished" << endl;
    cout << "> ";
}


void runBreakTimer() {
    for (; currentBreakTime <= breakTime; currentBreakTime++) {
        if (stopTimer) {
            cout << "break timer stopped" << endl;
            return;
        }
        this_thread::sleep_for(chrono::seconds(1));
    }
    cout << endl;
    cout << "! break timer finished" << endl;
    cout << "> ";
}