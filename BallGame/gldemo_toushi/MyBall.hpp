//
//  MyBall.hpp
//  gldemo_toushi
//
//  Created by Philic on 15/10/22.
//  Copyright © 2015年 Philic. All rights reserved.
//

#ifndef MyBall_hpp
#define MyBall_hpp


#include "AllHeaders.h"

class MyBall
{
private:
    myVector3f position;
    myVector3f speed;
    myColor color;
    float size;
    float friction;
    int type;
public:
    MyBall();
    MyBall(int type);
    MyBall(float x, float y, float z, float size, int type);
    void draw();
    void setColor(float red, float green, float blue);
    void setPosition(float x, float y, float z);
    void setSize(float size);
    void setSpeed(float x, float y, float z);
    void setSpeed(myVector3f speed);
    void setType(int ballType);
    void move(float time);
    myVector3f nextPos(float time);
    myVector3f getPos();
    myVector3f getSpeed();
    void crashBall(MyBall &ball, float time);
    void crashWall(myVector3f wallFunc, float distance, float time);
    void printPos();
    void printSpeed();
};


#endif /* MyBall_hpp */
