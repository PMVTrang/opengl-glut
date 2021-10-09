#include <windows.h>
#include <cmath>
#include <GL/glut.h>
# define PI 3.14
 
GLfloat x_old = 400;
GLfloat y_old = 300;
static int level = 2; // initialize the level to draw
 
void init() {
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glShadeModel(GL_FLAT);
}
 
void drawKoch(GLfloat degree, GLfloat length, GLfloat n) {
    GLfloat rad = degree * PI / 180;
    GLfloat x_new = x_old + length * cos(rad);
    GLfloat y_new = y_old + length * sin(rad);
    if (n == 0) {
    	//opengl la state machine, gap cau lenh la switch state
    	//khong can 2 cau nay o right below glbegin
    	//o giua la ok
    	glVertex2f(x_old, y_old);
    	glVertex2f(x_new, y_new);
    	x_old = x_new;
    	y_old = y_new;
    }
    else {
    	n -= 1;
    	drawKoch(degree, length / 3, n);
    	drawKoch(degree + 60, length / 3, n);
    	drawKoch(degree - 60, length / 3, n);
    	drawKoch(degree, length / 3, n);
    }
}
 
void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    
    glClearColor(1.0, 0.0, 0.0, 0.0);
    glBegin(GL_LINES);
    
    // TODO call drawKoch() 3 times for 3 sides
		drawKoch(0, 200, level);
		drawKoch(-120, 200, level);
		drawKoch(120, 200, level);
	glEnd();
	
    glFlush();
    glutSwapBuffers();
}
 
void reshape(int w, int h) {
    glViewport(0, 0, (GLsizei) w, (GLsizei) h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, 800, 600, 0);
    //gluOrtho2D(1, 1, 1, 1);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}
 
int main(int argc, char *argv[]) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(800, 600);
	glutInitWindowPosition(100, 100);
    glutCreateWindow("Lab_03");
    init();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutMainLoop();
    return EXIT_SUCCESS;
}
