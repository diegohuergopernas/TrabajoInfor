#pragma once
#include "mundo.h"
#include <iostream>

//extern Mundo* mundo;// Declaraci�n de la variable global mundo

class Interfaz {
    Mundo* mundo;
public:
    void mostrarMenu();
    void iniciarJuego();
    Mundo& obtenerMundo() { return *mundo; }
};