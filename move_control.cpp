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

GLfloat rvalue = 1.0, gvalue = 1.0, bvalue = 1.0;//색을 나타내는 변수

bool Cur_left_rotate = false; //좌회전
bool Cur_right_rotate = false; //우회전
bool Cur_Zoom_in = false;
bool Cur_Zoom_out = false;
bool Cur_Move_left = false;
bool Cur_Move_right = false;
bool Cur_Stop = false;
bool twingkle = false;

GLfloat sq[4][2] = {0.0};	//x,y좌표
GLfloat X1,X2,X3,X4,Y1,Y2,Y3,Y4;
GLfloat temp1,temp2,temp3; //이전색상을 저장.
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


void MyKeyboard(unsigned char KeyPressed, int X, int Y) { //키보드클릭 이벤트루프
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
		rvalue = 0.25; gvalue = 0.0; bvalue = 0.5; break; //1~5 색깔선택
	}

}

void MyDisplay( ){			
	
	glClear(GL_COLOR_BUFFER_BIT);	
	glColor3f(rvalue, gvalue, bvalue);
	
	if(Cur_left_rotate){   //좌회전
		glRotatef(Cur_rotate,0.0, 0.0 , 1.0);

		glBegin(GL_POLYGON);
		glVertex3f(X1, Y1, 0.0);
		glVertex3f(X3, Y3, 0.0);
		glVertex3f(X4, Y4, 0.0);
		glVertex3f(X2, Y2, 0.0);
		glEnd( );

	}else if(Cur_right_rotate){  //우회전
		glRotatef(Cur_rotate,0.0, 0.0 , -1.0);

		glBegin(GL_POLYGON);
		glVertex3f(X1, Y1, 0.0);
		glVertex3f(X3, Y3, 0.0);
		glVertex3f(X4, Y4, 0.0);
		glVertex3f(X2, Y2, 0.0);
		glEnd( );

	}else if(Cur_Move_left == true){  //왼쪽이동 
		
		glTranslatef(0.01f,0.0f,0.0f);

		glBegin(GL_POLYGON);		
		glVertex3f(X1, Y1, 0.0);
		glVertex3f(X3, Y3, 0.0);
		glVertex3f(X4, Y4, 0.0);
		glVertex3f(X2, Y2, 0.0);
		glEnd( );

	}else if(Cur_Move_right == true){  //오른쪽 이동
		glTranslatef(-0.01f,0.0f,0.0f);

		glBegin(GL_POLYGON);	
		glVertex3f(X1, Y1, 0.0);
		glVertex3f(X3, Y3, 0.0);
		glVertex3f(X4, Y4, 0.0);
		glVertex3f(X2, Y2, 0.0);
		glEnd( );

	}else if(Cur_Zoom_in){  //확대
		glScalef(Cur_scale_x, Cur_scale_y, 1.0f); 
		
		glBegin(GL_POLYGON);
		glVertex3f(X1, Y1, 0.0);
		glVertex3f(X3, Y3, 0.0);
		glVertex3f(X4, Y4, 0.0);
		glVertex3f(X2, Y2, 0.0);
		glEnd( );
		
	}else if(Cur_Zoom_out){  //축소
		glScalef(-Cur_scale_x, -Cur_scale_y, 1.0f); 
		
		glBegin(GL_POLYGON);	
		glVertex3f(X1, Y1, 0.0);
		glVertex3f(X3, Y3, 0.0);
		glVertex3f(X4, Y4, 0.0);
		glVertex3f(X2, Y2, 0.0);
		glEnd( );
		
	}else{		//정지
		
		glBegin(GL_POLYGON);	
		glVertex3f(X1, Y1, 0.0);
		glVertex3f(X3, Y3, 0.0);
		glVertex3f(X4, Y4, 0.0);
		glVertex3f(X2, Y2, 0.0);
		glEnd( );
	}

	glFlush( ); 		
	
	//display callback 함수에서 장면을 모델링한후에
	glutSwapBuffers();	//buffer를 바꿔줌.					
}

void MyMainMenu(int entryID){

	if(entryID==1){   //회전
		
	}else if(entryID==2){  //확대,축소
		
	}else if(entryID==3){  //좌,우
		
	}else if(entryID==4){  //정지
		Cur_Stop = true;
		Cur_left_rotate = false; //좌회전
		Cur_right_rotate = false; //우회전
		Cur_Zoom_in = false;
		Cur_Zoom_out = false;
		Cur_Move_left = false;
		Cur_Move_right = false;
		twingkle=false;
	}else if(entryID==5){   //반짝이
		twingkle=true;
	}else if(entryID==6){  //종료
		exit(0);
	}

	glutPostRedisplay();

}

