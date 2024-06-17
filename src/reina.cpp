#include "reina.h"
#include "freeglut.h"
#include "ETSIDI.h"


void Reina::dibuja()
{
	glPushMatrix();
	glTranslated(-4.1, 0, 0);//posicion
	sprite.draw();
	
}

bool Reina::comprobarMovimiento()
{
    return false;
}
