/* -- INCLUDE FILES ------------------------------------------------------ */
#include <windows.h>
#include <GL/glut.h>
#include <fstream>
#include <iostream>
#include <string>
/* ----------------------------------------------------------------------- */
using namespace std;

const string FILE_NAME = "dinosaur.dat";

class Piece {
	public:
		int numOfPoints;
		float* x;
		float* y;
		
		Piece();
		void setPiece(int nop);
};

class FileHelper {
	public:
		void ReadData(string, Piece* &pieces, int& numOfPieces);
};

Piece::Piece() {
	this->numOfPoints = 0;
}

void Piece::setPiece(int nop) {
	this->numOfPoints = nop;
	this->x = new float[this->numOfPoints];
	this->y = new float[this->numOfPoints];
}

void FileHelper::ReadData(string fileName, Piece* &pieces, int& numOfPieces) {
	ifstream inStream;
	inStream.open(fileName.c_str());
	
	if (!inStream) {
		cout << "Can not open this file" << endl;
	} else {
		inStream >> numOfPieces;
		pieces = new Piece[numOfPieces];
		int nPoint;
		
		for (int i = 0; i < numOfPieces; i++) {
			inStream >> nPoint;
			pieces[i].setPiece(nPoint);
			for (int j = 0; j < nPoint; j++) {
				inStream >> pieces[i].x[j] >> pieces[i].y[j];
				
			}
		}
	}
	inStream.close();
}

Piece* pieces;
int numOfPieces = 0;

// Use FileHelper to open and read the data file
void readData() {
	FileHelper file;
	file.ReadData(FILE_NAME, pieces, numOfPieces);
}

void init()  {
	glClearColor(0, 0, 0, 0);
	gluOrtho2D(-400, 800, 0, 600);
	//glShadeModel(GL_FLAT);
}

void display()  {
	readData();
	
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1, 1, 1);
    
    for (int i = 0; i < numOfPieces; i++) {
    	glBegin(GL_LINE_STRIP);
    		for (int j = 0; j < pieces[i].numOfPoints; j++) {
    			glVertex2f(pieces[i].x[j], pieces[i].y[j]);
    		}
    	glEnd();
    }
	
	for (int i = 0; i < numOfPieces; i++) {
    	glBegin(GL_LINE_STRIP);
    		for (int j = 0; j < pieces[i].numOfPoints; j++) {
    			glVertex2f((-0.5) * pieces[i].x[j], 0.5 * pieces[i].y[j]);
    		}
    	glEnd();
    }
	
    glFlush();
    glutSwapBuffers();
	
	// TODO extra: draw 2 dinosaurs opposite to each other (head to head)
	// 1 dinosaur is haft the size of the other
}

int main(int argc, char *argv[])  {
	// TODO
	glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(800, 600);
	glutInitWindowPosition(100, 100);
    glutCreateWindow("dinosaur");
    
	init();
    
    glutDisplayFunc(display);
    glutMainLoop();
    return EXIT_SUCCESS;
}


