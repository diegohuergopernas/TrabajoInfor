#pragma once
#include "tablero.h"
#include "freeglut.h"
#include "listapiezas.h"
#include"caballo.h"
class Mundo
{
public:
	Mundo(int filas = 8, int columnas = 8) : tablero(filas, columnas) {}
	Caballo caballo;
	Tablero tablero;
	Pieza* pieza;
	ListaPiezas piezas;
	void dibujaMundo();
};