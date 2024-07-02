#include "mundo.h"
#include "pieza.h"
#include "math.h"
#include <iostream>
#include "torre.h"
#include "caballo.h"
#include "alfil.h"
#include "reina.h"
#include "rey.h"
#include "peon.h"


Mundo::Mundo(int filas, int columnas) : tablero(filas, columnas), turnoActual(BLANCO) {
    // Agregar piezas al tablero
    piezas.agregar(new Torre(BLANCO, Coordenadas(0, 0)));
    piezas.agregar(new Torre(NEGRO, Coordenadas(7, 7)));
    piezas.agregar(new Caballo(BLANCO, Coordenadas(0, 1)));
    piezas.agregar(new Caballo(NEGRO, Coordenadas(7, 6)));
    piezas.agregar(new Alfil(BLANCO, Coordenadas(0, 2)));
    piezas.agregar(new Alfil(NEGRO, Coordenadas(7, 5)));
    piezas.agregar(new Reina(BLANCO, Coordenadas(0, 3)));
    piezas.agregar(new Reina(NEGRO, Coordenadas(7, 3)));
    piezas.agregar(new Rey(BLANCO, Coordenadas(0, 4)));
    piezas.agregar(new Rey(NEGRO, Coordenadas(7, 4)));
    for (int i = 0; i < 8; ++i) {
        piezas.agregar(new Peon(BLANCO, Coordenadas(1, i)));
        piezas.agregar(new Peon(NEGRO, Coordenadas(6, i)));
    }
}
void Mundo::dibujaMundo()
{
    tablero.dibujarTablero();
    piezas.dibuja();
    /*int filas = tablero.getFilas();
    int columnas = tablero.getColumnas();
    float casillaSize = tablero.getCasillaSize();

    // Calcula el centro del tablero
    float centerX = columnas * casillaSize / 2.0f;
    float centerY = filas * casillaSize / 2.0f;

    // Ajusta la posición de la cámara según el tamaño del tablero
    float eyeX = centerX;
    float eyeY = centerY;
    float eyeZ = (filas > columnas ? filas : columnas) * casillaSize;  // La distancia de la cámara depende del tamaño del tablero

    gluLookAt(eyeX, eyeY, eyeZ +150,  // Posición del ojo
        centerX, centerY, 0.0,      // Hacia qué punto mira
        0.0, 1.0, 0);      // Definimos hacia arriba (eje Y)
   /* tablero.dibujarTablero();
    caballo.dibuja();
    reina.dibuja();*/
    //pieza.dibujarPieza();*/

}

void Mundo::moverPieza(Coordenadas origen, Coordenadas destino) {
    Pieza* pieza = obtenerPiezaEn(origen);
    if (pieza && esMovimientoValido(pieza, destino)) {
        Pieza* destinoPieza = obtenerPiezaEn(destino);
        if (destinoPieza && destinoPieza->getColor() != pieza->getColor()) {
            piezas.eliminar(destinoPieza);
        }
        pieza->moverPieza(destino);
        cambiarTurno();
    }
}

Pieza* Mundo::obtenerPiezaEn(Coordenadas coord) {
    return piezas.obtenerPiezaEn(coord);
}

bool Mundo::esMovimientoValido(Pieza* pieza, Coordenadas destino) {
    return pieza->comprobarMovimiento(destino);
}

bool Mundo::esJaque(Color color) {
    // Lógica para verificar si el rey del color dado está en jaque
    return false;
}
