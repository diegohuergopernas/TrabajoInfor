#pragma once
#include "pieza.h"

class Caballo  {
	
	ETSIDI::Sprite sprite{ "bin/imagenes/caballo_n.png" };
public:
	Caballo() {
		//sprite.setCenter(0, 0);
		sprite.setSize(1.5, 1.5);// tamaño
	}
	void dibuja();
};