
//------------------------
#include <windows.h>
#include <stdio.h>
#include <iostream>
#include "myGLFunctions.h"

//�}�N�� --------------------------------------------------------------------------------------
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

#ifndef DEG2RAD
#define DEG2RAD 0.017453295199432957692				//(M_PI/180.0)
#endif

#ifndef RAD2DEG
#define RAD2DEG 57.29577951308232876846364344191	//(180.0/M_PI)
#endif

//------------------------
#define WIDTH 640
#define HEIGHT 480

//------------------------
typedef struct{
	double distance;		// ���_���畨�̂܂ł̋��� [m]
	double twist;		// �������̉�]�p�x [rad]
	double elevation;	// ���̂������낷�p�x [rad]
	double azimuth;		// ���������̉�]�p�x [rad]
	double s;			// ��ʏ�̈ʒu�i�������j
	double t;			// ��ʏ�̈ʒu�i�c�����j
} camera_data;

//------------------------
void display(void);
void reshape(int w, int h);
void mouseButton (int button, int state, int x, int y);
void mouseWheel(int wheel_num, int direction, int x, int y);
void mouseMotion (int x, int y);
void keyboard (unsigned char key, int x, int y); 
void idle(void);
void init(void);

//------------------------
int g_mButton=0;
int g_xBegin=0;
int g_yBegin=0;
camera_data g_camera;

