#include <glut.h>						
#include <gl/gl.h>							
#include <gl/glu.h>				
#include <stdlib.h>
#include <iostream>

using namespace std;
GLfloat window_width = 500;
GLfloat window_height = 500;
GLfloat delta = 0.01;
GLfloat Cur_scale_x = 1.0f;
GLfloat Cur_scale_y = 1.0f;
GLfloat Cur_rotate = 2.0f;

GLfloat rvalue = 1.0, gvalue = 1.0, bvalue = 1.0;//���� ��Ÿ���� ����

bool Cur_left_rotate = false; //��ȸ��
bool Cur_right_rotate = false; //��ȸ��
bool Cur_Zoom_in = false;
bool Cur_Zoom_out = false;
bool Cur_Move_left = false;
bool Cur_Move_right = false;
bool Cur_Stop = false;
bool twingkle = false;

GLfloat sq[4][2] = {0.0};	//x,y��ǥ
GLfloat X1,X2,X3,X4,Y1,Y2,Y3,Y4;
GLfloat temp1,temp2,temp3; //���������� ����.
GLint rr=0;

void MyTimer(int value){
	
	if(twingkle){
		if(!rr){
			temp1 = rvalue, temp2= gvalue; temp3=bvalue;
			rvalue=gvalue=bvalue=0;
			rr=1;
		}else{
			rvalue = temp1; gvalue = temp2; bvalue = temp3;
			rr=0;
		}
	}

	if(Cur_Stop){
		delta = delta;
		twingkle=false;
	}else{
		
		delta = delta + 0.001;
		if(Cur_Zoom_in){
			Cur_scale_x += 0.0001;
			Cur_scale_y += 0.0001;
		}else if(Cur_Zoom_out){
			Cur_scale_x -= 0.0001;
			Cur_scale_y -= 0.0001;			
		}else if(Cur_rotate){
			Cur_rotate = 5;
		}else{
			Cur_scale_x = Cur_scale_x;
			Cur_scale_y = Cur_scale_y;
		}
	}
	

	glutPostRedisplay();

	glutTimerFunc(40,MyTimer,1);
	
}


void MyMouse(GLint Button, GLint State, GLint X, GLint Y){
	glutAttachMenu(GLUT_RIGHT_BUTTON);
}


void MyKeyboard(unsigned char KeyPressed, int X, int Y) { //Ű����Ŭ�� �̺�Ʈ����
	switch(KeyPressed){
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
	}

}

