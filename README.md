# ENGG1340 Course Project (2021-22 S2)

## Members: 
#### Group 100
- Agrim Somani
  - UID: 3035946722
  - Username: AgrimSomani

- Karanveer Singh
  - UID: 3035918622
  - Username: thekaranvs
  
## Game Proposal
We plan to implement a dungeon crawler adventure video game where the player has to complete all the levels to escape the dungeon and win the game.

## Game Description
#### Name: Escape The Dungeon

#### Premise
You awake trapped in a sadistic millionare's dungeon. To escape, you must complete all the mine-games your kidnapper has laid out for you. If you fail, certain death awaits. Do your best to live up to the expectations placed on you!

##### Objective: Complete all minigames without losing all your HP.

#### Game Mechanics: 
The player will be able able to: 
- Move around the map in all 4 directions
- Have 100 points of health, which can be replenished with potions laid around the levels 
- Trigger random traps that deplete your HP
- Play the minigames set up for you by the enemy, which consists of Tic Tac Toe, Snakes And Ladders, Hangman, Rock Paper Scissors and lastly Crossword.

#### Game Rules:
You must complete all 5 levels, which have their own specific challenges and minigames, to finish the game. If a game is lost, 40 health is deducted from your health bar. If you finish all the games without losing all your health, you have successfully escaped the dungeon and won. A player can decide to quit when in dungeon, and save their status and reload the game when played again. However, if in middle of a minigame, a player cannot quit and save their progress, they must only quit when in the dungeon. 

#### Game Features (which fulfill coding requirements):

| Coding Requirements                      | Feature                                                                         |
| ---------------------------------------- | ------------------------------------------------------------------------------- |
| Generation of random game sets or events | A bot will randomly pick a move in the tic tac toe game, random words from an array of words related to ENGG1340 will be picked for hangman, and the CPU will also pick a random move in Rock Paper Scissors mini-game. There will also be random heal potions and traps that will affect the players health bar. |
| Data structures for storing game status  | An 2D array is used to store the dungeon and its staus after each move, and an user-defined structure is also made with member variables such as health variable which stores the health of the player, position variable which stores the position of the player in the dungeon, prevposition variable which will store the players previous position before it makes the move and lastly a counter variable which stores the number of mini-games played by the player.|
| Dynamic memory management                | Extensive use of vectors throughout the program. For example, a vector is used to store all the minigames which have not been played yet, to know which minigame can be played next. Another example is the useage of a vector to store the indexes at which health potions, traps and minigames are located in the dungeon array.|
| File input/output                        | A player can exit the game in the dungeon. If they want to load the game again and continue from the point left off in the dungeon, we will store the structure containing the health, level, traps object into an ofstream object.  When the player wants to play again, we can treat that same file as an ifstream object, and extract the level, health etc that the player had. |
| Program codes in multiple files          | Helper functions for a few minigames such as Hangman, Tic Tac Toe and Snakes and Ladders is stored in 3 seperate source files, according to which game the fucntions are required for.|

Please keep all the files and directories in this repository in the same directory in order for the makefile to work.
Academy 21 server was used for testing.

#### Compilation and Execution Instructions
To compile the game, use the command: make game\
To execute it, run the command: ./game\
No non-standard C++ libraries were used and there are no special requirements.
