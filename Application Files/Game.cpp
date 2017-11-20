//
//  Game.cpp
//  PAC-MAN 2017
//
//  Created by Carlos Estrada on 11/16/17.
//  Copyright © 2017 Carlos Estrada. All rights reserved.
//

#include "Game.hpp"

/***** GHOST LOGIC *****/
bool checkGhost(Player &pacman, Player &ghost) {
    return pacman.getCollider().checkCollision(ghost.getCollider(), 1.0) == true;
}

void ghostMultiplier(Player &pacman, Player &ghost, Vector2f &ghostPosition, Audio &eatghost, int &ghostCount, int &score) {
    if (checkGhost(pacman, ghost)) {
        ghostCount++;
        ghost.setPosition(ghostPosition);
        eatghost.play();

        if (ghostCount == 4) {
            score = score + 1600;
        }
        else if (ghostCount == 3) {
            score = score + 800;
        }
        else if (ghostCount == 2) {
            score = score + 400;
        }
        else if (ghostCount == 1) {
            score = score + 200;
        }
    }
}

void deathByGhost(Player &pacman) {
    pacman.playerstate = DEAD;
    pacman.setFrame(0);
    pacman.setSwitchTime(0.075);
    pacman.direction = NONE;
    pacman.body.setRotation(0);
}

/***** SCORE AND LEVELS *****/
void updatePoints(std::ostringstream &ss, int &score, Text &scoreValue) {
    ss.str("");
    ss << score;
    scoreValue.setString(ss.str());
}

void oneUp(int &score, int &lifeScore, int &lifeCount, Audio &life) {
    if (score >= lifeScore) { // GAIN A LIFE EVERY 10,000 POINTS
        if (lifeCount < 7) {
            lifeCount++;
            lifeScore += 10000;
            life.play();
        }
    }
}

void levelUp(int &pelletCount, int &level, float &looppitch, Audio &siren, Player &fruit, bool &isEaten) {
    level++;
    if (level < 7) {
        fruit.playerstate = level - 1;
    }
    else {
        fruit.playerstate = 5;
    }
    fruit.setPosition(Vector2f(512, 576));
    isEaten = false;
    pelletCount = 0;
    looppitch = 1.0;
    siren.setPitch(looppitch);
}

void setDifficulty(Player &blinky, Player &inky, Player &pinky, Player &clyde, float &edibleLimit) {
    float pacmanSpeed = 200, ghostSpeed = 120;
    if (edibleLimit > 0.0) {
        edibleLimit -= 1.0;
    }
    if (ghostSpeed < 160) {
        ghostSpeed += 5;
    }
    blinky.setSpeed(ghostSpeed);
    inky.setSpeed(ghostSpeed);
    pinky.setSpeed(ghostSpeed);
    clyde.setSpeed(ghostSpeed);
}

/***** SOUNDS *****/
void soundSwitcher(bool &isEdible, int &gamestate, Audio &siren, Audio &scatter) {
    if (gamestate == PLAYING) {
        if (isEdible) {
            siren.stop();
            scatter.play();
        }
        else {
            scatter.stop();
            siren.play();
        }
    }
    else {
        siren.stop();
        scatter.stop();
    }
}

/***** RESETS *****/
void resetStats(int &lifeCount, int &pelletCount, int &score, int &lifeScore, int &level, float &looppitch, Player &fruit, std::ostringstream &ss, Text &scoreValue, Clock &startClock, float &deltaTime) {
    level = 1;
    fruit.playerstate = 0;
    lifeCount = 4;
    pelletCount = 0;
    score = 0;
    lifeScore = 10000;
    looppitch = 1.0;
    updatePoints(ss, score, scoreValue);
    startClock.restart().asSeconds();
    deltaTime = 0;
}

void resetPlayersOnDeath(Player &pacman, Player &blinky, Player &inky, Player &pinky, Player &clyde) {
    Vector2f pacmanPos(512, 746);
    Vector2f blinkyPos(512, 405);
    Vector2f pinkyPos(512, 501);
    Vector2f inkyPos(463, 501);
    Vector2f clydePos(562, 501);
    
    pacman.setPosition(pacmanPos);
    pacman.direction = NONE;
    pacman.queueDirection = NONE;
    pacman.body.setRotation(0);
    pacman.setFrame(0);
    
    blinky.setPosition(blinkyPos);                // TOP
    inky.setPosition(inkyPos);                    // LEFT (GHOST PEN)
    pinky.setPosition(pinkyPos);                // MIDDLE (GHOST PEN)
    clyde.setPosition(clydePos);                // RIGHT (GHOST PEN)
    blinky.playerstate = FACERIGHT;
    inky.playerstate = FACEUP;
    pinky.playerstate = FACEDOWN;
    clyde.playerstate = FACEUP;
}

void resetOnGameOver(Player &pacman, Player &blinky, Player &inky, Player &pinky, Player &clyde, MazeData &maze, float &edibleTime) {
    resetPlayersOnDeath(pacman, blinky, inky, pinky, clyde);
    maze.placePellets(240);
    maze.placePellets(4);
    edibleTime = 10;
}



