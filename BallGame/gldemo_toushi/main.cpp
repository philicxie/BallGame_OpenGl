//
//  main.cpp
//  gldemo_toushi
//
//  Created by Philic on 15/10/22.
//  Copyright © 2015年 Philic. All rights reserved.
//

#define GLUT_DISABLE_ATEXIT_HACK


#include "AllHeaders.h"
#include "MyPlayGround.hpp"
#include "MyGameWorld.hpp"
#define WIN_WIDTH   1200
#define WIN_HEIGHT  800
//using namespace std;

MyGameWorld *game;
static bool Pause = false;
static float c=M_PI/180.0f;         //弧度和角度转换参数
static int du=90,oldmy=-1,oldmx=-1; //du是视点绕y轴的角度,opengl里默认y轴是上方向
static float r=100.0f,h=20.0f;      //r是视点绕y轴的半径,h是视点高度即在y轴上的坐标

//显示 回调函数
void OnDisplay(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST); //启用深度检测
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(r*cos(c*du), h, r*sin(c*du), 0, 0, 0, 0, 1.0, 0.0); //从视点看远点,y轴方向(0,1,0)是上方向
    game->draw();
    glutSwapBuffers();
}

//用于发送刷新信号的计时器
void gameLoop(int time)
{
    if(!Pause){
        game->simulate(0.07);
        glutPostRedisplay();
        glutTimerFunc(30, gameLoop, 1);
    }
}
//窗口尺寸变化后的回调函数
void OnReShape(int w,int h)
{
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION); //将当前矩阵指定为投影模式
    glLoadIdentity();
    if (0 != h){
        GLfloat aspect =(float)w / (float)h;
        gluPerspective(60.0f, aspect, 1.0f, 200.0f); //透视投影
    }
}

void OnMouse(int button, int state, int x, int y)
{
     //第一次鼠标按下时,记录鼠标在窗口中的初始坐标
    oldmx=x,oldmy=y;
    if (button==GLUT_LEFT_BUTTON) {
        GLint viewport[4];
        GLdouble mvmatrix[16], projmatrix[16];
        GLfloat winx, winy, winz;
        GLdouble posx, posy, posz;
        glPushMatrix();
        //glScalef(0.1, 0.1, 0.1);
        glGetIntegerv(GL_VIEWPORT, viewport);           /* 获取三个矩阵 */
        glGetDoublev(GL_MODELVIEW_MATRIX, mvmatrix);
        glGetDoublev(GL_PROJECTION_MATRIX, projmatrix);
        glPopMatrix();
        winx = x;
        winy = WIN_HEIGHT - y;
        glReadPixels((int)winx, (int)winy, 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &winz);          /* 获取深度 */
        gluUnProject(winx, winy, winz, mvmatrix, projmatrix, viewport, &posx, &posy, &posz);    /* 获取三维坐标 */
        game->hitCure(posx, posy, posz);
    }
}

void OnMouseMove(int x,int y) //处理鼠标拖动
{
    du+=x-oldmx; //鼠标在窗口x轴方向上的增量加到视点绕y轴的角度上，这样就左右转了
    h +=0.3f*(y-oldmy); //鼠标在窗口y轴方向上的改变加到视点的y坐标上，就上下转了
    
    if(h>100.0f)
        h=100.0f;
    else if(h<-100.0f)          //对视角高度做强制限制
        h=-100.0f;
    oldmx=x,oldmy=y; //把此时的鼠标坐标作为旧值，为下一次计算增量做准备
    glutPostRedisplay();
}

void OnKey(int key, int x, int y)
{
    if(key=='p')
        if(Pause){
            Pause = false;
            glutTimerFunc(100, gameLoop, 1);
        }
        else
            Pause = true;
}
void AddBalls()
{
    MyBall tem;
    tem.setPosition(-50, 0, -20);
    tem.setSize(5);
    tem.setType(QUAFFLE);
    game->addBall(tem);
    tem.setPosition(-30, 0, -20);
    game->addBall(tem);
    tem.setPosition(-10, 0, -20);
    game->addBall(tem);
    tem.setPosition(10, 0, -20);
    game->addBall(tem);
    tem.setPosition(30, 0, -20);
    game->addBall(tem);
    tem.setPosition(50, 0, -20);
    game->addBall(tem);
    tem.setSpeed(-20, 20 ,10);
    tem.setType(BLUDGER);
    tem.setPosition(-50, 0, 20);
    game->addBall(tem);
    tem.setPosition(-30, 0, 20);
    game->addBall(tem);
    tem.setPosition(-10, 0, 20);
    game->addBall(tem);
    tem.setPosition(10, 0, 20);
    game->addBall(tem);
    tem.setPosition(30, 0, 20);
    game->addBall(tem);
    tem.setPosition(50, 0, 20);
    game->addBall(tem);
}
//设置光照
void SetupLights()
{
    GLfloat ambientLight[]  = {0.2f,  0.2f,  0.2f,  1.0f};//环境光
    GLfloat diffuseLight[]  = {0.9f,  0.9f,  0.9f,  1.0f};//漫反射
    GLfloat specularLight[] = {1.0f,  1.0f,  1.0f,  1.0f};//镜面光
    GLfloat lightPos[]      = {50.0f, 80.0f, 60.0f, 1.0f};//光源位置
    
    glEnable(GL_LIGHTING);			//启用光照
    glLightfv(GL_LIGHT0, GL_AMBIENT,  ambientLight);	//设置环境光源
    glLightfv(GL_LIGHT0, GL_DIFFUSE,  diffuseLight);	//设置漫反射光源
    glLightfv(GL_LIGHT0, GL_SPECULAR, specularLight);	//设置镜面光源
    glLightfv(GL_LIGHT0, GL_POSITION, lightPos);		//设置灯光位置
    glEnable(GL_LIGHT0);			//打开第一个灯光
    
    glEnable(GL_COLOR_MATERIAL);	//启用材质的颜色跟踪
    glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);	//指定材料着色的面
    glMaterialfv(GL_FRONT, GL_SPECULAR, specularLight); //指定材料对镜面光的反应
    glMateriali(GL_FRONT, GL_SHININESS, 70);			//指定反射系数
}
int main(int argc, char* argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(WIN_WIDTH, WIN_HEIGHT);
    glutCreateWindow("魁地奇V1.0");
    glutReshapeFunc(OnReShape);
    //反走样处理
    glEnable(GL_POINT_SMOOTH);
    glEnable(GL_LINE_SMOOTH);
    glHint(GL_POINT_SMOOTH_HINT, GL_NICEST);
    glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);      glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    game = new MyGameWorld();
    AddBalls();
    
    glutDisplayFunc(OnDisplay);
    glutSpecialFunc(OnKey);
    glutMouseFunc(OnMouse);
    glutMotionFunc(OnMouseMove);
    SetupLights();
    glutTimerFunc(300, gameLoop, 1);
    glutMainLoop();
}