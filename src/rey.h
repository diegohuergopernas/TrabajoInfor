#pragma once
#include "pieza.h"
#include <string>

class Rey : public Pieza {
    ETSIDI::Sprite sprite;
public:
    Rey(Color color, Coordenadas coord)
        : Pieza(REY, color, coord), sprite(("bin/imagenes/rey_" + std::string(color == BLANCO ? "b" : "n") + ".png").c_str()) {
        sprite.setSize(1.5, 1.5);
    }

    void dibujarPieza() override {
        glPushMatrix();
        glTranslatef(coordenadas.get_x() - 0.5f, 0, coordenadas.get_y() - 0.5f);
        sprite.draw();
        glPopMatrix();
    }

    bool comprobarMovimiento(Coordenadas destino) override {
        int dx = abs(destino.get_x() - coordenadas.get_x());
        int dy = abs(destino.get_y() - coordenadas.get_y());
        return (dx <= 1 && dy <= 1);
    }
};