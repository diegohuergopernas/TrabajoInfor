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
#include "interfaz.h"
#include <thread>
#include <chrono>



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

        // Si el rey está en jaque, solo permitir movimientos que eviten el jaque
        if (esJaque(turnoBlanco ? BLANCO : NEGRO) && !movimientoEvitaJaque(pieza, destino)) {
            std::cout << "Movimiento invalido: debe mover para evitar el jaque" << std::endl;
            return;
        }

        if (pieza && esMovimientoValido(pieza, destino)) {
            if (pieza->getTipo() != CABALLO && !rutaDespejada(origen, destino)) {
                std::cout << "Movimiento invalido: ruta bloqueada" << std::endl;
                return;
            }
            // Logica especial peon
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
            //Logica para enroque
            if (pieza->getTipo() == REY && abs(destino.get_x() - origen.get_x()) == 2) {
                int direction = (destino.get_x() - origen.get_x()) > 0 ? 1 : -1;
                Coordenadas torrePos(origen.get_x() + 3 * direction, origen.get_y());
                if (direction == 1) { // Enroque corto
                    torrePos = Coordenadas(origen.get_x() + 3 * direction, origen.get_y());
                }
                else { // Enroque largo
                    torrePos = Coordenadas(origen.get_x() - 4, origen.get_y());
                }
                if (rutaDespejada(origen, torrePos)) {
                    Pieza* torre = obtenerPiezaEn(torrePos);
                    //Usamos el static cast para poder acceder a un método específico de torre que no pertenece a pieza
                    if (torre && torre->getTipo() == TORRE && !static_cast<Torre*>(torre)->haSidoMovido() && !static_cast<Rey*>(pieza)->haSidoMovido()) {
                        // Verificar que las casillas entre el origen y el destino no estén en jaque
                        Coordenadas intermedio1(origen.get_x() + direction, origen.get_y());
                        Coordenadas intermedio2(origen.get_x() + 2 * direction, origen.get_y());
                        if (!esJaque(pieza->getColor()) && !reyAmenazado(intermedio1, pieza->getColor()) && !reyAmenazado(intermedio2, pieza->getColor())) {
                            // Realizar el enroque
                            if (direction == 1) { // Enroque corto
                                torre->moverPieza(Coordenadas(destino.get_x() - direction, destino.get_y()));
                            }
                            else { // Enroque largo
                                torre->moverPieza(Coordenadas(destino.get_x() + 1, destino.get_y()));
                            }
                            static_cast<Torre*>(torre)->setMovido(true);
                        }
                        else {
                            std::cout << "Movimiento invalido: no se puede enrocar porque el rey está en jaque o pasa por una casilla en jaque" << std::endl;
                            return;
                        }
                    }
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
            Coordenadas posicionOriginal = pieza->getCoordenadas();
            pieza->moverPieza(destino);

            if (!movimientoEvitaJaque(pieza, destino)) {
                pieza->moverPieza(posicionOriginal);
                if (destinoPieza) {
                    piezas.agregar(destinoPieza);
                }
                std::cout << "Movimiento invalido: el movimiento deja al rey en jaque" << std::endl;
                return;
            }
            // Marcar la pieza como movida si es rey o torre
            if (pieza->getTipo() == REY) {
                static_cast<Rey*>(pieza)->setMovido(true);
            }
            else if (pieza->getTipo() == TORRE) {
                static_cast<Torre*>(pieza)->setMovido(true);
            }

            //Condicion de Jaque para movimiento de piezas
            if (esJaque(pieza->getColor())) {
                pieza->moverPieza(origen);
                if (destinoPieza) {
                    piezas.agregar(destinoPieza);
                }
                std::cout << "Movimiento invalido: el rey sigue en jaque" << std::endl;
                return;
            }
            promover(destino);
            cambiarTurno();

            if (esJaque(turnoBlanco ? NEGRO : BLANCO)) {
                std::cout << "Es jaque para las " << (turnoBlanco ? "negras" : "blancas") << std::endl;
                if (esJaqueMate(turnoBlanco ? NEGRO : BLANCO)) {
                    std::cout << "Es jaque mate, ganan las " << (turnoBlanco ? "blancas" : "negras") << std::endl;
                    std::this_thread::sleep_for(std::chrono::seconds(5));
                    interfaz.mostrarMenu();
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
bool Mundo::movimientoEvitaJaque(Pieza* pieza, Coordenadas destino){
    Coordenadas origen = pieza->getCoordenadas();
    Pieza* piezaDestino = obtenerPiezaEn(destino);
    pieza->moverPieza(destino);

    bool evitaJaque = !esJaque(pieza->getColor());

    // Verificar si el rey se mueve a una casilla que está protegida
    if (pieza->getTipo() == REY) {
        for (Pieza* p : piezas.obtenerPiezas()) {
            if (p->getColor() != pieza->getColor() && p->comprobarMovimiento(destino) && rutaDespejada(p->getCoordenadas(), destino)) {
                evitaJaque = false;
                break;
            }
        }
    }

    pieza->moverPieza(origen);

    if (piezaDestino) {
        piezas.agregar(piezaDestino);
    }

    return evitaJaque;
}
//funcion de promocion de peones
void Mundo::promover(Coordenadas destino) {
    Pieza* pieza = obtenerPiezaEn(destino);
    if (pieza && pieza->getTipo() == PEON) {
        int filaDestino = destino.get_y();
        if ((pieza->getColor() == BLANCO && filaDestino == 7) ||
            (pieza->getColor() == NEGRO && filaDestino == 0)) {
            char eleccion;
            std::cout << "Cambia peon: (c) Caballo, (f) Alfil, (t) Torre, (r) Reina: ";
            std::cin >> eleccion;
            Pieza* nuevaPieza = nullptr;

            switch (eleccion) {
            case 'c':
                nuevaPieza = new Caballo(pieza->getColor(), destino);
                break;
            case 'f':
                nuevaPieza = new Alfil(pieza->getColor(), destino);
                break;
            case 't':
                nuevaPieza = new Torre(pieza->getColor(), destino);
                break;
            case 'r':
            default:
                nuevaPieza = new Reina(pieza->getColor(), destino);
                break;
            }

            if (nuevaPieza) {
                piezas.eliminar(pieza);
                piezas.agregar(nuevaPieza);
            }
        }
    }
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

bool Mundo::esJaqueMate(Color color) {
    // Verifica si el rey del color dado está en jaque
    if (!esJaque(color)) {
        return false;
    }

    // Recorre todas las piezas del color dado
    for (auto pieza : piezas.obtenerPiezas()) {
        if (pieza->getColor() == color) {
            Coordenadas origen = pieza->getCoordenadas();
            for (int x = 0; x < tablero.getColumnas(); ++x) {
                for (int y = 0; y < tablero.getFilas(); ++y) {
                    Coordenadas destino(x, y);
                    if (esMovimientoValido(pieza, destino) && movimientoEvitaJaque(pieza, destino)) {
                        return false; // Hay un movimiento que puede evitar el jaque mate
                    }
                }
            }
        }
    }
    return true; // No hay movimientos que puedan evitar el jaque mate
}

