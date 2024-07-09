#include "../Headers/Controller.h"
#include "../Headers/ScreenResolution.h"

void Controller::update(float _deltaTime)
{
    vector<Figure*>& modelObjects = this->model.accessObjects();
    if (!modelObjects.empty()) {
        for (int id = 0; id < modelObjects.size(); id++) {
            Figure* object = modelObjects[id];

            if (object->isAlive()) {
                object->move(_deltaTime);
                object->rotate(_deltaTime);

                if (object->getY() > ScreenResolution::getWindowHeight() + object->getSize() && object->getVelocity() > 0)
                    object->setCoords(object->getX(), 0 - object->getSize());
                else if (object->getY() + object->getSize() < 0 && object->getVelocity() < 0)
                    object->setCoords(object->getX(), ScreenResolution::getWindowHeight() + object->getSize());

                auto objectPoints = object->getGlobalPoints();
                for (auto point : objectPoints) {
                    if (point.x < 0 || point.x > ScreenResolution::getWindowWidth())
                        object->die();
                }

                for (int supID = 0; supID < modelObjects.size(); supID++) {
                    if (supID == id) continue;
                    else if (object->intersects(modelObjects[supID])) {
                        object->die();
                        modelObjects[supID]->die();
                    }
                }
            }
            else {
                if (object->melt()) {
                    modelObjects.erase(modelObjects.begin() + id);
                    id--;
                }
            }
        }
    }
}

void Controller::handleInput() {
    sf::Event event;
    while (view.accessWindow().pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            view.accessWindow().close();

        else if (event.type == sf::Event::KeyPressed) {
            if (this->model.accessActiveFigure() != nullptr) {
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
            }

            switch (event.key.code) {
            case sf::Keyboard::Space:
                this->model.addRandomRhomb();
                break;
            case sf::Keyboard::Escape:
                view.accessWindow().close();
                break;
            case sf::Keyboard::Delete:
                this->model.killActive();
                break;
            case sf::Keyboard::Left:
                this->model.switchActivityLeft();
                break;
            case sf::Keyboard::Right:
                this->model.switchActiviyRight();
                break;
            default:
                break;
            }
        }
    }
}

