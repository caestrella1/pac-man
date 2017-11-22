//
//  Player.cpp
//  PAC-MAN 2017
//
//  Created by Carlos Estrada on 11/16/17.
//  Copyright © 2017 Carlos Estrada. All rights reserved.
//
#include "Player.hpp"
#include <time.h>
#include <iostream>

Player::Player(float speed) {
    pause();
}

Player::Player(std::string spritesheet, size_t spritesize, size_t numberofStates, size_t framesperState, float speed) {
    IntRect textrect(0, 0, spritesize, spritesize);
    TextureRect = textrect;
    
    setOrigin(spritesize / 2, spritesize / 2);
    objtexture.loadFromFile(resourcePath() + "Graphics/" + spritesheet);
    state = new Animation[numberofStates];
    
    for (int i = 0; i < numberofStates; i++) {
        state[i].setSpriteSheet(objtexture);
        
        for (int j = 0; j < framesperState; j++) {
            state[i].addFrame(IntRect(j * spritesize, i * spritesize, spritesize, spritesize));
        }
    }
    setAnimation(state[0]);
    pause();
}

void Player::initialize(std::string spritesheet, size_t spritesize, size_t numberofStates, size_t framesperState, float speed) {
    setOrigin(spritesize / 2, spritesize / 2);
    objtexture.loadFromFile(resourcePath() + "Graphics/" + spritesheet);
    state = new Animation[numberofStates];
    
    for (int i = 0; i < numberofStates; i++) {
        state[i].setSpriteSheet(objtexture);
        
        for (int j = 0; j < framesperState; j++) {
            state[i].addFrame(IntRect(j * spritesize, i * spritesize, spritesize, spritesize));
        }
    }
    setAnimation(state[0]);
    play();
}

void Player::switchState(size_t playerstate) {
    pstate = playerstate;
    play(state[playerstate]);
}

void Player::setPlayerSpeed(float speed) {
    speed_ = speed;
}

void Player::setAnimationSpeed(float speed) {
    setFrameTime(seconds(speed));
}

IntRect Player::getTextureRect() {
    return TextureRect;
}

bool Player::isCurrentDirectionValid(Node node, int choosedirection) {
    if (choosedirection == UP && node.isUpValid) {
        return true;
    }
    else if (choosedirection == DOWN && node.isDownValid) {
        return true;
    }
    else if (choosedirection == LEFT && node.isLeftValid) {
        return true;
    }
    else if (choosedirection == RIGHT && node.isRightValid) {
        return true;
    }
    return false;
}

void Player::nextDirection() {
    if (WASDkeys) {
        if (Keyboard::isKeyPressed(Keyboard::D))
            queueDirection = RIGHT;
        else if (Keyboard::isKeyPressed(Keyboard::A))
            queueDirection = LEFT;
        else if (Keyboard::isKeyPressed(Keyboard::W))
            queueDirection = UP;
        else if (Keyboard::isKeyPressed(Keyboard::S))
            queueDirection = DOWN;
    }
    else {
        if (Keyboard::isKeyPressed(Keyboard::Right))
            queueDirection = RIGHT;
        else if (Keyboard::isKeyPressed(Keyboard::Left))
            queueDirection = LEFT;
        else if (Keyboard::isKeyPressed(Keyboard::Up))
            queueDirection = UP;
        else if (Keyboard::isKeyPressed(Keyboard::Down))
            queueDirection = DOWN;
    }
}

void Player::setDirectionAtNode(Node node) {
    if (queueDirection == UP) {
        if (node.isUpValid) {
            direction = UP;
        }
        else {
            if (!isCurrentDirectionValid(node, direction)) {
                direction = NONE;
            }
        }
    }
    else if (queueDirection == DOWN) {
        if (node.isDownValid) {
            direction = DOWN;
        }
        else {
            if (!isCurrentDirectionValid(node, direction)) {
                direction = NONE;
            }
        }
    }
    else if (queueDirection == LEFT) {
        if (node.isLeftValid) {
            direction = LEFT;
        }
        else {
            if (!isCurrentDirectionValid(node, direction)) {
                direction = NONE;
            }
        }
    }
    else if (queueDirection == RIGHT) {
        if (node.isRightValid) {
            direction = RIGHT;
        }
        else {
            if (!isCurrentDirectionValid(node, direction)) {
                direction = NONE;
            }
        }
    }
}

