#include "interfaz.h"

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
    void Interfaz::iniciarJuego() {
        mostrarMenu();

        origen = Coordenadas(0, 0);
        destino = Coordenadas(0, 0);
        seleccionOrigen = true;

        glutKeyboardFunc(procesarEntrada);
    }
    // Dibuja el mundo con el tamaño seleccionado
    mundo->dibujaMundo();

    delete mundo;

}