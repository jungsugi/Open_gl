#include <glut.h>
#include <gl\GL.h>      
#include <gl\GLU.h>
#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

GLfloat WindowWidth = 300;
GLfloat WindowHeight = 300;
GLfloat WindowPosition_width = 100;
GLfloat WindowPosition_hieght = 100;

GLint TopLeftX, TopLeftY, BottomRightX, BottomRightY; //x,y ��ǥ ����
GLfloat rvalue = 0.0, gvalue = 0.0, bvalue = 0.0;//���� ��Ÿ���� ����
int LineWidth = 1;//������ �� ���⸦ ��Ÿ���� ����
int shape;

class Figure{
public:
	GLfloat f_rvalue,f_gvalue,f_bvalue;	//������ ���� ����.
	GLint topleft_x, topleft_y, bottomright_x, bottomright_y;	//��ġ.
	int line_width;
	int f_shape;
};

Figure figure[1000];

int counts=0;

void MyMouseClick(GLint Button, GLint State, GLint X, GLint Y) { //���콺Ŭ�� �̺�Ʈ����
	if (Button == GLUT_LEFT_BUTTON && State == GLUT_DOWN) { //���콺 �������� 
		
		figure[counts].f_rvalue = rvalue;	//���� ���� ���� ����.
		figure[counts].f_gvalue = gvalue;
		figure[counts].f_bvalue = bvalue;
		figure[counts].topleft_x = X;
		figure[counts].topleft_y = Y;
		figure[counts].f_shape = shape;		//���� ���� ����.
		figure[counts].line_width = LineWidth;		//���� ���� �β� ����.
		glLineWidth(figure[counts].line_width);  //�� ���� ���� �Լ�
		cout << "����"<<counts<<endl; //���� ���.
		cout << "�ٳʺ�"<<figure[counts].line_width <<endl;
	}
	if(State == GLUT_UP){  //���콺�� ������,
		counts++;
	}
}

void MyKeyboard(unsigned char KeyPressed, int X, int Y) { //Ű����Ŭ�� �̺�Ʈ����
	switch (KeyPressed) { //Ű�� ��������
	case '1':
		rvalue = 1.0; gvalue = 0.0; bvalue = 0.0; break;
	case '2':
		rvalue = 0.5; gvalue = 0.0; bvalue = 0.0; break;
	case '3':
		rvalue = 0.0; gvalue = 0.5; bvalue = 0.0; break;
	case '4':
		rvalue = 0.0; gvalue = 1.0; bvalue = 0.0; break;
	case '5':
		rvalue = 0.0; gvalue = 0.0; bvalue = 1.0; break;
	case '6':
		rvalue = 0.0; gvalue = 0.0; bvalue = 0.5; break; 
	case '7':
		rvalue = 0.25; gvalue = 0.0; bvalue = 0.5; break; //1~5 ������
	
	case 'q':
		exit(0); break;//q ���ý� ȭ�� ����
	case 27:
		counts=-1; 
		
		glutPostRedisplay(); break;//esc ���ý� ȭ�� Ŭ����
	case 'r':
	case 'R':	
		shape = 0; break; //r ���ý� �簢�� ���
	case 'T':
	case 't':
		shape = 1; break;//t ���ý� �ﰢ�� ���
	case 'L':
	case 'l':
		shape = 2;break; //'l' ���ý� ���� 
	case '[':
		LineWidth += 2; 
		
		break;//�� ���� ����
	case ']':
		LineWidth -= 2; if (LineWidth <= 0) { LineWidth = 1; }
		
		break; // ������ ���� �����Ⱑ '0'���� �۾����� '1'�� �ʱ�ȭ
	case 's':	//save���!
		break;
	}
}


void MyMouseMove(GLint X, GLint Y) {
//���콺 ���� �̺�Ʈ����

	figure[counts].bottomright_x = X;
	figure[counts].bottomright_y = Y;

	glutPostRedisplay(); //������ ��� �䱸�ϵ��� ��.
	
		
}

