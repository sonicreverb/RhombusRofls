#include "../Headers/Controller.h"
#include <iostream>

void Controller::update()
{
    vector<Figure*>& modelObjects = this->model.accessObjects();
    if (!modelObjects.empty()) {
        for (auto object : modelObjects) {
            object->move(0, 0.5);
            object->rotate();

            if (object->getY() + object->getSize() > 1080) // todo dynamic resolution
                object->move(0, -1 * (object->getY() + object->getSize() > 1080));
        }
            
    }
}

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
