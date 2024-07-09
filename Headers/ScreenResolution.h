#pragma once
#include <SFML/Graphics.hpp>


class ScreenResolution {
public:
    static sf::VideoMode getDesktopMode();
    static int getWindowWidth();
    static int getWindowHeight();

private:
    static sf::VideoMode desktopMode;
};