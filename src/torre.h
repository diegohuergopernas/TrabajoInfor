#pragma once
#include "pieza.h"
#include <string>
class Torre :public Pieza  {
	ETSIDI::Sprite sprite;
    bool movido = FALSE;
public:
	Torre(Color color, Coordenadas coord)
		: Pieza(TORRE, color, coord), sprite(("bin/imagenes/torre_" + std::string(color == BLANCO ? "b" : "n") + ".png").c_str()) {
		sprite.setSize(1.0, 1.0);
	}
	void dibujarPieza()override {
        glPushMatrix();
        glTranslatef(coordenadas.get_x() - 0.5f, coordenadas.get_y() - 0.5f, 0.01);
        sprite.draw();
        glPopMatrix();
    }

    bool comprobarMovimiento(Coordenadas destino) override {
        int dx = abs(destino.get_x() - coordenadas.get_x());
        int dy = abs(destino.get_y() - coordenadas.get_y());
        return (dx == 0 || dy == 0);
    }
    bool haSidoMovido() const {
        return movido;
    }

    void setMovido(bool valor) {
        movido = valor;
    }
   
};