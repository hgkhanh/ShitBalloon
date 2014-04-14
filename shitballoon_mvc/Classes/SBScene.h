//
//  SBScene.h
//  shitballoon_mvc
//
//  Created by Khanh Hoang Nguyen on 3/25/14.
//  Copyright __MyCompanyName__ 2014. All rights reserved.
//
#ifndef __HELLO_WORLD_H__
#define __HELLO_WORLD_H__
#include "cocos2d.h"
#include "SBBaseScene.h"
#include "Box2D.h"
#include "extension.h"
#define PTM_RATIO 32.0
#define AIR_RESIST_SCALE 0.2
#define MAX_FORCE  150
using namespace cocos2d;
using namespace cocos2d::extension;
class SBScene : public SBBaseScene
{
public:
    SBScene();
    ~SBScene();
    static CCScene* scene();
    virtual bool init();
    CREATE_FUNC(SBScene);
};

#endif // __HELLO_WORLD_H__
