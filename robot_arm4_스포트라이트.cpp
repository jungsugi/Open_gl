#include <windows.h>
#include <gl/gl.h>
#include <gl/glu.h>
#include <gl/glut.h>
#include <math.h>

//헤더파일 
int speed = 1.0;

void Base();
void Lower_Arm();
void Upper_Arm();
void Base_mini();

static float thetaBase;
static float thetaLower;
static float thetaUpper;

GLfloat spotlight = 0;  //스포트라이트 방향
GLboolean light0_enable = true;  // 위치성광원 켜기
GLboolean light1_enable = true;  // 스포트라이트 켜기

GLfloat zoom = 100.0;
GLfloat zoomAngle = 1.0;
GLfloat view_A = 0, view_B = 0, view_C = 0;
GLboolean Perspective = false;
GLUquadricObj *p;

GLfloat r=0, g=0, b=0;

void MyLightInit()  //광원 초기화
{
	GLfloat MyGlobalAmbient[] = { 0.8, 0.4, 0.4, 1.0 };
	GLfloat light0_ambient[] = { 0.5, 0.5, 0.5, 1 };
	GLfloat light0_diffuse[] = { 0.5, 0.5, 0.5, 1 };
	GLfloat light0_specular[] = { 1, 1, 1, 1 };

	GLfloat light1_ambient[] = { 1.0, 0.0, 0.0, 1 };
	GLfloat light1_diffuse[] = { 0.5, 0.5, 0.5, 1 };
	GLfloat light1_specular[] = { 0, 0, 0, 1 };

	GLfloat material_ambient[] = { 0.3, 0.3, 0.3, 1 };
	GLfloat material_diffuse[] = { 0.8, 0.8, 0.8, 1 };
	GLfloat material_specular[] = { 0, 0, 0, 1 };
	GLfloat material_shininess[] = { 25 };

	glShadeModel(GL_SMOOTH);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);

	glEnable(GL_LIGHT0);
	glLightfv(GL_LIGHT0, GL_AMBIENT, light0_ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light0_diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light0_specular);

	glEnable(GL_LIGHT1);
	glLightfv(GL_LIGHT1, GL_AMBIENT, light1_ambient);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, light1_diffuse);
	glLightfv(GL_LIGHT1, GL_SPECULAR, light1_specular);

	glMaterialfv(GL_FRONT, GL_DIFFUSE, material_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, material_specular);
	glMaterialfv(GL_FRONT, GL_AMBIENT, material_ambient);
	glMaterialfv(GL_FRONT, GL_SHININESS, material_shininess);

	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, MyGlobalAmbient);
	glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);

}

void InitVisibility()
{
	glCullFace(GL_FRONT);
	glFrontFace(GL_CCW);
	glEnable(GL_DEPTH_TEST);
}

void MyDisplay()
{

	GLfloat LightPosition0[] = { 0.3, -0.5, 1, 1 };
	GLfloat LightPosition1[] = { 0, 1, 0, 1 };
	GLfloat LightDirection[] = { spotlight, -1, 0 };
	GLfloat SpotAngle1[] = { 60.0 };
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glEnable(GL_BLEND);  //안티 엘리어징 
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_POINT_SMOOTH);
	glHint(GL_POINT_SMOOTH_HINT, GL_NICEST);

	p = gluNewQuadric();

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	gluLookAt(view_A + 1, view_B + 1, view_C + 1, 0, 0, 0, 0, 1, 0);  //카메라 시점
	glLightfv(GL_LIGHT0, GL_POSITION, LightPosition0);
	glLightfv(GL_LIGHT1, GL_POSITION, LightPosition1);
	glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, LightDirection);
	glLightfv(GL_LIGHT1, GL_SPOT_CUTOFF, SpotAngle1);
	glLightf(GL_LIGHT1, GL_SPOT_EXPONENT, 1.0);

	glLightfv(GL_LIGHT0, GL_POSITION, LightPosition0);

	//엄마 로봇팔 

	glColor3f(1.0, 0.0, 0.0);
	Base();
	Base_mini();
	glColor3f(0.0, 1.0, 0.0);
	Lower_Arm();
	glColor3f(0.0, 0.0, 1.0);
	Upper_Arm();

	// 로봇팔 1

	glTranslatef(2, 3, 1);
	glScalef(0.5, 0.5, 0.5);

	glColor3f(0.5, 0.5, 0.0);
	Base();
	Base_mini();
	glColor3f(0.5, 0.0, 0.05);
	Lower_Arm();
	glColor3f(0.0, 0.5, 0.5);
	Upper_Arm();

	//로봇팔 2

	glTranslatef(-5, -4, 1);

	glColor3f(0.1, 0.0, 0.0);
	Base();
	Base_mini();
	glColor3f(0.0, 0.1, 0.0);
	Lower_Arm();
	glColor3f(0.0, 0.0, 0.1);
	Upper_Arm();

	glutSwapBuffers();  //더블버퍼링

}

