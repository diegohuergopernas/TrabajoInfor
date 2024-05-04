#include "tablero.h"

void Tablero::dibujarTablero() {
    // Tamaño de cada casilla del tablero
    float casillaSize = 1.0f;

    // Dibuja el tablero
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            // Calcula las coordenadas de la esquina superior izquierda de la casilla
            float x = i * casillaSize;
            float y = j * casillaSize;

            // Alterna las casillas de colores
            if ((i + j) % 2 == 0) {
                glColor3f(0.937, 0.847, 0.749); // crema
            }
            else {
                glColor3f(0.364, 0.533, 0.364); // verde
            }

            // Dibuja un cuadrado con las coordenadas calculadas
            glBegin(GL_QUADS);
            glVertex2f(x, y);
            glVertex2f(x + casillaSize, y);
            glVertex2f(x + casillaSize, y + casillaSize);
            glVertex2f(x, y + casillaSize);
            glEnd();
        }
    }
}
