#include "interfaz.h"

// Variables globales para manejo del juego
extern Mundo* mundo;  // Declaración de la variable global

Coordenadas origen, destino;
bool seleccionOrigen = true;

void Interfaz::mostrarMenu() {
    int opcion;
    std::cout << "Seleccione el tipo de tablero:\n";
    std::cout << "1. 4x5 con un único peons\n";
    std::cout << "2. Speed Chess\n";
    std::cout << "3. Tablero estandar\n";
    std::cout << "Ingrese una opcion: ";
    std::cin >> opcion;

    Mundo* mundo;
    switch (opcion) {
    case 1:
        mundo = new Mundo(4, 5);
        break;
    case 2:
        mundo = new Mundo(5, 6);
        break;
    case 3:
    default:
        std::cout << "Opción no válida, se utilizará tamaño por defecto (8x8).\n";
        mundo = new Mundo();
        break;
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
   

