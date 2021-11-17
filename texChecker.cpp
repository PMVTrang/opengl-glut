#include <gl/glut.h>
#include <iostream>
#include <cstdlib> 	//srand
#include <ctime>

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
	srand(time(NULL));
	int i, j, c;
	int tmp1, tmp2, tmp3;
	//draw colorati checkboard
	for (int i = 0; i < checkImageHeight; i++) {
		for (int j = 0; j < checkImageWidth; j++) {
			//if the cell is black
			if (!((i & cellSize) == 0)^((j & cellSize)== 0)) {
				checkImage[i][j][0] = 0;		//r
				checkImage[i][j][1] = 0;		//g
				checkImage[i][j][2] = 0;		//b
			} else {
				//the first pixel in the non-black cell
				if (i % cellSize == 0 && j % cellSize == 0) {
					tmp1 = rand() % 256;
					tmp2 = rand() % 256;
					tmp3 = rand() % 256;
					
					checkImage[i][j][0] = (GLubyte) tmp1;		//r
					checkImage[i][j][1] = (GLubyte) tmp2;		//g
					checkImage[i][j][2] = (GLubyte) tmp3;		//b
				} else {
					//lay mau cua o neighbor
					if (i % cellSize == 0) {
						checkImage[i][j][0] = checkImage[i][j - 1][0];		//r
						checkImage[i][j][1] = checkImage[i][j - 1][1];		//g
						checkImage[i][j][2] = checkImage[i][j - 1][2];		//b
					} else {
						checkImage[i][j][0] = checkImage[i - 1][j][0];		//r
						checkImage[i][j][1] = checkImage[i - 1][j][1];		//g
						checkImage[i][j][2] = checkImage[i - 1][j][2];		//b
					}
				}
			}
			checkImage[i][j][3] = (GLubyte) 255;	//a
			
		}
	}
	
	/*draw simple black and white checkboard
	for (i = 0; i < checkImageHeight; i++) {
		for (j = 0; j < checkImageWidth; j++) {
			c = (((i & cellSize) == 0)^((j & cellSize)== 0)) * 255;
			checkImage[i][j][0] = (GLubyte) c;		//r
			checkImage[i][j][1] = (GLubyte) c;		//g
			checkImage[i][j][2] = (GLubyte) c;		//b
			checkImage[i][j][3] = (GLubyte) 255;	//a
			
		}
	}
	*/
}

void init(void) {
	glClearColor(0.0, 0.0, 0.0, 0.0);
	//glShadeModel(GL_FLAT);		//dont find this necessary
	//glEnable(GL_DEPTH_TEST);	//dont find this necessary
	
	makeCheckImage();

	//glPixelStorei(GL_UNPACK_ALIGNMENT, 1);	//dont find this necessary
	
	glGenTextures(1, &texName);	//generate texture name (more like id)
	glBindTexture(GL_TEXTURE_2D, texName);	//bind texture obj to texture data
	//this bind is to set parameters and stuff
	
	//con thieu phan texture management but only use 1 texture here so idc
	
	//texture wrapping
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
	//bottom-left, upper-left, upper-right, bottom-right -> counterclock wise
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
