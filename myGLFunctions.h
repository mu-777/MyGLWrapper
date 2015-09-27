//====================================================================================//
//���O�FmyGLFunctions.h
//�����FOpenGL�ɂ��`�悷��}�`�Ɨ��̂̑f��
//====================================================================================//
#ifndef MYGLFUNCTIONS_H
#define MYGLFUNCTIONS_H


#include <math.h>
#include <string>

#define GLUT_BUILDING_LIB//��������Ȃ���#include <GL/glut.h> �ŃR���p�C���G���[���o�邱�Ƃ�����D
#include <GL/freeglut.h> // GL/glut.h��ǂݍ��߂΁CGL/gl.h, GL/glu.h���ǂݍ��܂��



	void drawCylinder(const float radius, const int div ,const float width);//�~��(���C���[���f��)
	void drawCylinderSurface(const float radius, const int div ,const float width);//�~��(�T�[�t�F�X���f��)

	void drawSphere(double sphere_size);//��
	void drawCircle (const float radius, const int div);//�~
	void drawCircleEdge(const float radius, const int div);//�~��

	void drawGrandAxis (void);//���W��
		
	void drawGrand (int width, int depth, int interval);//�n�� 
	void drawGrand2 (double width, double depth, double interval, double power);

	void drawGrandRadial (double radius ,double degree); //�n�ʁi���@����̕��ˏ���j
	void drawGrandEqualDistance (double radius ,double interval);	//�n�ʁi���@����̓��������j
	void drawLine(double startPoint[], double endPoint[]);
	void drawEye(float width, float height);
	void drawEye2 (double width, double height, double h_gakaku);
	void drawObstacle(void);
	void drawRailroadLine(double modelSize[3], double startPos[3], double endPos[3]);
	void drawRailroadLine(double modelSize[3], double aspect, double h_gakaku, double startPos[6], double endPos[3]);
	void drawString(double global_x, double global_y, double global_z, std::string const& str);
	void drawString(double screen_x, double screen_y, double width, double height, std::string const& str);
	void drawStringBig(double screen_x, double screen_y, double width, double height, std::string const& str);
	void drawLayerOnScreen(double width, double height, double alpha);
		



#endif