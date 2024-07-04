#include "freeglut.h"
#include "ETSIDI.h"
#include "mundo.h"
#include "interfaz.h"
#include "listapiezas.h"
#include "tablero.h"

//NO HACE FALTA LLAMARLAS EXPLICITAMENTE
void OnDraw(void); //esta funcion sera llamada para dibujar
void OnTimer(int value); //esta funcion sera llamada cuando transcurra una temporizacion
void OnKeyboardDown(unsigned char key, int x, int y); //cuando se pulse una tecla	
// Función para dibujar un rectángulo (cursor) en la posición del cursor
int cursorX = 0; // Posición del cursor en el eje X
int cursorY = 0; // Posición del cursor en el eje Y
void drawCursor(float x, float y, float size) {
	glDisable(GL_DEPTH_TEST);
	glLineWidth(5.0); // Grosor de la línea
	glColor3f(1.0, 0.0, 0.0); // Color rojo
	glBegin(GL_LINE_LOOP);
	glVertex2f(x, y);
	glVertex2f(x + size, y);
	glVertex2f(x + size, y + size);
	glVertex2f(x, y + size);
	glTranslatef(0.0, 0.0, 0.1);
	glEnd();
	glLineWidth(1.0); // Restablecer grosor de línea al valor predeterminado
	glEnable(GL_DEPTH_TEST);
}

Mundo* mundo;
Tablero tablero;
Interfaz interfaz;

int main(int argc,char* argv[])
{
	//Inicializar el gestor de ventanas GLUT
	//y crear la ventana
	glutInit(&argc, argv);
	glutInitWindowSize(800,600);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutCreateWindow("MiJuego");

	//habilitar luces y definir perspectiva
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHTING);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_COLOR_MATERIAL);	
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective( 40.0, 800/600.0f, 0.1, 150);

	//Registrar los callbacks
	glutDisplayFunc(OnDraw);
	glutTimerFunc(25,OnTimer,0);//le decimos que dentro de 25ms llame 1 vez a la funcion OnTimer()
	glutKeyboardFunc(OnKeyboardDown);

	//POSIBLE INICIALIZACION
	

	// Inicializa interfaz
	interfaz.iniciarJuego();
	mundo = &interfaz.obtenerMundo();		
	
	//pasarle el control a GLUT,que llamara a los callbacks
	glutMainLoop();	

	return 0;   
}

void OnDraw(void)
{
	//Borrado de la pantalla	
   	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//Para definir el punto de vista
	glMatrixMode(GL_MODELVIEW);	
	glLoadIdentity();
	// Ajustar la cámara para ver el tablero desde arriba
	int filas = mundo->getTablero().getFilas();
	int columnas = mundo->getTablero().getColumnas();
	float casillaSize = mundo->getTablero().getCasillaSize();

	// Calcula el centro del tablero
	float centerX = columnas * casillaSize / 2.0f;
	float centerY = filas * casillaSize / 2.0f;

	// Ajusta la posición de la cámara según el tamaño del tablero
	float eyeX = centerX;
	float eyeY = centerY;
	float eyeZ = (filas > columnas ? filas : columnas) * casillaSize;  // La distancia de la cámara depende del tamaño del tablero

	gluLookAt(eyeX, eyeY, eyeZ + 7,  // Posición del ojo
		centerX, centerY, 0.0,      // Hacia qué punto mira
		0.0, 1.0, 0);      // Definimos hacia arriba (eje Y).0); // Vector de arriba (negativo en Z para que mire desde arriba)


	//interfaz.mostrarMenu();
	if (mundo) {
		mundo->dibujaMundo();
	}
	// Dibujar el cursor de selección
	drawCursor(cursorX * casillaSize, cursorY * casillaSize, casillaSize);
	
	//no borrar esta linea ni poner nada despues
	glutSwapBuffers();
}
void OnKeyboardDown(unsigned char key, int x_t, int y_t)
{

	// Implementación de teclas en interfaz
	glutPostRedisplay();
}

void OnTimer(int value)
{
//poner aqui el código de animacion
	

	//no borrar estas lineas
	glutTimerFunc(25,OnTimer,0);
	glutPostRedisplay();
}
