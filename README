ENCE260 Assignment

Rock, Paper, Scissors programmed on an AVR ATmega32 micro-controller.

**Developed By**: Matt Lane(mla159) and Daniel Neal (dne33)

**Publish Date**: October 2022


## Setting up

1. Clone the UCFK4 git repository: This contains all the necessary drivers and utilities to run the battleships application
```
 git clone https://eng-git.canterbury.ac.nz/steve.weddell/ence260-ucfk4.git
```

2. Clone our game: It needs to be cloned into the assignment directory in the ucfk4 folder
```
 cd ence260-ucfk4/assignment
 git clone https://eng-git.canterbury.ac.nz/ence260-2022/group_236.git
 cd group_236
```


## File Structure
    - `game.c`: Contains the main game task scheduling, logic and game phase tracking
    - `game_logic.c`, `game_logic.h`: Contains all game logic operations (deciding winners and cycling through choices)
    - `game_display.c`, `game_display.h`: Contains all game display operations (displaying messages and RPS choices)
    - `Makefile`: Contains the basic Makefile for game.c

## Usage
From within this directory, the following commands can be run
    - `make clean`: Removes old object files from directory
    - `make`: Compiles source code and builds object files
    - `make program`: Loads program into UCFK4 flash memory
Run `make` and then `make program` to start playing!

## Game Play
**Starting the Game**: There will be a loading screen being `PRESS UP TO START` press the navswitch up get past this message.
**Note**: All messages displayed like this can be skipped by pressing up on the nav switch.


**Hint**: You dont need your boards to be close before you send so make sure your opponent doesnt get a peak!
**Choose your character**: After passing the start screen you will be presented with "R" for rock. Flick the nav switch left and right to cycle through youyr choices. To select a character press down on the navswitch to "Lock it in" a blue led should light up indicating you are ready to fight. 
 
**Starting**: Once both players have chosen the item, make sure the boards are within IR range, and players should push the button next to the IR transmitter to compare the chosen items. only one person will need to send so click the button and hope you win.

**Result**: If you win a little marker will appear in the bottom left of your screen after you skip the win/lose/draw screen.You will also be prompted to select another character. First to five wins so make sure you think hard!

**End Of Game**:  After 5 wins (or losses) you will be greeted with a overall winner/loser screen. If you'd like to play again simply press the nav switch up again.

