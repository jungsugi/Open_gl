#include<glut.h>
#include<gl\GLU.h>
#include<gl\GL.h>
#include<fstream>

#define WIDTH 4
#define HEIGHT 3

int Row_Max;	//�̹����� �ִ� ���Ǽ� 
int Col_Max;	//�ִ� ���Ǽ�
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
		Texture();	//������
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

Texture ImageOne; //texture �̹��� 

Texture::Texture ()
{
}

void Texture::ReadPPMImage(char* fn){  //fn�� �����̸�  --> ppm������� �����б�
	int tmpint;		// ppm�� ���õ� �����ε� > > 
	char str[100];  //���� ��ü�� ������ ����

	FILE* inFile = fopen(fn, "rb");  //���Ͻ�Ʈ�� ����.

	if(inFile == NULL){  //������ ������, 
		printf("Can't open input file %s. Exitng.\n", fn);
		exit(1);
	}

	fscanf(inFile, "P%d\n", &tmpint);

	if (tmpint != 6)  // ppm�� ���õ� �����ε�.
    {
        printf ("Input file is not ppm. Exiting.\n");
        exit (1);
    }

	fgets(str, 100, inFile);  //���ϰ�ü�� str�� ����.(���Ϸκ��� ���ڿ��� �о��)

	while(str[0] == '#')  //image dimensions�� �о�´�. --> �ǳ��� '#'��
		fgets(str, 100, inFile);

	sscanf(str, "%d %d", &image.width, &image.height);  //�̹� ������ ����� ������ �ٸ������� ����. sscanf�Լ�
	fgets(str, 100, inFile);  //���Ϸ� ���� ���ڿ��� �о���̴� �Լ�
	sscanf(str, "%d", &tmpint);	

	if(tmpint != 255)
		printf("Warning : maxvalue is not 255 in ppm file\n");
	image.numChannels = 3;  //3����-> R,G,B
	image.pixels = (unsigned char*) malloc (image.numChannels * image.width *  image.height * sizeof (unsigned char)); //������RGB���� �ʿ���pixel �����Ҵ�.
	
	if(image.pixels == NULL){  //�̹����� ������ ����ó��
		 printf ("Can't allocate image of size %dx%d. Exiting\n", image.width, image.height);
        exit (1);
	}else{
		printf("Reading image %s of size %dx%d\n", fn, image.width, image.height);
	}
	
	fread (image.pixels, sizeof (unsigned char), image.numChannels * image.width * image.height, inFile); 
	//image.pixel�� ���� -> �������ϳ���ũ��, �о���� �����Ͱ���, ������Ͻ�Ʈ��
    fclose (inFile);
}

void FillMyTexture() {
    int s, t;
    for(s = 0; s < WIDTH; s++) {
        for(t = 0; t < HEIGHT; t++) {
            GLubyte Intensity = ((s + t) % 2) * 255;    //0�� ���, 255�� ���
            MyTexture[s][t][0] = Intensity;             //Red ���� �Ҵ�
            MyTexture[s][t][1] = Intensity;             //Green ���� �Ҵ�
            MyTexture[s][t][2] = Intensity;             //Blue ���� �Ҵ�
        }
    }
}

void MyInit() {
    glClearColor (0.0, 0.0, 0.0, 0.0);
    glEnable (GL_DEPTH_TEST);

    glGenTextures (1, &ImageOne.texName); 
    ImageOne.ReadPPMImage("īī��1.ppm");
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