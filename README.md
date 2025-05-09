# cli-project

This simple project is a pomodoro timer usable in the terminal CLI. The idea behind this is that you can set up a pomodoro timer with different focus and break timer options.

## Features

    - Custom focus and break timer
    - arguments options


## Libraries and Tools

    - string stream
    - main arguments

## Problems that need to be solved

    - The pomodoro timer is using a software delay. The code will be using a cache to optimize runtime meaning that it would not be the exact timing for the focus and break time. To solve this, the software timer should use volatile instead so that it will always go to memory instead of the cache 

## Next steps
