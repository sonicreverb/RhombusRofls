#include "../Headers/ScreenResolution.h"

sf::VideoMode ScreenResolution::desktopMode = sf::VideoMode::getDesktopMode();

sf::VideoMode ScreenResolution::getDesktopMode() {
    return desktopMode;
}

int ScreenResolution::getWindowWidth() {
    return desktopMode.width;
}

int ScreenResolution::getWindowHeight() {
    return desktopMode.height;
}