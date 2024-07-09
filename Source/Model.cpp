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
	if ((currentVelocity < ScreenResolution::getWindowHeight() && _value > 0) ||
		(currentVelocity > -1 * ScreenResolution::getWindowHeight() && _value < 0)) {
		currentVelocity += _value;
		this->setVelocity(currentVelocity);
	}
}

void Figure::editRotationVelocity(float _value)
{
	float currentRotationVelocity = this->getRotationSpeed();
	if ((currentRotationVelocity < ScreenResolution::getWindowHeight() / 2 && _value > 0) ||
		(currentRotationVelocity > -1 * ScreenResolution::getWindowHeight() / 2 && _value < 0)) {
		currentRotationVelocity += _value;
		this->setRotationSpeed(currentRotationVelocity);
	}
}

bool Figure::melt()
{
	sf::Color currentColor = this->getColor();
	sf::Color newColor(currentColor.r, currentColor.g, currentColor.b, currentColor.a - 5);
	this->setColor(newColor);
	return newColor.a <= 0;
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
 	this->setColor(RhombToSfColorAdapter(static_cast<RhombColors>(rand() % 5)));
	this->setActivity(false);

	Figure::setRotationSpeed(100);
	Figure::setVelocity(ScreenResolution::getWindowHeight() / 7);
	Figure::setScale(1.f);
	Figure::setLive(true);
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

vector<sf::Vector2f> Rhombus::getPoints()
{
	vector<sf::Vector2f> points;
	size_t pointCount = shape.getPointCount();
	sf::Vector2f position = shape.getPosition();
	sf::Vector2f scale = shape.getScale();
	float rotation = shape.getRotation();
	float radians = rotation * 3.14159265358979323846 / 180.0;

	for (size_t i = 0; i < pointCount; ++i) {
		sf::Vector2f point = shape.getPoint(i);

		point.x *= scale.x;
		point.y *= scale.y;

		float rotatedX = point.x * std::cos(radians) - point.y * std::sin(radians);
		float rotatedY = point.x * std::sin(radians) + point.y * std::cos(radians);

		points.push_back(sf::Vector2f(rotatedX, rotatedY) + position);
	}

	return points;
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

bool Rhombus::melt()
{
	if (!Figure::melt()) {
		this->shape.setFillColor(this->getColor());
		return false;
	} 
	else return true;
}

void Rhombus::die()
{
	if (this->isActive()) {
		this->setActivity(false);
	}

	Figure::setRotationSpeed(0);
	Figure::setVelocity(0);
	Figure::setLive(false);
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
	default:
		break;
	}
}

void Model::addRandomRhomb()
{
	if (this->accessObjects().size() == 10)
		this->accessObjects()[rand() % 10]->die();
	else if (this->accessObjects().size() < 10) {
		Rhombus* addedObject = new Rhombus(rand() % ScreenResolution::getWindowWidth() * 0.8 + ScreenResolution::getWindowWidth() * 0.1,
			rand() % ScreenResolution::getWindowHeight(), ScreenResolution::getWindowHeight() / 20);

		this->switchActivityTo(addedObject);
		this->objects.push_back(addedObject);
		this->sortObjects();
	}
}

void Model::killActive()
{

	Figure* activeObject = this->accessActiveFigure();
	if (activeObject != nullptr) {
		activeObject->die();
		this->setActiveFigure(nullptr);
	}
	
}

void Model::sortObjects()
{
	std::sort(objects.begin(), objects.end(), [](Figure* a, Figure* b) {
		return a->getCoords().x < b->getCoords().x;
		});
}

int Model::getActiveObjectID()
{
	Figure* activeFigure = this->accessActiveFigure();
	if (activeFigure == nullptr)
		return -1;
	else {
		auto objects = this->accessObjects();
		for (int id = 0; id < objects.size(); id++)
			if (activeFigure == objects[id]) return id;

		return -1;
	}
}

void Model::switchActivityTo(Figure* _figure)
{
	Figure* activeObject = this->accessActiveFigure();
	if (activeObject != nullptr)
		activeObject->setActivity(false);

	this->setActiveFigure(_figure);
	_figure->setActivity(true);
}

void Model::switchActivityLeft()
{
	int currentActiveID = this->getActiveObjectID();
	if (currentActiveID != -1) {
		if (currentActiveID == 0)
			currentActiveID = this->objects.size() - 1;
		else
			currentActiveID -= 1;

		switchActivityTo(this->accessObjects()[currentActiveID]);
	}
	else {
		if (!this->objects.empty()) {
			currentActiveID = 0;
			switchActivityTo(this->accessObjects()[currentActiveID]);
		}
	}
}

void Model::switchActiviyRight()
{
	int currentActiveID = this->getActiveObjectID();
	if (currentActiveID != -1) {
		if (currentActiveID == this->objects.size() - 1)
			currentActiveID = 0;
		else
			currentActiveID += 1;

		switchActivityTo(this->accessObjects()[currentActiveID]);
	}
	else {
		if (!this->objects.empty()) {
			currentActiveID = this->objects.size() - 1;
			switchActivityTo(this->accessObjects()[currentActiveID]);
		}
	}
}
