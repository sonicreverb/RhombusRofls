#include "../Headers/Application.h"

void Aplication::run()
{
	sf::Clock clock;

	while (this->window.isOpen()) {
		sf::Time deltaTime = clock.restart();
		this->controller.handleInput();
		this->controller.update(deltaTime.asSeconds());
		this->view.render();
	}
}
