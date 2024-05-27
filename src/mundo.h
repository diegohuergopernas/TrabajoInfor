#pragma once
#include "tablero.h"
#include "freeglut.h"
#include "reina.h"
class Mundo
{
public:
	Mundo() {};

	Tablero tablero;
	Pieza* pieza;

	void dibujaMundo();
};