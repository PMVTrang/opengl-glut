#include <gl/glut.h>

//WIDTH 800
//HEIGHT 600

void init()  {
 	glClearColor(0.0, 0.0, 0.0, 0.0);  // set clear color to black
	glMatrixMode(GL_PROJECTION);  // projection matrix
	glLoadIdentity();  // set current matrix to identity matrix
	
	//UPDATE WIDTH HEIGHT
	gluOrtho2D(0, 800, 0, 600);	//origin at bottom left
	//gluOrtho2d(-400, 400, -300, 300);	//origin at center
	
	glMatrixMode(GL_MODELVIEW);  // model view matrix
	glLoadIdentity();
}

//still dont find this useful
/*
void reshape(int w, int h) {
    glViewport(0, 0, (GLsizei) w, (GLsizei) h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, 800, 600, 0);
    //gluOrtho2D(1, 1, 1, 1);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}
*/


void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glClearColor(0.0, 0.0, 0.0, 0.0);

	glColor3f(1,1,1);
	
	//draw stuff here
	
	glFlush();
    glutSwapBuffers();
    glutPostRedisplay();
}




// Use mouse event to animate
void mouse(int button, int state, int x, int y) {
	switch (button) {
		case GLUT_LEFT_BUTTON:
			break;
		case GLUT_RIGHT_BUTTON:
			break;
		default:
			break;
	}
}

// To get mouse current coordinate 

void mouseMotion(int x, int y) {
}

//Only catch events of "normal" keyboard: numbers, letters
void keyboard(unsigned char key, int x, int y) {
	switch (key) {
		case 32:  // space key
			break;
		//other cases
		default:
			break;
	}
}

// Only catch events of arrow keys, F keys
void specialKeyboard (int key, int x, int y) {
	switch(key) {
		case GLUT_KEY_LEFT:
			break;
		case GLUT_KEY_RIGHT:
			break;
		//other cases
		default:
			break;
	}   
}

int main(int argc, char *argv[])  {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	//UPDATE WIDTH HEIGHT
	glutInitWindowSize(800, 600);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Aardvark");
  	init();  
	glutDisplayFunc(display);  			// set display function
	glutMouseFunc(mouse);  				// set mouse function
	glutMotionFunc(mouseMotion);		//or passiveMotionFunc() google di
	glutKeyboardFunc(keyboard);  		// set normal keyboard function
	glutSpecialFunc(specialKeyboard);	// set special keyboard func
	//glutReshapeFunc(reshape);			// reshape function
  	glutMainLoop();  					// loop responding to events.
  	return 0;
}


