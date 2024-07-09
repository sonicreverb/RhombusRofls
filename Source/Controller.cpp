#include "../Headers/Controller.h"
#include "../Headers/ScreenResolution.h"

void Controller::update(float _deltaTime)
{
    vector<Figure*>& modelObjects = this->model.accessObjects();
    if (!modelObjects.empty()) {
        for (auto object : modelObjects) {
            object->move(_deltaTime);
            object->rotate(_deltaTime);

            if (object->getY() - object->getSize() > ScreenResolution::getWindowHeight())
                object->move(0, -1 * (object->getY() + object->getSize()));
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
