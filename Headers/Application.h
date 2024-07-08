#pragma once
#include "Model.h"
#include "Controller.h"
#include "View.h"


class Aplication {
private:	
	sf::RenderWindow window;

	Model model;
	Controller controller;
	View view;

public: 
	// todo dynamic screen resolution
	Aplication(): window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "RhombusRofls"), model(), view(this->model, this->window), controller(this->model, this->view) {} 
	void run();
};