#include <windows.h>
#include <cmath>
#include <GL/glut.h>
# define PI 3.14
 
GLfloat x_old = 200; //x=200 == radius, de tranh net keo ve tu x_old den diem ve
GLfloat y_old = 00;
static int level = 10; //level odd ? petal = level : petal = 2 x level
static int radius = 200;
 
void init() {
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glShadeModel(GL_FLAT);
}
 
void drawRose(GLfloat degree) {
	GLfloat rad = degree * PI / 180;
	int x_new = radius * cos(level * rad) * cos(rad);
	int y_new = radius * cos(level * rad) * sin(rad);
	glVertex2f(x_old, y_old);
    glVertex2f(x_new, y_new);
	x_old = x_new;
	y_old = y_new;	
}
 
void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    
    glClearColor(0.0, 0.0, 0.0, 0.0);
    
    glBegin(GL_LINE_STRIP);
	    for (int i = 0; i <= 360; i++) {
	    	drawRose(i);
	    }
    glEnd();
	
    glFlush();
    glutSwapBuffers();
}
 
void reshape(int w, int h) {
    glViewport(0, 0, (GLsizei) w, (GLsizei) h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-400, 400, 300, -300);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}
 
int main(int argc, char *argv[]) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(800, 600);
	glutInitWindowPosition(100, 100);
    glutCreateWindow("rose");
    init();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutMainLoop();
    return EXIT_SUCCESS;
}
