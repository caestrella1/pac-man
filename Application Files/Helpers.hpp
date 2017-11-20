//
//  Helpers.hpp
//  PAC-MAN 2017
//
//  Created by Carlos Estrada on 11/16/17.
//  Copyright © 2017 Carlos Estrada. All rights reserved.
//

#pragma once
#include "ResourcePath.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>
#include <string>
using namespace sf;

#define WinX 1024
#define WinY 1024
#define spriteSize 42
#define pelletSize 8
#define powerPelletSize 26

#define NONE -1
#define LEFT 0
#define RIGHT 1
#define UP 2
#define DOWN 3

#define ALIVE 0
#define DEAD 1
#define REVIVED 2

#define FACELEFT 0
#define FACERIGHT 1
#define FACEUP 2
#define FACEDOWN 3
#define SCATTER 4
#define BLINK 5

static const float WinLength = WinX, WinHeight = WinY;

void ResizeView(const RenderWindow &window, View& view); // ASPECT RATIO FUNCTION

class Audio : public Sound {
    SoundBuffer buffer;
public:
    Audio(std::string path);
};

class addText : public Text {
    Font gameFont;
public:
    addText(std::string path);
};
