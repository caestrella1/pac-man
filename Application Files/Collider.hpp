//
//  Colliders.hpp
//  PAC-MAN 2017
//
//  Created by Carlos Estrada on 11/16/17.
//  Copyright © 2017 Carlos Estrada. All rights reserved.
//
#pragma once
#include "Animation.hpp"
using namespace sf;

class Collider {
public:
    Collider(RectangleShape& body);

	void move(float dx, float dy) { body.move(dx, dy); }

	bool checkCollision(Collider other, float push);
	Vector2f GetPosition() { return body.getPosition(); }
	Vector2f GetHalfSize() { return body.getSize() / 2.0f; }

private:
	RectangleShape& body;
};

