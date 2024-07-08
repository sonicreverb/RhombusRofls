#pragma once
#include <utility>
#include <vector>
#include <SFML/Graphics.hpp>

using namespace std;

class Figure {
private:
	pair<float, float> coords;
	float size;
	sf::Color color;

public:
	virtual void move(float offsetX, float offsetY) = 0;
	virtual void display(sf::RenderWindow& window) = 0;

	pair<double, double> getCoords() { return this->coords; }
	double getX() { return this->coords.first; }
	double getY() { return this->coords.second; }
	float getSize() { return this->size; }

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
	float rotationAngle;
public:
	Rhombus(float x, float y, float size);

	void move(float offsetX, float offsetY) override;
	void display(sf::RenderWindow& window) override;
	void rotate();

	void setColor(sf::Color _color) override;
	void setScale(float scale);
};

class Model {
private:
	vector<Figure*> objects;
public:
	void addRandomRhomb();

	vector<Figure*>& accessObjects() { return this->objects; }
};