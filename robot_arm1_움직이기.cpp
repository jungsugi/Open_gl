#include <gl/glut.h>
#include <gl/gl.h>
#include <gl/glu.h>
#include <math.h>
#include <stdio.h>

GLUquadricObj *c;   //quadric object�� ����Ű�� GLU object
static GLfloat base, lower, upper;

void Base() {
	glColor3f(1.0, 0, 0);
	glTranslatef(0, -1, 0);
	glRotatef(-90, 1, 0, 0);
	glRotatef(base, 0, 0, 1);
	gluCylinder(c, 0.4, 0.4, 0.3, 8, 5);   //c=��鰴ü, base:�Ʒ�������, top:��������, height:����, slices:�ʼ�, stacks:�Ǽ� 
}

void lower_arm() {
	glColor3f(0, 0, 1.0);
	glRotatef(base, 0, 1,0);
	glTranslatef(0, -0.7, 0);
	glRotatef(lower, 0, 0, 1);
	glTranslatef(0, 0.5, 0);
	glScalef(0.2, 1, 0.2);
	glutWireCube(1);
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
	glutWireCube(1);
}

void MyDisplay() { //������ �׸��� �Լ�
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);		//���̾� ��Ÿ���� ��� ����� ������Ŀ� ������ ��.
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);	//face: GL_FRONT, GL_BACK, GL_FRONT_AND_ACK  /mode: GL_POINT,GL_LINE, GL_FILL
	glLoadIdentity();  //��������� ���� ��ķ� �ʱ�ȭ ��.
	gluLookAt(1, 1, 1, 0, 0.0, 0, 0.0, 1.0, 0.0); //3���� �׷�, �ٶ󺸴� ��ġ(x,y,z), ī�޶󰡺����ִ°�(x,y,z) , ī�޶������� ����Ű�� ����(0.0,1.0, 0.0), (0.0, -1.0, 0.0)�̶��, �Ųٷ� ����
	
	glPushMatrix();  //���縦 �����ϴ°��� �ƴϰ�, �Ʒ� stack�� �����ؼ� �ϳ� ������°�.
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
	else if (KeyPressed == 'l') {
		if (lower <= 88)
			lower += 2;
	}
	else if (KeyPressed == ';') {
		if (lower >= -88)
			lower -= 2;
	}
	else if (KeyPressed == ',') {
		if (upper <= 88)
			upper += 2;
	}
	else if (KeyPressed == '.') {
		if (upper >= -88)
			upper -= 2;
	}
	glutPostRedisplay();
}

void init(void) {
	c = gluNewQuadric();
	gluQuadricDrawStyle(c, GLU_LINE);
	base = 0; upper = 0; lower = 0;
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glEnable(GL_DEPTH_TEST);
}

int main(int argc, char** argv) {

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(300, 200);
	glutCreateWindow("OpenGL Drawing Example");
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	glOrtho(-3.0, 3.0, -3.0, 3.0, -3.0, 3.0);
	glutDisplayFunc(MyDisplay);
	glutKeyboardFunc(MyKeyboard);
	init();
	glutMainLoop();

	return 0;
}