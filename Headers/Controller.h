#pragma once
#include "Model.h"
#include "View.h"


class Controller {
private:
	Model& model;
	View& view;
public:
	Controller(Model& _model, View& _view) : model(_model), view(_view) {};

	void handleInput();
};