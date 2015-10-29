//
//  MyBall.cpp
//  gldemo_toushi
//
//  Created by Philic on 15/10/22.
//  Copyright © 2015年 Philic. All rights reserved.
//

#include "myBall.hpp"
#include <iostream>
#define COINCIDE_SCALE 1.1f
using namespace std;

MyBall::MyBall()
{
    
}

MyBall::MyBall(int type)
{
    if (type==QUAFFLE)
        this->friction = -0.5;
    else
        friction = -0.2;
    position = myVector3f(0, 0, 0);
    size = 0;
    color = myColor(0, 0, 0);
}
MyBall::MyBall(float x, float y, float z, float size, int type)
{
    position = myVector3f(x, y, z);
    this->size = size;
    color = myColor(0,0,0);
}

void MyBall::draw()
{
    glPushMatrix();
    glTranslated(position.x, position.y, position.z);
    glColor3f(color.red, color.green, color.blue);
    glutSolidSphere(size, 20, 200);
    glPopMatrix();
}

void MyBall::setColor(float red, float green, float blue)
{
    this->color = myColor(red, green, blue);
}

void MyBall::setSize(float size)
{
    this->size = size;
}

void MyBall::setPosition(float x, float y, float z)
{
    this->position = myVector3f(x, y, z);
}

void MyBall::setSpeed(float x, float y, float z)
{
    this->speed = myVector3f(x, y, z);
}

void MyBall::setSpeed(myVector3f speed_t)
{
    this->speed = speed_t;
}

void MyBall::setType(int ballType)
{
    this->type = ballType;
    if(type==QUAFFLE){
        friction = -0.05;
        setColor(0.3, 0.2, 0.5);
    }
    if(type==BLUDGER){
        friction = 0.0;
        setColor(0.7, 0.3, 0.2);
    }
    if(type==CUEBALL){
        friction = -0.4;
    }
}

myVector3f MyBall::nextPos(float time_t)
{
//    position.x += time_t*speed.x;
//    position.y += time_t*speed.y;
//    position.z += time_t*speed.z;
    //position = position+speed*time_t;
    return myVecPlus(this->position, myVecScale(time_t, this->speed));
}


myVector3f MyBall::getPos()
{
    return this->position;
}

myVector3f MyBall::getSpeed()
{
    return this->speed;
}
void MyBall::move(float time_t)
{
    position = nextPos(time_t);
    this->speed = myVecPlus(this->speed, myVecScale(time_t*friction, this->speed));
    
}

void MyBall::crashBall(MyBall &ball, float time_t)
{
    myVector3f posa = this->nextPos(time_t);
    myVector3f posb = ball.nextPos(time_t);
    float length = myVecLength(posa, posb);
    myVector3f a2b = myVecPoint(posa, posb);
    myVector3f b2a = myVecPoint(posb, posa);
    if(length<=this->size+ball.size){
        myVector3f spa = this->speed;
        myVector3f chga = myVecScale(myVecMulti(a2b, spa)/myVecLength(a2b)/myVecLength(a2b), a2b);
        myVector3f spb = ball.speed;
        myVector3f chgb = myVecScale(myVecMulti(b2a, spb)/myVecLength(b2a)/myVecLength(b2a), b2a);
        this->speed = myVecPlus(chgb, myVecMinus(spa, chga));
        ball.speed  = myVecPlus(chga, myVecMinus(spb, chgb));
    }
    if(length<=(this->size+ball.size)/COINCIDE_SCALE){
        float bias = (this->size+ball.size-length)/2;
        this->position = myVecPlus(posa, myVecScale(bias/myVecLength(b2a), b2a));
        ball.position = myVecPlus(posb, myVecScale(bias/myVecLength(a2b), a2b));
    }
}

void MyBall::crashWall(myVector3f wallFunc, float distance, float time_t)
{
    myVector3f pos = this->nextPos(time_t);
    float length = (float)fabs(myVecMulti(pos, wallFunc)+distance);
    if (length<=this->size) {
        myVector3f spt = this->speed;
        myVector3f cht = myVecScale(myVecMulti(wallFunc, spt)/myVecLength(wallFunc)/myVecLength(wallFunc), wallFunc);
        this->speed = myVecMinus(spt, myVecScale(2, cht));
    }
    if(length<(this->size)/COINCIDE_SCALE){
        float bias = (this->size-length)/2;
        this->position = myVecPlus(pos, myVecScale(bias/myVecLength(wallFunc), wallFunc));
    }

}

void MyBall::printPos()
{
    cout<<position.x<<" "<<position.y<<" "<<position.z<<endl;
}

void MyBall::printSpeed()
{
    cout<<speed.x<<" "<<speed.y<<" "<<speed.z<<endl;
}


















