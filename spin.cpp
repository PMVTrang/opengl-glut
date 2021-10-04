#include <gl/glut.h>
#include <iostream>

static GLfloat spin = 0.0;

static int WIN_SIZE = 500;

//the origin's position in window's coordinate
//aka from the top-left corner
int xo, yo;
int magic = 10;


void init(void){
	xo = 250;
	yo = 250;
	
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glShadeModel(GL_FLAT);
}

void drawTriangle() {
	glColor3f(1.0, 1.0, 1.0);

	glBegin(GL_TRIANGLES);	
		glVertex2f(-5, -5); 
		glVertex2f(-5, 5); 
		glVertex2f(5, 0); 
	glEnd();
}

/*
* x, y : mouse's current position
* 10 - arbitrary number lmao bias 
* because triangle's size is small
*/
bool checkInsideTriangle (int x, int y) {
	if (xo - magic <= x && x <= xo + magic 
		&& yo - magic <= y && y <= yo + magic){
			return true;
	}
	return false;
}

void display() {
	glClear(GL_COLOR_BUFFER_BIT);
	
	glPushMatrix();
	glRotatef(spin, 0.0, 0.0, 1.0);
	glColor3f(1.0, 0.0, 0.0);
	glRectf(-45, -45, 45, 45);
	glPopMatrix();
	
	drawTriangle();
	
	glutSwapBuffers();
}

void spinDisplay(void) {
	spin = spin + 2.0;
	if (spin > 360.0)
	spin = spin - 360.0;
	glutPostRedisplay();
}

void reshape(int w, int h) {
	glViewport(0, 0, (GLsizei) w, (GLsizei) h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-250, 250, -250, 250, -1.0, 1.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

/*
* To handle mouse click/unclick event
* x, y - mouse position from top-left corner
*/
void mouse(int button, int state, int x, int y) {
	switch (button) {
		case GLUT_LEFT_BUTTON:
			if (state == GLUT_DOWN) {
				glutIdleFunc(spinDisplay);
			}
			break;
		case GLUT_RIGHT_BUTTON:
			if (state == GLUT_DOWN) {
				glutIdleFunc(NULL);
			}	
			break;
		default:
			break;
	}
	
}

/*
* To translate the origin
* x, y - mouse position
* xt, yt - the amount to move origin according to the viewport ortho or sth idk
*/
void translate(int x, int y) {
	int xt = 0, yt = 0;
	//x in the 1st or 4th quarter
	if (x >= WIN_SIZE / 2) {
		xt = x - xo;
		if (y <= WIN_SIZE / 2) { //the 1st quarter
			yt = yo - y;
		} else { //the 4th
			yt = -(y - yo);
		}
	} else {
		xt = -(xo - x);
		if (y <= WIN_SIZE / 2) { //the 2nd quarter
			yt = yo - y;
		} else { //the 3rd
			yt = -(y - yo);
		}
	}
	glTranslatef(xt, yt, 0.0);
	glutPostRedisplay();
	//update the position to mouse's 
	xo = x;
	yo = y;	
}

void mouseDrag (int x, int y) {
	std::cout<< "drag x = " << x << " y = " << y << std::endl;  
	translate(x, y);
}


 int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(WIN_SIZE, WIN_SIZE); 
	glutInitWindowPosition(200, 100);
	glutCreateWindow(argv[0]);
	init();
	glutDisplayFunc(display); 
	glutReshapeFunc(reshape); 
	glutMouseFunc(mouse);
	glutMotionFunc(mouseDrag);
	glutMainLoop();
 return 0;
}
