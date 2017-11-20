//
//  Platform.hpp
//  PAC-MAN 2017
//
//  Created by Carlos Estrada on 11/16/17.
//  Copyright © 2017 Carlos Estrada. All rights reserved.
//
#pragma once
#include "Collider.hpp"
using namespace sf;

class Platform {
public:
    Texture powerPelletTexture;
    void create(std::string mode, Vector2f size, Vector2f position);
    void create(Texture& powerpellet, Vector2f size, Vector2f position);
	Vector2f getPosition() { return body.getPosition(); }
	void setPosition(Vector2f newPos);

	void draw(RenderWindow& window);
	Collider getCollider() { return Collider(body); }

private:
	RectangleShape body;
};
