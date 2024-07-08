#pragma once
#include "Model.h"
#include "Controller.h"
#include "View.h"


class Aplication {
private:	
	Model model;
	Controller controller;
	View view;

public: 
	Aplication(): model(), view(this->model), controller(this->model, this->view) {}
	void run() { return; }
};