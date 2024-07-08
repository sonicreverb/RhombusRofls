#pragma once
#include "Model.h"

class View {
private:
	Model& model;
public:
	View(Model& _model): model(_model) {}

	void render();
};