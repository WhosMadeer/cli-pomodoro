# cli-project

This simple project is a pomodoro timer usable in the terminal CLI. The idea behind this is that you can set up a pomodoro timer with different focus and break timer options. This project was done within a couple of hours without the use of AI.

1. Set up the pomodoro sessions using the set command

```
set -f <minutes> -b <minutes> -a <bool>
```
-f sets focus time
-b sets break time
-a tells the timer to continue to the next cycle automatically

2. Start the timer using the start command

```
start
```

3. Pause the timer using pause

```
pause
```

4. Stop or continue once it is paused
```
stop
continue
```

once the timer is stopped, it will go to the next cycle when the user runs the start command (focus -> break, break -> focus)
the continue command will continue from the current time

5. Get the current status using the status command
```
status
```


## Features

- Custom focus and break timer
- arguments options
- status with time and display
- multi threading for timer


## Libraries and Tools

- string stream
- main arguments
- thread
- atomic variables

## Problems that need to be solved

- The pomodoro timer is using a software delay. The code will be using a cache to optimize runtime meaning that it would not be the exact timing for the focus and break time. To solve this, the software timer should use volatile instead so that it will always go to memory instead of the cache 

## Next steps

- add a graphic UI in the terminal to show a progress bar and current status
- add cycle count to see how many focus sessions have been completed