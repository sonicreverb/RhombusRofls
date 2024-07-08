#include "../Headers/Model.h"

void Figure::setColor(sf::Color _color)
{
	this->color = _color;
}

void Figure::setSize(float _size)
{
	this->size = _size;
}

Rhombus::Rhombus(float _x, float _y, float _size): rotationAngle(0.2), scale(1.f)
{
	shape.setPointCount(4);
	shape.setPoint(0, sf::Vector2f(-_size / 2, 0));
	shape.setPoint(1, sf::Vector2f(0, -_size));
	shape.setPoint(2, sf::Vector2f(_size / 2, 0));
	shape.setPoint(3, sf::Vector2f(0, _size));
	shape.setPosition(_x, _y);

	this->setSize(_size);
	this->setColor(RhombToSfColorAdapter(static_cast<RhombColors>(rand() % 6)));
}

void Rhombus::move(float _offsetX, float _offsetY)
{
	this->shape.move(_offsetX, _offsetY);
	this->updateCoords();
}

void Rhombus::display(sf::RenderWindow& _window)
{
	_window.draw(this->shape);
}

void Rhombus::rotate()
{
	this->shape.rotate(this->rotationAngle);
}

void Rhombus::setColor(sf::Color _color)
{
	Figure::setColor(_color);
	this->shape.setFillColor(_color);
}

void Rhombus::setScale(float _scale)
{
	this->scale = _scale;
	this->shape.setScale(_scale, _scale);
}

sf::Color RhombToSfColorAdapter(RhombColors _color)
{
	switch (_color)
	{
	case RhombColors::Passive1:
		return sf::Color(140, 164, 250, 255);
		break;
	case RhombColors::Passive2:
		return sf::Color(198, 250, 140, 255);
		break;
	case RhombColors::Passive3:
		return sf::Color(250, 164, 140, 255);
		break;
	case RhombColors::Passive4:
		return sf::Color(168, 87, 64, 255);
		break;
	case RhombColors::Passive5:
		return sf::Color(91, 98, 122, 255);
		break;
	case RhombColors::Active:
		return sf::Color(200, 20, 0, 255);
		break;
	default:
		break;
	}
}

void Model::addRandomRhomb()
{
	this->objects.push_back(new Rhombus(rand() % 1920, rand() % 1080, 100)); // todo dynamic screen resolution
}
