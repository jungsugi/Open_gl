#include <gl/glut.h>
#include <gl/gl.h>
#include <gl/glu.h>
#include <math.h>
#include <stdio.h>

GLUquadricObj *c;   //quadric object를 가리키는 GLU object
static GLfloat base, lower, upper;
GLfloat eye1 = 5, eye2, eye3 = 5, upX,upY,upZ, zoom = 45, asp=3.0;
GLfloat zoom_dex = 0;
GLint see;
GLfloat camera_front[], camera_left[], camera_right[];

 
void Base() {
	glColor3f(1.0, 0, 0);
	glTranslatef(0, -1, 0);
	glRotatef(-90, 1, 0, 0); //x축을 -90도 회전
	glRotatef(base, 0, 0, 1);  //z축을 base각도 만큼 회전
	gluCylinder(c, 0.4, 0.4, 0.3, 8, 5);   //c=곡면객체, base:아랫면지름, top:윗면지름, height:높이, slices:쪽수, stacks:판수 
}

void Base2(){
	glColor3f(1.0, 0, 0);
	glTranslatef(0, -1, 0);
	glRotatef(-90, 1, 0, 0); //x축을 -90도 회전
	glRotatef(0, 0, 0, 1);  //z축을 base각도 만큼 회전
	gluCylinder(c, 0.4, 0.4, 0.3, 8, 5);   //c=곡면객체, base:아랫면지름, top:윗면지름, height:높이, slices:쪽수, stacks:판수 
}

void lower_arm() {
	glColor3f(0, 0, 1.0);
	glRotatef(base, 0, 1,0); 
	glTranslatef(0, -0.7, 0); 
	glRotatef(lower, 0, 0, 1); 
	glTranslatef(0, 0.5, 0); 
	glScalef(0.2, 1, 0.2); 
	glutSolidCube(1);
}

void lower_arm2() {
	glColor3f(0, 0, 1.0);
	glRotatef(0, 0, 1,0); 
	glTranslatef(0, -0.7, 0); 
	glRotatef(lower, 0, 0, 1); 
	glTranslatef(0, 0.5, 0); 
	glScalef(0.2, 1, 0.2); 
	glutSolidCube(1);
}

void upper_arm() {
	glColor3f(0, 1.0, 0);
	glRotatef(base, 0, 1, 0);
	glTranslatef(0, -0.7, 0);
	glRotatef(lower, 0, 0, 1);
	glTranslatef(0, 1.0, 0);
	glRotatef(upper,0, 0, 1);
	glTranslatef(0, 0.4, 0);
	glScalef(0.2, 0.8, 0.2);
	glutSolidCube(1);
}

void upper_arm2() {
	glColor3f(0, 1.0, 0);
	glRotatef(0, 0, 1, 0);
	glTranslatef(0, -0.7, 0);
	glRotatef(lower, 0, 0, 1);
	glTranslatef(0, 1.0, 0);
	glRotatef(upper,0, 0, 1);
	glTranslatef(0, 0.4, 0);
	glScalef(0.2, 0.8, 0.2);
	glutSolidCube(1);
}

void robot(){
	glColor3f(0.5, 1.0, 0.0);
	glBegin(GL_QUADS); //삼각형 그리기.
	glVertex3f(0.2, 0.0, 0.2);
	glVertex3f(0.2, 0.0, -0.2);
	glVertex3f(-0.2, 0.0, -0.2);
	glVertex3f(-0.2, 0.0, 0.2);

	glEnd();
	glFlush();
}

