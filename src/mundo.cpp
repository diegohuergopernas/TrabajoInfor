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
    
}
void Mundo::dibujaMundo()
{
    tablero.dibujarTablero();
    piezas.dibuja();
    

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
