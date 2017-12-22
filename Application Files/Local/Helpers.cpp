//
//  Helpers.cpp
//  PAC-MAN 2017
//
//  Created by Carlos Estrada on 11/16/17.
//  Copyright © 2017 Carlos Estrada. All rights reserved.
//

#include "Helpers.hpp"

#ifndef __APPLE__
std::string resourcePath() {
    return "Application Files/Resources/";
}
#endif

void ResizeView(const RenderWindow &window, View& view) { // ASPECT RATIO FUNCTION
    float aspectRatio = float(window.getSize().x / float(window.getSize().y));
    view.setSize(WinLength * aspectRatio, WinLength);
}

Audio::Audio(std::string filename) {
    buffer.loadFromFile(resourcePath() + "Audio/" + filename);
    setBuffer(buffer);
}