void MyDisplay( ){			
	
	glClear(GL_COLOR_BUFFER_BIT);	
	glColor3f(rvalue, gvalue, bvalue);
	
	if(Cur_left_rotate){   //��ȸ��
		glRotatef(Cur_rotate,0.0, 0.0 , 1.0);

		glBegin(GL_POLYGON);
		glVertex3f(X1, Y1, 0.0);
		glVertex3f(X3, Y3, 0.0);
		glVertex3f(X4, Y4, 0.0);
		glVertex3f(X2, Y2, 0.0);
		glEnd( );

	}else if(Cur_right_rotate){  //��ȸ��
		glRotatef(Cur_rotate,0.0, 0.0 , -1.0);

		glBegin(GL_POLYGON);
		glVertex3f(X1, Y1, 0.0);
		glVertex3f(X3, Y3, 0.0);
		glVertex3f(X4, Y4, 0.0);
		glVertex3f(X2, Y2, 0.0);
		glEnd( );

	}else if(Cur_Move_left == true){  //�����̵� 
		
		glTranslatef(0.01f,0.0f,0.0f);

		glBegin(GL_POLYGON);		
		glVertex3f(X1, Y1, 0.0);
		glVertex3f(X3, Y3, 0.0);
		glVertex3f(X4, Y4, 0.0);
		glVertex3f(X2, Y2, 0.0);
		glEnd( );

	}else if(Cur_Move_right == true){  //������ �̵�
		glTranslatef(-0.01f,0.0f,0.0f);

		glBegin(GL_POLYGON);	
		glVertex3f(X1, Y1, 0.0);
		glVertex3f(X3, Y3, 0.0);
		glVertex3f(X4, Y4, 0.0);
		glVertex3f(X2, Y2, 0.0);
		glEnd( );

	}else if(Cur_Zoom_in){  //Ȯ��
		glScalef(Cur_scale_x, Cur_scale_y, 1.0f); 
		
		glBegin(GL_POLYGON);
		glVertex3f(X1, Y1, 0.0);
		glVertex3f(X3, Y3, 0.0);
		glVertex3f(X4, Y4, 0.0);
		glVertex3f(X2, Y2, 0.0);
		glEnd( );
		
	}else if(Cur_Zoom_out){  //���
		glScalef(-Cur_scale_x, -Cur_scale_y, 1.0f); 
		
		glBegin(GL_POLYGON);	
		glVertex3f(X1, Y1, 0.0);
		glVertex3f(X3, Y3, 0.0);
		glVertex3f(X4, Y4, 0.0);
		glVertex3f(X2, Y2, 0.0);
		glEnd( );
		
	}else{		//����
		
		glBegin(GL_POLYGON);	
		glVertex3f(X1, Y1, 0.0);
		glVertex3f(X3, Y3, 0.0);
		glVertex3f(X4, Y4, 0.0);
		glVertex3f(X2, Y2, 0.0);
		glEnd( );
	}

	glFlush( ); 		
	
	//display callback �Լ����� ����� �𵨸����Ŀ�
	glutSwapBuffers();	//buffer�� �ٲ���.					
}

void MyMainMenu(int entryID){

	if(entryID==1){   //ȸ��
		
	}else if(entryID==2){  //Ȯ��,���
		
	}else if(entryID==3){  //��,��
		
	}else if(entryID==4){  //����
		Cur_Stop = true;
		Cur_left_rotate = false; //��ȸ��
		Cur_right_rotate = false; //��ȸ��
		Cur_Zoom_in = false;
		Cur_Zoom_out = false;
		Cur_Move_left = false;
		Cur_Move_right = false;
		twingkle=false;
	}else if(entryID==5){   //��¦��
		twingkle=true;
	}else if(entryID==6){  //����
		exit(0);
	}

	glutPostRedisplay();

}

void MySubMenu(int entryID){
	if(entryID==1){   //��ȸ��
		glutTimerFunc(40,MyTimer,1); 
		Cur_left_rotate = true; //��ȸ��
		Cur_right_rotate = false; //��ȸ��
		Cur_Zoom_in = false;
		Cur_Zoom_out = false;
		Cur_Move_left = false;
		Cur_Move_right = false;
		Cur_Stop = false;
		cout << "��ȸ��" <<endl;
	}else if(entryID==2){  //��ȸ��
		glutTimerFunc(40,MyTimer,1); 

		Cur_left_rotate = false; //��ȸ��
		Cur_right_rotate = true; //��ȸ��
		Cur_Zoom_in = false;
		Cur_Zoom_out = false;
		Cur_Move_left = false;
		Cur_Move_right = false;
		Cur_Stop = false;
		cout << "��ȸ��" <<endl;

	}else if(entryID==3){  //Ȯ��
		glutTimerFunc(40,MyTimer,1); 
		
		Cur_left_rotate = false; //��ȸ��
		Cur_right_rotate = false; //��ȸ��
		Cur_Zoom_in = true;
		Cur_Zoom_out = false;
		Cur_Move_left = false;
		Cur_Move_right = false;
		Cur_Stop = false;
		cout << "Ȯ��" <<endl;
		
	}else if(entryID==4){  //���
		glutTimerFunc(40,MyTimer,1); 
		
		Cur_left_rotate = false; //��ȸ��
		Cur_right_rotate = false; //��ȸ��
		Cur_Zoom_in = false;
		Cur_Zoom_out = true;
		Cur_Move_left = false;
		Cur_Move_right = false;
		Cur_Stop = false;
		cout << "���" <<endl;

	}else if(entryID==5){  //�·��̵�
		glutTimerFunc(40,MyTimer,1); 
		Cur_left_rotate = false; //��ȸ��
		Cur_right_rotate = false; //��ȸ��
		Cur_Zoom_in = false;
		Cur_Zoom_out = false;
		Cur_Move_left = true;
		Cur_Move_right = false;
		Cur_Stop = false;
		cout << "���̵�" <<endl;

	}else if(entryID==6){  //����̵�
		glutTimerFunc(40,MyTimer,1); 
		Cur_left_rotate = false; //��ȸ��
		Cur_right_rotate = false; //��ȸ��
		Cur_Zoom_in = false;
		Cur_Zoom_out = false;
		Cur_Move_left = false;
		Cur_Move_right = true;
		Cur_Stop = false;
		cout << "���̵�" <<endl;
	}

}


