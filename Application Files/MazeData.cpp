//
//  MazeData.cpp
//  PAC-MAN 2017
//
//  Created by Carlos Estrada on 11/16/17.
//  Copyright © 2017 Carlos Estrada. All rights reserved.
//
#include "MazeData.hpp"
#include <sstream>

void MazeData::loadPellets(int arraySize) {
    powerPelletTexture.loadFromFile(resourcePath() + "/Graphics/maze-ppellet.png");

	if (arraySize == 4) {
		for (int i = 0; i < arraySize; i++) {
			powerPellet[i].create(powerPelletTexture, Vector2f(powerPelletSize, powerPelletSize), Vector2f(0.0f, 0.0f));
		}
	}
	else if (arraySize == 240) {
		for (int i = 0; i < arraySize; i++) {
			pellet[i].create("pellet", Vector2f(pelletSize, pelletSize), Vector2f(0.0f, 0.0f));
		}
	}
}

void MazeData::placePellets(int arraySize) {
	// Power Pellets
	if (arraySize == 4) {
		powerPellet[0].setPosition(Vector2f(157, 179));	// top left
		powerPellet[1].setPosition(Vector2f(157, 746));	// bottom left
		powerPellet[2].setPosition(Vector2f(869, 179));	// top right
		powerPellet[3].setPosition(Vector2f(869, 746)); // bottom right
	}
	// Pellets
	else if (arraySize == 240) {
		// ROW 1 LEFT
		for (int i = 0; i < 12; i++) {
			pellet[i].setPosition(Vector2f(157 + (28.5 * i), 121));
		}
		// ROW 1 RIGHT
		for (int i = 12; i < 24; i++) {
			pellet[i].setPosition(Vector2f(157 + (28.5 * (i + 2)), 121));
		}

		// ROW 2
		for (int i = 24; i < 50; i++) {
			pellet[i].setPosition(Vector2f(157 + (28.5 * (i - 24)), 235));
		}

		// ROW 3 LEFT 1
		for (int i = 50; i < 56; i++) {
			pellet[i].setPosition(Vector2f(157 + (28.5 * (i - 50)), 319));
		}
		// ROW 3 LEFT 2
		for (int i = 56; i < 60; i++) {
			pellet[i].setPosition(Vector2f(157 + (28.5 * (i - 48)), 319));
		}

		// ROW 3 RIGHT 1
		for (int i = 60; i < 64; i++) {
			pellet[i].setPosition(Vector2f(157 + (28.5 * (i - 46)), 319));
		}

		// ROW 3 RIGHT 2
		for (int i = 64; i < 70; i++) {
			pellet[i].setPosition(Vector2f(157 + (28.5 * (i - 44)), 319));
		}

		// ROW 4 LEFT
		for (int i = 70; i < 82; i++) {
			pellet[i].setPosition(Vector2f(157 + (28.5 * (i - 70)), 659));
		}
		// ROW 4 RIGHT
		for (int i = 82; i < 94; i++) {
			pellet[i].setPosition(Vector2f(157 + (28.5 * (i - 68)), 659));
		}

		// ROW 5 LEFT 1
		for (int i = 94; i < 96; i++) {
			pellet[i].setPosition(Vector2f(157 + (28.5 * (i - 93)), 746));
		}
		// ROW 5 LEFT 2
		for (int i = 96; i < 103; i++) {
			pellet[i].setPosition(Vector2f(157 + (28.5 * (i - 91)), 746));
		}
		// ROW 5 RIGHT 1
		for (int i = 103; i < 110; i++) {
			pellet[i].setPosition(Vector2f(157 + (28.5 * (i - 89)), 746));
		}
		// ROW 5 RIGHT 2
		for (int i = 110; i < 112; i++) {
			pellet[i].setPosition(Vector2f(157 + (28.5 * (i - 87)), 746));
		}

		// ROW 6 LEFT 1
		for (int i = 112; i < 118; i++) {
			pellet[i].setPosition(Vector2f(157 + (28.5 * (i - 112)), 830));
		}
		// ROW 6 LEFT 2
		for (int i = 118; i < 122; i++) {
			pellet[i].setPosition(Vector2f(157 + (28.5 * (i - 110)), 830));
		}
		// ROW 6 RIGHT 1
		for (int i = 122; i < 126; i++) {
			pellet[i].setPosition(Vector2f(157 + (28.5 * (i - 108)), 830));
		}
		// ROW 6 RIGHT 2
		for (int i = 126; i < 132; i++) {
			pellet[i].setPosition(Vector2f(157 + (28.5 * (i - 106)), 830));
		}
		// ROW 7
		for (int i = 132; i < 158; i++) {
			pellet[i].setPosition(Vector2f(157 + (28.5 * (i - 132)), 916));
		}

		// COLUMN 1
		pellet[158].setPosition(Vector2f(157, 121 + (28.5 * (1))));
		pellet[159].setPosition(Vector2f(157, 121 + (28.5 * (3))));
		pellet[160].setPosition(Vector2f(157, 121 + (28.5 * (5))));
		pellet[161].setPosition(Vector2f(157, 121 + (28.5 * (6))));
		pellet[162].setPosition(Vector2f(157, 121 + (28.5 * (20))));
		pellet[163].setPosition(Vector2f(157, 121 + (28.5 * (21))));
		pellet[164].setPosition(Vector2f(157, 121 + (28.5 * (26))));
		pellet[165].setPosition(Vector2f(157, 121 + (28.5 * (27))));

		// COLUMN 2
		pellet[166].setPosition(Vector2f(214, 121 + (28.5 * (23))));
		pellet[167].setPosition(Vector2f(214, 121 + (28.5 * (24))));

		// COLUMN 3
		pellet[168].setPosition(Vector2f(299, 121 + (28.5 * (1))));
		pellet[169].setPosition(Vector2f(299, 121 + (28.5 * (2))));
		pellet[170].setPosition(Vector2f(299, 121 + (28.5 * (3))));
		pellet[171].setPosition(Vector2f(299, 121 + (28.5 * (5))));
		pellet[172].setPosition(Vector2f(299, 121 + (28.5 * (6))));
		for (int i = 173; i < 184; i++) {
			pellet[i].setPosition(Vector2f(299, 121 + (28.5 * (i - 165))));
		}
		pellet[184].setPosition(Vector2f(299, 121 + (28.5 * (20))));
		pellet[185].setPosition(Vector2f(299, 121 + (28.5 * (21))));
		pellet[186].setPosition(Vector2f(299, 121 + (28.5 * (23))));
		pellet[187].setPosition(Vector2f(299, 121 + (28.5 * (24))));

		// COLUMN 4
		pellet[188].setPosition(Vector2f(385, 121 + (28.5 * (5))));
		pellet[189].setPosition(Vector2f(385, 121 + (28.5 * (6))));
		pellet[190].setPosition(Vector2f(385, 121 + (28.5 * (23))));
		pellet[191].setPosition(Vector2f(385, 121 + (28.5 * (24))));

		// COLUMN 5
		pellet[192].setPosition(Vector2f(470, 121 + (28.5 * (1))));
		pellet[193].setPosition(Vector2f(470, 121 + (28.5 * (2))));
		pellet[194].setPosition(Vector2f(470, 121 + (28.5 * (3))));
		pellet[195].setPosition(Vector2f(470, 121 + (28.5 * (20))));
		pellet[196].setPosition(Vector2f(470, 121 + (28.5 * (21))));
		pellet[197].setPosition(Vector2f(470, 121 + (28.5 * (26))));
		pellet[198].setPosition(Vector2f(470, 121 + (28.5 * (27))));

		// HALF WAY POINT (ALL VERTICAL COLUMNS CAN BE MIRRORED)

		// COLUMN 6
		pellet[199].setPosition(Vector2f(556, 121 + (28.5 * (1))));
		pellet[200].setPosition(Vector2f(556, 121 + (28.5 * (2))));
		pellet[201].setPosition(Vector2f(556, 121 + (28.5 * (3))));
		pellet[202].setPosition(Vector2f(556, 121 + (28.5 * (20))));
		pellet[203].setPosition(Vector2f(556, 121 + (28.5 * (21))));
		pellet[204].setPosition(Vector2f(556, 121 + (28.5 * (26))));
		pellet[205].setPosition(Vector2f(556, 121 + (28.5 * (27))));

		// COLUMN 7
		pellet[206].setPosition(Vector2f(641, 121 + (28.5 * (5))));
		pellet[207].setPosition(Vector2f(641, 121 + (28.5 * (6))));
		pellet[208].setPosition(Vector2f(641, 121 + (28.5 * (23))));
		pellet[209].setPosition(Vector2f(641, 121 + (28.5 * (24))));

		// COLUMN 8
		pellet[210].setPosition(Vector2f(727, 121 + (28.5 * (1))));
		pellet[211].setPosition(Vector2f(727, 121 + (28.5 * (2))));
		pellet[212].setPosition(Vector2f(727, 121 + (28.5 * (3))));
		pellet[213].setPosition(Vector2f(727, 121 + (28.5 * (5))));
		pellet[214].setPosition(Vector2f(727, 121 + (28.5 * (6))));
		for (int i = 215; i < 226; i++) {
			pellet[i].setPosition(Vector2f(727, 121 + (28.5 * (i - 207))));
		}
		pellet[226].setPosition(Vector2f(727, 121 + (28.5 * (20))));
		pellet[227].setPosition(Vector2f(727, 121 + (28.5 * (21))));
		pellet[228].setPosition(Vector2f(727, 121 + (28.5 * (23))));
		pellet[229].setPosition(Vector2f(727, 121 + (28.5 * (24))));

		// COLUMN 9
		pellet[230].setPosition(Vector2f(812, 121 + (28.5 * (23))));
		pellet[231].setPosition(Vector2f(812, 121 + (28.5 * (24))));

		// COLUMN 10
		pellet[232].setPosition(Vector2f(869, 121 + (28.5 * (1))));
		pellet[233].setPosition(Vector2f(869, 121 + (28.5 * (3))));
		pellet[234].setPosition(Vector2f(869, 121 + (28.5 * (5))));
		pellet[235].setPosition(Vector2f(869, 121 + (28.5 * (6))));
		pellet[236].setPosition(Vector2f(869, 121 + (28.5 * (20))));
		pellet[237].setPosition(Vector2f(869, 121 + (28.5 * (21))));
		pellet[238].setPosition(Vector2f(869, 121 + (28.5 * (26))));
		pellet[239].setPosition(Vector2f(869, 121 + (28.5 * (27))));
	}
}

