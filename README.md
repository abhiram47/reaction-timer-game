# Reaction Timer Game

## Version 1
- Random delay (3-10 sec)
- High Resolution timer for accurate measurements 
- crossplatform (Win/Linux)
- Display reaction time in ms

## What i learned 
- using rand() and srand() for randomization
- platform specific timing ('QueryPerformanceCounter' is used in Win)
- basic input capture using getch()

## Next Steps
- Add structures to organize game data
- Implement state machine for game flow
- Track multiple rounds and statistics


-------------------------------------------------------------------------------------


## Version 2 
- State Machine : ive rebuild the game with enum and state machines (STATE_MENU, STATE_READY, STATE_WAITING, STATE_FIRED, STATE_RESULT).
- Data Structures : added structs to structure all the data (PlayerStats, GameSettings)
- The game now tracks and records the 
    - best time 
    - worst  time 
    - avg time
    - total games played 
- The game now have an interactive menu
- Input Bug Fix: Solved input buffering issues by replacing all getchar() calls with getch()

## What i learned 
- How to design and implement a state machine with switch statements
- How to organize data using structs 
- The difference between buffered (getchar()) and unbuffered (getch()) input and how to fix related bugs.
- How to build a clean, looping game menu.

## Next Steps
- Try to find if anyone cheats by pressing the button before the "fire" cmd as i saw there is an o/p coming on pressing it before the "fire" indication.
- save the states to another file as they will persist between game sessions 
- make main(); more cleaner. 


-------------------------------------------------------------------------------------


## Version 3