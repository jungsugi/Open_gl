#include <gl/glut.h>
#include <gl/gl.h>
#include <gl/glu.h>
#include <math.h>
#include <stdio.h>

GLUquadricObj *c;   //quadric object를 가리키는 GLU object
static GLfloat base, lower, upper;

void Base() {
	glColor3f(1.0, 0, 0);
	glTranslatef(0, -1, 0);
	glRotatef(-90, 1, 0, 0);
	glRotatef(base, 0, 0, 1);
	gluCylinder(c, 0.4, 0.4, 0.3, 8, 5);   //c=곡면객체, base:아랫면지름, top:윗면지름, height:높이, slices:쪽수, stacks:판수 
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

void MyDisplay() { //도형을 그리는 함수
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);		//뒤이어 나타나는 행렬 명령이 투영행렬에 영향을 줌.
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);	//face: GL_FRONT, GL_BACK, GL_FRONT_AND_ACK  /mode: GL_POINT,GL_LINE, GL_FILL
	glLoadIdentity();  //투영행렬을 단위 행렬로 초기화 함.
	gluLookAt(1, 1, 1, 0, 0.0, 0, 0.0, 1.0, 0.0); //3가지 그룹, 바라보는 위치(x,y,z), 카메라가보고있는곳(x,y,z) , 카메라위쪽을 가리키는 벡터(0.0,1.0, 0.0), (0.0, -1.0, 0.0)이라면, 거꾸로 보기
	
	glPushMatrix();  //현재를 복사하는것이 아니고, 아래 stack을 저장해서 하나 더만드는것.
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