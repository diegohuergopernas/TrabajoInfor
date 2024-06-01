#include"caballo.h"

void Caballo::dibuja()
{
	glPushMatrix();
	glTranslated(1.1, -0.2, 1);//posicion
	sprite.draw();
}