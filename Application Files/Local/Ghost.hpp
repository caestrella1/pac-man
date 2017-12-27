//
//  Ghost.hpp
//  PAC-MAN 2017
//
//  Created by Carlos Estrada on 12/21/17.
//  Copyright © 2017 Carlos Estrada. All rights reserved.
//

#ifndef Ghost_hpp
#define Ghost_hpp

#include "Player.hpp"

class Ghost : public Player {
public:
    bool isEdible = false;
    
    Ghost(float speed = 10);
    Ghost(std::string spritesheet, size_t spritesize, size_t numberofStates, size_t framesperState, float speed = 10);
    
    void create(std::string spritesheet, size_t spritesize, size_t numberofStates,
                size_t framesperState, float speed = 10);
    
    void moveGhost(Time deltaTime, int gstate, float edibleTime, float edibleLimit);
    void ghostAI();
    
private:
    int findOpposite(int dir);
};

#endif /* Ghost_hpp */
