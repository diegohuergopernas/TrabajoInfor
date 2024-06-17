#pragma once
#include "pieza.h"
#include "coordenadas.h"
class Reina {
	Coordenadas actual{};
	Coordenadas siguiente{};
	ETSIDI::Sprite sprite{ "bin/imagenes/reina_n.png" };
public:
	Reina() {
		//sprite.setCenter(0, 0);
		sprite.setSize(1.5, 1.5);// tamaño
	}
	Coordenadas get_actual() { return actual; }
	Coordenadas get_siguiente() { return siguiente; }
	void dibuja();
	bool comprobarMovimiento();


};
