#include<glut.h>
#include<gl\GLU.h>
#include<gl\GL.h>
#include<fstream>

#define WIDTH 4
#define HEIGHT 3

int Row_Max;	//이미지의 최대 행의수 
int Col_Max;	//최대 열의수
int Window_Width = 700;
int Window_Height = 700;

GLubyte MyTexture[WIDTH][HEIGHT][3];
const float fMinX = -5.0, fMinY = -5.0, fNearZ = 1.0, fMaxX = 5.0 , fMaxY = 5.0 , fFarZ = 10.0;


struct Image{
	unsigned char* pixels;
	int width;
	int height;
	int numChannels;
};

class Texture{
	public:
		Texture();	//생성자
		void Prepare(int texN);
		void ReadPPMImage( char *fn);
		GLuint texName;
		Image image;
};


void Texture::Prepare(int texN){
	this->texName = texN;
	glPixelStorei(GL_UNPACK_ALIGNMENT , 1);
	glBindTexture(GL_TEXTURE_2D, texName);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, image.width, image.height, 0, GL_RGB, GL_UNSIGNED_BYTE, image.pixels);
}

Texture ImageOne; //texture 이미지 

Texture::Texture ()
{
}

void Texture::ReadPPMImage(char* fn){  //fn은 파일이름  --> ppm방법으로 파일읽기
	int tmpint;		// ppm에 관련된 변수인듯 > > 
	char str[100];  //파일 객체를 저장할 변수

	FILE* inFile = fopen(fn, "rb");  //파일스트림 저장.

	if(inFile == NULL){  //파일이 없을때, 
		printf("Can't open input file %s. Exitng.\n", fn);
		exit(1);
	}

	fscanf(inFile, "P%d\n", &tmpint);

	if (tmpint != 6)  // ppm에 관련된 변수인듯.
    {
        printf ("Input file is not ppm. Exiting.\n");
        exit (1);
    }

	fgets(str, 100, inFile);  //파일객체를 str에 저장.(파일로부터 문자열을 읽어옴)

	while(str[0] == '#')  //image dimensions를 읽어온다. --> 맨끝이 '#'임
		fgets(str, 100, inFile);

	sscanf(str, "%d %d", &image.width, &image.height);  //이미 변수에 저장된 값들을 다른변수에 저장. sscanf함수
	fgets(str, 100, inFile);  //파일로 부터 문자열을 읽어들이는 함수
	sscanf(str, "%d", &tmpint);	

	if(tmpint != 255)
		printf("Warning : maxvalue is not 255 in ppm file\n");
	image.numChannels = 3;  //3차원-> R,G,B
	image.pixels = (unsigned char*) malloc (image.numChannels * image.width *  image.height * sizeof (unsigned char)); //각각의RGB값에 필요한pixel 동적할당.
	
	if(image.pixels == NULL){  //이미지가 없을때 예외처리
		 printf ("Can't allocate image of size %dx%d. Exiting\n", image.width, image.height);
        exit (1);
	}else{
		printf("Reading image %s of size %dx%d\n", fn, image.width, image.height);
	}
	
	fread (image.pixels, sizeof (unsigned char), image.numChannels * image.width * image.height, inFile); 
	//image.pixel에 저장 -> 데이터하나의크기, 읽어들일 데이터갯수, 대상파일스트림
    fclose (inFile);
}

void FillMyTexture() {
    int s, t;
    for(s = 0; s < WIDTH; s++) {
        for(t = 0; t < HEIGHT; t++) {
            GLubyte Intensity = ((s + t) % 2) * 255;    //0는 흑색, 255는 백색
            MyTexture[s][t][0] = Intensity;             //Red 값에 할당
            MyTexture[s][t][1] = Intensity;             //Green 값에 할당
            MyTexture[s][t][2] = Intensity;             //Blue 값에 할당
        }
    }
}

void MyInit() {
    glClearColor (0.0, 0.0, 0.0, 0.0);
    glEnable (GL_DEPTH_TEST);

    glGenTextures (1, &ImageOne.texName); 
    ImageOne.ReadPPMImage("카카오1.ppm");
    ImageOne.Prepare(1) ;
}


void MyReshape(int width, int height){
	glViewport (0, 0, width, height);

    glMatrixMode (GL_PROJECTION);
    glLoadIdentity ();

    glOrtho (fMinX, fMaxX, fMinY, fMaxY, fNearZ, fFarZ);

    glMatrixMode (GL_MODELVIEW);
    glLoadIdentity ();
}


void MyDisplay(){

	glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable (GL_TEXTURE_2D);
    glTexEnvf (GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_BLEND);
    glBindTexture (GL_TEXTURE_2D, ImageOne.texName); 

    glBegin(GL_QUADS);
        glTexCoord2f(0,1);
        glVertex3f(-5.5,5,-6);
        glTexCoord2f(0,0);
        glVertex3f(-5.5,-5,-6);
        glTexCoord2f(1,0);
        glVertex3f(5,-5,-6);
        glTexCoord2f(1,1);
        glVertex3f(5,5,-6);
    glEnd();
    glDisable(GL_TEXTURE_2D);

    glutSwapBuffers ();
    glFlush ();

}



void main(int argc, char* argv[]){
	    // init GLUT and create window
    glutInit (&argc, argv);
    glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowPosition(100,100);
    glutInitWindowSize(500,500);
    glutCreateWindow ("OpenGL - Rotating Cubes");

    MyInit ();

    // register callbacks
    glutDisplayFunc (MyDisplay);
    glutReshapeFunc (MyReshape);

    // enter GLUT event processing cycle
    glutMainLoop();

}