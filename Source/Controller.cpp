#include "../Headers/Controller.h"
#include "../Headers/ScreenResolution.h"

#include <iostream>

void Controller::update(float _deltaTime)
{
    vector<Figure*>& modelObjects = this->model.accessObjects();
    if (!modelObjects.empty()) {
        for (auto object : modelObjects) {
            object->move(_deltaTime);
            object->rotate(_deltaTime);

            if (object->getY() > ScreenResolution::getWindowHeight() + object->getSize() && object->getVelocity() > 0)
                object->setCoords(object->getX(), 0 - object->getSize());
            else if (object->getY() + object->getSize() < 0 && object->getVelocity() < 0)
                object->setCoords(object->getX(), ScreenResolution::getWindowHeight() + object->getSize());
        }
    }
}

void Controller::handleInput() {
    sf::Event event;
    while (view.accessWindow().pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            view.accessWindow().close();

        else if (event.type == sf::Event::KeyPressed) {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
                if (event.key.code == sf::Keyboard::Equal || event.key.code == sf::Keyboard::Add)
                    this->model.accessActiveFigure()->setScale(1.1);
                else if (event.key.code == sf::Keyboard::Hyphen || event.key.code == sf::Keyboard::Subtract)
                    this->model.accessActiveFigure()->setScale(0.91);
            }

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::R)) {
                if (event.key.code == sf::Keyboard::Equal || event.key.code == sf::Keyboard::Add)
                    this->model.accessActiveFigure()->editRotationVelocity(20);
                else if (event.key.code == sf::Keyboard::Hyphen || event.key.code == sf::Keyboard::Subtract)
                    this->model.accessActiveFigure()->editRotationVelocity(-20);
            }

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::V)) {
                if (event.key.code == sf::Keyboard::Equal || event.key.code == sf::Keyboard::Add)
                    this->model.accessActiveFigure()->editVelocity(20);
                else if (event.key.code == sf::Keyboard::Hyphen || event.key.code == sf::Keyboard::Subtract)
                    this->model.accessActiveFigure()->editVelocity(-20);
            }

            switch (event.key.code) {
            case sf::Keyboard::Space:
                this->model.addRandomRhomb();
                break;
            case sf::Keyboard::Escape:
                view.accessWindow().close();
                break;
            default:
                break;
            }
        }
    }
}

