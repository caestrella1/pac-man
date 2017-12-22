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
    RenderWindow window(VideoMode(WinX, WinY), "PAC-MAN 2017", Style::Default);
    View view(Vector2f(WinX / 2, WinY / 2), Vector2f(WinX, WinY));
    window.setKeyRepeatEnabled(false);

    Clock deltaClock, edibleClock, fruitClock, startClock;
    Time deltaTime, startTime, deathTime;
    float edibleTime = 0.0, fruitTime = 0.0;
    
    /*** VARIABLES ***/
    MazeData maze;
    int ghostCount = 0, pelletCount = 0, lifeCount = 4, lifeScore = 10000;
    int gamestate = STARTING, level = 1, score = 0, hiscore = getHighScore();
    bool atLeastOneEdible = false, showFruit = false;
    float looppitch = 1.00, edibleLimit = 10.0;
    std::ostringstream ss;

    /*** TEXT ***/
    Font font; font.loadFromFile(resourcePath() + "Graphics/font.ttf");
    Text playerScore("", font), playerHiScore("", font), ready("READY!", font, 40),
    gameover("GAME   OVER", font, 53), hiScoreText("HI SCORE", font);

    hiScoreText.setPosition(Vector2f(512, 40));
    playerScore.setPosition(Vector2f(150, 40));
    playerHiScore.setPosition(Vector2f(675, 40));
    ready.setPosition(Vector2f(450, 550));
    gameover.setPosition(Vector2f(370, 540));

    hiScoreText.setFillColor(Color(208, 62, 25));            // RED
    playerHiScore.setFillColor(Color(255, 255, 255));        // WHITE
    playerScore.setFillColor(Color(255, 255, 255));          // WHITE
    ready.setFillColor(Color(255, 255, 0));                  // YELLOW
    gameover.setFillColor(Color(208, 62, 25));               // RED

    updatePoints(ss, score, playerScore);
    updatePoints(ss, hiscore, playerHiScore);
    // END TEXT

    /*** PLAYERS ***/
    float pacmanSpeed = 50, ghostSpeed = 35;
    Player pacman("char-pacman.png", 16, 2, 18); pacman.setFrameTime(seconds(0.025)); pacman.pause();
    Ghost blinky("char-blinky.png", 16, 6, 2); blinky.setFrameTime(seconds(0.25));
    Ghost inky("char-inky.png", 16, 6, 2); inky.setFrameTime(seconds(0.25));
    Ghost pinky("char-pinky.png", 16, 6, 2); pinky.setFrameTime(seconds(0.25));
    Ghost clyde("char-clyde.png", 16, 6, 2); clyde.setFrameTime(seconds(0.25));
    
    float scale = 2.5;
    pacman.setScale(scale, scale);
    blinky.setScale(scale, scale);
    inky.setScale(scale, scale);
    pinky.setScale(scale, scale);
    clyde.setScale(scale, scale);
    
    pacman.setPlayerSpeed(pacmanSpeed);
    blinky.setPlayerSpeed(ghostSpeed);
    inky.setPlayerSpeed(ghostSpeed);
    pinky.setPlayerSpeed(ghostSpeed);
    clyde.setPlayerSpeed(ghostSpeed);

    resetGame(pacman, blinky, inky, pinky, clyde, maze, gamestate);
    // END PLAYERS

    /*** SOUNDS ***/
    bool isMuted = false;
    Audio chomp1("chomp1.wav"), chomp2("chomp2.wav"), scatter("scatter.wav"), theme("theme.wav");
    Audio siren("siren.wav"), eatfruit("eatfruit.wav"), life("life.wav"), death("death.wav"), eatghost("eatghost.wav");
    scatter.setLoop(true); siren.setLoop(true); theme.play();
    // END SOUNDS

    /*** FRUIT ***/
    Player fruit("fruit-all.png", 16, 6, 1);
    fruit.setPosition(Vector2f(512, 576));
    fruit.setScale(scale, scale);

    RectangleShape fruitSprite[6];    // FRUIT LIST
    for (int i = 0; i < 6; i++) {
        fruitSprite[i].setSize(Vector2f(spriteSize, spriteSize));
        fruitSprite[i].setPosition(Vector2f(832 - ((spriteSize * 1.25) * i), 970));
    }

    Texture cherry, strawberry, orange, apple, watermelon, key;
    cherry.loadFromFile(resourcePath() + "Graphics/fruit-cherry.png");
    strawberry.loadFromFile(resourcePath() + "Graphics/fruit-strawberry.png");
    orange.loadFromFile(resourcePath() + "Graphics/fruit-orange.png");
    apple.loadFromFile(resourcePath() + "Graphics/fruit-apple.png");
    watermelon.loadFromFile(resourcePath() + "Graphics/fruit-watermelon.png");
    key.loadFromFile(resourcePath() + "Graphics/fruit-key.png");

    fruitSprite[0].setTexture(&cherry);
    fruitSprite[1].setTexture(&strawberry);
    fruitSprite[2].setTexture(&orange);
    fruitSprite[3].setTexture(&apple);
    fruitSprite[4].setTexture(&watermelon);
    fruitSprite[5].setTexture(&key);
    // END FRUIT

    RectangleShape lives[7];
    Texture livesTexture;
    livesTexture.loadFromFile(resourcePath() + "Graphics/maze-lives.png");
    for (int i = 0; i < 7; i++) {
        lives[i].setSize(Vector2f(spriteSize, spriteSize));
        lives[i].setTexture(&livesTexture);
        lives[i].setPosition(Vector2f(150 + ((spriteSize * 1.25) * i), 970));
    }
    
    Player sound("sound.png", 80, 2, 1);
    sound.setPosition(Vector2f(860, 55));
    sound.setScale(Vector2f(0.4, 0.4));

    /*** PAUSE STATE ***/
    Texture pauseBG, selectArrow;
    pauseBG.loadFromFile(resourcePath() + "Graphics/menu-bg.png");
    selectArrow.loadFromFile(resourcePath() + "Graphics/menu-select.png");

    RectangleShape pauseOpacity, pauseMenu, select;
    Vector2f selectPos(380, 365);

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
    
    size_t pauseSize = 50;
    Text paused("PAUSED", font, pauseSize), continueText("CONTINUE", font, pauseSize),
    restartText("RESTART", font, pauseSize), quitText("QUIT", font, pauseSize),
    controlText("CONTROLS", font, pauseSize), WASDText("WASD KEYS >", font, pauseSize-5);

    paused.setFillColor(Color(70, 191, 238));           // CYAN
    continueText.setFillColor(Color(255, 255, 255));    // WHITE
    restartText.setFillColor(Color(255, 255, 255));     // WHITE
    quitText.setFillColor(Color(255, 255, 255));        // WHITE
    controlText.setFillColor(Color(255, 255, 255));     // WHITE
    WASDText.setFillColor(Color(255, 255, 255));        // WHITE

    paused.setPosition(Vector2f(435, 250));
    continueText.setPosition(Vector2f(435, 350));
    restartText.setPosition(Vector2f(435, 400));
    quitText.setPosition(Vector2f(435, 450));
    controlText.setPosition(Vector2f(435, 550));
    WASDText.setPosition(Vector2f(435, 600));
    // END PAUSE STATE

    /******************** MAIN GAME LOOP ********************/
    while (window.isOpen()) {
        deltaTime = deltaClock.restart();
        Event checkEvent;

        while (window.pollEvent(checkEvent)) {
            // WINDOW INTERACTION
            if (checkEvent.type == Event::Closed) {        // CLOSE WINDOW
                window.close();
            }
            else if (checkEvent.type == Event::Resized) {  // RESIZE WINDOW
                ResizeView(window, view);
                if (gamestate == PLAYING) {
                    gamestate = PAUSED;
                    soundSwitcher(atLeastOneEdible, gamestate, siren, scatter);
                }
            }
            else if (checkEvent.type == Event::LostFocus) {  // INACTIVE WINDOW
                if (gamestate == PLAYING) {
                    gamestate = PAUSED;
                    soundSwitcher(atLeastOneEdible, gamestate, siren, scatter);
                }
            }
            else if (checkEvent.type == Event::KeyPressed && checkEvent.key.code == Keyboard::M) {
                toggleMute(isMuted, sound, chomp1, chomp2, scatter, theme, siren, eatfruit, life, death, eatghost);
            }
            

            // GAME INTERACTION
            if (gamestate == PLAYING) { // PAUSE WITH SPACEBAR
                if (checkEvent.type == Event::KeyPressed && checkEvent.key.code == Keyboard::Space) {
                    gamestate = PAUSED;
                    soundSwitcher(atLeastOneEdible, gamestate, siren, scatter);
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
                            WASDText.setString("< ARROW KEYS");
                        }
                    }
                    else if (checkEvent.key.code == Keyboard::Left) {   // SELECT LEFT
                        if (selectPos.y == 615) {
                            pacman.WASDkeys = true;
                            WASDText.setString("WASD KEYS >");
                        }
                    }
                }
                // PERFORM SELECTED ACTION
                if (selectPos.y == 465 && checkEvent.key.code == Keyboard::Return) {       // SELECT QUIT (MENU)
                    window.close();
                }
                else if (selectPos.y == 415 && checkEvent.key.code == Keyboard::Return) {   // SELECT RESTART (MENU)
                    resetGame(pacman, blinky, inky, pinky, clyde, maze, gamestate);
                    resetStats(lifeCount, pelletCount, score, lifeScore, level, looppitch, fruit, ss, playerScore, startClock);

                    theme.play();
                    eatfruit.play();
                    gamestate = STARTING;
                }
                else if (selectPos.y == 365 && checkEvent.key.code == Keyboard::Return) {   // SELECT CONTINUE
                    gamestate = PLAYING;
                    eatfruit.play();
                    soundSwitcher(atLeastOneEdible, gamestate, siren, scatter);
                }
            }
            else if (gamestate == LOSER) {   // PRESS SPACE TO RESTART
                if (checkEvent.type == Event::KeyPressed && checkEvent.key.code == Keyboard::Space) {
                    gamestate = STARTING;
                    resetGame(pacman, blinky, inky, pinky, clyde, maze, gamestate);
                    resetStats(lifeCount, pelletCount, score, lifeScore, level, looppitch, fruit, ss, playerScore, startClock);
                    eatfruit.play();
                    theme.play();
                }
            }
        }    // END OF WINDOW EVENTS POLLING

        /*** CHARACTER ANIMATIONS ***/
        pacman.update(deltaTime);
        blinky.update(deltaTime);
        inky.update(deltaTime);
        pinky.update(deltaTime);
        clyde.update(deltaTime);
        // END CHARACTER ANIMATIONS

        if (gamestate == STARTING) {
            startTime = startClock.getElapsedTime();
            pacman.manageState();
            if (startTime.asSeconds() >= 4.2) {
                gamestate = PLAYING;
                pacman.setState(ALIVE);
                pacman.manageState();
                soundSwitcher(atLeastOneEdible, gamestate, siren, scatter);
                showFruit = false;
            }
        }
        else if (gamestate == DYING) {
            float elapsedTime = startClock.getElapsedTime().asSeconds();
            if (elapsedTime >= 1.3) {
                resetGame(pacman, blinky, inky, pinky, clyde, maze, gamestate);
                lifeCount--;    // DEDUCT LIFE AFTER DEATH ANIMATION
                lifeCount < 0 ? gamestate = LOSER : gamestate = STARTING;
                if (gamestate == LOSER && score >= hiscore) {
                    saveHighScore(hiscore);
                    playerHiScore.setFillColor(Color(255, 255, 255));
                }
            }
        }
        else if (gamestate == WINNER) {
            float elapsedTime = startClock.getElapsedTime().asSeconds();
            maze.mazeBG.update(deltaTime);
            if (elapsedTime >= 3.0) {
                setDifficulty(blinky, inky, pinky, clyde, edibleLimit);
                soundSwitcher(atLeastOneEdible, gamestate, siren, scatter);
                levelUp(pelletCount, level, looppitch, siren, fruit);
                resetGame(pacman, blinky, inky, pinky, clyde, maze, gamestate);
                startClock.restart().asSeconds();
                gamestate = STARTING;
            }
        }
        else if (gamestate == PLAYING) {       // MAIN GAME LOOP
            if (pelletCount >= 244) {
                startClock.restart().asSeconds();
                gamestate = WINNER;
            }
            /*** CHARACTER MOVEMENT ***/
            pacman.setDirection();
            for (int i = 0; i < 65; i++) {
                findNode(blinky, maze.node.get()[i]);
                findNode(inky, maze.node.get()[i]);
                findNode(pinky, maze.node.get()[i]);
                findNode(clyde, maze.node.get()[i]);
                findNode(pacman, maze.node.get()[i]);
            }
            for (int i = 0; i < 7; i++) {
                findNode(blinky, maze.ghostNode.get()[i]);
                findNode(inky, maze.ghostNode.get()[i]);
                findNode(pinky, maze.ghostNode.get()[i]);
                findNode(clyde, maze.ghostNode.get()[i]);
            }
            
            blinky.ghostAI(); inky.ghostAI(); pinky.ghostAI(); clyde.ghostAI();
            ghostCollisions(pacman, blinky, eatghost, ghostCount, score, gamestate, death, atLeastOneEdible, startClock);
            ghostCollisions(pacman, inky, eatghost, ghostCount, score, gamestate, death, atLeastOneEdible, startClock);
            ghostCollisions(pacman, pinky, eatghost, ghostCount, score, gamestate, death, atLeastOneEdible, startClock);
            ghostCollisions(pacman, clyde, eatghost, ghostCount, score, gamestate, death, atLeastOneEdible, startClock);
            soundSwitcher(atLeastOneEdible, gamestate, siren, scatter);
            updatePoints(ss, score, playerScore);
            
            if (score > hiscore) {
                hiscore = score;
                playerHiScore.setFillColor(Color(180, 180, 180));
                updatePoints(ss, hiscore, playerHiScore);
            }
            
            atLeastOneEdible = (blinky.isEdible || inky.isEdible || pinky.isEdible || clyde.isEdible);
            if (atLeastOneEdible) {
                edibleTime = edibleClock.getElapsedTime().asSeconds();

                if (edibleTime >= edibleLimit) {
                    atLeastOneEdible = false;
                    blinky.isEdible = inky.isEdible = pinky.isEdible = clyde.isEdible = false;
                    soundSwitcher(atLeastOneEdible, gamestate, siren, scatter);
                    ghostCount = 0;
                }
            }


            /*** PELLET LOGIC ***/
            for (int i = 0; i < 240; i++) {   // SMALL PELLETS
                if (checkCollision(pacman, maze.pellet.get()[i])) {
                    score = score + 10;
                    updatePoints(ss, score, playerScore);
                    oneUp(score, lifeScore, lifeCount, life);

                    pelletCount % 2 == 0 ? chomp1.play() : chomp2.play();

                    pelletCount++;
                    if (pelletCount % 50 == 0 && pelletCount != 0) {
                        looppitch += 0.025;        // INCREASE PITCH EVERY 50 PELLETS
                        siren.setPitch(looppitch);
                    }
                    maze.pellet.get()[i].setPosition(Vector2f(0, WinY * 10));
                }
            }
            for (int i = 0; i < 4; i++) {        // POWER PELLETS
                if (checkCollision(pacman, maze.powerPellet.get()[i])) {
                    score = score + 50;
                    updatePoints(ss, score, playerScore);
                    oneUp(score, lifeScore, lifeCount, life);
                    pelletCount++;
                    
                    blinky.isEdible = inky.isEdible = pinky.isEdible = clyde.isEdible = true;
                    edibleClock.restart();
                    
                    pelletCount % 2 == 0 ? chomp1.play() : chomp2.play();
                    soundSwitcher(atLeastOneEdible, gamestate, siren, scatter);
                    
                    if (pelletCount % 50 == 0 && pelletCount != 0) {
                        looppitch += 0.025;        // INCREASE PITCH EVERY 50 PELLETS
                        siren.setPitch(looppitch);
                    }

                    maze.powerPellet.get()[i].setPosition(Vector2f(0, WinY * 10));
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
                    if (checkCollision(pacman, fruit)) {
                        switch (level) {
                            case 1: score = score + 100;
                                break;
                            case 2: score = score + 300;
                                break;
                            case 3: score = score + 500;
                                break;
                            case 4: score = score + 700;
                                break;
                            case 5: score = score + 1000;
                                break;
                            default: score = score + 2000;
                                break;
                        }

                        updatePoints(ss, score, playerScore);
                        eatfruit.play();
                        showFruit = false;
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
        
        // MOVE AFTER TOUCHING NODE
        pacman.movePlayer(deltaTime, gamestate);
        blinky.moveGhost(deltaTime, gamestate, edibleTime, edibleLimit);
        inky.moveGhost(deltaTime, gamestate, edibleTime, edibleLimit);
        pinky.moveGhost(deltaTime, gamestate, edibleTime, edibleLimit);
        clyde.moveGhost(deltaTime, gamestate, edibleTime, edibleLimit);
        // END CHARACTER MOVEMENT

        window.setView(view);
        window.clear();

        /*** DRAWING ***/
        // ALWAYS DRAWING
        window.draw(maze.mazeBG);
        window.draw(playerScore);
        window.draw(playerHiScore);
        window.draw(hiScoreText);
        window.draw(sound);
        
        for (int i = 0; i < 240; i++) {   // SMALL PELLETS
            if (maze.pellet.get()[i].getPosition().y <= WinY) {
                window.draw(maze.pellet.get()[i]);
            }
        }

        for (int i = 0; i < 4; i++) {       // POWER PELLETS
            if (maze.powerPellet.get()[i].getPosition().y <= WinY) {
                maze.powerPellet.get()[i].update(deltaTime);
                window.draw(maze.powerPellet.get()[i]);
            }
        }

        for (int i = 0; i < lifeCount; i++) {
            window.draw(lives[i]);
        }

        int fruitlimit = level < 7 ? level : 6;
        for (int i = 0; i < fruitlimit; i++) {
            window.draw(fruitSprite[i]);
        }

        // CONDITIONAL DRAWING
        if (gamestate == PLAYING) {
            fruit.update(deltaTime);
            if (showFruit) {
                window.draw(fruit);
            }
        }

        if (gamestate != LOSER) {
            window.draw(pacman);
        }
        if (gamestate != DYING && gamestate != WINNER) {
            window.draw(blinky);
            window.draw(inky);
            window.draw(pinky);
            window.draw(clyde);
        }

        if (gamestate == STARTING) {
            window.draw(ready);
        }
        else if (gamestate == LOSER) {
            window.draw(gameover);
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
            window.draw(WASDText);
        }
        // END DRAWING

        window.display();
    }
    return 0;
}
