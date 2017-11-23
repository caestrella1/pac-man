//
//  Game.cpp
//  PAC-MAN 2017
//
//  Created by Carlos Estrada on 11/16/17.
//  Copyright © 2017 Carlos Estrada. All rights reserved.
//

#include "Game.hpp"

/***** GHOST LOGIC *****/
void ghostMultiplier(Player &pacman, Player &ghost, Audio &eatghost, int &ghostCount, int &score) {
    Vector2f position(512, 501);
    if (checkCollision(pacman, ghost)) {
        ghostCount++;
        ghost.setPosition(position);
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

void managePlayerState(Player &pacman) {
    if (pacman.getState() == ALIVE) {
        pacman.setFrameTime(seconds(0.01));
        pacman.setLooped(true);
    }
    else if (pacman.getState() == DEAD) {
        pacman.setFrameTime(seconds(0.075));
        pacman.setLooped(false);
        pacman.setFrame(0);
        pacman.direction = NONE;
        pacman.setRotation(0);
    }
    if (pacman.getState() == REVIVED) {
        pacman.setLooped(false);
    }
}

void manageGhostState(Player &ghost, float edibleTime, float edibleLimit) {
    if (ghost.isEdible) {
        (edibleTime >= (edibleLimit / 1.5) && edibleTime < edibleLimit) ? ghost.switchState(BLINK) : ghost.switchState(SCATTER);
    }
}

bool checkCollision(Player& object1, Player& object2) {
    return Collision::BoundingBoxTest(object1, object2);
}

void findNode(Player& player, Node& node) {
    if ((Vector2i)node.getPosition() == (Vector2i)player.getPosition()) {
        player.setDirectionAtNode(node);
    }
}

/***** SCORE AND LEVELS *****/
void updatePoints(std::ostringstream &ss, int &score, Text &playerScore) {
    ss.str("");
    ss << score;
    playerScore.setString(ss.str());
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
        fruit.switchState(level - 1);
    }
    else {
        fruit.switchState(5);
    }
    fruit.setPosition(Vector2f(512, 576));
    isEaten = false;
    pelletCount = 0;
    looppitch = 1.0;
    siren.setPitch(looppitch);
}

void setDifficulty(Player &blinky, Player &inky, Player &pinky, Player &clyde, float &edibleLimit) {
    if (edibleLimit > 0.0) {
        edibleLimit -= 1.0;
    }
    if (blinky.getPlayerSpeed() < 160) {
        blinky.setPlayerSpeed(blinky.getPlayerSpeed() + 5);
        inky.setPlayerSpeed(inky.getPlayerSpeed() + 5);
        pinky.setPlayerSpeed(pinky.getPlayerSpeed() + 5);
        clyde.setPlayerSpeed(clyde.getPlayerSpeed() + 5);
    }
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
void resetStats(int &lifeCount, int &pelletCount, int &score, int &lifeScore, int &level, float &looppitch, Player &fruit, std::ostringstream &ss, Text &playerScore,
        Clock &startClock) {
    level = 1;
    fruit.switchState(0);
    lifeCount = 4;
    pelletCount = 0;
    score = 0;
    lifeScore = 10000;
    looppitch = 1.0;
    updatePoints(ss, score, playerScore);
    startClock.restart().asSeconds();
}

void resetGame(Player &pacman, Player &blinky, Player &inky, Player &pinky, Player &clyde, MazeData &maze, float &edibleTime, int &gamestate) {
    Vector2f pacmanPos(512, 746), blinkyPos(512, 405), inkyPos(463, 501), pinkyPos(512, 501), clydePos(562, 501);
    
    pacman.setPosition(pacmanPos);
    pacman.direction = NONE;
    pacman.queueDirection = NONE;
    pacman.setRotation(0);
    pacman.setFrame(0);
    
    blinky.setPosition(blinkyPos); inky.setPosition(inkyPos); pinky.setPosition(pinkyPos); clyde.setPosition(clydePos);
    blinky.switchState(FACERIGHT); inky.switchState(FACEUP); pinky.switchState(FACEDOWN); clyde.switchState(FACEUP);
    blinky.queueDirection = inky.queueDirection = pinky.queueDirection = clyde.queueDirection = NONE;
    blinky.direction = inky.direction = pinky.direction = clyde.direction = NONE;
    
    if (gamestate == LOSER) {
        edibleTime = 10;
    }
    else {
        if (gamestate != STARTING) {
            maze.placePellets(240);
            maze.placePellets(4);
        }
    }
}



