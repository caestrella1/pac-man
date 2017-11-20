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

class Player {
public:
	RectangleShape body;
	bool WASDkeys = true;
	float switchTime;

	Player(Texture* texture, Vector2u imageCount, float switchTime, float speed);

    int direction = NONE, queueDirection = NONE, tryDirection = NONE, playerstate = 0;
	Vector2f movement;

	void setTexture(Texture* texture);
	void setSwitchTime(float newSwitchTime);
	void setSpeed(float newSpeed);
	void setFrame(int newFrame);
	void update(float deltaTime, int gamestate);

	void nextDirection();
	void setDirectionAtNode(Node node);
	void setDirectionOpposite();
	void movePlayer(float deltaTime);
	void moveGhost(float deltaTime);

	void blinkyAI(float deltaTime, Player pacman);
	void inkyAI(float deltaTime, Player pacman);
	void pinkyAI(float deltaTime, Player pacman);
	void clydeAI(float deltaTime, Player pacman);

	void draw(RenderWindow& window);

	Vector2f getPosition() { return body.getPosition(); }
	void setPosition(Vector2f position);

	Collider getCollider() { return Collider(body); }

private:
	Animation animate;
	float speed;
    
    bool isCurrentDirectionValid(Node node, int choosedirection);
};
