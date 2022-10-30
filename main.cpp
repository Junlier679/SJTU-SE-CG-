#include <GL/glut.h>
#include <stdlib.h>
#include <windows.h>
#include <math.h>
#include <iostream>
using namespace std;
const GLfloat Pi = 3.1415926536f;

const GLfloat D = 0.7f;
const GLfloat R = 0.4f;
const GLfloat r1 = D * sin(Pi / 10) / sin(Pi * 126 / 180);
const GLfloat r2 = D * sin(Pi / 5) / sin(Pi * 126 / 180);
GLfloat d[5][5];

int starMode = 0;//0:white  1:solid  2:shining
int shiningType = -1;//the light type from the sun

void display(void) {
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT);
	
	GLfloat angelr1 = 3 * Pi / 10,angelD = Pi/2;
	GLfloat angelR1 = 0, angelR2 = Pi / 100;
	GLfloat xr1, yr1, xD, yD, zO;
	GLfloat angeld1 = Pi / 2, angeld3 = Pi / 2 + 3 * Pi / 180, angeld4 = Pi / 2 - 3 * Pi / 180;

	if (starMode == 2) {
		/*draw the shining light from the sun*/
		/*first level*/
		if (shiningType >= 1 && shiningType <= 3) {
			for (int i = 1;i <= 30;++i) {
				if (i % 2 == 0)glColor3f(1.0, 1.0, 0);
				else glColor3f(1.0, 1.0, 1.0);
				glBegin(GL_POLYGON);
				glVertex3f(d[1][1] * cos(angeld1), d[1][1] * sin(angeld1), 0);
				glVertex3f(d[1][3] * cos(angeld4), d[1][3] * sin(angeld4), 0);
				glVertex3f(d[1][2] * cos(angeld1), d[1][2] * sin(angeld1), 0);
				glVertex3f(d[1][3] * cos(angeld3), d[1][3] * sin(angeld3), 0);
				angeld1 += Pi * 12 / 180;
				angeld3 += Pi * 12 / 180;
				angeld4 += Pi * 12 / 180;
				glEnd();
			}
		}
		/*second level*/
		if (shiningType >= 2 && shiningType <= 4) {
			for (int i = 1;i <= 30;++i) {
				if (i % 2 == 0)glColor3f(1.0, 1.0, 0);
				else glColor3f(1.0, 1.0, 1.0);
				glBegin(GL_POLYGON);
				glVertex3f(d[2][1] * cos(angeld1), d[2][1] * sin(angeld1), 0);
				glVertex3f(d[2][3] * cos(angeld4), d[2][3] * sin(angeld4), 0);
				glVertex3f(d[2][2] * cos(angeld1), d[2][2] * sin(angeld1), 0);
				glVertex3f(d[2][3] * cos(angeld3), d[2][3] * sin(angeld3), 0);
				angeld1 += Pi * 12 / 180;
				angeld3 += Pi * 12 / 180;
				angeld4 += Pi * 12 / 180;
				glEnd();
			}
		}

		/*third level*/
		if (shiningType >= 3 && shiningType <= 5) {
			for (int i = 1;i <= 30;++i) {
				if (i % 2 == 0)glColor3f(1.0, 1.0, 0);
				else glColor3f(1.0, 1.0, 1.0);
				glBegin(GL_POLYGON);
				glVertex3f(d[3][1] * cos(angeld1), d[3][1] * sin(angeld1), 0);
				glVertex3f(d[3][3] * cos(angeld4), d[3][3] * sin(angeld4), 0);
				glVertex3f(d[3][2] * cos(angeld1), d[3][2] * sin(angeld1), 0);
				glVertex3f(d[3][3] * cos(angeld3), d[3][3] * sin(angeld3), 0);
				angeld1 += Pi * 12 / 180;
				angeld3 += Pi * 12 / 180;
				angeld4 += Pi * 12 / 180;
				glEnd();
			}
		}

		/*draw the orange sun bihind ths star*/
		glBegin(GL_TRIANGLES);
		glColor3f(1, 0.5, 0);
		for (int i = 1;i <= 200;++i) {
			glVertex3f(R * cos(angelR1), R * sin(angelR1), 0);
			glVertex3f(R * cos(angelR2), R * sin(angelR2), 0);
			glVertex3f(0, 0, 0);
			angelR1 += Pi / 100, angelR2 += Pi / 100;
		}
		glEnd();
	}

	/*draw the star*/
	glBegin(GL_TRIANGLES);
	for (int i = 1;i <= 10;++i) {
		/*set the z height and color first*/
		if (starMode != 0) {
			zO = 0.5f;
			if (i % 2 != 1) {
				glColor3f(0.6,0,0);
			}
			else {
				glColor3f(1, 0, 0);
			}
		}
		else {
			zO = 0.0f;
			glColor3f(1, 1, 1);
		}
		/*set the (x,y) of each line*/
		xr1 = r1 * cos(angelr1), yr1 = r1 * sin(angelr1);
		xD = D * cos(angelD), yD = D * sin(angelD);
		glVertex3f(0, 0, zO), glVertex3f(xr1, yr1, 0), glVertex3f(xD, yD, 0);
		if (i % 2 == 1)angelr1 += Pi * 2 / 5;
		else angelD += Pi * 2 / 5;
	}
	glEnd();

	glFlush();
}

void blingTimer(int val) {
	shiningType = (shiningType+1)%6;
	glutPostRedisplay();
	glutTimerFunc(300, blingTimer, 10);
}

void keyController(unsigned char key,int x,int y) {
	switch (key){
	case 'c':
		starMode = 1;
		glutPostRedisplay();
		break;
	case 's':
		starMode = 2,shiningType = -1;
		d[1][1] = 0.45f, d[2][1] = 0.55f, d[3][1] = 0.7f;
		for (int i = 1;i <= 3;++i) {
			d[i][3] = d[i][1] * sin(Pi * 144 / 180) / sin(Pi * 33 / 180);
			d[i][2] = d[i][3] * sin(Pi * 147 / 180) / sin(Pi * 30 / 180);
		}
		glutTimerFunc(300, blingTimer, 10);
		break;
	default:
		break;
	}
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(600, 600);
	glutInitWindowPosition(200, 200);
	glutCreateWindow("Star shining!");
	glutKeyboardFunc(keyController);
	glutDisplayFunc(display);
	glutMainLoop();
	return 0;
}