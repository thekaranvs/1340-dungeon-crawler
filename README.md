# ENGG1340 Course Project (2021-22 S2)

## Members: 
#### Group 100
- Agrim Somani
  UID: 3035946722
  Username: AgrimSomani

- Karanveer Singh
  UID: 3035918622
  Username: thekaranvs
  
## Game Proposal
We plan to implement a dungeon crawler adventure video game where the player has to complete all the levels to escape the dungeon and win the game.

## Game Description
#### Name: Escape The Dungeon (TBD)

#### Premise
You awake trapped in a sadistic millionare's dungeon. To escape, you must complete all the challenges and games your kidnapper has laid out for you. If you fail, certain death awaits. Do your best to live up to the expectations placed on you!

##### Objective: Complete all levels and minigames without losing all your HP, as fast as you can!

#### Game Mechanics: 
The player will be able able to: 
- Move around the map in all 4 directions
- Have 100 points of health, which can be replenished with potions laid around the levels 
- Pick up treasures to boost your final score
- Trigger random traps that deplete your HP
- Play the minigames set up for you by the enemy

#### Game Rules:
You must complete all 5 levels, which have their own specific challenges and minigames, to finish the game. Your score will be determined by the time you took to beat the game, your final HP, and all the bonus points you collected along the way.

#### Game Features (which fulfill coding requirements):

| Coding Requirements                      | Feature                                                                         |
| ---------------------------------------- | ------------------------------------------------------------------------------- |
| Generation of random game sets or events | A bot will randomly pick a move in the tic tac toe game, and other minigames we plan to implement. There will also be random heal potions and traps that will affect the players health bar. |
| Data structures for storing game status  | Will make a structure with objects such as an integer for health value,  a integer for which level the player is in, an array with all the different traps and potions that will be randomly generated for each game, there will also be an object which stores the date of the time when the player started the game, so we can calculate how long it took for the player to finish the game and give the player a score. |
| Dynamic memory management                | Use of vectors to store game objects (such as traps and potions) as well as pointers. |
| File input/output                        | A player can exit the game after they finish a level. If they want to laod the game again and continue from that level, we will store the structure containing the health, level, traps object into an ofstream object.  When the player wants to play again, we can treat that same file as an ifstream object, and extract the level, health etc that the player had. |
| Program codes in multiple files          | Each minigames code will be stored in different files |
