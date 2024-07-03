#pragma once
#include <vector> 
#include "pieza.h"
#include <algorithm>

using std::vector;
class ListaPiezas
{
    std::vector<Pieza*> piezas;

public:
    
    void eliminar(Pieza* p);
    void dibuja() { for (auto p : piezas) p->dibujarPieza(); }
    void agregar(Pieza* pieza) {
        piezas.push_back(pieza);
    }

    Pieza* obtenerPiezaEn(Coordenadas coord);
};
inline void ListaPiezas::eliminar(Pieza* p) {
    piezas.erase(std::remove(piezas.begin(), piezas.end(), p), piezas.end());
    delete p;
}

inline Pieza* ListaPiezas::obtenerPiezaEn(Coordenadas coord) {
    for (Pieza* p : piezas) {
        if (p->getCoordenadas().get_x() == coord.get_x() && p->getCoordenadas().get_y() == coord.get_y()) {
            return p;
        }
    }
    return nullptr;
}