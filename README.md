# Reaction Timer Game
## Gameplay
1. Press 1 to start a game
2. Wait for [FIRE!] signal
3. React as quickly as possible
4. View your stats (option 2)
5. Stats auto-save on exit

## Version History

**v1**: Basic timer with random delay and reaction measurement  
**v2**: State machine, structs, statistics tracking  
**v3**: Cheat detection, persistent storage, error handling

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
- Cheat Detection: Added kbhit() to detect if player pressed button before FIRE signal and reject invalid attempts.
- Persistent Storage: Implemented binary file I/O to save and load game stats (PlayerStats) between sessions using fwrite() and fread().
- Error Handling: Added validation for reaction times (rejects times < 0 or > 10000 ms) and file I/O operations with return values.
- Code Modularity: Extracted initialize_game() function and refactored each state into individual handler functions for cleaner main().
- Input Validation: Menu choices are validated, and load/save functions now return bool to signal success or failure.


## What i learned
- How to implement cheat detection by checking input state before processing
- Binary file I/O (fwrite/fread) for efficient structured data persistence
- Defensive programming: validating edge cases (div by zero, invalid times, file errors)
- How to return bool values to signal error conditions
- Modular function design: separating concerns into individual state handlers
- Safe initialization patterns: set defaults first, then conditionally override with loaded data


## Next Steps
- Implement cross-platform non-blocking input detection (replace Windows-specific kbhit())
- Add difficulty levels with configurable delay ranges
- Create leaderboard/ranking system based on reaction times
- Explore observer pattern for game state notifications     


-------------------------------------------------------------------------------------

## Version 4
