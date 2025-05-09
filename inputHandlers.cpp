#include "inputHandlers.h"

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

bool getBoolean(stringstream& ss, bool& f) { // * returns true if successful
    ss >> f;
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
            handleStart();
        }
        // set
        else if (command == commandOptions[2]) {
            handleSet(ss);
        }
        // stop
        else if (command == commandOptions[3]) {
            handleStop();
        }
        // continue
        else if (command == commandOptions[4]) {
            handleContinue();
        }
        // pause
        else if (command == commandOptions[5]) {
            handlePause();
        }
        // status
        else if (command == commandOptions[6]) {
            handleStatus();
        }
        // reset
        else if (command == commandOptions[7]) {
            handleReset();
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
void handleStart() {
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

void handleStop() { // run after pausing
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


void handlePause() {
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


void handleContinue() { // run after pausing
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
    string flag;
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
                cout << "focus time: " << value << endl;
            }
        }
        else if (args == "-b") {
            if (!getInteger(ss, value)) {
                ss.clear();
                ss.ignore(1000, ' ');
            }
            else {
                breakTime = value * 60;
                cout << "break time: " << value << endl;

            }
        }
        else if (args == "-a") {
            if (!getString(ss, flag)) {
                ss.clear();
                ss.ignore(1000, ' ');
            }
            else {
                if (flag == "true") {
                    automaticSwitch = true;
                }
                else {
                    automaticSwitch = false;
                }
                cout << "automatic switching: " << flag << endl;
            }
        }
    }
}

void handleStatus() {
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


void handleReset() {
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