void MyDisplay() { //도형을 그리는 함수

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //두 버퍼를 지운다.

	glViewport(0, 0, 250, 250);  //x,y, width,height
	glMatrixMode(GL_PROJECTION); //투영 행렬 설정.-> 카메라의 종류 및 줌 선택. 
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); //face: GL_FRONT, GL_BACK, GL_FRONT_AND_ACK  /mode: GL_POINT, GL_LINE,GL_FLL
	glPushMatrix();
	glLoadIdentity(); //좌표계를 초기화시킨다.
	glOrtho(-3.0, 3.0, -3.0, 3.0, -3.0, 3.0);
	gluLookAt(0, 1, 0, 0, 0, 0, 0, 0, 1);  //(카메라중심위치, 대상의중심위치, 바라보는 방향) 
	glPushMatrix();
	Base2();
	glPopMatrix();
	glPushMatrix();
	lower_arm2();
	glPopMatrix();
	glPushMatrix();
	upper_arm2();
	glPopMatrix();
	
	glPushMatrix();
	glRotatef(base, 0, 1,0);
	glPushMatrix();
	glTranslatef(1.0 + zoom_dex, 0 , 0);
	robot();
	glPopMatrix();
	
	glPopMatrix();
	

	glViewport(250, 0, 250, 250);
	glPushMatrix();
	glLoadIdentity();
	glOrtho(-3.0, 3.0, -3.0, 3.0, -3.0, 3.0);
	gluLookAt(1, 0, 0, 0, 0.0, 0, 0, 1, 0);
	glPushMatrix();
	Base();
	glPopMatrix();
	glPushMatrix();
	lower_arm();
	glPopMatrix();
	glPushMatrix();
	upper_arm();
	glPopMatrix();
	glPopMatrix();


	glViewport(0, 250, 500, 250);	
	glLoadIdentity();
	gluPerspective(zoom, 0.7, 0.1, 100.0);  //gluPerspective(45.0f, (GLfloat)width / (GLfloat)height, 1.0f, 100.0f);
	glMatrixMode(GL_MODELVIEW);
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glPushMatrix();
	gluLookAt(eye1, asp, eye3, 0, 0.0, 0, 0, 0.1, 0);
	glPushMatrix();
	Base();
	glPopMatrix();
	glPushMatrix();
	lower_arm();
	glPopMatrix();
	glPushMatrix();
	upper_arm();
	glPopMatrix();
	glPopMatrix();

	glutSwapBuffers();
}

void MyKeyboard(unsigned char KeyPressed, int X, int Y) {
	if (KeyPressed == 'o') {
		base +=2;
	}
	else if (KeyPressed == 'p') {
		base -=2;
	}
	else if (KeyPressed == 'a') {
		if (lower <= 88)
			lower += 2;
	}
	else if (KeyPressed == 's') {
		if (lower >= -88)
			lower -= 2;
	}
	else if (KeyPressed == 'q') {
		if (upper <= 88)
			upper += 2;
	}
	else if (KeyPressed == 'w') {
		if (upper >= -88)
			upper -= 2;
	}
	else if (KeyPressed == 'z') {
		zoom += 0.5;
		zoom_dex += 0.01;
	}
	else if (KeyPressed == 'x') {
		zoom -= 0.5;
		zoom_dex -= 0.01;
	}
	else if (KeyPressed == 'c') {
		asp += 0.1;
	}
	else if (KeyPressed == 'v') {
		asp -= 0.1;
	}

	glutPostRedisplay();
}

void init(void) {
	c = gluNewQuadric();  //로봇암 생성.
	gluQuadricDrawStyle(c, GLU_LINE); //로봇암 그리는 스타일
	base = 0; upper = 0; lower = 0;  //변환 값 0으로 초기화.
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);    
 	glEnable(GL_DEPTH_TEST);   //A물체를 그리고, 그 위에 B물체를 그렸을때 먼저 그린 A가 B를 가리는 현상이 나타날 수 있다.
							   //위 메서드를 사용하면 정상적으로 먼저 그린 A보다 나중에 그린 B가 위쪽에 그려지게 된다.
}

int main(int argc, char** argv) {
	glutInit(&argc, argv); 
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(300, 200);
	glutCreateWindow("OpenGL Drawing Example");
	glutDisplayFunc(MyDisplay);
	glutKeyboardFunc(MyKeyboard);
	init();
	glutMainLoop();

	return 0;
}