void Base(void)
{
	glPushMatrix();  //메트릭스 푸쉬

	glTranslatef(0, -1.0, 0);  //이동
	glRotatef(-90, 1, 0, 0);  //회전
	glRotatef(thetaBase, 0, 0, 1);

	gluCylinder(p, 0.5, 0.5, 0.2, 20, 2);
	glPopMatrix();  //메트릭스 팝
}

void Lower_Arm(void)
{
	glPushMatrix();

	glRotatef(thetaBase, 0, 1, 0);
	glTranslatef(0, -0.8, 0);

	glRotatef(thetaLower, 0, 0, 1);
	glTranslatef(0, 0.5, 0);

	glScalef(0.2, 1, 0.2);
	glutSolidCube(1);
	glPopMatrix();
}

void Upper_Arm(void)
{
	glPushMatrix();

	glRotatef(thetaBase, 0, 1, 0);
	glTranslatef(0, -0.8, 0);

	glRotatef(thetaLower, 0, 0, 1);
	glTranslatef(0, 1.0, 0);

	glRotatef(thetaUpper, 0, 0, 1);
	glTranslatef(0, 0.4, 0);

	glScalef(0.2, 0.8, 0.2);
	glutSolidCube(1);
	glPopMatrix();
}

void Base_mini(void)
{
	glPushMatrix();  //메트릭스 푸쉬

	glTranslatef(0, -1.0, 0);  //이동
	glRotatef(-90, 1, 0, 0);  //회전
	glRotatef(0, 0, 0, 1);

	gluCylinder(p, 0.6, 0.6, 0.4, 30, 1);
	glPopMatrix();  //메트릭스 팝
}

