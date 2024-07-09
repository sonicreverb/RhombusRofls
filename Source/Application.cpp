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

	while (this->window.isOpen()) {
		sf::Time deltaTime = clock.restart();
		this->controller.handleInput();
		this->controller.update(deltaTime.asSeconds());
		this->view.render();
	}
}