void MySubMenu(int entryID){
	if(entryID==1){   //좌회전
		glutTimerFunc(40,MyTimer,1); 
		Cur_left_rotate = true; //좌회전
		Cur_right_rotate = false; //우회전
		Cur_Zoom_in = false;
		Cur_Zoom_out = false;
		Cur_Move_left = false;
		Cur_Move_right = false;
		Cur_Stop = false;
		cout << "좌회전" <<endl;
	}else if(entryID==2){  //우회전
		glutTimerFunc(40,MyTimer,1); 

		Cur_left_rotate = false; //좌회전
		Cur_right_rotate = true; //우회전
		Cur_Zoom_in = false;
		Cur_Zoom_out = false;
		Cur_Move_left = false;
		Cur_Move_right = false;
		Cur_Stop = false;
		cout << "우회전" <<endl;

	}else if(entryID==3){  //확대
		glutTimerFunc(40,MyTimer,1); 
		
		Cur_left_rotate = false; //좌회전
		Cur_right_rotate = false; //우회전
		Cur_Zoom_in = true;
		Cur_Zoom_out = false;
		Cur_Move_left = false;
		Cur_Move_right = false;
		Cur_Stop = false;
		cout << "확대" <<endl;
		
	}else if(entryID==4){  //축소
		glutTimerFunc(40,MyTimer,1); 
		
		Cur_left_rotate = false; //좌회전
		Cur_right_rotate = false; //우회전
		Cur_Zoom_in = false;
		Cur_Zoom_out = true;
		Cur_Move_left = false;
		Cur_Move_right = false;
		Cur_Stop = false;
		cout << "축소" <<endl;

	}else if(entryID==5){  //좌로이동
		glutTimerFunc(40,MyTimer,1); 
		Cur_left_rotate = false; //좌회전
		Cur_right_rotate = false; //우회전
		Cur_Zoom_in = false;
		Cur_Zoom_out = false;
		Cur_Move_left = true;
		Cur_Move_right = false;
		Cur_Stop = false;
		cout << "좌이동" <<endl;

	}else if(entryID==6){  //우로이동
		glutTimerFunc(40,MyTimer,1); 
		Cur_left_rotate = false; //좌회전
		Cur_right_rotate = false; //우회전
		Cur_Zoom_in = false;
		Cur_Zoom_out = false;
		Cur_Move_left = false;
		Cur_Move_right = true;
		Cur_Stop = false;
		cout << "우이동" <<endl;
	}

}


void MyReshape(int NewWidth, int NewHeight) {
	// NewWidth, NewHeight : 변경된 윈도우 크기
	
	glViewport(0, 0, NewWidth, NewHeight);
	// 뷰포트 크기 변경
	GLfloat WidthFactor = (GLfloat)NewWidth / (GLfloat)window_width;
	GLfloat HeightFactor = (GLfloat)NewHeight / (GLfloat)window_height;
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-1.0 * WidthFactor, 1.0 * WidthFactor,
		-1.0 * HeightFactor, 1.0 * HeightFactor, -1.0, 1.0);		//z축은 변하지 않음.
	// 가시 부피 크기 변경
}


int main(int argc, char** argv){
	glutInit(&argc,argv);					
	glutInitDisplayMode(GLUT_RGB |GLUT_DOUBLE);	//더블 버퍼링을 사용함.
	glutInitWindowSize(window_width,window_height);
	glutInitWindowPosition(0, 0); 
	
	glClearColor (1.0,1.0,1.0,1.0f);
    glMatrixMode(GL_PROJECTION);    
    glLoadIdentity();    
    glOrtho(-1.0, 1.0, -1.0, 1.0, 1.0, -1.0);  
	
	//메뉴 만들기
	GLint rotate = glutCreateMenu(MySubMenu); //서브 메뉴 생성
	glutAddMenuEntry("좌회전", 1);	// 메뉴 속성정의
	glutAddMenuEntry("우회전", 2);

	GLint zoom = glutCreateMenu(MySubMenu); //서브 메뉴 생성
	glutAddMenuEntry("확대", 3);	// 메뉴 속성정의
	glutAddMenuEntry("축소", 4);
	
	GLint move = glutCreateMenu(MySubMenu); //서브 메뉴 생성
	glutAddMenuEntry("좌로이동", 5);	// 메뉴 속성정의
	glutAddMenuEntry("우로이동", 6);

	GLint MyMainMenuID = glutCreateMenu(MyMainMenu);// 메인메뉴 객체를 생성
	glutAddSubMenu("회전", rotate);
	glutAddSubMenu("확대 축소",zoom);
	glutAddSubMenu("이동", move);
	glutAddMenuEntry("생상변경", 3);
	glutAddMenuEntry("정지", 4);
	glutAddMenuEntry("반짝이", 5);
	glutAddMenuEntry("종료", 6);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
	//메뉴 만들기 종료.

	X1=-0.2;
	Y1=0.2;
	X2=0.2;
	Y2=0.2;
	X3=-0.2;
	Y3=-0.2;
	X4=0.2;
	Y4=-0.2;

	glutCreateWindow("내 이름쓰기"); 		   
	glutDisplayFunc(MyDisplay);
	glutMouseFunc(MyMouse);
   	glutReshapeFunc(MyReshape);			
	glutKeyboardFunc(MyKeyboard);
	glutMainLoop( );					
	return 0; 
}
