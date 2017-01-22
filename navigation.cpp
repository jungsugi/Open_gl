
#include <gl/glut.h>
#include <gl/gl.h>
#include <gl/glu.h>
#include <math.h>
#include<stdlib.h>
#include<cstdio>
#include<iostream>
#include<stdio.h>

using namespace std;

GLfloat color,scale, xt, yt, zt, angle;
GLdouble delta = 0.0;   //시점의 회전을 담당하는 각도변수
GLdouble theta = 45.0;
GLdouble tran = 0.0, tran2 = 0.0;   //확대와 축소를 담당하는 변수.?

GLint turn=0;
GLfloat xx = 1.0;
GLfloat yy = 1.0;
GLfloat zz = 1.0;

GLfloat oldx = 0.0;
GLfloat oldz = 0.0;
GLfloat s_turn, s_tran, s_tran2;

void barn() {
	glBegin(GL_POLYGON);
	glColor3f(0.0, 0.0, 0.5);
	glVertex3f(0, 0, 0);
	glVertex3f(0, 0, 1);
	glVertex3f(0, 1, 1);
	glVertex3f(0, 1, 0);
	glEnd();
	
	glBegin(GL_POLYGON);
	glColor3f(0.7, 0.0, 0.0);
	glVertex3f(0.5, 1.5, 0);
	glVertex3f(0, 1, 0);
	glVertex3f(0, 1, 1);
	glVertex3f(0.5, 1.5, 1);
	glEnd();
	
	glBegin(GL_POLYGON);
	glColor3f(0.8, 0.0, 0.0);
	glVertex3f(1, 1, 0);
	glVertex3f(0.5, 1.5, 0);
	glVertex3f(0.5, 1.5, 1);
	glVertex3f(1, 1, 1);
	glEnd();

	glBegin(GL_POLYGON);
	glColor3f(0.0, 0.0, 0.4);
	glVertex3f(1, 0, 0);
	glVertex3f(1, 1, 0);
	glVertex3f(1, 1, 1);
	glVertex3f(1, 0, 1);
	glEnd();

	glBegin(GL_POLYGON);
	glColor3f(0.0, 0.0, 0.6);
	glVertex3f(0, 0, 0);
	glVertex3f(1, 0, 0);
	glVertex3f(1, 0, 1);
	glVertex3f(0, 0, 1);
	glEnd();

	glBegin(GL_POLYGON);
	glColor3f(0.0, 0.0, 0.4);
	glVertex3f(0, 0, 1);
	glVertex3f(1, 0, 1);
	glVertex3f(1, 1, 1);
	glVertex3f(0.5, 1.5, 1);
	glVertex3f(0, 1, 1);
	glEnd();

	glBegin(GL_POLYGON);
	glColor3f(0.0, 0.0, 0.3);
	glVertex3f(0, 0, 0);
	glVertex3f(0, 1, 0);
	glVertex3f(0.5, 1.5, 0);
	glVertex3f(1, 1, 0);
	glVertex3f(1, 0, 0);
	glEnd();
}

void instanceBarn(GLfloat scale, GLfloat xt, GLfloat yt, GLfloat zt,GLfloat angle) {
	glTranslatef(xt, yt, zt);
	glScalef(scale, scale, scale);
	glRotatef(angle, 0, 1, 0);
	barn();
}

void MyDisplay() { //도형을 그리는 함수
	glViewport(0, 0, 1000, 1000);
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0.0, 0.0, 0.5);


	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(theta, 1.0, 1.0, 119.0);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(tran2, 0.0, tran);
	glRotatef(turn, 0, 1, 0);
	gluLookAt(0.2, 0.7, 0.2, 0, 0.0, -100.0, 0.0, 1.0, 0.0);
	glPushMatrix();
	glBegin(GL_POLYGON);
	glColor3f(0.0, 0.5, 0.0);
	glVertex3f(-10, 0, -10);
	glVertex3f(10, 0, -10);
	glVertex3f(10, 0, 10);
	glVertex3f(-10, 0, 10);
	glEnd();
	instanceBarn(1.0,3.0,0.0,3.0,30);
	instanceBarn(1.0, 5.0, 0.0, 3.0, 0);
	instanceBarn(1.0, 5.0, 0.0, 1.0, 60);
	instanceBarn(1.2, -3.0, 0.0, -3.0,0);
	instanceBarn(1.5, 7.0, 0.0, -7.0,90);
	instanceBarn(1.5, -7.0, 0.0, 7.0,0);
	glPopMatrix();

	glFlush();
}

void MyKeyboard(unsigned char KeyPressed, int X, int Y) {
	// 시점의 회전을 위한 delta값을 키보드에 의해 조정함
	if (KeyPressed == 's') {
		theta = theta + 1.0;
	}
	else if (KeyPressed == 'd') {
		theta = theta - 1.0;
	}
	else if (KeyPressed == 'o') {
		tran = tran + 0.1;
	}
	else if (KeyPressed == 'l') {
		tran = tran - 0.1;
	}
	else if (KeyPressed == 'k') {
		tran2 = tran2 + 0.1;
	}
	else if (KeyPressed == ';') {
		tran2 = tran2 - 0.1;
	}
	else if (KeyPressed == 'i') {
		turn=turn-1;
	}
	else if (KeyPressed == 'p') {
		turn =turn+1;
	}
	else if (KeyPressed == 'v') {
		s_turn = turn;
		s_tran = tran;
		s_tran2 = tran2;
	}
	else if (KeyPressed == 'b') {
		turn = s_turn;
		tran = s_tran;
		tran2 = s_tran2;
	}
	else if (KeyPressed == 27) {
		turn = 0;
		tran = 0;
		tran2 = 0;
	}
	else if (KeyPressed == 'q') {
		exit(0);
	}
	else if(KeyPressed == 32){ //스페이스바

	}
	else if(KeyPressed){  //백스페이스
	
	}

	glutPostRedisplay();
}

int main(int argc, char** argv) {

/*	int Key;
	Key=getchar();
	printf("%d",Key);  */

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB);
	glutInitWindowSize(1000, 1000);
	glutInitWindowPosition(300, 200);
	glutCreateWindow("OpenGL Drawing Example");
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glOrtho(-3.0, 3.0, -3.0, 3.0, -3.0, 3.0);
	glutDisplayFunc(MyDisplay);
	glutKeyboardFunc(MyKeyboard);
	glutMainLoop();

	return 0;
}