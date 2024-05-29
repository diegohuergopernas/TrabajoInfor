#include "mundo.h"
#include "pieza.h"
#include "math.h"

void Mundo::dibujaMundo()
{
    int filas = tablero.getFilas();
    int columnas = tablero.getColumnas();
    float casillaSize = tablero.getCasillaSize();

    // Calcula el centro del tablero
    float centerX = columnas * casillaSize / 2.0f;
    float centerY = filas * casillaSize / 2.0f;

    // Ajusta la posición de la cámara según el tamaño del tablero
    float eyeX = centerX;
    float eyeY = centerY;
    float eyeZ = (filas > columnas ? filas : columnas) * casillaSize;  // La distancia de la cámara depende del tamaño del tablero

    gluLookAt(eyeX, eyeY, eyeZ + 7,  // Posición del ojo
        centerX, centerY, 0.0,      // Hacia qué punto mira
        0.0, 1.0, 0);      // Definimos hacia arriba (eje Y)
    tablero.dibujarTablero();
    //pieza.dibujarPieza();

}
