#include "../Headers/Model.h"
#include "../Headers/ScreenResolution.h"

void Figure::setColor(sf::Color _color)
{
	this->color = _color;
}

void Figure::setSize(float _size)
{
	this->size = _size;
}

void Figure::setScale(float _scale)
{
	this->scale = _scale;
}

void Figure::editVelocity(float _value)
{
	float currentVelocity = this->getVelocity();
	currentVelocity += _value;
	this->setVelocity(currentVelocity);
}

void Figure::editRotationVelocity(float _value)
{
	float currentRotationVelocity = this->getRotationSpeed();
	currentRotationVelocity += _value;
	this->setRotationSpeed(currentRotationVelocity);
}

Rhombus::Rhombus(float _x, float _y, float _size)
{
	shape.setPointCount(4);
	shape.setPoint(0, sf::Vector2f(-_size / 2, 0));
	shape.setPoint(1, sf::Vector2f(0, -_size));
	shape.setPoint(2, sf::Vector2f(_size / 2, 0));
	shape.setPoint(3, sf::Vector2f(0, _size));
	shape.setPosition(_x, _y);

	this->setSize(_size);
	this->setColor(RhombToSfColorAdapter(static_cast<RhombColors>(rand() % 6)));
	this->setActivity(false);

	Figure::setRotationSpeed(100);
	Figure::setVelocity(ScreenResolution::getWindowHeight() / 7);
	Figure::setScale(1.f);
}

void Rhombus::move(float _deltaTime)
{
	this->shape.move(0, this->getVelocity() * _deltaTime);
	this->updateCoords();
}

void Rhombus::move(float _offsetX, float _offsetY)
{
	this->shape.move(_offsetX, _offsetY);
	this->updateCoords();
}

void Rhombus::display(sf::RenderWindow& _window)
{
	_window.draw(this->shape);
	if (this->isActive()) {
		sf::ConvexShape activityShape = this->shape;
		float shapeScale = Figure::getScale();
		activityShape.setScale(0.8 * shapeScale, 0.8 * shapeScale);
		activityShape.setFillColor(sf::Color::White);
		_window.draw(activityShape);
	}
}

void Rhombus::rotate(float _deltaTime)
{
	this->shape.rotate(this->getRotationSpeed() * _deltaTime);
}

void Rhombus::setColor(sf::Color _color)
{
	Figure::setColor(_color);
	this->shape.setFillColor(_color);
}

void Rhombus::setScale(float _scale)
{
	float currentScale = Figure::getScale();
	float currentSize = Figure::getSize();
	float newScale = currentScale * _scale;
	Figure::setScale(newScale);
	Figure::setSize(currentSize * _scale);
	this->shape.setScale(newScale, newScale);
}

void Rhombus::setCoords(float _x, float _y)
{
	Figure::setCoords(_x, _y);
	this->shape.setPosition(_x, _y);
}

void Rhombus::setCoords(sf::Vector2f _coords)
{
	Figure::setCoords(_coords);
	this->shape.setPosition(_coords);
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
	Rhombus* addedObject = new Rhombus(rand() % ScreenResolution::getWindowWidth(), rand() % ScreenResolution::getWindowHeight(), ScreenResolution::getWindowHeight() / 20);
	
	Figure* activeObject = this->accessActiveFigure();
	if (activeObject != nullptr)
		activeObject->setActivity(false);

	this->setActiveFigure(addedObject);
	addedObject->setActivity(true);

	this->objects.push_back(addedObject);
}
