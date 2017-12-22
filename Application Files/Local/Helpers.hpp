//
//  Helpers.hpp
//  PAC-MAN 2017
//
//  Created by Carlos Estrada on 11/16/17.
//  Copyright © 2017 Carlos Estrada. All rights reserved.
//

#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include <string>
using namespace sf;

#define WinX 1024
#define WinY 1024
#define spriteSize 42
#define pelletSize 8
#define powerPelletSize 26

#ifdef __APPLE__
#include "ResourcePath.hpp"
#endif

#ifndef __APPLE__
std::string resourcePath();
#endif

static const float WinLength = WinX, WinHeight = WinY;

void ResizeView(const RenderWindow &window, View& view);

class Audio : public Sound {
    SoundBuffer buffer;
public:
    Audio(std::string filename);
};
