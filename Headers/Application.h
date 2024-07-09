#pragma once
#include "Model.h"
#include "Controller.h"
#include "View.h"
#include "ScreenResolution.h"

class Aplication {
private:	
	sf::RenderWindow window;

	Model model;
	Controller controller;
	View view;

public: 
	Aplication() : window(ScreenResolution::getDesktopMode(), "RhombusRofls"), model(), view(this->model, this->window), controller(this->model, this->view) { srand(time(NULL)); }
	void run();
};