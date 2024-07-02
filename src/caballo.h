#pragma once
#include "pieza.h"
#include <string>
class Caballo : public Pieza {
	Coordenadas actual{};
	Coordenadas siguiente{};
	ETSIDI::Sprite sprite;
public:
	Caballo(Color color, Coordenadas coord)
		: Pieza(CABALLO, color, coord), sprite(("bin/imagenes/caballo_" + std::string(color == BLANCO ? "b" : "n") + ".png").c_str()) {
		sprite.setSize(1.5, 1.5);
	}
	Coordenadas get_actual() { return actual; }
	Coordenadas get_siguiente() { return siguiente; }
	void dibujarPieza() override {
		glPushMatrix();
		glTranslatef(coordenadas.get_x() - 3.5f, 0, coordenadas.get_y() - 3.5f);
		sprite.draw();
		glPopMatrix();
	}
	bool comprobarMovimiento(Coordenadas destino) override {
		int dx = abs(destino.get_x() - coordenadas.get_x());
		int dy = abs(destino.get_y() - coordenadas.get_y());
		return (dx == 2 && dy == 1) || (dx == 1 && dy == 2);
	}
};