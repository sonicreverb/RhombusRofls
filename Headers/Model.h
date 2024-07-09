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

public:
	virtual void move() = 0;
	virtual void move(float offsetX, float offsetY) = 0;
	virtual void rotate() = 0;
	virtual void display(sf::RenderWindow& window) = 0;

	sf::Vector2f getCoords() { return this->coords; }
	double getX() { return this->coords.x; }
	double getY() { return this->coords.y; }
	float getSize() { return this->size; }

	void setCoords(float x, float y) { this->coords = sf::Vector2f(x, y); }
	void setCoords(sf::Vector2f _coords) { this->coords = _coords; }
	virtual void setColor(sf::Color _color);
	void setSize(float _size);
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
	float scale;
	float velocity;
	float rotationAngle;
public:
	Rhombus(float x, float y, float size);

	void move() override;
	void move(float offsetX, float offsetY) override;
	void display(sf::RenderWindow& window) override;
	void rotate() override;

	sf::ConvexShape& accessShape() { return this->shape; }

	void setColor(sf::Color _color) override;
	void setScale(float scale);
	void updateCoords() { this->setCoords(this->shape.getPosition()); }
};

class Model {
private:
	vector<Figure*> objects;
public:
	void addRandomRhomb();

	vector<Figure*>& accessObjects() { return this->objects; }
};