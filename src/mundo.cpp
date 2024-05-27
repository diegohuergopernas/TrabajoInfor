#include "mundo.h"
#include "pieza.h"

void Mundo::dibujaMundo()
{
	gluLookAt(6, 6, 20,  // posicion del ojo
		6, 6, 0.0,      // hacia que punto mira  (0,0,0) 
		0.0, 1.0, 0);      // definimos hacia arriba (eje Y) 
	tablero.dibujarTablero();
	//pieza.dibujarPieza();

}