void MyKeyboard(unsigned char KeyPressed, int x, int y)
{
	if (thetaBase >= 360.0)
		thetaBase -= 360.0;

	if (thetaLower >= 90.0)
		thetaLower = 90.0;

	if (thetaLower <= -90.0)
		thetaLower = -90.0;

	if (thetaUpper >= 90.0)
		thetaUpper = 90.0;

	if (thetaUpper <= -90.0)
		thetaUpper = -90.0;

	if (zoom < -100)
		zoom = -100;

	switch (KeyPressed)
	{
	case 27:
		exit(0);
		break;

	case 'w':  //위팔 아래로 움직임
		thetaUpper -= speed;
		break;
	case 'q':  //위팔 위로 움직임
		thetaUpper += speed;
		break;

	case 's':  //아래팔이 아래로 움직임
		thetaLower -= speed;
		break;
	case 'a':  //아래팔이 위로 움직임
		thetaLower += speed;
		break;

	case 'x':  //몸통이 오른쪽으로 돌아감
		thetaBase += speed;
		break;
	case 'z':  //몸통이 왼쪽으로 돌아감
		thetaBase -= speed;
		break;

	case 'r':   // ZoomIn, 확대
		zoom -= 1.0;
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		if (!Perspective)
			gluPerspective(zoom, zoomAngle, 0.1, 10.0);
		break;

	case 't':  // ZoomOut, 축소
		zoom += 1.0;
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		if (!Perspective)
			gluPerspective(zoom, zoomAngle, 0.1, 10.0);
		break;

	case 'f':  //좌측 시점 변환
		view_A += 0.1;
		view_C -= 0.1;
		if (!Perspective){
			glMatrixMode(GL_PROJECTION);
			glLoadIdentity();
			gluPerspective(zoom, zoomAngle, 0.1, 10.0);
		}
		break;

	case 'g':  //우측 시점 변환
		view_A -= 0.1;
		view_C += 0.1;
		if (!Perspective){
			glMatrixMode(GL_PROJECTION);
			glLoadIdentity();
			gluPerspective(zoom, zoomAngle, 0.1, 10.0);
		}
		break;

	case 'v':  //위쪽 시점 변환
		view_B += 0.1;
		if (!Perspective){
			glMatrixMode(GL_PROJECTION);
			glLoadIdentity();
			gluPerspective(zoom, zoomAngle, 0.1, 10.0);
		}
		break;

	case 'b':  //아랫쪽 시점 변환
		view_B -= 0.1;
		if (!Perspective){
			glMatrixMode(GL_PROJECTION);
			glLoadIdentity();
			gluPerspective(zoom, zoomAngle, 0.1, 10.0);
		}
		break;

	default:
		break;
	}
	glutPostRedisplay();
}

void Keyboard(int key, int x, int y)
{
	switch (key)
	{
	case GLUT_KEY_F1:  //평행투상
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		Perspective = true;
		glOrtho(-zoomAngle, zoomAngle, -2.0, 2.0, -10, 10);
		break;

	case GLUT_KEY_F2:  //원근투상
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		Perspective = false;
		gluPerspective(100, zoomAngle, 0.1, 10.0);
		break;

	case GLUT_KEY_F3:  //위치성광원 켰다 끄기
		if (light0_enable == false)
		{
			glEnable(GL_LIGHT0);
			light0_enable = true;
		}
		else
		{
			glDisable(GL_LIGHT0);
			light0_enable = false;
		}
		break;
	case GLUT_KEY_F4:  //스포트라이트 켰다끄기
		if (light1_enable == false)
		{
			glEnable(GL_LIGHT1);
			light1_enable = true;
		}
		else
		{
			glDisable(GL_LIGHT1);
			light1_enable = false;
		}
		break;
	case GLUT_KEY_F5:  //스포트라이트 왼쪽으로 비추기
		if (spotlight > -1.0)
			spotlight -= 0.1;
		else;
		break;
	case GLUT_KEY_F6:  //스포트라이트 오른쪽으로 비추기
		if (spotlight < 1.0)
			spotlight += 0.1;
		else;
		break;

	default:
		break;
	}
	glutPostRedisplay();

}

void MyReshape(int w, int h)  //Reshape 
{
	if (h == 0) 	h = 1;
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	if (w <= h)
		glOrtho(-2.0, 2.0, -2.0*(float)h / (float)w, 2.0*(float)h / (float)w, -10.0, 10.0);
	else
		glOrtho(-2.0*(float)w / (float)h, 2.0*(float)w / (float)h, -2.0, 2.0, -10.0, 10.0);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void Init(void)  //초기화
{
	p = gluNewQuadric();
	gluQuadricDrawStyle(p, GLU_LINE);
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glEnable(GL_DEPTH_TEST);
	gluPerspective(zoom, zoomAngle, 0.1, 10.0);
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	thetaBase = 0;
	thetaLower = 0;
	thetaUpper = 0;

}

void main(int argc, char* argv[])  //메인함수
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowSize(700, 700);
	glutCreateWindow("OpenGL");

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	MyLightInit();

	glutDisplayFunc(MyDisplay);
	glutReshapeFunc(MyReshape);
	glutKeyboardFunc(MyKeyboard);
	glutSpecialFunc(Keyboard);

	Init();
	InitVisibility();

	glutMainLoop();
}