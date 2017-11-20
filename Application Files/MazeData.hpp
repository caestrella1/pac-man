//
//  MazeData.hpp
//  PAC-MAN 2017
//
//  Created by Carlos Estrada on 11/16/17.
//  Copyright © 2017 Carlos Estrada. All rights reserved.
//
#pragma once
#include "Player.hpp"

class MazeData {
	Texture powerPelletTexture, fruitTexture;

public:
	Platform powerPellet[4];
	Platform pellet[240];

	Node node[65];
	Node ghostNode[7];

	void loadPellets(int arraySize);
	void placePellets(int arraySize);
	void drawPellets(RenderWindow& window, int arraySize);

	void placeNodes();
    void setValidNodeMovements();
    void teleportPlayer(Player &player);
};
