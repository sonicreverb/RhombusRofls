#include "../Headers/Controller.h"

void Controller::handleInput()
{
    sf::Event event;
    while (view.accessWindow().pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            view.accessWindow().close();
        else if (event.type == sf::Event::KeyPressed) {
            if (event.key.code == sf::Keyboard::Space) {
                this->model.addRandomRhomb();
            }
        }
    }
}
