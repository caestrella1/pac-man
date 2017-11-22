//
//  Game.hpp
//  PAC-MAN 2017
//
//  Created by Carlos Estrada on 11/16/17.
//  Copyright © 2017 Carlos Estrada. All rights reserved.
//

#ifndef Game_hpp
#define Game_hpp
#include "MazeData.hpp"
#include <sstream>
#include <iostream>

#define STARTING    0    // WHEN GAME IS AT "READY" STATE
#define PLAYING     1    // WHEN PLAYER IS MOVING / UNPAUSED
#define DYING       2    // WHEN PACMAN DIES
#define PAUSED      3    // WHEN GAME IS PAUSED
#define WINNER      4    // WHEN PLAYER COLLECTS ALL PELLETS
#define LOSER       5    // WHEN LIVES REACH ZERO

// GHOST LOGIC
void ghostMultiplier(Player &pacman, Player &ghost, Vector2f &ghostPosition, Audio &eatghost, int &ghostCount, int &score);
void managePlayerState(Player &pacman);

bool checkCollision(Player& object1, Player& object2);
void findNode(Player& player, Node& node);

// SCORE AND LEVELS
void updatePoints(std::ostringstream &ss, int &score, Text &scoreValue);
void oneUp(int &score, int &lifeScore, int &lifeCount, Audio &life);
void levelUp(int &pelletCount, int &level, float &looppitch, Audio &siren, Player &fruit, bool &isEaten);
void setDifficulty(Player &blinky, Player &inky, Player &pinky, Player &clyde, float &edibleLimit);

// SOUND
void soundSwitcher(bool &isEdible, int &gamestate, Audio &siren, Audio &scatter);

// RESETS
void resetStats(int &lifeCount, int &pelletCount, int &score, int &lifeScore, int &level, float &looppitch, Player &fruit, std::ostringstream &ss, Text &scoreValue, Clock &startClock);
void resetPlayersOnDeath(Player &pacman, Player &blinky, Player &inky, Player &pinky, Player &clyde);
void resetOnGameOver(Player &pacman, Player &blinky, Player &inky, Player &pinky, Player &clyde, MazeData &maze, float &edibleTime);

#endif /* Game_hpp */
