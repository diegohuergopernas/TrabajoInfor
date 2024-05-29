#include "interfaz.h"

void Interfaz::mostrarMenu() {
    int opcion;
    std::cout << "Seleccione el tipo de tablero:\n";
    std::cout << "1. 4×5 con un único peóns\n";
    std::cout << "2. Speed Chess\n";
    std::cout << "Ingrese una opcion: ";
    std::cin >> opcion;

    Mundo* mundo;
    switch(opcion) {
        case 1:
            mundo = new Mundo(4, 5);
            break;
        case 2:
            mundo = new Mundo(5, 6);
            break;
        default:
            std::cout << "Opción no válida, se utilizará tamaño por defecto (8x8).\n";
            mundo = new Mundo();
            break;
    }

    // Dibuja el mundo con el tamaño seleccionado
    mundo->dibujaMundo();

    delete mundo;
}