#include "../Headers/View.h"

void View::render()
{
	this->window.clear();

	vector<Figure*>& modelObjects = this->model.accessObjects();
	if (!modelObjects.empty()) {
		for (auto object : modelObjects)
			object->display(window);
	}

	this->window.display();
}
