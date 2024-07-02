#pragma once
#include "freeglut.h"
#include "pieza.h"
#include <vector>

class Tablero {

	int filas;
	int columnas;
	double casillaSize;
	std::vector<Pieza*> piezas;

public:

	Tablero(int f = 8, int c = 8, float size = 1.5) : filas(f), columnas(c), casillaSize(size) {}

	void dibujarTablero();
	int getFilas() const { return filas; }
	int getColumnas() const { return columnas; }
	float getCasillaSize() const {
		return casillaSize;
	}
};