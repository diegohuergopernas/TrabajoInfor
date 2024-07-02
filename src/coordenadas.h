#pragma once
//semejnte a Vector2D de las practicas
class Coordenadas {
	int x, y;
public:
	Coordenadas(int x = 0, int y = 0) : x(x), y(y) {}
	int get_x() { return x; }
	int get_y() { return y; }
	void set_x(int x) { this->x = x; }
	void set_y(int y) { this->y = y; }

};