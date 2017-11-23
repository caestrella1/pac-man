//
//  Player.cpp
//  PAC-MAN 2017
//
//  Created by Carlos Estrada on 11/16/17.
//  Copyright © 2017 Carlos Estrada. All rights reserved.
//
#include "Player.hpp"
#include <time.h>

Player::Player(float speed) {
    play();
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
    play(state[0]);
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
    play(state[0]);
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

bool Player::isCurrentDirectionValid(Node node, int dir) {
    if (dir == UP && node.isUpValid) {
        return true;
    }
    else if (dir == DOWN && node.isDownValid) {
        return true;
    }
    else if (dir == LEFT && node.isLeftValid) {
        return true;
    }
    else if (dir == RIGHT && node.isRightValid) {
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

void Player::movePlayer(Time deltaTime, int gstate) {
    if (gstate != PLAYING) {
        if (getState() == DEAD) {
            play();
            return;
        }
        pause();
        return;
    }
    
    movement.x = 0.0; movement.y = 0.0;

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
    (movement.x > 0.0 || movement.x < 0.0 || movement.y > 0.0 || movement.y < 0.0) ? play() : pause();
}

void Player::moveGhost(Time deltaTime, int gstate) {
    if (gstate != PLAYING) {
        pause();
        return;
    }
    
    movement.x = 0.0; movement.y = 0.0;
    
    switch (direction) {
        case RIGHT: movement.x = speed_ * deltaTime.asSeconds();
            break;
        case LEFT: movement.x = -speed_ * deltaTime.asSeconds();
            break;
        case UP: movement.y = -speed_ * deltaTime.asSeconds();
            break;
        case DOWN: movement.y = speed_ * deltaTime.asSeconds();
            break;
    }
    if (!isEdible) {
        switch (direction) {
            case RIGHT: switchState(FACERIGHT);
                break;
            case LEFT: switchState(FACELEFT);
                break;
            case UP: switchState(FACEUP);
                break;
            case DOWN: switchState(FACEDOWN);
                break;
        }
    }

    move(movement);
    (movement.x > 0.0 || movement.x < 0.0 || movement.y > 0.0 || movement.y < 0.0) ? play() : pause();
}

int Player::findOpposite(int dir) {
    if (dir == RIGHT) {
        return LEFT;
    }
    else if (dir == LEFT) {
        return RIGHT;
    }
    else if (dir == UP) {
        return DOWN;
    }
    else if (dir == DOWN) {
        return UP;
    }
}

void Player::blinkyAI(Time deltaTime, Player pacman) {
    /*    BLINKY LOGIC:
        Follows directly behind PAC-MAN
        Always first out of ghost pen
    */
    
    int directions[3], index = 0;
    for (int i = 0; i < 4; i++) {
        if (i != findOpposite(direction)) {
            directions[index] = i;
            index++;
        }
    }
    queueDirection = directions[rand() % 3];
}

void Player::inkyAI(Time deltaTime, Player pacman) {
    /*    INKY LOGIC:
        Uses PAC-MAN's position/direction and Blinky's position
        Exits ghost pen after PAC-MAN eats 30 pellets
    */
    int directions[3], index = 0;
    for (int i = 0; i < 4; i++) {
        if (i != findOpposite(direction)) {
            directions[index] = i;
            index++;
        }
    }
    queueDirection = directions[rand() % 3];
}

void Player::pinkyAI(Time deltaTime, Player pacman) {
    /*    PINKY LOGIC:
        Ambushes PAC-MAN by positioning himself in his way
        Second out of pen, right on game start
    */
    int directions[3], index = 0;
    for (int i = 0; i < 4; i++) {
        if (i != findOpposite(direction)) {
            directions[index] = i;
            index++;
        }
    }
    queueDirection = directions[rand() % 3];
}

void Player::clydeAI(Time deltaTime, Player pacman) {
    /*    CLYDE LOGIC:
        Follows directly behind PAC-MAN like Blinky but scatters once he's too close
        Exits pen after 1/3 of pellets are eaten
    */
    int directions[3], index = 0;
    for (int i = 0; i < 4; i++) {
        if (i != findOpposite(direction)) {
            directions[index] = i;
            index++;
        }
    }
    queueDirection = directions[rand() % 3];
}

