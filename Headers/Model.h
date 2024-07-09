#pragma once
#include <utility>
#include <vector>
#include <SFML/Graphics.hpp>

using namespace std;

class Figure {
private:
	sf::Vector2f coords;
	float size;
	sf::Color color;
	bool activity;

	float scale;
	float velocity;
	float rotationSpeed;

public:
	virtual void move(float _deltaTime) = 0;
	virtual void move(float _offsetX, float _offsetY) = 0;
	virtual void rotate(float _deltaTime) = 0;
	virtual void display(sf::RenderWindow& window) = 0;

	sf::Vector2f getCoords() { return this->coords; }
	double getX() { return this->coords.x; }
	double getY() { return this->coords.y; }
	float getSize() { return this->size; }
	bool isActive() { return this->activity; }
	float getScale() { return this->scale; }
	float getVelocity() { return this->velocity; }
	float getRotationSpeed() { return this->rotationSpeed; }

	virtual void setCoords(float x, float y) { this->coords = sf::Vector2f(x, y); }
	virtual void setCoords(sf::Vector2f _coords) { this->coords = _coords; }
	virtual void setColor(sf::Color _color);
	void setSize(float _size);
	virtual void setScale(float _scale);
	void setActivity(bool _activity) { this->activity = _activity; }
	void setVelocity(float _velocity) { this->velocity = _velocity; }
	void setRotationSpeed(float _angle) { this->rotationSpeed = _angle; }

	void editVelocity(float _value);
	void editRotationVelocity(float _value);
};

enum class RhombColors {
	Passive1,
	Passive2,
	Passive3,
	Passive4,
	Passive5,
	Active
};

sf::Color RhombToSfColorAdapter(RhombColors _color);

class Rhombus : public Figure {
private:
	sf::ConvexShape shape;
public:
	Rhombus(float _x, float _y, float _size);

	void move(float _deltaTime) override;
	void move(float _offsetX, float _offsetY) override;
	void display(sf::RenderWindow& window) override;
	void rotate(float _deltaTime) override;

	sf::ConvexShape& accessShape() { return this->shape; }

	void setColor(sf::Color _color) override;
	void setScale(float scale) override;
	void setCoords(float _x, float _y) override;
	void setCoords(sf::Vector2f _coords) override;
	void updateCoords() { this->setCoords(this->shape.getPosition()); }
};

class Model {
private:
	vector<Figure*> objects;
	Figure* activeFigure = nullptr;
public:
	void addRandomRhomb();

	Figure* accessActiveFigure() { return this->activeFigure; }
	vector<Figure*>& accessObjects() { return this->objects; }

	void setActiveFigure(Figure* _figure) { this->activeFigure = _figure; }
};