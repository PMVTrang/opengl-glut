#include <windows.h>
#include <GL/glut.h>

#define MAX_N 100

float** A;
float** B;
int numberOfVertices;
float t = 0;
float dt = 0.02;

void init() {
	// TODO
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glColor3f(1.0, 1.0, 1.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, 800, 0, 600);
}

void createShape() {
    numberOfVertices = 8;
    
    A = new float*[MAX_N];
    B = new float*[MAX_N];
	for (int i = 0; i < MAX_N; ++i) {
	    A[i] = new float[2];
	    B[i] = new float[2];
    }
	// Than ngoi nha        
    A[0][0] = 600.0; A[0][1] = 300.0;
    A[1][0] = 500.0; A[1][1] = 335.0;
    A[2][0] = 310.0; A[2][1] = 400.0;
    A[3][0] = 310.0; A[3][1] = 400.0;
    A[4][0] = 185.0; A[4][1] = 350.0;
    A[5][0] = 40.0;  A[5][1] = 300.0;
    A[6][0] = 40.0;  A[6][1] = 40.0; 
    A[7][0] = 600.0;  A[7][1] = 40.0;       
	
	// Than oto
    B[0][0] = 600.0; B[0][1] = 300.0;
    B[1][0] = 450.0; B[1][1] = 300.0;
    B[2][0] = 400.0; B[2][1] = 350.0;
    B[3][0] = 200.0; B[3][1] = 350.0;
    B[4][0] = 150.0; B[4][1] = 300.0;
    B[5][0] = 40.0; B[5][1] = 300.0;
    B[6][0] = 40.0; B[6][1] = 200.0;
    B[7][0] = 600.0; B[7][1] = 200.0;        
}

float tweening(float a, float b, float t) {
	// TODO: tweening formula: p = (1-t)a + t*b
	return (1 - t) * a + t * b;
}

void drawTweening(float** A, float** B, int n, float t) {
    // TODO: drawing 1 little tweening motion with parameter "t"
    glBegin(GL_LINE_LOOP);
    for (int i = 0; i < n; i++) {
    	glVertex2f(tweening(A[i][0], B[i][0], t), 
					tweening(A[i][1], B[i][1], t));
    }
    glEnd();
    
}

void display(void) {
	// TODO: looping the whole tweening process back and forth
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0, 1.0, 1.0);
	
	t += dt;
	if (t >= 1 || t <= 0) {
		dt *= -1;
	}	
	
	drawTweening(A, B, numberOfVertices, t);
	
	glutSwapBuffers();
	glutPostRedisplay();
	//Use sleep or inscrease dt to slow down the animation
	Sleep(10); 
}

int main(int argc, char** argv) {
	// TODO: main
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(800, 600);
	glutInitWindowPosition(100, 150);
	glutCreateWindow("tweening");
	createShape();
	glutDisplayFunc(display);
	
	init();
	
	glutMainLoop();
}

