//
//  Nodes.cpp
//  PAC-MAN 2017
//
//  Created by Carlos Estrada on 11/18/17.
//  Copyright © 2017 Carlos Estrada. All rights reserved.
//

#include "Nodes.hpp"

Node::Node() {
    mazenode.setFillColor(Color(0, 0, 0, 0));
    mazenode.setSize(Vector2f(pelletSize, pelletSize));
    mazenode.setPosition(Vector2f(0.0f, 0.0f));
    mazenode.setOrigin(Vector2f(pelletSize / 2, pelletSize / 2));
    isUpValid = isDownValid = isLeftValid = isRightValid = false;
}

void Node::setPosition(Vector2f position) {
    mazenode.setPosition(position);
}

Vector2f Node::getPosition() {
    return mazenode.getPosition();
}

void Node::setValidDirections(bool up, bool down, bool left, bool right) {
    isUpValid = up;
    isDownValid = down;
    isLeftValid = left;
    isRightValid = right;
}
