//add some functions to texChecker.cpp
#include <gl/glut.h>
/* Create checkerboard textures */
#define checkImageWidth 64
#define checkImageHeight 64
#define subImageWidth 16
#define subImageHeight 16

#define WIDTH 600
#define HEIGHT 600

static GLuint texName;

static GLubyte checkImage[checkImageHeight][checkImageWidth][4];
static GLubyte subImage[subImageHeight][subImageWidth][4];

void makeCheckImages(void) {
	int i, j, c;
	for (i = 0; i < checkImageHeight; i++) {
		for (j = 0; j < checkImageWidth; j++) {
		//dont know what 0x is for yet
		c = (((i&0x8)==0) ^ ((j&0x8)==0))*255;
		checkImage[i][j][0] = (GLubyte) c;
		checkImage[i][j][1] = (GLubyte) c;
		checkImage[i][j][2] = (GLubyte) c;
		checkImage[i][j][3] = (GLubyte) 255;
		}
 	}
	for (i = 0; i < subImageHeight; i++) {
		for (j = 0; j < subImageWidth; j++) {
		c = (((i&0x4)==0) ^ ((j&0x4)==0))*255;
		subImage[i][j][0] = (GLubyte) c;
		subImage[i][j][1] = (GLubyte) 0;
		subImage[i][j][2] = (GLubyte) 0;
		subImage[i][j][3] = (GLubyte) 255;
		}
	}
}

void init(void) {
	glClearColor(0.0, 0.0, 0.0, 0.0);
	
	makeCheckImages();
	
	glGenTextures(1, &texName);	
	glBindTexture(GL_TEXTURE_2D, texName);	
		
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, checkImageWidth, 
				checkImageHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, checkImage);
}

void display(void) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	glEnable(GL_TEXTURE_2D);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE); 
	//draw the big black white checkboard in checkImage
	glBindTexture(GL_TEXTURE_2D, texName);
	
	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 0.0); glVertex3f(-2.0, -1.0, -2.0);
	glTexCoord2f(0.0, 1.0); glVertex3f(-2.0, 1.0, -2.0);
	glTexCoord2f(1.0, 1.0); glVertex3f(0.0, 1.0, -2.0);
	glTexCoord2f(1.0, 0.0); glVertex3f(0.0, -1.0, -2.0);
	
	glTexCoord2f(0.0, 0.0); glVertex3f(2.5, -1.0, -3.0);
	glTexCoord2f(0.0, 1.0); glVertex3f(2.5, 1.0, -3);
	glTexCoord2f(1.0, 1.0); glVertex3f(0.5, 1.0, -2);
	glTexCoord2f(1.0, 0.0); glVertex3f(0.5, -1.0, -2);
	glEnd();
	
	glFlush();
	
	glDisable(GL_TEXTURE_2D);
}

void keyboard(unsigned char key, int x, int y) {
	switch (key) {
		case 's':
		case 'S':
	//draw a sub image on the old big checkboard
			glBindTexture(GL_TEXTURE_2D, texName);
	//glTexSubImage to replace repeatedly the texture data with new images
	//12: xoffset, 44: yoffset						
			glTexSubImage2D(GL_TEXTURE_2D, 0, 12, 44, 
							subImageWidth, subImageHeight, 
							GL_RGBA, GL_UNSIGNED_BYTE, subImage);
		
			glutPostRedisplay();
			break;
		case 'r':
		case 'R':
	//redraw the big checkboard
			glBindTexture(GL_TEXTURE_2D, texName);
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 
						checkImageWidth, checkImageHeight, 0,
						GL_RGBA, GL_UNSIGNED_BYTE, checkImage);
			glutPostRedisplay();
			break;
		case 27:
			exit(0);
			break;
		default:
			break;
	}
}

void reshape(int w, int h) {
	glViewport(0, 0, (GLsizei) w, (GLsizei) h);
	
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(120, (GLfloat)w / (GLfloat)h, 1.0, 5.0);
	
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

int main(int argc, char *argv[])  {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(WIDTH, HEIGHT);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("replacing texture");
  	init();  
	glutDisplayFunc(display);  			// set display function
	glutReshapeFunc(reshape);	
	glutKeyboardFunc(keyboard);  		// set normal keyboard function
  	glutMainLoop();  					// loop responding to events.
  	return 0;
}
