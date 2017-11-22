//
//  Player.hpp
//  PAC-MAN 2017
//
//  Created by Carlos Estrada on 11/16/17.
//  Copyright © 2017 Carlos Estrada. All rights reserved.
//
#pragma once
#include "Nodes.hpp"
using namespace sf;

#define NONE -1
#define LEFT 0
#define RIGHT 1
#define UP 2
#define DOWN 3

#define ALIVE 0
#define DEAD 1
#define REVIVED 2

#define FACELEFT 0
#define FACERIGHT 1
#define FACEUP 2
#define FACEDOWN 3
#define SCATTER 4
#define BLINK 5

class Player : public AnimatedSprite {
    Animation* state;
    Texture objtexture;
    IntRect TextureRect;
    int pstate = 0;
    
public:
    int direction = NONE, queueDirection = NONE, tryDirection = NONE;
    bool WASDkeys = true;
    Vector2f movement;
    float speed_;
    
    Player(float speed = 10);
    Player(std::string spritesheet, size_t spritesize, size_t numberofStates, size_t framesperState, float speed = 10);
    void initialize(std::string spritesheet, size_t spritesize, size_t numberofStates, size_t framesperState, float speed = 10);
    
    void switchState(size_t playerstate);
    int getState() { return pstate; }
    void setPlayerSpeed(float speed);
    float getPlayerSpeed() { return speed_; }
    void setAnimationSpeed(float speed);
    
    IntRect getTextureRect();

    void nextDirection();
    void setDirectionAtNode(Node node);
    void setDirectionOpposite();
    void movePlayer(Time deltaTime);
    void moveGhost(Time deltaTime);

    void blinkyAI(Time deltaTime, Player pacman);
    void inkyAI(Time deltaTime, Player pacman);
    void pinkyAI(Time deltaTime, Player pacman);
    void clydeAI(Time deltaTime, Player pacman);

private:
    bool isCurrentDirectionValid(Node node, int choosedirection);
};

