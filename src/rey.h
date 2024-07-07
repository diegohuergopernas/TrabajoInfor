#pragma once
#include "pieza.h"
#include <string>

class Rey : public Pieza {
    ETSIDI::Sprite sprite;
    bool movido = FALSE;
public:
    Rey(Color color, Coordenadas coord)
        : Pieza(REY, color, coord), sprite(("bin/imagenes/rey_" + std::string(color == BLANCO ? "b" : "n") + ".png").c_str()) {
        sprite.setSize(1.0, 1.0);
    }

    void dibujarPieza() override {
        glPushMatrix();
        glTranslatef(coordenadas.get_x() - 0.5f, coordenadas.get_y() - 0.5f, 0.01);
        sprite.draw();
        glPopMatrix();
    }

    bool comprobarMovimiento(Coordenadas destino) override {
        int dx = abs(destino.get_x() - coordenadas.get_x());
        int dy = abs(destino.get_y() - coordenadas.get_y());
        return (dx <= 1 && dy <= 1) || (dx == 2 && dy == 0 && !movido);//se ha añadido un nuevo atributo para saber si se ha movido con anterioridad 
    }                                                                   //y poder ejecurar el movimiento de enroque

    bool haSidoMovido() const {
        return movido;
    }

    void setMovido(bool valor) {
        movido = valor;
    }
};