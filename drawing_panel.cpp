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

GLint TopLeftX, TopLeftY, BottomRightX, BottomRightY; //x,y 좌표 변수
GLfloat rvalue = 0.0, gvalue = 0.0, bvalue = 0.0;//색을 나타내는 변수
int LineWidth = 1;//도형의 선 굶기를 나타내는 변수
int shape;

class Figure{
public:
	GLfloat f_rvalue,f_gvalue,f_bvalue;	//도형의 색을 저장.
	GLint topleft_x, topleft_y, bottomright_x, bottomright_y;	//위치.
	int line_width;
	int f_shape;
};

Figure figure[1000];

int counts=0;

void MyMouseClick(GLint Button, GLint State, GLint X, GLint Y) { //마우스클릭 이벤트루프
	if (Button == GLUT_LEFT_BUTTON && State == GLUT_DOWN) { //마우스 눌렀을때 
		
		figure[counts].f_rvalue = rvalue;	//현재 도형 색상 설정.
		figure[counts].f_gvalue = gvalue;
		figure[counts].f_bvalue = bvalue;
		figure[counts].topleft_x = X;
		figure[counts].topleft_y = Y;
		figure[counts].f_shape = shape;		//현재 도형 설정.
		figure[counts].line_width = LineWidth;		//현재 선의 두께 설정.
		glLineWidth(figure[counts].line_width);  //선 굵기 설정 함수
		cout << "갯수"<<counts<<endl; //갯수 출력.
		cout << "줄너비"<<figure[counts].line_width <<endl;
	}
	if(State == GLUT_UP){  //마우스를 땠을때,
		counts++;
	}
}

void MyKeyboard(unsigned char KeyPressed, int X, int Y) { //키보드클릭 이벤트루프
	switch (KeyPressed) { //키를 눌렀을때
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
	
	case 'q':
		exit(0); break;//q 선택시 화면 나감
	case 27:
		counts=-1; 
		
		glutPostRedisplay(); break;//esc 선택시 화면 클리어
	case 'r':
	case 'R':	
		shape = 0; break; //r 선택시 사각형 모양
	case 'T':
	case 't':
		shape = 1; break;//t 선택시 삼각형 모양
	case 'L':
	case 'l':
		shape = 2;break; //'l' 선택시 직선 
	case '[':
		LineWidth += 2; 
		
		break;//선 굵기 설정
	case ']':
		LineWidth -= 2; if (LineWidth <= 0) { LineWidth = 1; }
		
		break; // 선굵기 설정 선굵기가 '0'보다 작아지면 '1'로 초기화
	case 's':	//save기능!
		break;
	}
}


void MyMouseMove(GLint X, GLint Y) {
//마우스 무브 이벤트루프

	figure[counts].bottomright_x = X;
	figure[counts].bottomright_y = Y;

	glutPostRedisplay(); //윈도우 재생 요구하도록 함.
	
		
}

void DisPlayRec(Figure &fig) { //사각형 도형 그리는 함수
	
	glLineWidth(fig.line_width);//선 굵기 설정 함수
	glColor3f(fig.f_rvalue,fig.f_gvalue,fig.f_bvalue); //색 설정 함수
	
	glBegin(GL_POLYGON);
	glVertex3f(fig.topleft_x / 300.0, (300 - fig.topleft_y) / 300.0, 0.0);
	glVertex3f(fig.bottomright_x / 300.0, (300 - fig.topleft_y) / 300.0, 0.0);
	glVertex3f(fig.bottomright_x / 300.0, (300 - fig.bottomright_y) / 300.0, 0.0);
	glVertex3f(fig.topleft_x / 300.0, (300 - fig.bottomright_y) / 300.0, 0.0);
	glEnd();

}



void DisPlayTri(Figure &fig) { //삼각형 도형 그리는 함수
	
	glLineWidth(fig.line_width);//선 굵기 설정 함수
	glColor3f(fig.f_rvalue,fig.f_gvalue,fig.f_bvalue); //색 설정 함수

	glBegin(GL_POLYGON);
	glVertex3f(fig.topleft_x / 300.0, (300 - fig.topleft_y) / 300.0, 0.0);
	glVertex3f(fig.bottomright_x / 300.0, (300 - fig.bottomright_y) / 300.0, 0.0);
	glVertex3f((2 * fig.topleft_x - fig.bottomright_x) / 300.0, (300 - fig.bottomright_y) / 300.0, 0.0);
	glEnd();
}

void DisPlayLine(Figure &fig) { //직선 그리는 함수
	glLineWidth(fig.line_width);  //선 굵기 설정 함수
	
	glBegin(GL_LINES);
	glColor3f(fig.f_rvalue,fig.f_gvalue,fig.f_bvalue); //색 설정 함수
	
	glVertex3f(fig.topleft_x / 300.0, (300 - fig.topleft_y) / 300.0, 0.0);
	glVertex3f(fig.bottomright_x / 300.0, (300 - fig.bottomright_y) / 300.0, 0.0);
	
	glEnd();
}

void MyDisplay() {
	glViewport(0, 0, 300, 300);//뷰포트 좌표계 설정
	glClear(GL_COLOR_BUFFER_BIT);//화면 클리어
	
	for(int i=0; i<counts; i++){
		glLineWidth(figure[i].line_width);  //선 굵기 설정 함수
		if (figure[i].f_shape == 0)	DisPlayRec(figure[i]); //선택한 도형 모양에 따라 도형 그림
		else if (figure[i].f_shape == 1) DisPlayTri(figure[i]);
		else if (figure[i].f_shape == 2) DisPlayLine(figure[i]);
	}if(counts>=0){
		if (figure[counts].f_shape == 0)	DisPlayRec(figure[counts]); //선택한 도형 모양에 따라 도형 그림
		else if (figure[counts].f_shape == 1) DisPlayTri(figure[counts]);
		else if (figure[counts].f_shape == 2) DisPlayLine(figure[counts]);
	}

	glFlush(); //명령 실행
}


int main(int argc, char** argv) {//메인함수부분
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
	glutMainLoop();//무한루프
	return 0;
}