void Player::setDirectionOpposite() {
    if (WASDkeys) {
        if (direction == RIGHT)
            if (Keyboard::isKeyPressed(Keyboard::A))
                direction = LEFT;
        if (direction == LEFT)
            if (Keyboard::isKeyPressed(Keyboard::D))
                direction = RIGHT;
        if (direction == UP)
            if (Keyboard::isKeyPressed(Keyboard::S))
                direction = DOWN;
        if (direction == DOWN)
            if (Keyboard::isKeyPressed(Keyboard::W))
                direction = UP;
    }
    else {
        if (direction == RIGHT)
            if (Keyboard::isKeyPressed(Keyboard::Left))
                direction = LEFT;
        if (direction == LEFT)
            if (Keyboard::isKeyPressed(Keyboard::Right))
                direction = RIGHT;
        if (direction == UP)
            if (Keyboard::isKeyPressed(Keyboard::Down))
                direction = DOWN;
        if (direction == DOWN)
            if (Keyboard::isKeyPressed(Keyboard::Up))
                direction = UP;
    }
}

void Player::movePlayer(Time deltaTime) {
    movement.x = 0.0;
    movement.y = 0.0;

    if (direction == RIGHT) {
        setRotation(0);
        movement.x = speed_ * deltaTime.asSeconds();
    }
    else if (direction == LEFT) {
        setRotation(180);
        movement.x = -speed_ * deltaTime.asSeconds();
    }
    else if (direction == UP) {
        setRotation(270);
        movement.y = -speed_ * deltaTime.asSeconds();
    }
    else if (direction == DOWN) {
        setRotation(90);
        movement.y = speed_ * deltaTime.asSeconds();
    }

    move(movement);
}

void Player::moveGhost(Time deltaTime) {
    movement.x = 0.0;
    movement.y = 0.0;

    if (direction == RIGHT) {
        movement.x = speed_ * deltaTime.asSeconds();
        switchState(FACERIGHT);
    }
    else if (direction == LEFT) {
        movement.x = -speed_ * deltaTime.asSeconds();
        switchState(FACELEFT);
    }
    else if (direction == UP) {
        movement.y = -speed_ * deltaTime.asSeconds();
        switchState(FACEUP);
    }
    else if (direction == DOWN) {
        movement.y = speed_ * deltaTime.asSeconds();
        switchState(FACEDOWN);
    }

    move(movement);
}

void Player::blinkyAI(Time deltaTime, Player pacman) {
    /*    BLINKY LOGIC:
        Follows directly behind PAC-MAN
        Always first out of ghost pen
    */
    queueDirection = rand() % 4;
}

void Player::inkyAI(Time deltaTime, Player pacman) {
    /*    INKY LOGIC:
        Uses PAC-MAN's position/direction and Blinky's position
        Exits ghost pen after PAC-MAN eats 30 pellets
    */
    queueDirection = rand() % 4;
}

void Player::pinkyAI(Time deltaTime, Player pacman) {
    /*    PINKY LOGIC:
        Ambushes PAC-MAN by positioning himself in his way
        Second out of pen, right on game start
    */
    queueDirection = rand() % 4;
}

void Player::clydeAI(Time deltaTime, Player pacman) {
    /*    CLYDE LOGIC:
        Follows directly behind PAC-MAN like Blinky but scatters once he's too close
        Exits pen after 1/3 of pellets are eaten
    */
    queueDirection = rand() % 4;
}

