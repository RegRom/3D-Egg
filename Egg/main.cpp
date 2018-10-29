/*************************************************************************************/

//  Szkielet programu do tworzenia modelu sceny 3-D z wizualizacj¹ osi 
//  uk³adu wspó³rzednych

/*************************************************************************************/

#include <windows.h>
#include <gl/gl.h>
#include <gl/glut.h>
#include <cmath>
#include <time.h>
#include <iostream>
#include <Windows.h>

const GLint N = 50;
typedef GLfloat point3[3];
static GLfloat theta[] = { 0.0, 0.0, 0.0 };
const GLdouble PI = 3.141592653589793238463;
GLint model;

struct Point {
	GLfloat x;
	GLfloat y;
	GLfloat z;
	GLfloat r;
	GLfloat g;
	GLfloat b;
};
Point surface[N][N];

float myRand()
{
	return static_cast <GLfloat> (rand()) / static_cast <GLfloat> (RAND_MAX);
}

void spinEgg()
{
	for (size_t i = 0; i < 3; i++)
	{
		theta[i] -= 0.5;
		if (theta[i] > 360.0) theta[0] -= 360.0;
	}
	Sleep(6);
	glutPostRedisplay(); //odœwie¿enie zawartoœci aktualnego okna
}

void Axes(void)
{

	point3  x_min = { -5.0, 0.0, 0.0 };
	point3  x_max = { 5.0, 0.0, 0.0 };
	// pocz¹tek i koniec obrazu osi x

	point3  y_min = { 0.0, -5.0, 0.0 };
	point3  y_max = { 0.0,  5.0, 0.0 };
	// pocz¹tek i koniec obrazu osi y

	point3  z_min = { 0.0, 0.0, -5.0 };
	point3  z_max = { 0.0, 0.0,  5.0 };
	//  pocz¹tek i koniec obrazu osi y

	glColor3f(1.0f, 0.0f, 0.0f);  // kolor rysowania osi - czerwony
	glBegin(GL_LINES); // rysowanie osi x

	glVertex3fv(x_min);
	glVertex3fv(x_max);

	glEnd();

	glColor3f(0.0f, 1.0f, 0.0f);  // kolor rysowania - zielony
	glBegin(GL_LINES);  // rysowanie osi y

	glVertex3fv(y_min);
	glVertex3fv(y_max);

	glEnd();

	glColor3f(0.0f, 0.0f, 1.0f);  // kolor rysowania - niebieski
	glBegin(GL_LINES); // rysowanie osi z

	glVertex3fv(z_min);
	glVertex3fv(z_max);

	glEnd();

}

// Funkcja okreœlaj¹ca co ma byæ rysowane (zawsze wywo³ywana gdy trzeba
// przerysowaæ scenê)

void generatePoints()
{
	for (size_t i = 0; i < N; i++)
	{
		for (size_t j = 0; j < N; j++)
		{
			// Zmienne wykorzystywane w równaniach
			GLfloat u = (GLfloat)i / (N - 1);
			GLfloat v = (GLfloat)j / (N - 1);
			// Implementacja równañ podanych w instrukcji
			surface[i][j].x = (-(90 * pow(u, 5)) + (225 * pow(u, 4)) - (270 * pow(u, 3)) + (180 * pow(u, 2)) - 45 * u) * cos(PI * v);
			surface[i][j].y = (160 * pow(u, 4)) - (320 * pow(u, 3)) + (160 * pow(u, 2));
			surface[i][j].z = (-(90 * pow(u, 5)) + (225 * pow(u, 4)) - (270 * pow(u, 3)) + (180 * pow(u, 2)) - 45 * u) * sin(PI * v);
			// Losowe kolory dla punktu
			surface[i][j].r = myRand();
			surface[i][j].b = myRand();
			surface[i][j].g = myRand();
		}
	}
}

