#pragma once
#include "coordenadas.h"
#include "ETSIDI.h"
enum Tipo { REY, REINA, ALFIL, TORRE, CABALLO, PEON };
enum Color { NEGRO, BLANCO };
class Pieza {
public:
	Color color;
	Tipo tipo;
	Coordenadas coordenadas;


	Pieza(Tipo tipo, Color color, Coordenadas coordenadas);
	virtual ~Pieza();

	//Funciones comunes a todas las piezas
	virtual void dibujarPieza() = 0; //virtual puro para especializar dibuja en cada pieza
	virtual void moverPieza(int fila, int columna, Pieza*) = 0; //virtual puro para especializar movimiento de cada pieza
	virtual void killPieza() = 0;//funcion matar

	void SetColor();
	void SetCoordenadas();
	void SetTipo();


};
