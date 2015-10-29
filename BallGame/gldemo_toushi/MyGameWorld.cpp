//
//  MyGameWorld.cpp
//  gldemo_toushi
//
//  Created by Philic on 15/10/23.
//  Copyright © 2015年 Philic. All rights reserved.
//

#include "MyGameWorld.hpp"
#define HIT_SPEED 50.0f

MyGameWorld::MyGameWorld()
{
    table = new MyPlayGround();
    MyBall tem;
    tem.setColor(0.9, 0.9, 0.9);
    tem.setSize(5);
    tem.setPosition(0, 0, 0);
    tem.setSpeed(0.01,0.01,0.01);
    tem.setType(CUEBALL);
    whiteBall = tem;
    tem.setColor(0.9, 0.5, 0.1);
    tem.setPosition(0, 20, 0);
    tem.setSpeed(0,0,0);
    tem.setSize(3);
    tem.setType(SNITCH);
    goldBall = tem;
}

void MyGameWorld::draw()
{
    table->draw();
    for(int i=0;i<balls.size();i++)
        balls[i].draw();
    whiteBall.draw();
    goldBall.draw();
}

void MyGameWorld::addBall(MyBall newBall)
{
    balls.push_back(newBall);
}

void MyGameWorld::hitCure(float x, float y, float z)
{
    myVector3f tem(x,y,z);
    if (myVecLength(tem, whiteBall.getPos())<=5) {
        myVector3f h2p = myVecPoint(tem, whiteBall.getPos());
        whiteBall.setSpeed(myVecScale(HIT_SPEED/myVecLength(h2p), h2p));
//        myVector3f iPosA = whiteBall.getPos();
//        myVector3f iPosB = myVecScale(HIT_SPEED/myVecLength(h2p)/2, h2p);
//        glColor3f(0.5, 0.3, 0.1);
//        glBegin(GL_LINE);
//        glVertex3f(iPosA.x, iPosA.y, iPosA.z);
//        glVertex3f(iPosB.x, iPosB.y, iPosB.z);
//        glEnd();
    }
}

void MyGameWorld::simulate(float time_t)
{
    srand((unsigned)time(NULL));
    int ranIndex = rand()%(balls.size());
    goldBall.setSpeed(balls[ranIndex].getSpeed());
    goldBall.crashBall(whiteBall, time_t);
    for(int i=0;i<balls.size();i++){
        goldBall.crashBall(balls[i], time_t);
        whiteBall.crashBall(balls[i], time_t);
        for(int j=i+1;j<balls.size();j++){
            balls[i].crashBall(balls[j], time_t);
        }
    }
    int wallCount = this->table->getWallCount();
    for(int i=0;i<balls.size();i++){
        for(int j=0;j<wallCount;j++)
            balls[i].crashWall(table->getWallFunc(j), table->getDistance(j), time_t);
        balls[i].move(time_t);
    }
    for(int i=0;i<wallCount;i++){
        whiteBall.crashWall(table->getWallFunc(i), table->getDistance(i), time_t);
        goldBall.crashWall(table->getWallFunc(i), table->getDistance(i), time_t);
    }
    whiteBall.move(time_t);
    goldBall.move(time_t);
}