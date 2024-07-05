#pragma once
#include "tablero.h"
#include <vector>
#include "listapiezas.h"
#include "pieza.h"
#include "ETSIDI.h"
class Mundo
{
	Tablero tablero;
	ListaPiezas piezas;
	bool turnoBlanco;
public:
	Mundo(int filas = 8, int columnas = 8);
	void moverPieza(Coordenadas origen, Coordenadas destino);
	Pieza* obtenerPiezaEn(Coordenadas coord);
	bool esMovimientoValido(Pieza* pieza, Coordenadas destino);
	bool esJaque(Color color);
	bool esJaqueMate(Color color);
	void cambiarTurno();
	ListaPiezas& obtenerListaPiezas() { return piezas; } // Getter para acceder a piezas	
	void dibujaMundo();
	bool rutaDespejada(Coordenadas origen, Coordenadas destino);
	Tablero& getTablero() { return tablero; }
	bool esTurnoBlanco()const { return turnoBlanco; };
	bool manejaTurno(Coordenadas origen, Mundo& mundo);
	
};



inline void Mundo::cambiarTurno() {
	turnoBlanco = !turnoBlanco;
}
