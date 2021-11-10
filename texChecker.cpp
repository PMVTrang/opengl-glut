#include <gl/glut.h>
#include <iostream>

/* Create checkerboard texture */
//width = height = 64 bit
//why changing number of bits but size of shape doesnt change?
#define checkImageWidth 64
#define checkImageHeight 64
#define cellSize 8	// = image / 8 because checkboard is 8x8

#define WIDTH 600
#define HEIGHT 600

// this is the texture
static GLubyte checkImage[checkImageHeight][checkImageWidth][4];

static GLuint texName;

// To generate checkboard texture
void makeCheckImage(void) {
	int i, j, c;
	for (i = 0; i < checkImageHeight; i++) {
		for (j = 0; j < checkImageWidth; j++) {
			//each checkboard cell has the size of [cellSize] bits
			//((i&0x8)==0)^((j&0x8)==0) wtf??
			c = (((i & cellSize) == 0)^((j & cellSize)== 0)) * 255;
			checkImage[i][j][0] = (GLubyte) c;		//r
			checkImage[i][j][1] = (GLubyte) c;		//g
			checkImage[i][j][2] = (GLubyte) c;		//b
			checkImage[i][j][3] = (GLubyte) 255;	//a
			
			//texture only works with rgba mode
		}
	}
}
void init(void) {
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glShadeModel(GL_FLAT);		//dont find this necessary
	glEnable(GL_DEPTH_TEST);	//dont find this necessary
	
	makeCheckImage();

	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);	//dont find this necessary
	
	glGenTextures(1, &texName);	//generate texture name (more like id)
	glBindTexture(GL_TEXTURE_2D, texName);	//bind texture obj to texture data
	//this bind is to set parameters and stuff
	
	//con thieu phan texture management but only use 1 texture here so idc
	
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	//mapping filter
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, checkImageWidth, 
				checkImageHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, checkImage);
}
void display(void) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	glEnable(GL_TEXTURE_2D);
	//create texture environment
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE); 
	//bind texture again -> this time we bind the texture to use it
	glBindTexture(GL_TEXTURE_2D, texName);
	//all thing texture-related tasks below will be map to this texture
	
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
	//why cant use GLUT_DOUBLE?
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(WIDTH, HEIGHT);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("checker texture");
  	init();  
	glutDisplayFunc(display);  			// set display function
	glutReshapeFunc(reshape);	
  	glutMainLoop();  					// loop responding to events.
  	return 0;
}
