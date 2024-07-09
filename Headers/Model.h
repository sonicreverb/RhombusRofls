#pragma once
#include <utility>
#include <vector>
#include <algorithm>
#include <SFML/Graphics.hpp>

using namespace std;

class Figure {
private:
	sf::Vector2f coords;
	float size;
	sf::Color color;
	bool activity;
	bool alive;

	float scale;
	float velocity;
	float rotationSpeed;

public:
	Figure(): activity(false), velocity(0), rotationSpeed(0.f), scale(1.f), size(0.f), alive(false){}

	virtual void move(float _deltaTime) = 0;
	virtual void move(float _offsetX, float _offsetY) = 0;
	virtual void rotate(float _deltaTime) = 0;
	virtual void display(sf::RenderWindow& window) = 0;

	sf::Vector2f getCoords() const { return this->coords; }
	double getX() const { return this->coords.x; }
	double getY() const { return this->coords.y; }
	float getSize() const { return this->size; }
	bool isActive() const { return this->activity; }
	bool isAlive() const { return this->alive; }
	float getScale() const { return this->scale; }
	float getVelocity() const { return this->velocity; }
	float getRotationSpeed() const { return this->rotationSpeed; }
	sf::Color getColor() const { return this->color; }
	virtual vector<sf::Vector2f> getPoints() = 0;

	virtual sf::ConvexShape& accessShape() = 0;
	virtual void setCoords(float x, float y) { this->coords = sf::Vector2f(x, y); }
	virtual void setCoords(sf::Vector2f _coords) { this->coords = _coords; }
	virtual void setColor(sf::Color _color);
	void setSize(float _size);
	virtual void setScale(float _scale);
	void setActivity(bool _activity) { this->activity = _activity; }
	void setLive(bool _live) { this->alive = _live; }
	void setVelocity(float _velocity) { this->velocity = _velocity; }
	void setRotationSpeed(float _angle) { this->rotationSpeed = _angle; }

	void editVelocity(float _value);
	void editRotationVelocity(float _value);

	virtual bool melt();
	virtual void die() = 0;
};

enum class RhombColors {
	Passive1,
	Passive2,
	Passive3,
	Passive4,
	Passive5,
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

	sf::ConvexShape& accessShape() override { return this->shape; }
	vector<sf::Vector2f> getPoints() override;

	void setColor(sf::Color _color) override;
	void setScale(float scale) override;
	void setCoords(float _x, float _y) override;
	void setCoords(sf::Vector2f _coords) override;
	void updateCoords() { this->setCoords(this->shape.getPosition()); }

	bool melt() override;
	void die() override;
};

class Model {
private:
	vector<Figure*> objects;
	Figure* activeFigure = nullptr;
public:
	void addRandomRhomb();
	void killActive();

	Figure* accessActiveFigure() { return this->activeFigure; }
	vector<Figure*>& accessObjects() { return this->objects; }

	void sortObjects();
	int getActiveObjectID();

	void setActiveFigure(Figure* _figure) { this->activeFigure = _figure; }
	void switchActivityTo(Figure* _figure);
	void switchActivityLeft();
	void switchActiviyRight();
};