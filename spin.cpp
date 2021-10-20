#include <gl/glut.h>
#include <windows.h>
#include <stdlib.h>

static GLfloat spin = 0.0;  // 0 -> 360
static bool spinning = false;  // flag for spinning
static GLint r=255, g=255, b=255;
static bool mouseDownTriangle = false;

struct Point {
	int x;
	int y;
};
// triangle points
Point t1 = {90, 95}, t2 = {100, 110}, t3 = {108, 92};
// square points
Point s1 = {75.0, 75.0}, s2 = {125.0, 125.0};
Point cur = {0, 0};
Point pre = {0, 0};

void init()  {
 	glClearColor(0.0, 0.0, 0.0, 0.0);  // set clear color to black
	glMatrixMode(GL_PROJECTION);  // projection matrix
	glLoadIdentity();  // set current matrix to identity matrix
	glOrtho(0, 400.0, 0, 400.0, -1.0, 1.0);
	glMatrixMode(GL_MODELVIEW);  // model view matrix
	glLoadIdentity();
}

float area(Point p1, Point p2, Point p3) {
	float a = ((p2.x - p1.x) * (p3.y - p1.y) - (p3.x - p1.x) * (p2.y - p1.y)) / 2.0;
  	return (a > 0) ? a : -a;
} 

bool inTriangle(int x, int y) {    
   Point p = {x, y};
   float A = area (t1, t2, t3);
   float A1 = area (p, t2, t3);
   float A2 = area (t1, p, t3);
   float A3 = area (t1, t2, p);
   return (A == A1 + A2 + A3); 
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    int dx = cur.x - pre.x;
    int dy = cur.y - pre.y;
    
    t1.x += dx; t1.y += dy;
    t2.x += dx; t2.y += dy;
    t3.x += dx; t3.y += dy;
    
    s1.x += dx; s1.y += dy;
    s2.x += dx; s2.y += dy;
    float mx = s1.x + (s2.x - s1.x)/2.0;
	float my = s1.y + (s2.y - s1.y)/2.0;
    
    // draw square spinning around its center
	glPushMatrix();  // remember where you are
		glTranslatef(mx, my, 0);
		glRotatef(spin, 0.0, 0.0, 1.0);
		glTranslatef(-mx, -my, 0);
		
		glColor3ub(r, g, b);  // set color state to white
		glRectf(s1.x, s1.y, s2.x, s2.y);  // draw rectangle 
	glPopMatrix();  // go back to where you were

	// draw triangle with 3 points
	glColor3f(0.2, 0.5, 0.3);
	glBegin(GL_TRIANGLES);
		glVertex2f(t1.x, t1.y);
		glVertex2f(t2.x, t2.y);
		glVertex2f(t3.x, t3.y);
	glEnd();
	// update previous mouse point
	pre.x = cur.x;
	pre.y = cur.y;
	glutSwapBuffers();
}

void spinDisplay() {  // update spin value
	spin = spin + 2.0;
	if (spin > 360.0)
	spin = spin - 360.0;
	Sleep(1);
	glutPostRedisplay();  // call display after update spin value
}

// Use mouse event to animate
void mouse(int button, int state, int x, int y) {
	y = 400 - y;  // convert mouse's y to window's y
	switch (button) {
		case GLUT_LEFT_BUTTON:
			if (state == GLUT_DOWN) {
				if (inTriangle(x, y)) {
					cur.x = pre.x = x;
					cur.y = pre.y = y;
					mouseDownTriangle = true;
				} else {
					mouseDownTriangle = false;
				}
				glutIdleFunc(spinDisplay);  // set idle callback
				spinning = true;
			} else if (state == GLUT_UP) {
				mouseDownTriangle = false;
			}
			break;
		case GLUT_RIGHT_BUTTON:
			if (state == GLUT_DOWN) {
				glutIdleFunc(NULL);
				spinning = false;
			}
			break;
		default:
			break;
	}
}

void mouseMotion(int x, int y) {
	y = 400 - y;  // convert mouse's y to window's y
	if (mouseDownTriangle == true) {
		pre.x = cur.x;
		pre.y = cur.y;
		// update current mouse position
		cur.x = x;
		cur.y = y;
	}
}

// Use keyboard event to animate
void keyboard(unsigned char key, int x, int y) {
	switch (key) {
		case 32:  // space key
			if (!spinning) {
				glutIdleFunc(spinDisplay);
				spinning = true;
			} else {
				glutIdleFunc(NULL);
				spinning = false;
			}
			changeColor();
			break;
		default:
			break;
	}
}
int main(int argc, char *argv[])  {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(400, 400);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Lab_02");
  	init();  // Initialize some things.
	glutDisplayFunc(display);  // set display function
	glutMouseFunc(mouse);  // set mouse function
	glutMotionFunc(mouseMotion);
	glutKeyboardFunc(keyboard);  // set keyboard function
  	glutMainLoop();  // loop responding to events.
  	return 0;
}

