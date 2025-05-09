#include <iostream>
#include <string>
#include <sstream>

using namespace std;

// * function declaration
void handleInput(stringstream& ss);
bool getInteger(stringstream& ss, int& x);
bool getString(stringstream& ss, string& s);


// * helper function
void handleStart(stringstream& ss);
void handleSet(stringstream& ss);


// * global variables
int focusTime;
int breakTime;

bool isRunning = false;
bool isFocusMode = false; // true is focus, false is break


string commandOptions[] = {
    "help",
    "start",
    "set",
    "clear",
};

string commandOptionsShorthand[] = {
    "-h"
};


string errorArray[] = {
    "invalid command",                                  // 0
    "invalid argument",                                 // 1
    "too few arguments",                                // 2
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
        // cout << ss.str() << endl;

        // start
        if (command == commandOptions[1]) { //TODO: add shorthand for start
            handleStart(ss);
        }
        // set
        else if (command == commandOptions[2]) {
            handleSet(ss);
        }
        else {
            cout << "Error: " << errorArray[0] << endl;
        }
    }
}

// TODO: add graphic for pomodoro countdown
void handleStart(stringstream& ss) {
    isRunning = true;
    string command;

    // currentBreakTime = 0;
    cout << "pomodoro started" << endl;
    cout << ">";

    if (isFocusMode) {
        for (volatile int currentFocusTime = 0; currentFocusTime <= focusTime; currentFocusTime++) {
            if (!getString(ss, command)) {
                ss.clear();
            }
        }
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