void MazeData::placeNodes() {
    ghostNode[0].setPosition(Vector2f(512, 405));
    ghostNode[1].setPosition(Vector2f(463, 475));
	ghostNode[2].setPosition(Vector2f(512, 475));
	ghostNode[3].setPosition(Vector2f(562, 475));
	ghostNode[4].setPosition(Vector2f(512, 501));
	ghostNode[5].setPosition(Vector2f(463, 501));
	ghostNode[6].setPosition(Vector2f(562, 501));

	// ROW 1
	node[0].setPosition(pellet[0].getPosition());
	node[1].setPosition(pellet[5].getPosition());
	node[2].setPosition(pellet[11].getPosition());
	node[3].setPosition(pellet[12].getPosition());
	node[4].setPosition(pellet[18].getPosition());
	node[5].setPosition(pellet[23].getPosition());

	// ROW 2
	node[6].setPosition(pellet[24].getPosition());
	node[7].setPosition(pellet[29].getPosition());
	node[8].setPosition(pellet[32].getPosition());
	node[9].setPosition(pellet[35].getPosition());
	node[10].setPosition(pellet[38].getPosition());
	node[11].setPosition(pellet[41].getPosition());
	node[12].setPosition(pellet[44].getPosition());
	node[13].setPosition(pellet[49].getPosition());

	// ROW 3
	node[14].setPosition(pellet[50].getPosition());
	node[15].setPosition(pellet[55].getPosition());
	node[16].setPosition(pellet[56].getPosition());

	node[17].setPosition(Vector2f(pellet[59].getPosition().x - 1, pellet[59].getPosition().y));
	node[18].setPosition(Vector2f(pellet[60].getPosition().x - 1, pellet[60].getPosition().y));

	node[19].setPosition(pellet[63].getPosition());
	node[20].setPosition(pellet[64].getPosition());
	node[21].setPosition(pellet[69].getPosition());

	// PORTAL ROW
	node[22].setPosition(pellet[178].getPosition());
	node[23].setPosition(Vector2f(pellet[178].getPosition().x + 86, pellet[178].getPosition().y));
	node[24].setPosition(Vector2f(pellet[220].getPosition().x - 86, pellet[220].getPosition().y));
	node[25].setPosition(pellet[220].getPosition());

	// GHOST HOUSE (TOP)
	node[26].setPosition(Vector2f(pellet[175].getPosition().x + 86, pellet[175].getPosition().y - 1));
	node[27].setPosition(Vector2f(pellet[175].getPosition().x + 170, pellet[175].getPosition().y - 1));
	node[28].setPosition(Vector2f(pellet[217].getPosition().x - (86 * 2), pellet[217].getPosition().y - 1));
	node[29].setPosition(Vector2f(pellet[217].getPosition().x - 86, pellet[217].getPosition().y - 1));

	// GHOST HOUSE (BOTTOM)
	node[30].setPosition(Vector2f(pellet[181].getPosition().x + 86, pellet[181].getPosition().y - 2));
	node[31].setPosition(Vector2f(pellet[223].getPosition().x - 86, pellet[223].getPosition().y - 2));

	// ROW 4
	node[32].setPosition(pellet[70].getPosition());
	node[33].setPosition(pellet[75].getPosition());
	node[34].setPosition(pellet[78].getPosition());
	node[35].setPosition(pellet[81].getPosition());
	node[36].setPosition(pellet[82].getPosition());
	node[37].setPosition(pellet[85].getPosition());
	node[38].setPosition(pellet[88].getPosition());
	node[39].setPosition(pellet[93].getPosition());

	// ROW 5
	node[40].setPosition(powerPellet[1].getPosition());
	node[41].setPosition(pellet[95].getPosition());

	node[42].setPosition(pellet[96].getPosition());
	node[43].setPosition(pellet[99].getPosition());
	node[44].setPosition(pellet[102].getPosition());
	node[45].setPosition(Vector2f(512, 746));
	node[46].setPosition(pellet[103].getPosition());
	node[47].setPosition(pellet[106].getPosition());
	node[48].setPosition(pellet[109].getPosition());
	
	node[49].setPosition(pellet[110].getPosition());
	node[50].setPosition(powerPellet[3].getPosition());

	// ROW 6
	node[51].setPosition(pellet[112].getPosition());
	node[52].setPosition(pellet[114].getPosition());
	node[53].setPosition(pellet[117].getPosition());
	node[54].setPosition(pellet[118].getPosition());
	node[55].setPosition(pellet[121].getPosition());
	node[56].setPosition(pellet[122].getPosition());
	node[57].setPosition(pellet[125].getPosition());
	node[58].setPosition(pellet[126].getPosition());
	node[59].setPosition(pellet[129].getPosition());
	node[60].setPosition(pellet[131].getPosition());

	// ROW 7
	node[61].setPosition(pellet[132].getPosition());
	node[62].setPosition(pellet[143].getPosition());
	node[63].setPosition(pellet[146].getPosition());
	node[64].setPosition(pellet[157].getPosition());

}

