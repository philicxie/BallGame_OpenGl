//
//  MyGameWorld.hpp
//  gldemo_toushi
//
//  Created by Philic on 15/10/23.
//  Copyright © 2015年 Philic. All rights reserved.
//

#ifndef MyGameWorld_hpp
#define MyGameWorld_hpp


#include "AllHeaders.h"
#include "MyBall.hpp"
#include <vector>
#include "MyPlayGround.hpp"
using namespace std;

class MyGameWorld
{
public:
    MyGameWorld();
    void addBall(MyBall newBall);
    void draw();
    void simulate(float time);
    void hitCure(float x, float y, float z);
private:
    vector<MyBall> balls;
    MyBall goldBall;
    MyBall whiteBall;
    MyPlayGround *table;
};
#endif /* MyGameWorld_hpp */
