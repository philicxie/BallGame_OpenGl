//
//  MyVectors.cpp
//  gldemo_toushi
//
//  Created by Philic on 15/10/22.
//  Copyright © 2015年 Philic. All rights reserved.
//

#include "MyVectors.hpp"


void myVector3f::normalize()
{
    
}

//myVector3f  operator+(myVector3f&a, myVector3f&b)
//{
//    myVector3f tem;
//    return tem;
//}
//myVector3f  operator*(float a,      myVector3f&b)
//{
//    return myVector3f(a*b.x, a*b.y, a*b.z);
//}

myVector3f myVector3f::operator*(float a)
{
    return myVector3f(a*this->x, a*this->y, a*this->z);
}

myVector3f myVector3f::operator+(myVector3f &a)
{
    return myVector3f(a.x+this->x, a.y+this->y, a.z+this->z);
}

float myVecLength(myVector3f a)
{
    return sqrtf(a.x*a.x+a.y*a.y+a.z*a.z);
}
float myVecLength(myVector3f a, myVector3f b)
{
    return sqrtf((a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y)+(a.z-b.z)*(a.z-b.z));
}

float myVecMulti(myVector3f a, myVector3f b)
{
    return a.x*b.x+a.y*b.y+a.z*b.z;
}

myVector3f myVecMid(myVector3f a, myVector3f b)
{
    return myVector3f((a.x+b.x)/2, (a.y+b.y)/2, (a.z+b.z)/2);
}

myVector3f myVecPoint(myVector3f a, myVector3f b)
{
    return myVector3f(b.x-a.x, b.y-a.y, b.z-a.z);
}

myVector3f myVecScale(float a, myVector3f b)
{
    return myVector3f(a*b.x, a*b.y, a*b.z);
}

myVector3f myVecPlus(myVector3f a, myVector3f b)
{
    return myVector3f(a.x+b.x, a.y+b.y, a.z+b.z);
}

myVector3f myVecMinus(myVector3f a, myVector3f b)
{
    return myVector3f(a.x-b.x, a.y-b.y, a.z-b.z);
}
