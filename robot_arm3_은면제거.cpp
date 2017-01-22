#include <gl/glut.h>
#include <gl/gl.h>
#include <gl/glu.h>
#include <math.h>
#include <stdio.h>

GLUquadricObj *c;
static GLfloat base, lower, upper, base2, lower2, upper2;
GLfloat eye1, eye2, eye3, upX,upY,upZ, zoom = 45, asp=3.0;
GLint see,fill,back;
GLboolean inner, clip;

GLfloat vertices[][3] = {
	{ -0.5, 0.5, -0.5 }, //0
	{ -0.5, 0.5, 0.5 },  //1
	{ 0.5, 0.5, 0.5 },   //2
	{ 0.5, 0.5, -0.5 },  //3
	{ -0.5, -0.5, -0.5 },//4
	{ -0.5, -0.5, 0.5 }, //5
	{ 0.5, -0.5, 0.5 },  //6
	{ 0.5, -0.5, -0.5 }  //7
};

GLfloat colors[][3] = {
	{ 1.0, 0.0, 0.0 },      // red  
	{ 1.0, 1.0, 0.0 },      // yellow  
	{ 0.0, 1.0, 0.0 },      // green  
	{ 0.0, 0.0, 1.0 },      // blue  
	{ 0.5, 0.5, 0.0 },      // gold
	{ 1.0, 0.0, 1.0 }        // magenta  
};

void Base() {
	glColor3f(1.0, 0, 0);
	glTranslatef(0, -1, 0);
	glRotatef(-90, 1, 0, 0);
	glRotatef(base, 0, 0, 1);
	gluCylinder(c, 0.4, 0.4, 0.3, 8, 5);
}

void Baby_Base() {
	glColor3f(1.0, 0.3, 0.3);
	glTranslatef(-2, -0.8, 0); 
	glRotatef(-90, 1, 0, 0);
	glRotatef(base2, 0, 0, 1);
	gluCylinder(c, 0.3, 0.3, 0.2, 8, 5);
}

void Baby_Base2() {
	glColor3f(1.0, 0.5, 0.5);
	glTranslatef(-4, -0.8, 0);
	glRotatef(-90, 1, 0, 0);
	glRotatef(base, 0, 0, 1);
	gluCylinder(c, 0.2, 0.2, 0.1, 8, 5);
}


void lower_arm() {
	glColor3f(0, 0, 1.0);
	glRotatef(base, 0, 1,0);	//'y축'이 같이 돌아가도록.
	glTranslatef(0, -0.7, 0);   
	glRotatef(lower, 0, 0, 1);  //'z축'이 lower팔 기울기.
	glTranslatef(0, 0.5, 0);    //
	glScalef(0.2, 1, 0.2);		
	
	glBegin(GL_QUADS);
	glColor3fv(colors[0]);
	glVertex3fv(vertices[0]);
	glVertex3fv(vertices[3]);
	glVertex3fv(vertices[2]);
	glVertex3fv(vertices[1]);

	glColor3fv(colors[1]);
	glVertex3fv(vertices[1]);
	glVertex3fv(vertices[2]);
	glVertex3fv(vertices[6]);
	glVertex3fv(vertices[5]);

	glColor3fv(colors[2]);
	glVertex3fv(vertices[3]);
	glVertex3fv(vertices[7]);
	glVertex3fv(vertices[6]);
	glVertex3fv(vertices[2]);

	glColor3fv(colors[3]);
	glVertex3fv(vertices[0]);
	glVertex3fv(vertices[3]);
	glVertex3fv(vertices[7]);
	glVertex3fv(vertices[4]);

	glColor3fv(colors[4]);
	glVertex3fv(vertices[7]);
	glVertex3fv(vertices[4]);
	glVertex3fv(vertices[5]);
	glVertex3fv(vertices[6]);

	glColor3fv(colors[5]);
	glVertex3fv(vertices[4]);
	glVertex3fv(vertices[0]);
	glVertex3fv(vertices[1]);
	glVertex3fv(vertices[5]);

	glEnd();
}

void lower_arm2() {
	glColor3f(0.3, 0.3, 1.0);
	glTranslatef(-2.0, -0.7, 0);
	glRotatef(base2, 0, 1, 0);
	glRotatef(lower2, 0, 0, 1);
	glTranslatef(0, 0.5, 0);
	glScalef(0.1, 0.8, 0.1);
	glutSolidCube(1);
}

