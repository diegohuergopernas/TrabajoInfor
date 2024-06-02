#include"caballo.h"

void Caballo::dibuja()
{
	glPushMatrix();
	glTranslated(1.1, -0.2, 1);//posicion
	sprite.draw();
}

//plateamiento inicial del algoritmo del movimiento
bool Caballo:: comprobarMovimiento() {
	if (siguiente.get_x() == actual.get_x() + 1 && (siguiente.get_y() == actual.get_y() + 2 || siguiente.get_y() == actual.get_y() - 2))
		return 1;
	else {
		if (siguiente.get_x() == actual.get_x() + 2 && (siguiente.get_y() == actual.get_y() + 1 || siguiente.get_y() == actual.get_y() - 1))
			return 1;
		else {
			if (siguiente.get_x() == actual.get_x() - 1 && (siguiente.get_y() == actual.get_y() + 2 || siguiente.get_y() == actual.get_y() - 2))
				return 1;
			else {
				if (siguiente.get_x() == actual.get_x() - 2 && (siguiente.get_y() == actual.get_y() + 1 || siguiente.get_y() == actual.get_y() - 1))
					return 1;
				else
					return 0;
			}
		}

	}
}