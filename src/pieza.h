#pragma once
#include "coordenadas.h"
#include "ETSIDI.h"
enum Tipo { REY, REINA, ALFIL, TORRE, CABALLO, PEON };
enum Color { NEGRO, BLANCO };
class Pieza {
protected:
	Color color;
	Tipo tipo;
	Coordenadas coordenadas;
	ETSIDI::Sprite sprite;
public:
	Pieza(Tipo tipo, Color color, Coordenadas coord);
	virtual ~Pieza();

	//Funciones comunes a todas las piezas
	virtual void dibujarPieza() = 0; //virtual puro para especializar dibuja en cada pieza
	virtual void moverPieza(Coordenadas destino); //virtual puro para especializar movimiento de cada pieza
	virtual bool comprobarMovimiento(Coordenadas destino) = 0;//comprobar movimiento valido

	Tipo getTipo() const { return tipo; }
	Color getColor() const { return color; }
	Coordenadas getCoordenadas() const { return coordenadas; }

};
inline Pieza::Pieza(Tipo tipo, Color color, Coordenadas coord)
	: tipo(tipo), color(color), coordenadas(coord), sprite("bin/imagenes/fondo.png") {}

inline void Pieza::moverPieza(Coordenadas destino) {
	coordenadas = destino;
}
