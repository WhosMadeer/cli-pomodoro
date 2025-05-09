#include "timer.h"

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
    if (automaticSwitch) {
        handleStart();
    }
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
    if (automaticSwitch) {
        handleStart();
    }
}