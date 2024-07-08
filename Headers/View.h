#pragma once
#include "Model.h"
#include <SFML/Graphics.hpp>

class View {
private:
	sf::RenderWindow& window;
	Model& model;
public:
	View(Model& _model, sf::RenderWindow& _window): model(_model), window(_window) {}

	void render();

	sf::RenderWindow& accessWindow() { return this->window; }
};