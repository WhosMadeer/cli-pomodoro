#include "pomodoro.h"


/* Global Variables */

int focusTime = 25 * 60;
int breakTime = 5 * 60;
// default options 


bool isRunning = false;
bool isFocusMode = false;
bool automaticSwitch = false;

thread timer; // only need one thread

atomic<bool> stopTimer(false);

volatile int currentFocusTime = 0;
volatile int currentBreakTime = 0;


/* string array */

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
    if (argc > 1) { // default app start
        stringstream ss;
        for (int i = 1; i < argc; i++) {
            ss << argv[i];
            ss << " ";
        }
        handleInput(ss);
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