void lower_arm3() {
	glColor3f(0.5, 0.5, 1.0);
	glTranslatef(-4.0, -0.8, 0);
	glRotatef(base, 0, 1, 0);
	glRotatef(lower, 0, 0, 1);
	glTranslatef(0, 0.4, 0);
	glScalef(0.1, 0.8, 0.1);
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
	glBegin(GL_QUADS);

	glColor3fv(colors[5]);
	glVertex3fv(vertices[0]);
	glVertex3fv(vertices[3]);
	glVertex3fv(vertices[2]);
	glVertex3fv(vertices[1]);

	glColor3fv(colors[4]);
	glVertex3fv(vertices[1]);
	glVertex3fv(vertices[2]);
	glVertex3fv(vertices[6]);
	glVertex3fv(vertices[5]);

	glColor3fv(colors[3]);
	glVertex3fv(vertices[3]);
	glVertex3fv(vertices[7]);
	glVertex3fv(vertices[6]);
	glVertex3fv(vertices[2]);

	glColor3fv(colors[2]);
	glVertex3fv(vertices[0]);
	glVertex3fv(vertices[3]);
	glVertex3fv(vertices[7]);
	glVertex3fv(vertices[4]);

	glColor3fv(colors[1]);
	glVertex3fv(vertices[7]);
	glVertex3fv(vertices[4]);
	glVertex3fv(vertices[5]);
	glVertex3fv(vertices[6]);

	glColor3fv(colors[0]);
	glVertex3fv(vertices[4]);
	glVertex3fv(vertices[0]);
	glVertex3fv(vertices[1]);
	glVertex3fv(vertices[5]);

	glEnd();
}

void upper_arm2() {
	glColor3f(0.3, 1.0, 0.3);
	glTranslatef(-2.0, -0.7, 0);
	glRotatef(base2, 0, 1, 0);
	glRotatef(lower2, 0, 0, 1);
	glTranslatef(0, 0.85, 0);
	glRotatef(upper2, 0, 0, 1);
	glTranslatef(0, 0.4, 0);
	glScalef(0.1, 0.7, 0.1);
	glutSolidCube(1);
}

void upper_arm3() {
	glColor3f(0.5, 1.0, 0.5);
	glTranslatef(-4.0, -0.8, 0);
	glRotatef(base, 0, 1, 0);
	glRotatef(lower, 0, 0, 1);
	glTranslatef(0, 0.85, 0);
	glRotatef(upper, 0, 0, 1);
	glTranslatef(0, 0.3, 0);
	glScalef(0.1, 0.7, 0.1);
	glutSolidCube(1);
}

//후면,은면 제거

void InitVisability() {
	glEnable(GL_CULL_FACE);  //후,은면 제거 모드 활성화.
	glFrontFace(GL_CCW);	 //시계 반대 방향.
	switch (fill)
	{
	case 1:
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		glutPostRedisplay();
		break;
	case 2:
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		glutPostRedisplay();
		break;
	}

	switch (back)
	{
	case 1:
		glCullFace(GL_BACK);
		glutPostRedisplay();
		break;
	case 2:
		glCullFace(GL_FRONT);
		glutPostRedisplay();
		break;
	case 3:
		glCullFace(GL_FRONT_AND_BACK);
		glutPostRedisplay();
		break;
	default:
		glDisable(GL_CULL_FACE);
		glutPostRedisplay();
		break;
	}

	glEnable(GL_DEPTH_TEST);
	glDepthMask(GL_TRUE);
	
}