void MazeData::setValidNodeMovements() {
    ghostNode[0].setValidDirections(false, true, true, true);
    ghostNode[1].setValidDirections(false, true, false, true);
    ghostNode[2].setValidDirections(true, true, true, true);
    ghostNode[3].setValidDirections(false, true, true, false);
    ghostNode[4].setValidDirections(true, false, false, true);
    ghostNode[5].setValidDirections(true, false, true, true);
    ghostNode[6].setValidDirections(true, false, true, false);
    
    // ROW 1
    node[0].setValidDirections(false, true, false, true);
    node[1].setValidDirections(false, true, true, true);
    node[2].setValidDirections(false, true, true, false);
    node[3].setValidDirections(false, true, false, true);
    node[4].setValidDirections(false, true, true, true);
    node[5].setValidDirections(false, true, true, false);
    
    // ROW 2
    node[6].setValidDirections(true, true, false, true);
    node[7].setValidDirections(true, true, true, true);
    node[8].setValidDirections(false, true, true, true);
    node[9].setValidDirections(true, false, true, true);
    node[10].setValidDirections(true, false, true, true);
    node[11].setValidDirections(false, true, true, true);
    node[12].setValidDirections(true, true, true, true);
    node[13].setValidDirections(true, true, true, false);
    
    // ROW 3
    node[14].setValidDirections(true, false, false, true);
    node[15].setValidDirections(true, true, true, false);
    node[16].setValidDirections(true, false, false, true);
    node[17].setValidDirections(false, true, true, false);
    node[18].setValidDirections(false, true, false, true);
    node[19].setValidDirections(true, false, true, false);
    node[20].setValidDirections(true, true, false, true);
    node[21].setValidDirections(true, false, true, false);
    
    // PORTAL ROW
    node[22].setValidDirections(true, true, true, true);
    node[23].setValidDirections(true, true, true, false);
    node[24].setValidDirections(true, true, false, true);
    node[25].setValidDirections(true, true, true, true);
    
    // GHOST HOUSE (TOP)
    node[26].setValidDirections(false, true, false, true);
    node[27].setValidDirections(true, false, true, true);
    node[28].setValidDirections(true, false, true, true);
    node[29].setValidDirections(false, true, true, false);
    
    // GHOST HOUSE (BOTTOM)
    node[30].setValidDirections(true, true, false, true);
    node[31].setValidDirections(true, true, true, false);
    
    // ROW 4
    node[32].setValidDirections(false, true, false, true);
    node[33].setValidDirections(true, true, true, true);
    node[34].setValidDirections(true, false, true, true);
    node[35].setValidDirections(false, true, true, false);
    node[36].setValidDirections(false, true, false, true);
    node[37].setValidDirections(true, false, true, true);
    node[38].setValidDirections(true, true, true, true);
    node[39].setValidDirections(false, true, true, false);
    
    // ROW 5
    node[40].setValidDirections(true, false, false, true);
    node[41].setValidDirections(false, true, true, false);
    node[42].setValidDirections(true, true, false, true);
    node[43].setValidDirections(false, true, true, true);
    node[44].setValidDirections(true, false, true, true);
    
    node[45].setValidDirections(false, false, true, true); // NODE 45: PACMAN POSITION
    
    node[46].setValidDirections(true, false, true, true);
    node[47].setValidDirections(false, true, true, true);
    node[48].setValidDirections(true, true, true, false);
    node[49].setValidDirections(false, true, false, true);
    node[50].setValidDirections(true, false, true, false);
    
    // ROW 6
    node[51].setValidDirections(false, true, false, true);
    node[52].setValidDirections(true, false, true, true);
    node[53].setValidDirections(true, false, true, false);
    node[54].setValidDirections(true, false, false, true);
    node[55].setValidDirections(false, true, true, false);
    node[56].setValidDirections(false, true, false, true);
    node[57].setValidDirections(true, false, true, false);
    node[58].setValidDirections(true, false, false, true);
    node[59].setValidDirections(true, false, true, true);
    node[60].setValidDirections(false, true, true, false);
    
    // ROW 7
    node[61].setValidDirections(true, false, false, true);
    node[62].setValidDirections(true, false, true, true);
    node[63].setValidDirections(true, false, true, true);
    node[64].setValidDirections(true, false, true, false);
}

void MazeData::teleportPlayer(Player &player) {
    if (player.getPosition().x <= 100) {
        player.setPosition(Vector2f(WinX - 100, player.getPosition().y));
    }
    else if (player.getPosition().x >= WinX - 100) {
        player.setPosition(Vector2f(100, player.getPosition().y));
    }
}

void MazeData::drawPellets(RenderWindow& window, int arraySize) {
	for (int i = 0; i < arraySize; i++) {
		powerPellet[i].draw(window);
	}
}
