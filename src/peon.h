#pragma once
#include "pieza.h"
#include <string>

class Peon : public Pieza {
    ETSIDI::Sprite sprite;
public:
    Peon(Color color, Coordenadas coord)
        : Pieza(PEON, color, coord), sprite(("bin/imagenes/peon_" + std::string(color == BLANCO ? "b" : "n") + ".png").c_str()) {
        sprite.setSize(1.0, 1.0);  // Ajusta el tamaño del sprite para que se vea en 2D
    }

    void dibujarPieza() override {
        glPushMatrix();
        glTranslatef(coordenadas.get_x() - 0.5f, coordenadas.get_y()- 0.5f, 0);
        sprite.draw();
        glPopMatrix();
    }

    bool comprobarMovimiento(Coordenadas destino) override {
        int dx = abs(destino.get_x() - coordenadas.get_x());
        int dy = destino.get_y() - coordenadas.get_y();
        if (color == BLANCO) {
            return (dx == 0 && dy == 1) || (coordenadas.get_y() == 1 && dx == 0 && dy == 2);
        }
        else {
            return (dx == 0 && dy == -1) || (coordenadas.get_y() == 6 && dx == 0 && dy == -2);
        }
    }
};