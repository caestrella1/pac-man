//
//  Platform.cpp
//  PAC-MAN 2017
//
//  Created by Carlos Estrada on 11/16/17.
//  Copyright © 2017 Carlos Estrada. All rights reserved.
//
#include "Platform.hpp"

void Platform::create(std::string mode, Vector2f size, Vector2f position) {
    if (mode == "pellet") {
        body.setFillColor(Color(237, 178, 149));
    }
    else if (mode == "powerpellet") {
        body.setTexture(&powerPelletTexture);
    }
    body.setSize(size);
    body.setOrigin(size / 2.0f);
    body.setPosition(position);
}

void Platform::create(Texture &powerpellet, Vector2f size, Vector2f position) {
    body.setTexture(&powerpellet);
    body.setSize(size);
    body.setOrigin(size / 2.0f);
    body.setPosition(position);
}

void Platform::draw(RenderWindow& window) {
	window.draw(body);
}

void Platform::setPosition(Vector2f newPos) {
	body.setPosition(newPos.x, newPos.y);
}
