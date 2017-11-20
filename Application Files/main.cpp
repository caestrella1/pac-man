//
//  main.cpp
//  PAC-MAN 2017
//
//  Created by Carlos Estrada on 11/16/17.
//  Copyright © 2017 Carlos Estrada. All rights reserved.
//

#include "Game.hpp"

int main() {
    /*** WINDOW & CLOCKS ***/
    RenderWindow window(VideoMode(WinX, WinY), "PAC-MAN '17", Style::Default);

//    window.setMouseCursorVisible(false);
    window.setKeyRepeatEnabled(false);

    View view(Vector2f(0.0, 0.0), Vector2f(WinX, WinY));
    view.setCenter(Vector2f(WinX / 2, WinY / 2));

    Clock clock, edibleClock, fruitClock, startClock, deathClock;
    Time startTime, deathTime;
    float edibleTime, fruitTime, deltaTime = 0.0;
    // END WINDOW & CLOCKS

    /*** MAZE ***/
    RectangleShape mazeRectangle;
    mazeRectangle.setSize(Vector2f(WinLength, WinHeight));

    Texture backgroundMaze;
    backgroundMaze.loadFromFile(resourcePath() + "/Graphics/maze-bg.png");
    mazeRectangle.setTexture(&backgroundMaze);

    MazeData maze;
    maze.setValidNodeMovements();
    maze.loadPellets(4);  maze.loadPellets(240);
    maze.placePellets(4); maze.placePellets(240); maze.placeNodes();
    // END MAZE

    /*** TEXT ***/
    std::string gameFont = "/Graphics/font.ttf";
    addText scoreText(gameFont), scoreValue(gameFont), ready(gameFont), gameover(gameFont);
    addText youwin(gameFont), playAgain(gameFont), continueLevel(gameFont);

    scoreText.setPosition(Vector2f(125, 40));
    scoreValue.setPosition(Vector2f(250, 40));
    ready.setPosition(Vector2f(450, 550));
    gameover.setPosition(Vector2f(370, 540));
    youwin.setPosition(Vector2f(405, 540));
    playAgain.setPosition(Vector2f(475, 40));
    continueLevel.setPosition(Vector2f(326, 730));

    scoreText.setFillColor(Color(208, 62, 25));            // RED
    scoreValue.setFillColor(Color(255, 255, 255));        // WHITE
    ready.setFillColor(Color(255, 255, 0));                // YELLOW
    gameover.setFillColor(Color(208, 62, 25));            // RED
    youwin.setFillColor(Color(70, 191, 238));            // CYAN
    playAgain.setFillColor(Color(255, 255, 0));            // YELLOW
    continueLevel.setFillColor(Color(255, 255, 255));    // WHITE

    ready.setCharacterSize(40);
    gameover.setCharacterSize(53);
    youwin.setCharacterSize(53);

    scoreText.setString("SCORE");
    ready.setString("READY!");
    gameover.setString("GAME   OVER");
    youwin.setString("YOU WIN!");
    playAgain.setString("PRESS SPACE TO PLAY AGAIN");
    continueLevel.setString("PRESS SPACE TO CONTINUE");

    std::ostringstream ss;
    int score = 0;
    ss << score;
    scoreValue.setString(ss.str());
    // END TEXT

    /*** PLAYERS ***/
    Texture pacmanTexture, blinkyTexture, inkyTexture, pinkyTexture, clydeTexture;
    pacmanTexture.loadFromFile(resourcePath() + "/Graphics/char-pacman.png");
    blinkyTexture.loadFromFile(resourcePath() + "/Graphics/char-blinky.png");
    inkyTexture.loadFromFile(resourcePath() + "/Graphics/char-inky.png");
    pinkyTexture.loadFromFile(resourcePath() + "/Graphics/char-pinky.png");
    clydeTexture.loadFromFile(resourcePath() + "/Graphics/char-clyde.png");

    float pacmanSpeed = 200, ghostSpeed = 120;
    Vector2f pacmanPos(512, 746), blinkyPos(512, 405), pinkyPos(512, 501), inkyPos(463, 501), clydePos(562, 501);
    Player pacman(&pacmanTexture, Vector2u(20, 3), 0.015, pacmanSpeed);
    Player blinky(&blinkyTexture, Vector2u(2, 6), 0.15, ghostSpeed);
    Player inky(&inkyTexture, Vector2u(2, 6), 0.15, ghostSpeed);
    Player pinky(&pinkyTexture, Vector2u(2, 6), 0.15, ghostSpeed);
    Player clyde(&clydeTexture, Vector2u(2, 6), 0.15, ghostSpeed);
    
    pacman.setPosition(pacmanPos);
    blinky.setPosition(blinkyPos);
    inky.setPosition(pinkyPos);
    pinky.setPosition(pinkyPos);
    clyde.setPosition(clydePos);

    resetPlayersOnDeath(pacman, blinky, inky, pinky, clyde);        // SET PLAYER STARTING POSITIONS
    // END PLAYERS

    /*** SOUNDS ***/
    Audio chomp1("Audio/chomp1.wav"), chomp2("Audio/chomp2.wav"), scatter("Audio/scatter.wav");
    Audio theme("Audio/theme.wav"), siren("Audio/siren.wav"), eatfruit("Audio/eatfruit.wav");
    Audio life("Audio/life.wav"), death("Audio/death.wav"), eatghost("Audio/eatghost.wav");


    scatter.setLoop(true);
    siren.setLoop(true);
    theme.play();
    // END SOUNDS

    /*** FRUIT ***/
    Texture fruitTexture;            // INTERACTIVE FRUIT
    fruitTexture.loadFromFile(resourcePath() + "/Graphics/fruit-all.png");
    Player fruit(&fruitTexture, Vector2u(1, 6), 0.15, (spriteSize * 2.75));
    fruit.setPosition(Vector2f(512, 576));

    RectangleShape fruitSprite[6];    // FRUIT LIST
    for (int i = 0; i < 6; i++) {
        fruitSprite[i].setSize(Vector2f(spriteSize, spriteSize));
        fruitSprite[i].setPosition(Vector2f(832 - ((spriteSize * 1.25) * i), 970));
    }

    Texture cherry, strawberry, orange, apple, watermelon, key;
    cherry.loadFromFile(resourcePath() + "/Graphics/fruit-cherry.png");
    strawberry.loadFromFile(resourcePath() + "/Graphics/fruit-strawberry.png");
    orange.loadFromFile(resourcePath() + "/Graphics/fruit-orange.png");
    apple.loadFromFile(resourcePath() + "/Graphics/fruit-apple.png");
    watermelon.loadFromFile(resourcePath() + "/Graphics/fruit-watermelon.png");
    key.loadFromFile(resourcePath() + "/Graphics/fruit-key.png");

    fruitSprite[0].setTexture(&cherry);
    fruitSprite[1].setTexture(&strawberry);
    fruitSprite[2].setTexture(&orange);
    fruitSprite[3].setTexture(&apple);
    fruitSprite[4].setTexture(&watermelon);
    fruitSprite[5].setTexture(&key);
    // END FRUIT

    /*** VARIABLES ***/
    int gamestate = STARTING, level = 1;
    int ghostCount = 0, pelletCount = 0, lifeCount = 4, lifeScore = 10000;
    float looppitch = 1.00, edibleLimit = 10.0;

    bool isEdible, isEaten, edibleSound, startInit, sirenInit, showFruit;
    isEdible = isEaten = edibleSound = startInit = sirenInit = showFruit = false;

    RectangleShape lives[7];
    Texture livesTexture;
    livesTexture.loadFromFile(resourcePath() + "/Graphics/maze-lives.png");
    for (int i = 0; i < 7; i++) {
        lives[i].setSize(Vector2f(spriteSize, spriteSize));
        lives[i].setTexture(&livesTexture);
        lives[i].setPosition(Vector2f(150 + ((spriteSize * 1.25) * i), 970));
    }
    // END VARIABLES

    /*** PAUSE STATE ***/
    Texture pauseBG, selectArrow;
    pauseBG.loadFromFile(resourcePath() + "/Graphics/menu-bg.png");
    selectArrow.loadFromFile(resourcePath() + "/Graphics/menu-select.png");

    RectangleShape pauseOpacity, pauseMenu, select;
    Vector2f selectPos;
    selectPos.x = 380;
    selectPos.y = 365;

    pauseOpacity.setSize(Vector2f(WinX, WinY));
    pauseMenu.setSize(Vector2f(600, 750));
    select.setSize(Vector2f(32, 32));

    pauseOpacity.setPosition(0, 0);
    pauseMenu.setPosition(Vector2f(512, 512));
    pauseMenu.setOrigin(pauseMenu.getSize().x / 2.0, pauseMenu.getSize().y / 2.0);
    select.setPosition(selectPos);

    pauseOpacity.setFillColor(Color(0, 0, 0, 100));
    pauseMenu.setTexture(&pauseBG);
    select.setTexture(&selectArrow);

    addText paused(gameFont), continueText(gameFont), restartText(gameFont);
    addText quitText(gameFont), controlText(gameFont), WASDText(gameFont), ArrowText(gameFont);

    paused.setFillColor(Color(70, 191, 238));            // CYAN
    continueText.setFillColor(Color(255, 255, 255));    // WHITE
    restartText.setFillColor(Color(255, 255, 255));        // WHITE
    quitText.setFillColor(Color(255, 255, 255));        // WHITE
    controlText.setFillColor(Color(255, 255, 255));        // WHITE
    WASDText.setFillColor(Color(255, 255, 255));        // WHITE
    ArrowText.setFillColor(Color(255, 255, 255));        // WHITE

    paused.setCharacterSize(50);
    continueText.setCharacterSize(50);
    restartText.setCharacterSize(50);
    quitText.setCharacterSize(50);
    controlText.setCharacterSize(50);
    WASDText.setCharacterSize(45);
    ArrowText.setCharacterSize(45);

    paused.setPosition(Vector2f(435, 250));
    continueText.setPosition(Vector2f(435, 350));
    restartText.setPosition(Vector2f(435, 400));
    quitText.setPosition(Vector2f(435, 450));
    controlText.setPosition(Vector2f(435, 550));
    WASDText.setPosition(Vector2f(435, 600));
    ArrowText.setPosition(Vector2f(435, 600));

    paused.setString("PAUSED");
    continueText.setString("CONTINUE");
    restartText.setString("RESTART");
    quitText.setString("QUIT");
    controlText.setString("CONTROLS");
    WASDText.setString("WASD KEYS >");
    ArrowText.setString("< ARROW KEYS");
    // END PAUSE STATE

    /******************** MAIN GAME LOOP ********************/
    while (window.isOpen()) {
        deltaTime = clock.restart().asSeconds();
        Event checkEvent;

        while (window.pollEvent(checkEvent)) {
            // WINDOW INTERACTION
            if (checkEvent.type == Event::Closed) {        // CLOSE WINDOW
                window.close();
            }
            else if (checkEvent.type == Event::Resized) {  // RESIZE WINDOW
                ResizeView(window, view);
                gamestate = PAUSED;
                soundSwitcher(isEdible, gamestate, siren, scatter);
            }
            else if (checkEvent.type == Event::LostFocus) {  // INACTIVE WINDOW
                ResizeView(window, view);
                gamestate = PAUSED;
                soundSwitcher(isEdible, gamestate, siren, scatter);
            }
            
            if (checkEvent.type == Event::KeyPressed) { // NEW GAME
                if (checkEvent.key.code == Keyboard::N && checkEvent.key.control) {
                    resetOnGameOver(pacman, blinky, inky, pinky, clyde, maze, edibleTime);
                    resetStats(lifeCount, pelletCount, score, lifeScore, level, looppitch, fruit, ss, scoreValue, startClock, deltaTime);
                    soundSwitcher(isEdible, gamestate, siren, scatter);
                    
                    theme.play();
                    eatfruit.play();
                    isEdible = false;
                    startInit = false;
                    gamestate = STARTING;
                }
            }
            

            // GAME INTERACTION
            if (gamestate == PLAYING) { // PAUSE WITH SPACEBAR
                if (checkEvent.type == Event::KeyPressed && checkEvent.key.code == Keyboard::Space) {
                    //std::cout << "GAME PAUSED" << std::endl;
                    gamestate = PAUSED;
                    soundSwitcher(isEdible, gamestate, siren, scatter);
                }
            }
            else if (gamestate == PAUSED) { // PAUSE MENU
                if (checkEvent.type == Event::KeyPressed) { // KEY PRESS ACTIONS
                    // CURSOR MOVEMENT
                    if (checkEvent.key.code == Keyboard::Down) { // SELECT DOWN
                        if (selectPos.y + 50 == 515) { // SKIPS BLANK SPACE
                            selectPos.y = 565;
                        }
                        else if (selectPos.y + 50 <= 615) { // MOVES CURSOR
                            selectPos.y += 50;
                            select.setPosition(selectPos);
                        }
                    }
                    else if (checkEvent.key.code == Keyboard::Up) { // SELECT UP
                        if (selectPos.y - 50 == 565) { // SKIPS BLANK SPACE
                            selectPos.y = 515;
                        }
                        if (selectPos.y - 50 >= 365) {    // MOVES CURSOR
                            selectPos.y -= 50;
                            select.setPosition(selectPos);
                        }
                    }
                    else if (checkEvent.key.code == Keyboard::Right) {   // SELECT RIGHT
                        if (selectPos.y == 615) {
                            pacman.WASDkeys = false;
                        }
                    }
                    else if (checkEvent.key.code == Keyboard::Left) {   // SELECT LEFT
                        if (selectPos.y == 615) {
                            pacman.WASDkeys = true;
                        }
                    }
                }
                // PERFORM SELECTED ACTION
                if (selectPos.y == 465 && checkEvent.key.code == Keyboard::Return) {       // SELECT QUIT (MENU)
                    window.close();
                }
                else if (selectPos.y == 415 && checkEvent.key.code == Keyboard::Return) {   // SELECT RESTART (MENU)
                    resetOnGameOver(pacman, blinky, inky, pinky, clyde, maze, edibleTime);
                    resetStats(lifeCount, pelletCount, score, lifeScore, level, looppitch, fruit, ss, scoreValue, startClock, deltaTime);

                    theme.play();
                    eatfruit.play();
                    isEdible = false;
                    startInit = false;
                    gamestate = STARTING;
                    //std::cout << "GAME RESTARTED" << std::endl;
                }
                else if ((selectPos.y == 365 && checkEvent.key.code == Keyboard::Return) || (checkEvent.type == Event::KeyPressed && checkEvent.key.code == Keyboard::Space)) {   // SELECT CONTINUE
                    gamestate = PLAYING;
                    eatfruit.play();
                    soundSwitcher(isEdible, gamestate, siren, scatter);
                    //std::cout << "GAME UNPAUSED" << std::endl;
                }
            }
            else if (gamestate == WINNER || gamestate == LOSER) {   // PRESS SPACE TO RESTART
                if (checkEvent.type == Event::KeyPressed && checkEvent.key.code == Keyboard::Space) {
                    resetOnGameOver(pacman, blinky, inky, pinky, clyde, maze, edibleTime);

                    if (gamestate == LOSER) {
                        resetStats(lifeCount, pelletCount, score, lifeScore, level, looppitch, fruit, ss, scoreValue, startClock, deltaTime);
                        theme.play();
                    }

                    eatfruit.play();
                    isEdible = false;
                    startInit = false;
                    gamestate = STARTING;
                }
            }
        }    // END OF WINDOW EVENTS POLLING

        /*** CHARACTER ANIMATIONS ***/
        pacman.update(deltaTime, gamestate);
        blinky.update(deltaTime, gamestate);
        inky.update(deltaTime, gamestate);
        pinky.update(deltaTime, gamestate);
        clyde.update(deltaTime, gamestate);
        // END CHARACTER ANIMATIONS

        if (gamestate == PLAYING || gamestate == STARTING) {
            pacman.nextDirection();        // ALLOW DIRECTION QUEUE WHEN NOT PAUSED
            blinky.blinkyAI(deltaTime, pacman);
            inky.inkyAI(deltaTime, pacman);
            pinky.pinkyAI(deltaTime, pacman);
            clyde.clydeAI(deltaTime, pacman);
        }

        if (gamestate == STARTING) {
            if (!startInit) {
                startClock.restart().asSeconds();
                startInit = true;
//                std::cout << "LEVEL " << level << "... ";
            }

            startTime = startClock.getElapsedTime();
            if (deathTime.asSeconds() > 0.0 && deathTime.asSeconds() < 4.2) {
                pacman.playerstate = REVIVED;
            }
            if (startTime.asSeconds() >= 4.2) {
                gamestate = PLAYING;
                pacman.playerstate = ALIVE;
                pacman.setFrame(0);
                pacman.setSwitchTime(0.015);
                soundSwitcher(isEdible, gamestate, siren, scatter);
                showFruit = false;
//                std::cout << "GO!" << std::endl;
            }
        }
        else if (gamestate == PLAYING) {       // MAIN GAME LOOP
            if (pelletCount >= 244) {
                gamestate = WINNER;
                setDifficulty(blinky, inky, pinky, clyde, edibleLimit);
                soundSwitcher(isEdible, gamestate, siren, scatter);
                levelUp(pelletCount, level, looppitch, siren, fruit, isEaten);
            }
            /*** CHARACTER MOVEMENT ***/
            pacman.setDirectionOpposite();        // OPPOSITE DIRECTION CHANGE
            for (int i = 0; i < 65; i++) {       // CHANGE DIRECTION ON NODE
                if ((Vector2i)maze.node[i].getPosition() == (Vector2i)blinky.getPosition()) {
                    blinky.setDirectionAtNode(maze.node[i]);
                }
                if ((Vector2i)maze.node[i].getPosition() == (Vector2i)inky.getPosition()) {
                    inky.setDirectionAtNode(maze.node[i]);
                }
                if ((Vector2i)maze.node[i].getPosition() == (Vector2i)pinky.getPosition()) {
                    pinky.setDirectionAtNode(maze.node[i]);
                }
                if ((Vector2i)maze.node[i].getPosition() == (Vector2i)clyde.getPosition()) {
                    clyde.setDirectionAtNode(maze.node[i]);
                }
                if ((Vector2i)maze.node[i].getPosition() == (Vector2i)pacman.getPosition()) {
                    pacman.setDirectionAtNode(maze.node[i]);
                }
            }
            for (int i = 0; i < 7; i++) {       // CHANGE DIRECTION ON NODE (GHOST START POSITIONS)
                if ((Vector2i)maze.ghostNode[i].getPosition() == (Vector2i)blinky.getPosition()) {
                    blinky.setDirectionAtNode(maze.ghostNode[i]);
                }
                if ((Vector2i)maze.ghostNode[i].getPosition() == (Vector2i)inky.getPosition()) {
                    inky.setDirectionAtNode(maze.ghostNode[i]);
                }
                if ((Vector2i)maze.ghostNode[i].getPosition() == (Vector2i)pinky.getPosition()) {
                    pinky.setDirectionAtNode(maze.ghostNode[i]);
                }
                if ((Vector2i)maze.ghostNode[i].getPosition() == (Vector2i)clyde.getPosition()) {
                    clyde.setDirectionAtNode(maze.ghostNode[i]);
                }
            }
            // MOVE AFTER TOUCHING NODE
            pacman.movePlayer(deltaTime);
            blinky.moveGhost(deltaTime);
            inky.moveGhost(deltaTime);
            pinky.moveGhost(deltaTime);
            clyde.moveGhost(deltaTime);
            // END CHARACTER MOVEMENT

            /*** COLLISIONS ***/
            if (isEdible) {
                edibleTime = edibleClock.getElapsedTime().asSeconds();

                if (edibleTime >= (edibleLimit / 1.5) && edibleTime < edibleLimit) {
                    blinky.playerstate = BLINK;
                    inky.playerstate = BLINK;
                    pinky.playerstate = BLINK;
                    clyde.playerstate = BLINK;
                }
                else {
                    blinky.playerstate = SCATTER;
                    inky.playerstate = SCATTER;
                    pinky.playerstate = SCATTER;
                    clyde.playerstate = SCATTER;
                }

                // EDIBLE GHOST SCORES
                ghostMultiplier(pacman, blinky, blinkyPos, eatghost, ghostCount, score);
                ghostMultiplier(pacman, inky, inkyPos, eatghost, ghostCount, score);
                ghostMultiplier(pacman, pinky, pinkyPos, eatghost, ghostCount, score);
                ghostMultiplier(pacman, clyde, clydePos, eatghost, ghostCount, score);
                updatePoints(ss, score, scoreValue);

                if (edibleTime >= edibleLimit) {
                    isEdible = false;
                    soundSwitcher(isEdible, gamestate, siren, scatter);
                    ghostCount = 0;
                }
            }
            else {
                if (checkGhost(pacman, blinky) || checkGhost(pacman, inky) || checkGhost(pacman, pinky) || checkGhost(pacman, clyde)) {
                    gamestate = DYING;
                    death.play();
                    soundSwitcher(isEdible, gamestate, siren, scatter);
                    deathByGhost(pacman);
                    deathClock.restart().asSeconds();
                }
            }

            /*** PELLET LOGIC ***/
            for (int i = 0; i < 240; i++) {   // SMALL PELLETS
                if (pacman.getCollider().checkCollision(maze.pellet[i].getCollider(), 0.0)) {
                    score = score + 10;
                    updatePoints(ss, score, scoreValue);
                    oneUp(score, lifeScore, lifeCount, life);

                    if (pelletCount % 2 == 0) {
                        chomp1.play();
                    }
                    else {
                        chomp2.play();
                    }

                    pelletCount++;
                    if (pelletCount % 50 == 0 && pelletCount != 0) {
                        looppitch += 0.025;        // INCREASE PITCH EVERY 50 PELLETS
                        siren.setPitch(looppitch);
                    }
                    maze.pellet[i].setPosition(Vector2f(0, WinY * 10));
                }
            }
            for (int i = 0; i < 4; i++) {        // POWER PELLETS
                if (pacman.getCollider().checkCollision(maze.powerPellet[i].getCollider(), 0.0)) {
                    score = score + 50;
                    updatePoints(ss, score, scoreValue);
                    oneUp(score, lifeScore, lifeCount, life);

                    if (pelletCount % 2 == 0) {
                        chomp1.play();
                    }
                    else {
                        chomp2.play();
                    }

                    pelletCount++;
                    isEdible = true;
                    edibleClock.restart();

                    soundSwitcher(isEdible, gamestate, siren, scatter);
                    if (pelletCount % 50 == 0 && pelletCount != 0) {
                        looppitch += 0.025;        // INCREASE PITCH EVERY 50 PELLETS
                        siren.setPitch(looppitch);
                    }

                    maze.powerPellet[i].setPosition(Vector2f(0, WinY * 10));
                }
            }    // END PELLET LOGIC

            /*** FRUIT LOGIC ***/
            startTime = startClock.getElapsedTime();
            if (startTime.asSeconds() > 35.0 && startTime.asSeconds() < 35.1) {
                showFruit = true;
                fruitClock.restart().asSeconds();
            }
            if (showFruit) {
                fruitTime = fruitClock.getElapsedTime().asSeconds();
                if (fruitTime >= 0.0 && fruitTime <= 10.0) {
                    if (pacman.getCollider().checkCollision(fruit.getCollider(), 0.0)) {
                        if (level == 1)
                            score = score + 100;
                        else if (level == 2)
                            score = score + 300;
                        else if (level == 3)
                            score = score + 500;
                        else if (level == 4)
                            score = score + 700;
                        else if (level == 5)
                            score = score + 1000;
                        else if (level >= 6)
                            score = score + 2000;

                        fruit.setPosition(pinkyPos);
                        updatePoints(ss, score, scoreValue);
                        eatfruit.play();
                        isEaten = true;
                    }
                }
                if (fruitTime >= 9.99 && fruitTime <= 10.0)
                    showFruit = false;
            }
            // END FRUIT LOGIC

            // Teleports players to opposite x-coordinate when off screen
            maze.teleportPlayer(pacman);
            maze.teleportPlayer(blinky);
            maze.teleportPlayer(pinky);
            maze.teleportPlayer(inky);
            maze.teleportPlayer(clyde);
            
        }    // MAIN GAME LOOP END
        else if (gamestate == DYING) {
            if (startInit) {
                startClock.restart().asSeconds();
            }
            deathTime = deathClock.getElapsedTime();
            
            if (deathTime.asSeconds() >= 1.475) {
                lifeCount--;    // DEDUCT LIFE AFTER DEATH ANIMATION
                resetPlayersOnDeath(pacman, blinky, inky, pinky, clyde);

                if (lifeCount < 0) {
                    gamestate = LOSER;
                }
                else {
                gamestate = STARTING;
                }
            }
        }
        else if (gamestate == WINNER) {
            pacman.setFrame(0);
        }

        window.clear();
        window.setView(view);

        /*** DRAWING ***/
        // ALWAYS DRAWING
        window.draw(mazeRectangle);        // MAZE BACKGROUND
        for (int i = 0; i < 240; i++) {   // SMALL PELLETS
            maze.pellet[i].draw(window);
        }

        for (int i = 0; i < 4; i++) {       // POWER PELLETS
            maze.powerPellet[i].draw(window);
        }

        window.draw(scoreValue);
        window.draw(scoreText);

        for (int i = 0; i < lifeCount; i++) {
            window.draw(lives[i]);
        }

        if (level < 7) {
            for (int ii = 0; ii < level; ii++) {
                window.draw(fruitSprite[ii]);
            }
        }
        else {
            for (int ii = 0; ii < 6; ii++) {
                window.draw(fruitSprite[ii]);
            }
        }

        // CONDITIONAL DRAWING
        if (gamestate == PLAYING) {
            fruit.update(deltaTime, gamestate);
            if (!isEaten) {
                if (showFruit) {
                fruit.draw(window);
                }
            }
        }

        if (gamestate != LOSER) {
            pacman.draw(window);
        }
        if (gamestate != DYING) {
            blinky.draw(window);
            inky.draw(window);
            pinky.draw(window);
            clyde.draw(window);
        }

        if (gamestate == LOSER) {                   // GAME OVER (LOSING)
            window.draw(gameover);
            window.draw(playAgain);
        }
        else if (gamestate == WINNER) {           // GAME OVER (WINNING)
            window.draw(youwin);
            window.draw(continueLevel);
        }
        else if (gamestate == STARTING) {
            window.draw(ready);
        }
        else if (gamestate == PAUSED) {   // PAUSE MENU
            window.draw(pauseOpacity);
            window.draw(pauseMenu);
            window.draw(paused);
            window.draw(continueText);
            window.draw(restartText);
            window.draw(quitText);
            window.draw(controlText);
            window.draw(select);

            if (pacman.WASDkeys) {
                window.draw(WASDText);
            }
            else {
                window.draw(ArrowText);
            }
        }
        // END DRAWING

        window.display();
    }
    return 0;
}

