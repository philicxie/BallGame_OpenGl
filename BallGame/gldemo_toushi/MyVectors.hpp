//
//  MyVectors.hpp
//  gldemo_toushi
//
//  Created by Philic on 15/10/22.
//  Copyright © 2015年 Philic. All rights reserved.
//

#ifndef MyVectors_hpp
#define MyVectors_hpp

#include <stdio.h>
#include <math.h>
#include <GLUT/GLUT.h>
class myColor
{
public:
    myColor(){
        red = 0.0;
        green = 0.0;
        blue = 0.0;
    }
    myColor(float a,float b,float c){
        red     = a;
        green   = b;
        blue    = c;
    }
    float red;
    float green;
    float blue;
};

struct myVector3f
{
public:
    myVector3f(){
        x = 0.0;
        y = 0.0;
        z = 0.0;
    }
    myVector3f(float a, float b, float c){
        x = a;
        y = b;
        z = c;
    }
    float x;
    float y;
    float z;
    void normalize();
    myVector3f  operator+(myVector3f& a);
    myVector3f  operator*(float a);
};

//float       operator*(myVector3f&a, myVector3f&b);

float myVecLength(myVector3f a);
float myVecLength(myVector3f a, myVector3f b);
float myVecMulti(myVector3f a, myVector3f b);
myVector3f myVecMid(myVector3f a, myVector3f b);
myVector3f myVecPoint(myVector3f a, myVector3f b);
myVector3f myVecScale(float a, myVector3f b);
myVector3f myVecPlus(myVector3f a, myVector3f b);
myVector3f myVecMinus(myVector3f a, myVector3f b);

#endif /* MyVectors_hpp */
