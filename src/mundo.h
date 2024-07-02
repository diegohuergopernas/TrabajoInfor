#pragma once
#include "tablero.h"
#include "freeglut.h"
#include "listapiezas.h"
#include "pieza.h"
#include "ETSIDI.h"
class Mundo
{
	Tablero tablero;
	ListaPiezas piezas;
	Color turnoActual;
public:
	Mundo(int filas = 8, int columnas = 8);
	void moverPieza(Coordenadas origen, Coordenadas destino);
	Pieza* obtenerPiezaEn(Coordenadas coord);
	bool esMovimientoValido(Pieza* pieza, Coordenadas destino);
	bool esJaque(Color color);
	void cambiarTurno();
	Color obtenerTurnoActual() const { return turnoActual; }
	ListaPiezas& obtenerListaPiezas() { return piezas; } // Getter para acceder a piezas	
	void dibujaMundo();
};



inline void Mundo::cambiarTurno() {
	turnoActual = (turnoActual == BLANCO) ? NEGRO : BLANCO;
}