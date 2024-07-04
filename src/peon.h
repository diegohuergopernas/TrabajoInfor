#pragma once
#include "pieza.h"
#include <string>
extern Mundo* mundo;
class Peon : public Pieza {
    
public:
    Peon(Color color, Coordenadas coord)
        : Pieza(PEON, color, coord), sprite(("bin/imagenes/peon_" + std::string(color == BLANCO ? "b" : "n") + ".png").c_str()) {
        sprite.setSize(1.0, 1.0);  // Ajusta el tamaño del sprite para que se vea en 2D
    }

    void dibujarPieza() override {
        glPushMatrix();
        glTranslatef(coordenadas.get_x() - 0.5f, coordenadas.get_y() - 0.5f, 0.01);
        sprite.draw();
        glPopMatrix();
    }

    bool comprobarMovimiento(Coordenadas destino) override {
        int dx = abs(destino.get_x() - coordenadas.get_x());
        int dy = destino.get_y() - coordenadas.get_y();
        if (color == BLANCO) {
            if (dx == 1 && dy == 1 && mundo->obtenerPiezaEn(destino) && mundo->obtenerPiezaEn(destino)->getColor() != color) {
                return true; //captura en diagonal
            }
            return (dx == 0 && dy == 1) || (coordenadas.get_y() == 1 && dx == 0 && dy == 2);//movimiento normal
        }
        else {
            if (dx == 0 && dy == -1 && mundo->obtenerPiezaEn(destino) && mundo->obtenerPiezaEn(destino)->getColor() != color) {
                return true;//captura en diagonal
            }
            return (dx == 0 && dy == -1) || (coordenadas.get_y() == 6 && dx == 0 && dy == -2);//movimiento normal
        }
    }
private:
    ETSIDI::Sprite sprite;
};
