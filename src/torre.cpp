#include "torre.h"

Torre::Torre(Color color, Coordenadas coord) :Pieza(color, coord, TORRE) {}

void Torre::dibuja() {
	Sprite spriteNeg{ "bin/imagenes/torreneg.png" };
	Sprite spriteBlc{ "bin/imagenes/torreblc.png" };
}