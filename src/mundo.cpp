#include "mundo.h"

void Mundo::dibujaMundo()
{
	gluLookAt(0, 7.5, 20,  // posicion del ojo
		0.0, 7.5, 0.0,      // hacia que punto mira  (0,0,0) 
		0.0, 1.0, 0.0);      // definimos hacia arriba (eje Y) 
	tablero.dibujarTablero();
}