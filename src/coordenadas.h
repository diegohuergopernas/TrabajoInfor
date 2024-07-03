#pragma once
//semejnte a Vector2D de las practicas
class Coordenadas {
	int x, y;
public:
	Coordenadas(double x = 0, double y = 0) : x(x), y(y) {}
	double get_x() const{ return x; }
	double get_y() const{ return y; }
	void set_x(double x) { this->x = x; }
	void set_y(double y) { this->y = y; }

};