void MyDisplay() { //도형을 그리는 함수

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glViewport(0, 0, 500, 500);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	
	if(clip)
		gluPerspective(zoom, 1.0, sqrt(50+asp*asp), 100.0); //y축 시야각, 너비와높이의비율(시야의 종횡비), (z축으로)가까운면, (z축으로)먼면,
	else
		gluPerspective(zoom, 1.0, 0.1, 100.0);
	
	glMatrixMode(GL_MODELVIEW);

	glPushMatrix();
	if(inner)
		gluLookAt(0, -1, 0, 0, 0.0, 0, 0, 0.0, 1);
	else
		gluLookAt(5, asp, 5, 0, 0.0, 0, 0, 1, 0);
	
	glPushMatrix();
	glColor3f(0.5f, 0.f, 0.f);
	glBegin(GL_LINE_LOOP);	//x축 -> 빨간
	glVertex3f(5.0, 0.0 , 0.0); //시작점.	
	glColor3f(1.0f, 0.f, 0.f);
	glVertex3f(-5.0, 0.0, 0.0);	//끝점.
	glEnd();

	glColor3f(0.f, 0.5f, 0.f);
	glBegin(GL_LINE_LOOP);	//y축 ->초록
	glVertex3f(0.0, 5.0 , 0.0); //시작점.
	glColor3f(0.f, 1.f, 0.f);	
	glVertex3f(0.0, -5.0, 0.0);	//끝점.
	glEnd();

	glColor3f(0.f, 0.f, 0.2f);
	glBegin(GL_LINE_LOOP);	//z축 ->파란
	glVertex3f(0.0, 0.0 , 5.0); //시작점.
	glColor3f(0.f, 0.f, 1.0f);	
	glVertex3f(0.0, 0.0, -5.0);	//끝점.
	glEnd();
	glPopMatrix();

	glPushMatrix();	
	Base();
	glPopMatrix();
	glPushMatrix();
	lower_arm();
	glPopMatrix();
	glPushMatrix();
	upper_arm();
	glPopMatrix();

	glPushMatrix();
	Baby_Base();
	glPopMatrix();
	glPushMatrix();
	lower_arm2();
	glPopMatrix();
	glPushMatrix();
	upper_arm2();
	glPopMatrix();

	glPushMatrix();
	Baby_Base2();
	glPopMatrix();
	glPushMatrix();
	lower_arm3();
	glPopMatrix();
	glPushMatrix();
	upper_arm3();
	glPopMatrix();
	
	glPopMatrix();

	glutSwapBuffers();
}

void MyKeyboard(unsigned char KeyPressed, int X, int Y) {
	if (KeyPressed == 'o') {
		base +=2;
		base2 -=2;
	}
	else if (KeyPressed == 'p') {
		base -=2;
		base2 +=2;
	}
	else if (KeyPressed == 'l') {
		if (lower <= 88)
			lower += 2;
			lower2 -= 2;
	}
	else if (KeyPressed == ';') {
		if (lower >= -88)
			lower -= 2;
			lower2 += 2;
	}
	else if (KeyPressed == ',') {
		if (upper <= 88)
			upper += 2;
			upper2 -= 2;
	}
	else if (KeyPressed == '.') {
		if (upper >= -88)
			upper -= 2;
			upper2 += 2;
	}
	else if (KeyPressed == 'z') {
		zoom += 1;
	}
	else if (KeyPressed == 'x') {
		zoom -= 1;
	}
	else if (KeyPressed == 'c') {
		asp += 0.1;
	}
	else if (KeyPressed == 'v') {
		asp -= 0.1;
	}
	else if (KeyPressed == 'f') {
		fill = 1;
		InitVisability();
	}
	else if (KeyPressed == 'g') {
		fill = 2;
		InitVisability();
	}
	else if (KeyPressed == 'a') {
		inner = true;
		clip = false;
		MyDisplay();
	}
	else if (KeyPressed == 's') {
		inner = false;
		clip = true;
		MyDisplay();
	}
	else if (KeyPressed == 'd') {
		inner = false;
		clip = false;
		MyDisplay();
	}
	else if (KeyPressed == 'q') {
		back = 1;
		InitVisability();
	}
	else if (KeyPressed == 'w') {
		back = 2;
		InitVisability();
	}
	else if (KeyPressed == 'e') {
		back = 3;
		InitVisability();
	}
	else if (KeyPressed == 'r') {
		back = 0;
		InitVisability();
	}
	glutPostRedisplay();
}
void init(void) {
	c = gluNewQuadric();
	gluQuadricDrawStyle(c, GLU_LINE);
	base = 0; upper = 0; lower = 0;
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	
}

int main(int argc, char** argv) {

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(300, 200);
	glutCreateWindow("OpenGL Drawing Example");
	InitVisability();
	glutDisplayFunc(MyDisplay);
	glutKeyboardFunc(MyKeyboard);
	init();
	glutMainLoop();

	return 0;
}