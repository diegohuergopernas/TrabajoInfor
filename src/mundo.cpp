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


Mundo::Mundo(int filas, int columnas) : tablero(filas, columnas), turnoBlanco(BLANCO){
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
    if(pieza){
        if (pieza->getColor() != turnoBlanco) {
            std::cout << "Movimiento invalido: es el turno del otro color" << std::endl;
            return;
        }
        if (pieza && esMovimientoValido(pieza, destino)) {
            if (pieza->getTipo() != CABALLO && !rutaDespejada(origen, destino)) {
                std::cout << "Movimiento invalido: ruta bloqueada" << std::endl;
                return;
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
            //Condicion de Jaque para movimiento de piezas
            if (esJaque(pieza->getColor())) {
                pieza->moverPieza(origen);
                if (destinoPieza) {
                    piezas.agregar(destinoPieza);
                }
                std::cout << "Movimiento invalido: el rey sigue en jaque" << std::endl;
                return;
            }
            cambiarTurno();

            if (esJaque(turnoBlanco ? NEGRO : BLANCO)) {
                std::cout << "Es jaque para las " << (turnoBlanco ? "negras" : "blancas") << std::endl;
                if (esJaqueMate(turnoBlanco ? NEGRO : BLANCO)) {
                    std::cout << "Es jaque mate, ganan las " << (turnoBlanco ? "blancas" : "negras") << std::endl;
                }
            }
        }
  
    }
}

Pieza* Mundo::obtenerPiezaEn(Coordenadas coord) {
    return piezas.obtenerPiezaEn(coord);
}

bool Mundo::esMovimientoValido(Pieza* pieza, Coordenadas destino) {
    return pieza->comprobarMovimiento(destino);
}
//comprueba los posibles movimientos para evitar el jaque
bool Mundo::movimientoEvitaJaque(Pieza* pieza, Coordenadas destino)
{
    Coordenadas origen = pieza->getCoordenadas();
    Pieza* piezaDestino = obtenerPiezaEn(destino);
    pieza->moverPieza(destino);

    bool evitaJaque = !esJaque(pieza->getColor());
    pieza->moverPieza(origen);

    if (piezaDestino) {
        piezas.agregar(piezaDestino);
    }

    return evitaJaque;;
}
//Comprueba si el rey esta amenazado por alguna pieza
bool Mundo::reyAmenazado(Coordenadas reyPos, Color color)
{
    for (Pieza* pieza : piezas.obtenerPiezas()) {
        if (pieza->getColor() != color && esMovimientoValido(pieza, reyPos)) {
            if(pieza->getTipo()==CABALLO){
            return true;
        }
        if (pieza->getTipo() == REY) {
            continue; // El rey no puede amenazar a otro rey directamente.
        }
        if (rutaDespejada(pieza->getCoordenadas(), reyPos)) {
            return true;
        }
      }
    }
    return false;
}

bool Mundo::esJaque(Color color) {
    // Lógica para verificar si el rey del color dado está en jaque
    Coordenadas reyPos;
    for (auto pieza : piezas.obtenerPiezas()) {
        if (pieza->getTipo() == REY && pieza->getColor() == color) {
            reyPos = pieza->getCoordenadas();
            break;
        }
    }
    return reyAmenazado(reyPos, color);
}

bool Mundo::esJaqueMate(Color color)
{
    
    return false;
}
