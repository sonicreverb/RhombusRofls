#include "../Headers/View.h"
#include "../Headers/ScreenResolution.h"

View::View(Model& _model, sf::RenderWindow& _window) : model(_model), window(_window)
{
    if (font.loadFromFile("Daydream.ttf")) {
        this->instructionsText.setFont(font);
        this->instructionsText.setString("Rhombus Rofls by Vladislav Krasivin\n\nSPACE to spawn Rhombus\n\nS and +/- to edit scale\n\nR and +/- to edit rotation velocity\n\n"
            "V and +/- to edit velocity\n\nDEL to kill active Rhombus\n\n Left/Right arrow to navigate\n\n ESC to EXIT\n");
        this->instructionsText.setCharacterSize(ScreenResolution::getWindowHeight() / 50);
        this->instructionsText.setFillColor(sf::Color::White);

        sf::FloatRect textRect = instructionsText.getLocalBounds();

        this->instructionsText.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
        this->instructionsText.setPosition(static_cast<float>(window.getSize().x) / 2.0f, static_cast<float>(window.getSize().y) / 2.0f);
    }
}

void View::render()
{
    this->window.clear();

    this->window.draw(this->instructionsText);

    std::vector<Figure*>& modelObjects = this->model.accessObjects();
    if (!modelObjects.empty()) {
        for (auto object : modelObjects)
            object->display(window);
    }

    this->window.display();
}