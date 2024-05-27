#include "reina.h"
#include "freeglut.h"
#include "ETSIDI.h"


void Reina::dibujarPieza()
{
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, ETSIDI::getTexture("imagenes/reina_blanca.png").id);

    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f); glVertex2f(-0.5f, -0.5f);
    glTexCoord2f(1.0f, 0.0f); glVertex2f(0.5f, -0.5f);
    glTexCoord2f(1.0f, 1.0f); glVertex2f(0.5f, 0.5f);
    glTexCoord2f(0.0f, 1.0f); glVertex2f(-0.5f, 0.5f);
    glEnd();

    glDisable(GL_TEXTURE_2D);
}
