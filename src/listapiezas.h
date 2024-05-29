#pragma once
#include <vector> 
#include "pieza.h" 
using std::vector;
class ListaPiezas
{
	vector<Pieza*> lista;
public:
	void agregar(Pieza* p) { lista.push_back(p); }
	void dibuja() { for (auto p : lista)p->dibujarPieza(); }
};