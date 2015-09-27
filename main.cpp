
//------------------------
#include <windows.h>
#include <stdio.h>
#include <iostream>
#include "myGLFunctions.h"

//マクロ --------------------------------------------------------------------------------------
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
	double distance;		// 視点から物体までの距離 [m]
	double twist;		// 視線回りの回転角度 [rad]
	double elevation;	// 物体を見下ろす角度 [rad]
	double azimuth;		// 鉛直軸回りの回転角度 [rad]
	double s;			// 画面上の位置（横方向）
	double t;			// 画面上の位置（縦方向）
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

	glutKeyboardFunc(keyboard);		// 一般キー
	glutMouseFunc(mouseButton);				// マウスクリック
	glutMouseWheelFunc(mouseWheel);	// マウスホイール
	glutMotionFunc(mouseMotion);			// マウスドラッグ
	//描画関数
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutIdleFunc(idle);				// アイドル：実質メインループ・データの取得など（NULLにすると登録なし）


	glutMainLoop();		//イベント待ち無限ループ
	
	return 0;
}


void display(void){
	
	glClear(GL_COLOR_BUFFER_BIT |	//カラーバッファの初期化
			GL_DEPTH_BUFFER_BIT);	//デプスバッファの初期化

	glLoadIdentity();	//モデルビュー変換行列の初期化

		//gluLookAt(15.0+g_camera.s, 15.0, 15.0,	//この座標から
		//	0.0, 0.0, 0.0,	//この点を見る
		//	0.0, 0.0, 1.0);	//上はこの方向
	
	glPushMatrix();
	//------------
	glTranslated(g_camera.s, -g_camera.t, -g_camera.distance);// 視点から物体までの距離
	glRotated(-g_camera.twist*RAD2DEG, 0.0, 0.0, 1.0);// 視線回りの回転角度
	glRotated(-g_camera.elevation*RAD2DEG, 1.0, 0.0, 0.0);// 物体を見下ろす角度
	glRotated(-g_camera.azimuth*RAD2DEG, 0.0, 0.0, 1.0);// 鉛直軸回りの回転角度
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
		glColor3d(1.0, 1.0, 0.0);//黄色
//		drawCircle(1.0, 10.0);
	glPopMatrix();

	glPushMatrix();
		glTranslated(2.0, 0.0, 0.0);
		glLineWidth(5.0);	//線の太さ
		glColor3d(0.0, 1.0, 0.0);//緑
//		drawCircleEdge(2.0, 10.0);
	glPopMatrix();

	glPushMatrix();
		glTranslated(-2.0, 0.0, 0.0);
		glColor3d(0.0, 1.0, 1.0);//水色
//		drawCylinder(2.0, 100.0, 5.0);
	glPopMatrix();

	glPushMatrix();
		//glTranslated(-2.0, 0.0, 0.0);
		glColor3d(1.0, 0.0, 0.0);//赤色
//		drawCylinderSurface(2.0, 30.0, 3.0);
	glPopMatrix();

	glPushMatrix();
		glLineWidth(3.0);
		glColor3f(1.0, 0.0, 1.0);	//ピンク色
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



	glutSwapBuffers();	//バッファのスワップ（ダブルバッファモードでの描画コマンド(参考:http://www.ics.kagoshima-u.ac.jp/edu/ProgramingJava/UsingImage/s5.html)）

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
	// ドラッグ開始点のx, y座標値を取得
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

		
	//マウスホイールのスクロール量に応じてズーム
	//　ホイールが動いたときに呼び出されるこの関数内で更新グローバル変数を更新する必要がある！
	g_camera.distance -= (double)wheelScroll/20.0;
	
	// 結果を描画に反映
	glutPostRedisplay();
}

void mouseMotion (int x, int y) 
{
	//変数
	int xDisp, yDisp;

	// マウス移動距離の計算
	xDisp = x - g_xBegin;
	yDisp = y - g_yBegin;

	switch(g_mButton){
	// 左ボタンのドラッグで物体と視点の角度を変える
	case GLUT_LEFT_BUTTON:
		g_camera.azimuth -= ((double) xDisp / 2.0) * DEG2RAD;
		g_camera.elevation -= ((double) yDisp / 2.0) * DEG2RAD;
		break;

	// 中央ボタンのドラッグで画面2次元平面の移動
	case GLUT_MIDDLE_BUTTON:
		g_camera.s += (double) xDisp / 40.0;	
		g_camera.t += (double) yDisp / 40.0;	
		break;

	// 右ボタンのドラッグ何もなし
	case GLUT_RIGHT_BUTTON:

		break;
	}

	// 次のステップのマウスの出発点の更新
	g_xBegin = x;
	g_yBegin = y;



	// 描画に反映
	glutPostRedisplay();
}


void keyboard (unsigned char key, int x, int y) 
{
	
	//if(&keyboardInput==NULL){memset(&keyboardInput, 0.0, sizeof(keyboardInput));}

	//switch(key){

	//case 'x'://x方向に0.01進んだとする
	//	keyboardInput.x	+= 0.01;
	//	break;

	//case 'y'://y方向に0.01進んだとする
	//	keyboardInput.y += 0.01;
	//	break;

	//case 'z'://z方向に0.01進んだとする
	//	keyboardInput.z += 0.01;
	//	break;
	//}

	// 描画に反映
	glutPostRedisplay();
}


void idle(void){


}

void init(void){

	ZeroMemory(&g_camera, 0.0);
	g_camera.distance=5.0;

	// 投影変換行列スタックを操作対象とする
	glMatrixMode(GL_PROJECTION);


}
