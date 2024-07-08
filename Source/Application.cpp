#include "../Headers/Application.h"

void Aplication::run()
{
	while (this->window.isOpen()) {
		this->controller.handleInput();
		this->view.render();
	}
}