void MyReshape(int NewWidth, int NewHeight) {
	// NewWidth, NewHeight : ����� ������ ũ��
	
	glViewport(0, 0, NewWidth, NewHeight);
	// ����Ʈ ũ�� ����
	GLfloat WidthFactor = (GLfloat)NewWidth / (GLfloat)window_width;
	GLfloat HeightFactor = (GLfloat)NewHeight / (GLfloat)window_height;
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-1.0 * WidthFactor, 1.0 * WidthFactor,
		-1.0 * HeightFactor, 1.0 * HeightFactor, -1.0, 1.0);		//z���� ������ ����.
	// ���� ���� ũ�� ����
}


int main(int argc, char** argv){
	glutInit(&argc,argv);					
	glutInitDisplayMode(GLUT_RGB |GLUT_DOUBLE);	//���� ���۸��� �����.
	glutInitWindowSize(window_width,window_height);
	glutInitWindowPosition(0, 0); 
	
	glClearColor (1.0,1.0,1.0,1.0f);
    glMatrixMode(GL_PROJECTION);    
    glLoadIdentity();    
    glOrtho(-1.0, 1.0, -1.0, 1.0, 1.0, -1.0);  
	
	//�޴� �����
	GLint rotate = glutCreateMenu(MySubMenu); //���� �޴� ����
	glutAddMenuEntry("��ȸ��", 1);	// �޴� �Ӽ�����
	glutAddMenuEntry("��ȸ��", 2);

	GLint zoom = glutCreateMenu(MySubMenu); //���� �޴� ����
	glutAddMenuEntry("Ȯ��", 3);	// �޴� �Ӽ�����
	glutAddMenuEntry("���", 4);
	
	GLint move = glutCreateMenu(MySubMenu); //���� �޴� ����
	glutAddMenuEntry("�·��̵�", 5);	// �޴� �Ӽ�����
	glutAddMenuEntry("����̵�", 6);

	GLint MyMainMenuID = glutCreateMenu(MyMainMenu);// ���θ޴� ��ü�� ����
	glutAddSubMenu("ȸ��", rotate);
	glutAddSubMenu("Ȯ�� ���",zoom);
	glutAddSubMenu("�̵�", move);
	glutAddMenuEntry("���󺯰�", 3);
	glutAddMenuEntry("����", 4);
	glutAddMenuEntry("��¦��", 5);
	glutAddMenuEntry("����", 6);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
	//�޴� ����� ����.

	X1=-0.2;
	Y1=0.2;
	X2=0.2;
	Y2=0.2;
	X3=-0.2;
	Y3=-0.2;
	X4=0.2;
	Y4=-0.2;

	glutCreateWindow("�� �̸�����"); 		   
	glutDisplayFunc(MyDisplay);
	glutMouseFunc(MyMouse);
   	glutReshapeFunc(MyReshape);			
	glutKeyboardFunc(MyKeyboard);
	glutMainLoop( );					
	return 0; 
}