void DisPlayRec(Figure &fig) { //�簢�� ���� �׸��� �Լ�
	
	glLineWidth(fig.line_width);//�� ���� ���� �Լ�
	glColor3f(fig.f_rvalue,fig.f_gvalue,fig.f_bvalue); //�� ���� �Լ�
	
	glBegin(GL_POLYGON);
	glVertex3f(fig.topleft_x / 300.0, (300 - fig.topleft_y) / 300.0, 0.0);
	glVertex3f(fig.bottomright_x / 300.0, (300 - fig.topleft_y) / 300.0, 0.0);
	glVertex3f(fig.bottomright_x / 300.0, (300 - fig.bottomright_y) / 300.0, 0.0);
	glVertex3f(fig.topleft_x / 300.0, (300 - fig.bottomright_y) / 300.0, 0.0);
	glEnd();

}



void DisPlayTri(Figure &fig) { //�ﰢ�� ���� �׸��� �Լ�
	
	glLineWidth(fig.line_width);//�� ���� ���� �Լ�
	glColor3f(fig.f_rvalue,fig.f_gvalue,fig.f_bvalue); //�� ���� �Լ�

	glBegin(GL_POLYGON);
	glVertex3f(fig.topleft_x / 300.0, (300 - fig.topleft_y) / 300.0, 0.0);
	glVertex3f(fig.bottomright_x / 300.0, (300 - fig.bottomright_y) / 300.0, 0.0);
	glVertex3f((2 * fig.topleft_x - fig.bottomright_x) / 300.0, (300 - fig.bottomright_y) / 300.0, 0.0);
	glEnd();
}

void DisPlayLine(Figure &fig) { //���� �׸��� �Լ�
	glLineWidth(fig.line_width);  //�� ���� ���� �Լ�
	
	glBegin(GL_LINES);
	glColor3f(fig.f_rvalue,fig.f_gvalue,fig.f_bvalue); //�� ���� �Լ�
	
	glVertex3f(fig.topleft_x / 300.0, (300 - fig.topleft_y) / 300.0, 0.0);
	glVertex3f(fig.bottomright_x / 300.0, (300 - fig.bottomright_y) / 300.0, 0.0);
	
	glEnd();
}

void MyDisplay() {
	glViewport(0, 0, 300, 300);//����Ʈ ��ǥ�� ����
	glClear(GL_COLOR_BUFFER_BIT);//ȭ�� Ŭ����
	
	for(int i=0; i<counts; i++){
		glLineWidth(figure[i].line_width);  //�� ���� ���� �Լ�
		if (figure[i].f_shape == 0)	DisPlayRec(figure[i]); //������ ���� ��翡 ���� ���� �׸�
		else if (figure[i].f_shape == 1) DisPlayTri(figure[i]);
		else if (figure[i].f_shape == 2) DisPlayLine(figure[i]);
	}if(counts>=0){
		if (figure[counts].f_shape == 0)	DisPlayRec(figure[counts]); //������ ���� ��翡 ���� ���� �׸�
		else if (figure[counts].f_shape == 1) DisPlayTri(figure[counts]);
		else if (figure[counts].f_shape == 2) DisPlayLine(figure[counts]);
	}

	glFlush(); //��� ����
}


int main(int argc, char** argv) {//�����Լ��κ�
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB);
	glutInitWindowSize(WindowWidth, WindowHeight);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("OpenGL Drawing Example");

	glClearColor(1.0, 1.0, 1.0, 1.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	glOrtho(0.0, 1.0, 0.0, 1.0, -1.0, 1.0);

	glutDisplayFunc(MyDisplay);
	glutKeyboardFunc(MyKeyboard);
	glutMouseFunc(MyMouseClick);
	glutMotionFunc(MyMouseMove);
	glutMainLoop();//���ѷ���
	return 0;
}