#pragma once
#include "mundo.h"
#include <iostream>

//extern Mundo* mundo;// Declaración de la variable global mundo

class Interfaz {
    Mundo* mundo;
public:
    void mostrarMenu();
    void iniciarJuego();
    Mundo& obtenerMundo() { return *mundo; }
};