void drawEgg(int model)
{
	if (model == 1)
	{
		for (size_t i = 0; i < N; i++)
		{
			for (size_t j = 0; j < N; j++)
			{
					glBegin(GL_POINTS);
					glColor3f(surface[i][j].r, surface[i][j].g, surface[i][j].b);
					glVertex3f(surface[i][j].x, surface[i][j].y - 5.0f, surface[i][j].z);
					glEnd();
			}
		}
	}
	else if (model == 2)
	{
		for (size_t i = 0; i < N; i++)
		{
			for (size_t j = 0; j < N; j++)
			{
				glBegin(GL_LINE_STRIP);
				glColor3f(surface[i][j].r, surface[i][j].g, surface[i][j].b);
				glVertex3f(surface[i][j].x, surface[i][j].y - 5.0f, surface[i][j].z);

				glColor3f(surface[(i + 1) % N][(j + 1) % N].r, surface[(i + 1) % N][(j + 1) % N].g, surface[(i + 1) % N][(j + 1) % N].b);
				glVertex3f(surface[(i + 1) % N][(j + 1) % N].x, surface[(i + 1) % N][(j + 1) % N].y - 5.0f, surface[(i + 1) % N][(j + 1) % N].z);
				glEnd();
			}
		}
	}
	else if (model == 3)
	{
		for (size_t i = 0; i < N; i++)
		{
			for (size_t j = 0; j < N; j++)
			{
				glBegin(GL_TRIANGLES);
				glColor3f(surface[i][j].r, surface[i][j].g, surface[i][j].b);
				glVertex3f(surface[i][j].x, surface[i][j].y - 5.0f, surface[i][j].z);
				glColor3f(surface[i][(j + 1) % N].r, surface[i][(j + 1) % N].g, surface[i][(j + 1) % N].b);
				glVertex3f(surface[i][(j + 1) % N].x, surface[i][(j + 1) % N].y - 5.0f, surface[i][(j + 1) % N].z);
				glColor3f(surface[(i + 1) % N][(j + 1) % N].r, surface[(i + 1) % N][(j + 1) % N].g, surface[(i + 1) % N][(j + 1) % N].b);
				glVertex3f(surface[(i + 1) % N][(j + 1) % N].x, surface[(i + 1) % N][(j + 1) % N].y - 5.0f, surface[(i + 1) % N][(j + 1) % N].z);
				glEnd();

				glBegin(GL_TRIANGLES);
				glColor3f(surface[i][j].r, surface[i][j].g, surface[i][j].b);
				glVertex3f(surface[i][j].x, surface[i][j].y - 5.0f, surface[i][j].z);
				glColor3f(surface[(i + 1) % N][j].r, surface[(i + 1) % N][j].g, surface[(i + 1) % N][j].b);
				glVertex3f(surface[(i + 1) % N][j].x, surface[(i + 1) % N][j].y - 5.0f, surface[(i + 1) % N][j].z);
				glColor3f(surface[(i + 1) % N][(j + 1) % N].r, surface[(i + 1) % N][(j + 1) % N].g, surface[(i + 1) % N][(j + 1) % N].b);
				glVertex3f(surface[(i + 1) % N][(j + 1) % N].x, surface[(i + 1) % N][(j + 1) % N].y - 5.0f, surface[(i + 1) % N][(j + 1) % N].z);
				glEnd();
			}
		}
	}
}

void RenderScene(void)
{

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	// Czyszczenie okna aktualnym kolorem czyszcz¹cym

	glLoadIdentity();
	// Czyszczenie macierzy bie¿¹cej

	Axes();
	// Narysowanie osi przy pomocy funkcji zdefiniowanej wy¿ej

	glRotatef(theta[0], 1.0, 0.0, 0.0);
	glRotatef(theta[1], 0.0, 1.0, 0.0);
	glRotatef(theta[2], 0.0, 0.0, 1.0);

	drawEgg(model);

	glFlush();
	// Przekazanie poleceñ rysuj¹cych do wykonania

	glutSwapBuffers();
	//

}

void keys(unsigned char key, int x, int y)
{
	if (key == 'p') model = 1;
	if (key == 'w') model = 2;
	if (key == 's') model = 3;

	RenderScene(); // przerysowanie obrazu sceny
}

// Funkcja ustalaj¹ca stan renderowania
void MyInit(void)
{

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	// Kolor czyszc¹cy (wype³nienia okna) ustawiono na czarny

}

void ChangeSize(GLsizei horizontal, GLsizei vertical)
{

	GLfloat AspectRatio;
	// Deklaracja zmiennej AspectRatio  okreœlaj¹cej proporcjê
	// wymiarów okna 

	if (vertical == 0)  // Zabezpieczenie przed dzieleniem przez 0

		vertical = 1;

	glViewport(0, 0, horizontal, vertical);
	// Ustawienie wielkoœciokna okna widoku (viewport)
	// W tym przypadku od (0,0) do (horizontal, vertical)  

	glMatrixMode(GL_PROJECTION);
	// Prze³¹czenie macierzy bie¿¹cej na macierz projekcji 

	glLoadIdentity();
	// Czyszcznie macierzy bie¿¹cej            

	AspectRatio = (GLfloat)horizontal / (GLfloat)vertical;
	// Wyznaczenie wspó³czynnika  proporcji okna
	// Gdy okno nie jest kwadratem wymagane jest okreœlenie tak zwanej
	// przestrzeni ograniczaj¹cej pozwalaj¹cej zachowaæ w³aœciwe
	// proporcje rysowanego obiektu.
	// Do okreslenia przestrzeni ograniczj¹cej s³u¿y funkcja
	// glOrtho(...)            

	if (horizontal <= vertical)

		glOrtho(-7.5, 7.5, -7.5 / AspectRatio, 7.5 / AspectRatio, 10.0, -10.0);

	else

		glOrtho(-7.5*AspectRatio, 7.5*AspectRatio, -7.5, 7.5, 10.0, -10.0);

	glMatrixMode(GL_MODELVIEW);
	// Prze³¹czenie macierzy bie¿¹cej na macierz widoku modelu                                    

	glLoadIdentity();
	// Czyszcenie macierzy bie¿¹cej

}

// G³ówny punkt wejœcia programu. Program dzia³a w trybie konsoli
int main(void)
{
	srand(time(NULL));
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(500, 500);
	glutCreateWindow("Jajko");

	generatePoints();

	glutDisplayFunc(RenderScene);
	glutReshapeFunc(ChangeSize);
	glutIdleFunc(spinEgg);
	glutKeyboardFunc(keys);

	MyInit();

	glEnable(GL_DEPTH_TEST);
	// W³¹czenie mechanizmu usuwania powierzchni niewidocznych

	glutMainLoop();
	// Funkcja uruchamia szkielet biblioteki GLUT

	return 0;
}