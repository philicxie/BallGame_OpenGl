//
//  MyPlayGround.cpp
//  gldemo_toushi
//
//  Created by Philic on 15/10/23.
//  Copyright © 2015年 Philic. All rights reserved.
//

#include "MyPlayGround.hpp"
#define SCALE_X 11.0f
#define SCALE_Y 7.0f
#define TRUE_X  82.5f
#define TRUE_Y  52.5f

MyPlayGround::MyPlayGround()
{
    distances.push_back(TRUE_X);
    distances.push_back(TRUE_Y);
    distances.push_back(TRUE_X);
    distances.push_back(TRUE_Y);
    distances.push_back(5);
    distances.push_back(60);
    wallFuncs.push_back(myVector3f(1,0,0));
    wallFuncs.push_back(myVector3f(0,0,1));
    wallFuncs.push_back(myVector3f(-1,0,0));
    wallFuncs.push_back(myVector3f(0,0,-1));
    wallFuncs.push_back(myVector3f(0,1,0));
    wallFuncs.push_back(myVector3f(0,-1,0));
}

void MyPlayGround::draw()
{
    glPushMatrix();
    glTranslated(0.0, -5.75, 0.0);
    glColor3f(0.8f, 0.5f, 0.7f);
    glScaled(SCALE_X, 0.1, SCALE_Y);
    glutSolidCube(2*TRUE_X/SCALE_X);
    glPopMatrix();
}

int MyPlayGround::getWallCount()
{
    return wallFuncs.size();
}

myVector3f MyPlayGround::getWallFunc(int index)
{
    return  wallFuncs[index];
}

float MyPlayGround::getDistance(int index)
{
    return distances[index];
}