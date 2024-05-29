#pragma once
#include "tablero.h"
#include "freeglut.h"
#include "reina.h"
class Mundo
{
public:
	Mundo(int filas = 8, int columnas = 8) : tablero(filas, columnas) {}

	Tablero tablero;
	Pieza* pieza;

	void dibujaMundo();
};