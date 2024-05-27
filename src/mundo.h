#pragma once
#include "tablero.h"
#include "freeglut.h"
class Mundo
{
public:
	Mundo() {};

	Tablero tablero;

	void dibujaMundo();
};