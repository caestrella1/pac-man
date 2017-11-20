//
//  Animation.hpp
//  PAC-MAN 2017
//
//  Created by Carlos Estrada on 11/16/17.
//  Copyright © 2017 Carlos Estrada. All rights reserved.
//
#pragma once
#include "Helpers.hpp"
using namespace sf;

class Animation {
private:
    Vector2u frameCount;
    float totalTime;
    
public:
    Animation(Texture* texture, Vector2u imageCount, float switchTime);
    void Update(int playerstate, float deltaTime);
    
    IntRect uvRect;
    Vector2u currentFrame;
    float switchTime;
};
