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

// GHOST LOGIC
void ghostCollisions(Player &pacman, Player &ghost, Audio &eatghost, int &ghostCount, int &score, int &gamestate,
                     Audio &death, bool &edible, Clock &startClock);
void managePlayerState(Player &pacman);

bool checkCollision(Player& object1, Player& object2);
void findNode(Player& player, Node& node);

// SCORE AND LEVELS
void updatePoints(std::ostringstream &ss, int &score, Text &playerScore);
void oneUp(int &score, int &lifeScore, int &lifeCount, Audio &life);
void levelUp(int &pelletCount, int &level, float &looppitch, Audio &siren, Player &fruit, bool &isEaten);
void setDifficulty(Player &blinky, Player &inky, Player &pinky, Player &clyde, float &edibleLimit);

// SOUND
void soundSwitcher(bool &isEdible, int &gamestate, Audio &siren, Audio &scatter);
void toggleMute(bool &isMuted, Player &sound, Audio &chomp1, Audio &chomp2, Audio &scatter, Audio &theme,
                Audio &siren, Audio &eatfruit, Audio &life, Audio &death, Audio &eatghost);

// RESETS
void resetStats(int &lifeCount, int &pelletCount, int &score, int &lifeScore, int &level, float &looppitch, Player &fruit,
                std::ostringstream &ss, Text &playerScore, Clock &startClock);
void resetGame(Player &pacman, Player &blinky, Player &inky, Player &pinky, Player &clyde, MazeData &maze, int &gamestate);

#endif /* Game_hpp */
