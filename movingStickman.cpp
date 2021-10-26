#include <GL/glut.h>
#include <cmath>
#include <iostream>

#define PI 3.14
float angle = 0.5;	//goc quay a b
float angleMax = 10;
float tmp = 1.5;	//he so nhan quay a c
float speed = 0.6;	//khoang di chuyen theo truc x
int cntSwing = 0;
int cntSwingMax = 30;	//de han che angle
int cntStep = 0;
int cntStepMax = 300;	//han che khoang di chuyen
bool alreadyLeft = false;

class Point {
public:
	float x;
	float y;
	void draw();		
};

void Point::draw() {
	glVertex2f(x, y);
}

void drawLine(Point a, Point b) {
	glBegin(GL_LINES);
		a.draw();
		b.draw();
	glEnd();
}

Point person[11] = {
	{10, 290},	//dau
	{10, 240},	//vai
	{10, 130},	//eo
	{10, 178},	//diem cui tro thu 1
	{30, 110},	//diem mui tay thu 2
	{10, 178},	//diem cui tro thu 2
	{30, 110},	//diem mui tay thu 2
	{30, 65},	//dau goi thu 1
	{10, 2},	//ban chan thu 1
	{30, 65},	//dau goi thu 2 
	{10, 2},	//ban chan thu 2
};

void rotate(float angle, float tmp, Point a, Point &b, Point &c) {
	int bx = b.x;
	int cx = c.x;
	
	b.x = (b.x - a.x) * cos(angle * PI / 180) 
			- (b.y - a.y) * sin(angle * PI / 180) + a.x;
	b.y = (bx - a.x) * sin(angle * PI / 180) 
			+ (b.y - a.y) * cos(angle * PI / 180) + a.y;
	c.x = (c.x - a.x) * cos(tmp * angle * PI / 180) 
			- (c.y - a.y) * sin(tmp * angle * PI / 180) + a.x;
	c.y = (cx - a.x) * sin(tmp * angle * PI / 180) 
			+ (c.y - a.y) * cos(tmp * angle * PI / 180) + a.y;
}

void init() {
	glClearColor(1.0, 1.0, 1.0, 0.0);
	glColor3f(0.0, 0.0, 0.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-100, 500, 0, 400);
}

void drawMan(float angle) {
	//ve dau
	
}

void display() {
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0.0, 0.0, 0.0);
	glTranslated(speed, 0, 0);
			
	glPointSize(80);
	glLineWidth(7);
	glBegin(GL_POINTS);
		//glVertex2f(0, 0);
		person[0].draw();
	glEnd();	
	
	//ve than
	drawLine(person[0], person[2]);
	
	//ve canh tay 1
	glColor3f(1.0, 0.0, 0.0);
	rotate(angle, tmp, person[1], person[3], person[4]);
	//vai toi cui tro
	drawLine(person[1], person[3]);
	//cui tro toi ban tay
	drawLine(person[3], person[4]);
	
	glColor3f(0.0, 0.0, 0.0);
	//ve canh tay 2
	rotate(-angle, tmp, person[1], person[5], person[6]);
	//vai toi cui tro
	drawLine(person[1], person[5]);
	//cui tro toi ban tay
	drawLine(person[5], person[6]);
	
	
	//ve chan 1
	rotate(angle, tmp, person[2], person[7], person[8]);
	//eo toi dau goi
	drawLine(person[2], person[7]);
	//dau goi toi ban chan
	drawLine(person[7], person[8]);
	
	//ve chan 2
	rotate(-angle, tmp, person[2], person[9], person[10]);
	//eo toi dau goi
	drawLine(person[2], person[9]);
	//dau goi toi ban chan
	drawLine(person[9], person[10]);
	
	cntSwing++;
	if (cntSwing >= cntSwingMax) {
		angle = -angle;
		cntSwing = 0;
	}
	cntStep++;
	if (cntStep >= cntStepMax) {
		speed = -speed;
		cntStep = 0;
		for (int i = 0; i < 11; i++) {
			person[i].x = -person[i].x;
		}
	}
	
	glutSwapBuffers();	
	glutPostRedisplay();
}

void handleKeyboard(int key, int x, int y) {
	/*
	switch(key) {
		case GLUT_KEY_LEFT:
			if (!alreadyLeft) {
				speed = -speed;
				for (int i = 0; i < 11; i++) {
					person[i].x = -person[i].x;
				}
				alreadyLeft = true;
			} 
			drawMan(angle);
			break;
		case GLUT_KEY_RIGHT:
			speed = (speed > 0) ? speed : -speed;
			drawMan(angle);
			if (alreadyLeft) {
				speed = -speed;
				for (int i = 0; i < 11; i++) {
					person[i].x = -person[i].x;
				}
				
			} 
			alreadyLeft = false;
			break;
		default:
			break;
	}                                      

	angle += 5;
	if (angle > angleMax) {
		angle = 0;
	}
	
	glTranslated(speed, 0, 0);
	
	glutPostRedisplay();
	*/
}

int main(int argc, char *argv[]) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(600, 400);
	glutInitWindowPosition(100, 150);
	glutCreateWindow("moving stick man");
	glutDisplayFunc(display);
	glutSpecialFunc(handleKeyboard);	//register for special keyboard
	
	init();
	
	glutMainLoop();
}


