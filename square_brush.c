#include <GL/glut.h>
#include <stdlib.h>

static void demoMenu(int id);
static void myInit(void);
static void myReshape(int x, int y);
static void mouse(int btn, int state, int x, int y);
static void keyboard(unsigned char key, int x, int y);
static void display(void);
static void drawSquare(int x, int y);

GLsizei wh = 500, ww = 500;
GLfloat size = 20.0;

int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(wh, ww);
	glutCreateWindow("Square Brush");

	glutCreateMenu(demoMenu);
	glutAddMenuEntry("increase square size", 1);
	glutAddMenuEntry("decrease square size", 2);
	glutAddMenuEntry("clean", 3);
	glutAttachMenu(GLUT_RIGHT_BUTTON);

	myInit();

	glutReshapeFunc(myReshape);
	glutMouseFunc(mouse);
	glutMotionFunc(drawSquare);
	glutKeyboardFunc(keyboard);
	glutDisplayFunc(display);

	glutMainLoop();
}

static void demoMenu(int id)
{
	if (id == 1) {
		size *= 2.0;
	} else if (id == 2 && size > 1.0) {
		size /= 2.0;
	} else {
		glClearColor(0.0, 0.0, 0.0, 0.0);
		glClear(GL_COLOR_BUFFER_BIT);
		glFlush();
	}
}

static void myInit(void)
{
	glViewport(0, 0, ww, wh);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0.0, (GLdouble)ww, 0.0, (GLdouble)wh, -1.0, 1.0);
	glMatrixMode(GL_MODELVIEW);

	glClearColor(0.0, 0.0, 0.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT);
	glFlush();
}

static void myReshape(int w, int h)
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0.0, (GLdouble)w, 0.0, (GLdouble)h, -1.0, 1.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glViewport(0, 0, w, h);
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);
	glFlush();

	ww = w;
	wh = h;
	
}

static void display(void) {}

static void mouse(int btn, int state, int x, int y)
{
	if (btn == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		drawSquare(x, y);
	}
	if (btn == GLUT_MIDDLE_BUTTON && state == GLUT_DOWN) {
		exit(EXIT_SUCCESS);
	}
}

static void keyboard(unsigned char key, int x, int y)
{
	(void) x;
	(void) y;
	if (key == 'q' || key == 'Q') {
		exit(EXIT_SUCCESS);
	}
}

static void drawSquare(int x, int y)
{
	y = wh - y;

	glColor3ub((char)rand() % 256, (char)rand() % 256, (char)rand() % 256);

	glBegin(GL_POLYGON);
		glVertex2f(x + size, y + size);
		glVertex2f(x - size, y + size);
		glVertex2f(x - size, y - size);
		glVertex2f(x + size, y - size);
	glEnd();

	glFlush();
}
