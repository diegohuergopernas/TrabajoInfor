#pragma once
#include "pieza.h"
#include "coordenadas.h"
class Torre : public Pieza {
public:
	Torre(Color color, Coordenadas cord);
	void dibujarPieza() override;

};