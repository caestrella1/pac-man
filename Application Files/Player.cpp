//
//  Player.cpp
//  PAC-MAN 2017
//
//  Created by Carlos Estrada on 11/16/17.
//  Copyright © 2017 Carlos Estrada. All rights reserved.
//
#include "Player.hpp"
#include <time.h>

Player::Player(Texture* texture, Vector2u imageCount, float switchTime, float speed) :
	animate(texture, imageCount, switchTime)
{
	this->speed = speed;
	playerstate = 0;

	body.setSize(Vector2f(spriteSize, spriteSize));
	body.setPosition(Vector2f(0, 0));
	body.setOrigin(body.getSize() / 2.0f);
	body.setTexture(texture);
	srand(time(NULL));
}

void Player::setPosition(Vector2f position) {
	body.setPosition(position.x, position.y);
}

void Player::setTexture(Texture* texture) {
	body.setTexture(texture);
}

void Player::setSwitchTime(float newSwitchTime) {
	this->animate.switchTime = newSwitchTime;
}

void Player::setSpeed(float newSpeed) {
	this->speed = newSpeed;
}

void Player::setFrame(int newFrame) {
	this->animate.currentFrame.x = newFrame;
}

void Player::update(float deltaTime, int gamestate) {
	animate.Update(playerstate, deltaTime);
	body.setTextureRect(animate.uvRect);
}

bool Player::isCurrentDirectionValid(Node node, int choosedirection) {
    if (choosedirection == UP && node.isUpValid) {
        return true;
    }
    else if (choosedirection == DOWN && node.isDownValid) {
        return true;
    }
    else if (choosedirection == LEFT && node.isLeftValid) {
        return true;
    }
    else if (choosedirection == RIGHT && node.isRightValid) {
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

void Player::movePlayer(float deltaTime) {
	movement.x = 0.0;
	movement.y = 0.0;

	if (direction == RIGHT) {
		body.setRotation(0);
		movement.x = speed * deltaTime;
	}
	else if (direction == LEFT) {
		body.setRotation(180);
		movement.x = -speed * deltaTime;
	}
	else if (direction == UP) {
		body.setRotation(270);
		movement.y = -speed * deltaTime;
	}
	else if (direction == DOWN) {
		body.setRotation(90);
		movement.y = speed * deltaTime;
	}

	body.move(movement);
}

void Player::moveGhost(float deltaTime) {
	movement.x = 0.0;
	movement.y = 0.0;

	if (direction == RIGHT) {
		movement.x = speed * deltaTime;
		playerstate = FACERIGHT;
	}
	else if (direction == LEFT) {
		movement.x = -speed * deltaTime;
		playerstate = FACELEFT;
	}
	else if (direction == UP) {
		movement.y = -speed * deltaTime;
		playerstate = FACEUP;
	}
	else if (direction == DOWN) {
		movement.y = speed * deltaTime;
		playerstate = FACEDOWN;
	}

	body.move(movement);
}

void Player::blinkyAI(float deltaTime, Player pacman) {
	/*	BLINKY LOGIC:
		Follows directly behind PAC-MAN
		Always first out of ghost pen
	*/
	queueDirection = rand() % 4;
}

void Player::inkyAI(float deltaTime, Player pacman) {
	/*	INKY LOGIC:
		Uses PAC-MAN's position/direction and Blinky's position
		Exits ghost pen after PAC-MAN eats 30 pellets
	*/
	queueDirection = rand() % 4;
}

void Player::pinkyAI(float deltaTime, Player pacman) {
	/*	PINKY LOGIC:
		Ambushes PAC-MAN by positioning himself in his way
		Second out of pen, right on game start
	*/
	queueDirection = rand() % 4;
}

void Player::clydeAI(float deltaTime, Player pacman) {
	/*	CLYDE LOGIC:
		Follows directly behind PAC-MAN like Blinky but scatters once he's too close
		Exits pen after 1/3 of pellets are eaten
	*/
	queueDirection = rand() % 4;
}

void Player::draw(RenderWindow& window) {
	window.draw(body);
}
