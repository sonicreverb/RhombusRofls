#include "../Headers/Application.h"

void Aplication::run()
{
	while (this->window.isOpen()) {
		this->controller.handleInput();
		this->controller.update();
		this->view.render();
	}
}
