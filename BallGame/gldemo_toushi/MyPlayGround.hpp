//
//  MyPlayGround.hpp
//  gldemo_toushi
//
//  Created by Philic on 15/10/23.
//  Copyright © 2015年 Philic. All rights reserved.
//

#ifndef MyPlayGround_hpp
#define MyPlayGround_hpp

#include <stdio.h>
#include <GLUT/GLUT.h>
#include <stdlib.h>
#include <vector>
#include "MyVectors.hpp"

using namespace std;
class MyPlayGround
{
public:
    MyPlayGround();
    void draw();
    int getWallCount();
    myVector3f getWallFunc(int index);
    float getDistance(int index);
private:
    vector<myVector3f>wallFuncs;
    vector<float>distances;
};
#endif /* MyPlayGround_hpp */
