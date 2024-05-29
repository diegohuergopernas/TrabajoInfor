#include "interfaz.h"

void Interfaz::mostrarMenu() {
    int opcion;
    std::cout << "Seleccione el tipo de tablero:\n";
    std::cout << "1. 4�5 con un �nico pe�ns\n";
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
            std::cout << "Opci�n no v�lida, se utilizar� tama�o por defecto (8x8).\n";
            mundo = new Mundo();
            break;
    }

    // Dibuja el mundo con el tama�o seleccionado
    mundo->dibujaMundo();

    delete mundo;
}