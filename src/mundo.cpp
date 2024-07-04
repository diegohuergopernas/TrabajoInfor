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
bool Mundo::rutaDespejada(Coordenadas origen, Coordenadas destino) {
    int dx = destino.get_x() - origen.get_x();
    int dy = destino.get_y() - origen.get_y();

    int stepX = (dx == 0) ? 0 : (dx > 0) ? 1 : -1;
    int stepY = (dy == 0) ? 0 : (dy > 0) ? 1 : -1;

    int x = origen.get_x() + stepX;
    int y = origen.get_y() + stepY;

    while (x != destino.get_x() || y != destino.get_y()) {
        if (obtenerPiezaEn(Coordenadas(x, y))) {
            return false;
        }
        x += stepX;
        y += stepY;
    }

    return true;
}

void Mundo::moverPieza(Coordenadas origen, Coordenadas destino) {
    Pieza* pieza = obtenerPiezaEn(origen);
    if (pieza && esMovimientoValido(pieza, destino)) {
        if (pieza->getTipo() != CABALLO && !rutaDespejada(origen, destino)) {
            std::cout << "Movimiento invalido: ruta bloqueada" << std::endl;
            return;
        }
        //logica especial peon
        if (pieza->getTipo() == PEON) {
            int dx = abs(destino.get_x() - origen.get_x());
            int dy = destino.get_y() - origen.get_y();
            if ((dx == 1 && dy == ((pieza->getColor() == BLANCO) ? 1 : -1)) && obtenerPiezaEn(destino)) {
                // Captura en diagonal
            }
            else if (dx != 0 || obtenerPiezaEn(destino)) {
                std::cout << "Movimiento invalido: el peón no puede moverse a esa casilla" << std::endl;
                return;
            }
        }
        Pieza* destinoPieza = obtenerPiezaEn(destino);
        if (destinoPieza && destinoPieza->getColor() != pieza->getColor()) {
            piezas.eliminar(destinoPieza);
        }
        else if (destinoPieza) {
            std::cout << "Movimiento invalido: hay una pieza del mismo color en el destino" << std::endl;
            return;
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

bool Mundo::esJaqueMate(Color color)
{
    return false;
}
