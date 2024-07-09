#include "../Headers/Application.h"
#include <SFML/Audio.hpp>

void Aplication::run()
{
	sf::Clock clock;
	sf::Music music;

	if (music.openFromFile("MusicBG.ogg")) {
		music.setLoop(true);
		music.play();
	}

	sf::Image icon;
	if (icon.loadFromFile("Icon.png")) {
		window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
	}

	while (this->window.isOpen()) {
		sf::Time deltaTime = clock.restart();
		this->controller.handleInput();
		this->controller.update(deltaTime.asSeconds());
		this->view.render();
	}
}
