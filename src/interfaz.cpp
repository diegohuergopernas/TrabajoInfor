#include "interfaz.h"
#include "mundo.h"
#include "pieza.h"
#include "peon.h"
#include "torre.h"
#include "caballo.h"
#include "alfil.h"
#include "reina.h"
#include "rey.h"
#include <iostream>
#include "freeglut.h"

// Variables globales para manejo del juego
extern Mundo* mundo;  // Declaración de la variable global

Coordenadas origen, destino;
bool seleccionOrigen = true;

void Interfaz::mostrarMenu() {
    int opcion;
    std::cout << "Seleccione el tipo de tablero:\n";
    std::cout << "1. 4x5 con un unico peon\n";
    std::cout << "2. Speed Chess\n";
    std::cout << "3. Tablero estandar\n";
    std::cout << "Ingrese una opcion: ";
    std::cin >> opcion;

    switch (opcion) {
    case 1:
        mundo = new Mundo(4, 5);
        mundo->obtenerListaPiezas().agregar(new Peon(BLANCO, Coordenadas(3, 1)));
        mundo->obtenerListaPiezas().agregar(new Torre(BLANCO, Coordenadas(0, 0)));
        mundo->obtenerListaPiezas().agregar(new Caballo(BLANCO, Coordenadas(2, 0)));
        mundo->obtenerListaPiezas().agregar(new Alfil(BLANCO, Coordenadas(1, 0)));
        mundo->obtenerListaPiezas().agregar(new Rey(BLANCO, Coordenadas(3, 0)));
        mundo->obtenerListaPiezas().agregar(new Peon(NEGRO, Coordenadas(0, 3)));
        mundo->obtenerListaPiezas().agregar(new Torre(NEGRO, Coordenadas(3, 4)));
        mundo->obtenerListaPiezas().agregar(new Caballo(NEGRO, Coordenadas(1, 4)));
        mundo->obtenerListaPiezas().agregar(new Alfil(NEGRO, Coordenadas(2, 4)));
        mundo->obtenerListaPiezas().agregar(new Rey(NEGRO, Coordenadas(0, 4)));
        break;
    case 2:
        mundo = new Mundo(5, 6);
        //piezas blancas
        mundo->obtenerListaPiezas().agregar(new Torre(BLANCO, Coordenadas(0, 0)));
        mundo->obtenerListaPiezas().agregar(new Caballo(BLANCO, Coordenadas(1, 0)));
        mundo->obtenerListaPiezas().agregar(new Alfil(BLANCO, Coordenadas(2, 0)));
        mundo->obtenerListaPiezas().agregar(new Rey(BLANCO, Coordenadas(3, 0)));
        mundo->obtenerListaPiezas().agregar(new Reina(BLANCO, Coordenadas(4, 0)));
        for (int i = 0; i < 5; ++i) {
            mundo->obtenerListaPiezas().agregar(new Peon(BLANCO, Coordenadas(i, 1)));
        }
        //piezas negras
        mundo->obtenerListaPiezas().agregar(new Reina(NEGRO, Coordenadas(0, 5)));
        mundo->obtenerListaPiezas().agregar(new Rey(NEGRO, Coordenadas(1, 5)));
        mundo->obtenerListaPiezas().agregar(new Alfil(NEGRO, Coordenadas(2, 5)));
        mundo->obtenerListaPiezas().agregar(new Caballo(NEGRO, Coordenadas(3, 5)));
        mundo->obtenerListaPiezas().agregar(new Torre(NEGRO, Coordenadas(4, 5)));
        for (int i = 0; i < 5; ++i) {
            mundo->obtenerListaPiezas().agregar(new Peon(NEGRO, Coordenadas(i, 4)));
        }
        break;
    case 3:
    default:
        mundo = new Mundo();
        // Piezas blancas
        mundo->obtenerListaPiezas().agregar(new Torre(BLANCO, Coordenadas(0, 0)));
        mundo->obtenerListaPiezas().agregar(new Caballo(BLANCO, Coordenadas(1, 0)));
        mundo->obtenerListaPiezas().agregar(new Alfil(BLANCO, Coordenadas(2, 0)));
        mundo->obtenerListaPiezas().agregar(new Reina(BLANCO, Coordenadas(3, 0)));
        mundo->obtenerListaPiezas().agregar(new Rey(BLANCO, Coordenadas(4, 0)));
        mundo->obtenerListaPiezas().agregar(new Alfil(BLANCO, Coordenadas(5, 0)));
        mundo->obtenerListaPiezas().agregar(new Caballo(BLANCO, Coordenadas(6, 0)));
        mundo->obtenerListaPiezas().agregar(new Torre(BLANCO, Coordenadas(7, 0)));
        for (int i = 0; i < 8; ++i) {
            mundo->obtenerListaPiezas().agregar(new Peon(BLANCO, Coordenadas(i, 1)));
        }
        // Piezas negras
        mundo->obtenerListaPiezas().agregar(new Torre(NEGRO, Coordenadas(0, 7)));
        mundo->obtenerListaPiezas().agregar(new Caballo(NEGRO, Coordenadas(1, 7)));
        mundo->obtenerListaPiezas().agregar(new Alfil(NEGRO, Coordenadas(2, 7)));
        mundo->obtenerListaPiezas().agregar(new Reina(NEGRO, Coordenadas(3, 7)));
        mundo->obtenerListaPiezas().agregar(new Rey(NEGRO, Coordenadas(4, 7)));
        mundo->obtenerListaPiezas().agregar(new Alfil(NEGRO, Coordenadas(5, 7)));
        mundo->obtenerListaPiezas().agregar(new Caballo(NEGRO, Coordenadas(6, 7)));
        mundo->obtenerListaPiezas().agregar(new Torre(NEGRO, Coordenadas(7, 7)));
        for (int i = 0; i < 8; ++i) {
            mundo->obtenerListaPiezas().agregar(new Peon(NEGRO, Coordenadas(i, 6)));
        }
        
    }
}
void procesarEntrada(unsigned char key, int x, int y) {
    // Mover el origen y el destino basado en las teclas presionadas
    // Por ejemplo, WASD para mover, Enter para confirmar
    switch (key) {
    case 'w':
        if (seleccionOrigen) origen.set_y(origen.get_y() + 1);
        else destino.set_y(destino.get_y() + 1);
        break;
    case 's':
        if (seleccionOrigen) origen.set_y(origen.get_y() - 1);
        else destino.set_y(destino.get_y() - 1);
        break;
    case 'a':
        if (seleccionOrigen) origen.set_x(origen.get_x() - 1);
        else destino.set_x(destino.get_x() - 1);
        break;
    case 'd':
        if (seleccionOrigen) origen.set_x(origen.get_x() + 1);
        else destino.set_x(destino.get_x() + 1);
        break;
    case 13: // Enter
        if (seleccionOrigen) {
            // Verificar si hay una pieza en la posición origen
            if (mundo->obtenerPiezaEn(origen)) {
                seleccionOrigen = false;
            }
        }
        else {
            // Intentar mover la pieza
            try {
                mundo->moverPieza(origen, destino);
                seleccionOrigen = true;
            }
            catch (const std::exception& e) {
                std::cout << "Movimiento inválido: " << e.what() << std::endl;
                seleccionOrigen = true;
            }
        }
        break;
    default:
        break;
    }
    glutPostRedisplay();
}
void Interfaz::iniciarJuego() {
    mostrarMenu();

    origen = Coordenadas(0, 0);
    destino = Coordenadas(0, 0);        
    seleccionOrigen = true;

        glutKeyboardFunc(procesarEntrada);
}
    // Dibuja el mundo con el tamaño seleccionado
   

