// KHONG THE TUONG TAC DUOC VOI CA TEXTURE???? BI LOI BINDING MAYBE???
#include <cstdlib>
#include <iostream>
#include <fstream>

#include <GL/glut.h>
#include <GL/glext.h>

#define checkImageWidth 64
#define checkImageHeight 64
#define cellSize 8

using namespace std;

// Globals.
static unsigned int texture[2]; // Array of texture indices.
static unsigned char chessboard[checkImageWidth][checkImageHeight][3]; // Storage for chessboard image.
static float angle = 0.0; // Angle to rotate textured square.
static int cur_tex_id = 0; // Currently displayed texture id.

// Struct of bitmap file.
struct BitMapFile {
   int sizeX;	//width
   int sizeY;	//height
   unsigned char *data;  // 3D image  (width, height, rgb)
};

// Routine to read a bitmap file.
// Works only for uncompressed bmp files of 24-bit color.
BitMapFile *getBMPData(string filename) {
   BitMapFile *bmp = new BitMapFile;
   unsigned int size, offset, headerSize;
  
   // Read input file name.
   ifstream infile(filename.c_str(), ios::binary);
 
   // Get the starting point of the image data.
   infile.seekg(10);
   infile.read((char *) &offset, 4); 
   
   // Get the header size of the bitmap.
   infile.read((char *) &headerSize,4);

   // Get width and height values in the bitmap header.
   infile.seekg(18);
   infile.read( (char *) &bmp->sizeX, 4);
   infile.read( (char *) &bmp->sizeY, 4);

   // Allocate buffer for the image.
   size = bmp->sizeX * bmp->sizeY * 24;
   bmp->data = new unsigned char[size];

   // Read bitmap data.
   infile.seekg(offset);
   infile.read((char *) bmp->data , size);
   
   // Reverse color from bgr to rgb.
   int temp;
   for (int i = 0; i < size; i += 3)
   { 
      temp = bmp->data[i];
	  bmp->data[i] = bmp->data[i+2];
	  bmp->data[i+2] = temp;
   }

   return bmp;
}

// Load external textures.
void loadExternalTextures() {
	// Local storage for bmp image data.
	BitMapFile *image;
	
	// Load the texture.
	image = getBMPData("texImg_launch.bmp"); 
	
	// TODO: Activate texture index texture[0] with bind function
	glGenTextures(1, &texture[0]);	
	glBindTexture(GL_TEXTURE_2D, texture[0]);
	
	// TODO: Set texture parameters for wrapping.
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
 	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// TODO: Set texture parameters for filtering.
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	
	// TODO: Specify an image as the texture to be bound with the currently active texture index.
	//Tai sao bao la texture only works with rgba
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, image->sizeX, 
				image->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, image->data);
}

// Routine to load a program-generated image as a texture. 
void loadProceduralTextures() {
	// TODO: Activate texture index texture[1] with bind function
	glGenTextures(1, &texture[1]);	
	glBindTexture(GL_TEXTURE_2D, texture[1]);
	
	// TODO: Set texture parameters for wrapping.
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
 	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	
	// TODO: Set texture parameters for filtering.
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	
	// TODO: Specify an image as the texture to be bound with the currently active texture index.
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, checkImageWidth, 
				checkImageHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, chessboard);
}

// Create 64 x 64 RGB image of a chessboard.
void createChessboard() {
	// TODO: create chessboard texture programmatically
	int i, j, c;
	for (i = 0; i < checkImageHeight; i++) {
		for (j = 0; j < checkImageWidth; j++) {
			c = (((i & cellSize) == 0)^((j & cellSize)== 0)) * 255;
			chessboard[i][j][0] = (GLubyte) c;		//r
			chessboard[i][j][1] = (GLubyte) c;		//g
			chessboard[i][j][2] = (GLubyte) c;		//b			
		}
	}
}

// Initialization routine.
void init() {
   glClearColor(0, 0, 0, 0.0); 

   // Create texture index array.
   glGenTextures(2, texture); 

   // Load external texture.
   loadExternalTextures();
   
   // Generate and load procedural texture
   createChessboard();
   loadProceduralTextures();

   // Turn on OpenGL texturing.
   glEnable(GL_TEXTURE_2D);

   // Specify how texture values combine with current surface color values.
   glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE); 
}

// Drawing routine.
void display() {
   glClear(GL_COLOR_BUFFER_BIT);
   
   glRotatef(angle, 0.0, 1.0, 0.0); 

   // Activate a texture corresponding to cur_tex_id.
   glBindTexture(GL_TEXTURE_2D, texture[cur_tex_id]);        

   // TODO: Create a polygon with texture coordinates mapped to the vertices
	glBegin(GL_POLYGON);
	glTexCoord2f(0.0, 0.0); glVertex3f(-10, -10, 0);
	glTexCoord2f(0.0, 1.0); glVertex3f(-10, 10, 0);
	glTexCoord2f(1.0, 1.0); glVertex3f(10, 10, 0);
	glTexCoord2f(1.0, 0.0); glVertex3f(10, -10, 0);
	glEnd();
	
	glFlush();
	   
	glutSwapBuffers();	
}

// OpenGL window reshape routine.
void reshape(int w, int h) {
   glViewport(0, 0, (GLsizei)w, (GLsizei)h);
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   glFrustum(-5.0, 5.0, -5.0, 5.0, 5.0, 100.0);
   gluLookAt(0.0, 0.0, 20.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
}

// Keyboard input processing routine.
void keyInput(unsigned char key, int x, int y) {
   switch(key) {
      case ' ':  // press Space key
         // TODO: toggle cur_tex_id from 0 to 1 and vice versa
         //cur_tex_id = !cur_tex_id;
		if (cur_tex_id) {
			cur_tex_id = 0;
		} else {
			cur_tex_id = 1;
		}
		//glBindTexture(GL_TEXTURE_2D, texture[cur_tex_id]); 
		break;
      case 127:  // press Delete key
		 // TODO: reset angle
         break;
      default:
         break;
   }
   glutPostRedisplay();
}

// Callback routine for non-ASCII key entry.
void specialKeyInput(int key, int x, int y) {
	switch(key) {
		case GLUT_KEY_LEFT:
			// TODO: rotate the polygon to the left
			angle = -20;
			break;
		case GLUT_KEY_RIGHT:
			// TODO: rotate the polygon to the right
			angle = 20;
			break;
		default:
        	break;
	}
   	glutPostRedisplay();
}

// Routine to output interaction instructions to the C++ window.
void printInteraction(void)
{
   cout << "Interaction:" << endl;
   cout << "Press the left and right arrow keys to rotate the square." << endl
	    << "Press space to toggle between textures." << endl
        << "Press delete to reset." << endl;
}

// Main routine.
int main(int argc, char **argv) 
{
   printInteraction();
   glutInit(&argc, argv);
   glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
   glutInitWindowSize(500, 500);
   glutInitWindowPosition(100, 100);
   glutCreateWindow("texture from image.cpp");
   
   init();
   
   glutDisplayFunc(display);
   glutReshapeFunc(reshape);
   glutKeyboardFunc(keyInput);
   glutSpecialFunc(specialKeyInput);
   
   glutMainLoop();
   return 0; 
}

