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
	int filas = tablero.getFilas();
	int columnas = tablero.getColumnas();
	float casillaSize = tablero.getCasillaSize();

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
	
	//no borrar esta linea ni poner nada despues
	glutSwapBuffers();
}
void OnKeyboardDown(unsigned char key, int x_t, int y_t)
{
	//poner aqui el código de teclado
	

	glutPostRedisplay();
}

void OnTimer(int value)
{
//poner aqui el código de animacion
	

	//no borrar estas lineas
	glutTimerFunc(25,OnTimer,0);
	glutPostRedisplay();
}
