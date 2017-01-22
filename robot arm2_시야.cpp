#include <gl/glut.h>
#include <gl/gl.h>
#include <gl/glu.h>
#include <math.h>
#include <stdio.h>

GLUquadricObj *c;   //quadric object�� ����Ű�� GLU object
static GLfloat base, lower, upper;
GLfloat eye1 = 5, eye2, eye3 = 5, upX,upY,upZ, zoom = 45, asp=3.0;
GLfloat zoom_dex = 0;
GLint see;
GLfloat camera_front[], camera_left[], camera_right[];

 
void Base() {
	glColor3f(1.0, 0, 0);
	glTranslatef(0, -1, 0);
	glRotatef(-90, 1, 0, 0); //x���� -90�� ȸ��
	glRotatef(base, 0, 0, 1);  //z���� base���� ��ŭ ȸ��
	gluCylinder(c, 0.4, 0.4, 0.3, 8, 5);   //c=��鰴ü, base:�Ʒ�������, top:��������, height:����, slices:�ʼ�, stacks:�Ǽ� 
}

void Base2(){
	glColor3f(1.0, 0, 0);
	glTranslatef(0, -1, 0);
	glRotatef(-90, 1, 0, 0); //x���� -90�� ȸ��
	glRotatef(0, 0, 0, 1);  //z���� base���� ��ŭ ȸ��
	gluCylinder(c, 0.4, 0.4, 0.3, 8, 5);   //c=��鰴ü, base:�Ʒ�������, top:��������, height:����, slices:�ʼ�, stacks:�Ǽ� 
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
	glBegin(GL_QUADS); //�ﰢ�� �׸���.
	glVertex3f(0.2, 0.0, 0.2);
	glVertex3f(0.2, 0.0, -0.2);
	glVertex3f(-0.2, 0.0, -0.2);
	glVertex3f(-0.2, 0.0, 0.2);

	glEnd();
	glFlush();
}

void MyDisplay() { //������ �׸��� �Լ�

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //�� ���۸� �����.

	glViewport(0, 0, 250, 250);  //x,y, width,height
	glMatrixMode(GL_PROJECTION); //���� ��� ����.-> ī�޶��� ���� �� �� ����. 
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); //face: GL_FRONT, GL_BACK, GL_FRONT_AND_ACK  /mode: GL_POINT, GL_LINE,GL_FLL
	glPushMatrix();
	glLoadIdentity(); //��ǥ�踦 �ʱ�ȭ��Ų��.
	glOrtho(-3.0, 3.0, -3.0, 3.0, -3.0, 3.0);
	gluLookAt(0, 1, 0, 0, 0, 0, 0, 0, 1);  //(ī�޶��߽���ġ, ������߽���ġ, �ٶ󺸴� ����) 
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
	c = gluNewQuadric();  //�κ��� ����.
	gluQuadricDrawStyle(c, GLU_LINE); //�κ��� �׸��� ��Ÿ��
	base = 0; upper = 0; lower = 0;  //��ȯ �� 0���� �ʱ�ȭ.
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);    
 	glEnable(GL_DEPTH_TEST);   //A��ü�� �׸���, �� ���� B��ü�� �׷����� ���� �׸� A�� B�� ������ ������ ��Ÿ�� �� �ִ�.
							   //�� �޼��带 ����ϸ� ���������� ���� �׸� A���� ���߿� �׸� B�� ���ʿ� �׷����� �ȴ�.
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