//------------------------
int main(int argc, char **argv){

	glutInit(&argc,argv);
	init();

	glutInitDisplayMode(GLUT_RGBA| GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowSize(WIDTH,HEIGHT);
	glutCreateWindow("MyGLClassTest");

	glutKeyboardFunc(keyboard);		// ��ʃL�[
	glutMouseFunc(mouseButton);				// �}�E�X�N���b�N
	glutMouseWheelFunc(mouseWheel);	// �}�E�X�z�C�[��
	glutMotionFunc(mouseMotion);			// �}�E�X�h���b�O
	//�`��֐�
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutIdleFunc(idle);				// �A�C�h���F�������C�����[�v�E�f�[�^�̎擾�ȂǁiNULL�ɂ���Ɠo�^�Ȃ��j


	glutMainLoop();		//�C�x���g�҂��������[�v
	
	return 0;
}


void display(void){
	
	glClear(GL_COLOR_BUFFER_BIT |	//�J���[�o�b�t�@�̏�����
			GL_DEPTH_BUFFER_BIT);	//�f�v�X�o�b�t�@�̏�����

	glLoadIdentity();	//���f���r���[�ϊ��s��̏�����

		//gluLookAt(15.0+g_camera.s, 15.0, 15.0,	//���̍��W����
		//	0.0, 0.0, 0.0,	//���̓_������
		//	0.0, 0.0, 1.0);	//��͂��̕���
	
	glPushMatrix();
	//------------
	glTranslated(g_camera.s, -g_camera.t, -g_camera.distance);// ���_���畨�̂܂ł̋���
	glRotated(-g_camera.twist*RAD2DEG, 0.0, 0.0, 1.0);// �������̉�]�p�x
	glRotated(-g_camera.elevation*RAD2DEG, 1.0, 0.0, 0.0);// ���̂������낷�p�x
	glRotated(-g_camera.azimuth*RAD2DEG, 0.0, 0.0, 1.0);// ���������̉�]�p�x
	//------------
	drawSphere(0.3);


	glPushMatrix();
		glTranslated(1.0,1.0,1.0);
		drawGrandAxis();	
	glPopMatrix();

	glPushMatrix();
		drawGrandAxis();	
	glPopMatrix();

	glPushMatrix();
		glColor3d(1.0, 1.0, 0.0);//���F
//		drawCircle(1.0, 10.0);
	glPopMatrix();

	glPushMatrix();
		glTranslated(2.0, 0.0, 0.0);
		glLineWidth(5.0);	//���̑���
		glColor3d(0.0, 1.0, 0.0);//��
//		drawCircleEdge(2.0, 10.0);
	glPopMatrix();

	glPushMatrix();
		glTranslated(-2.0, 0.0, 0.0);
		glColor3d(0.0, 1.0, 1.0);//���F
//		drawCylinder(2.0, 100.0, 5.0);
	glPopMatrix();

	glPushMatrix();
		//glTranslated(-2.0, 0.0, 0.0);
		glColor3d(1.0, 0.0, 0.0);//�ԐF
//		drawCylinderSurface(2.0, 30.0, 3.0);
	glPopMatrix();

	glPushMatrix();
		glLineWidth(3.0);
		glColor3f(1.0, 0.0, 1.0);	//�s���N�F
//		drawEye(WIDTH, HEIGHT);
	glPopMatrix();

	glPushMatrix();
			
	glPopMatrix();

	glPushMatrix();
	
	glPopMatrix();
	glPushMatrix();
	
	glPopMatrix();
	glPushMatrix();
	
	glPopMatrix();
	glPushMatrix();
	
	glPopMatrix();


	glPopMatrix();



	glutSwapBuffers();	//�o�b�t�@�̃X���b�v�i�_�u���o�b�t�@���[�h�ł̕`��R�}���h(�Q�l:http://www.ics.kagoshima-u.ac.jp/edu/ProgramingJava/UsingImage/s5.html)�j

}


void reshape(int w, int h){
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(30.0, (double)w / (double)h, 1.0, 100000000000000.0);
	glMatrixMode(GL_MODELVIEW);
}


void mouseButton (int button, int state, int x, int y) 
{
	if(state == GLUT_DOWN){
		switch(button){

			case GLUT_LEFT_BUTTON:
				g_mButton = button;
				break;
			case GLUT_MIDDLE_BUTTON:
				g_mButton = button;
				break;
			case GLUT_RIGHT_BUTTON:
				g_mButton = button;
				break;
		}
	// �h���b�O�J�n�_��x, y���W�l���擾
	g_xBegin = x;
	g_yBegin = y;
	}
}

void mouseWheel(int wheel_num, int direction, int x, int y)
{
	
	int wheelScroll=0;

	if(direction==1){ wheelScroll = 5; }
	else if(direction==-1){ wheelScroll = -5; }
	else { wheelScroll = 0; }

		
	//�}�E�X�z�C�[���̃X�N���[���ʂɉ����ăY�[��
	//�@�z�C�[�����������Ƃ��ɌĂяo����邱�̊֐����ōX�V�O���[�o���ϐ����X�V����K�v������I
	g_camera.distance -= (double)wheelScroll/20.0;
	
	// ���ʂ�`��ɔ��f
	glutPostRedisplay();
}

void mouseMotion (int x, int y) 
{
	//�ϐ�
	int xDisp, yDisp;

	// �}�E�X�ړ������̌v�Z
	xDisp = x - g_xBegin;
	yDisp = y - g_yBegin;

	switch(g_mButton){
	// ���{�^���̃h���b�O�ŕ��̂Ǝ��_�̊p�x��ς���
	case GLUT_LEFT_BUTTON:
		g_camera.azimuth -= ((double) xDisp / 2.0) * DEG2RAD;
		g_camera.elevation -= ((double) yDisp / 2.0) * DEG2RAD;
		break;

	// �����{�^���̃h���b�O�ŉ��2�������ʂ̈ړ�
	case GLUT_MIDDLE_BUTTON:
		g_camera.s += (double) xDisp / 40.0;	
		g_camera.t += (double) yDisp / 40.0;	
		break;

	// �E�{�^���̃h���b�O�����Ȃ�
	case GLUT_RIGHT_BUTTON:

		break;
	}

	// ���̃X�e�b�v�̃}�E�X�̏o���_�̍X�V
	g_xBegin = x;
	g_yBegin = y;



	// �`��ɔ��f
	glutPostRedisplay();
}


void keyboard (unsigned char key, int x, int y) 
{
	
	//if(&keyboardInput==NULL){memset(&keyboardInput, 0.0, sizeof(keyboardInput));}

	//switch(key){

	//case 'x'://x������0.01�i�񂾂Ƃ���
	//	keyboardInput.x	+= 0.01;
	//	break;

	//case 'y'://y������0.01�i�񂾂Ƃ���
	//	keyboardInput.y += 0.01;
	//	break;

	//case 'z'://z������0.01�i�񂾂Ƃ���
	//	keyboardInput.z += 0.01;
	//	break;
	//}

	// �`��ɔ��f
	glutPostRedisplay();
}


void idle(void){


}

void init(void){

	ZeroMemory(&g_camera, 0.0);
	g_camera.distance=5.0;

	// ���e�ϊ��s��X�^�b�N�𑀍�ΏۂƂ���
	glMatrixMode(GL_PROJECTION);


}
