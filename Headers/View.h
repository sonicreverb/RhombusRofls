#pragma once
#include "Model.h"
#include <SFML/Graphics.hpp>

class View {
private:
	sf::RenderWindow& window;
	Model& model;
	sf::Text instructionsText;
	sf::Font font;
public:

	View(Model& _model, sf::RenderWindow& _window);

	void render();

	sf::RenderWindow& accessWindow() { return this->window; }
};