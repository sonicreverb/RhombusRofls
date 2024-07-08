#pragma once
#include "Model.h"
#include <SFML/Graphics.hpp>

// todo dynamic resolution
#define WINDOW_WIDTH 1920
#define WINDOW_HEIGHT 1080

class View {
private:
	sf::RenderWindow& window;
	Model& model;
public:
	View(Model& _model, sf::RenderWindow& _window): model(_model), window(_window) {}

	void render();

	sf::RenderWindow& accessWindow() { return this->window; }
};