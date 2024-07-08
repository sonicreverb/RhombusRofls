#pragma once
#include <utility>
#include <vector>

using namespace std;

class Figure {
private:
	pair<double, double> coords;

public:
	pair<double, double> getCoords() { return this->coords; }
	double getX() { return this->coords.first; }
	double getY() { return this->coords.second; }
};


class Rhombus : public Figure {

};

class Model {
private:
	vector<Figure*> objects;
public:
	Model() { }
};