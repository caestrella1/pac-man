//
//  Animation.cpp
//  PAC-MAN 2017
//
//  Created by Carlos Estrada on 11/16/17.
//  Copyright © 2017 Carlos Estrada. All rights reserved.
//

#include "Animation.hpp"

Animation::Animation(Texture* texture, Vector2u frameCount, float switchTime) {
    this->frameCount = frameCount;
    this->switchTime = switchTime;
    totalTime = 0.0f;
    currentFrame.x = 0;
    
    uvRect.width = texture->getSize().x / float(frameCount.x);
    uvRect.height = texture->getSize().y / float(frameCount.y);
}

void Animation::Update(int playerstate, float deltaTime) {
    currentFrame.y = playerstate;
    totalTime += deltaTime;
    
    if (totalTime >= switchTime) {
        totalTime -= switchTime;
        currentFrame.x++;
        
        if (currentFrame.x >= frameCount.x) {
            currentFrame.x = 0;
        }
    }
    
    uvRect.top = currentFrame.y * uvRect.height;
    uvRect.left = currentFrame.x * uvRect.width;
    uvRect.width = abs(uvRect.width);
}
