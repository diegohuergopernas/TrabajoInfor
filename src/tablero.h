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

	Tablero(int c = 8, int f = 8, float size = 1.0) : filas(f), columnas(c), casillaSize(size) {}

	void dibujarTablero();
	int getFilas() const { return filas; }
	int getColumnas() const { return columnas; }
	float getCasillaSize() const {
		return casillaSize;
	}
};