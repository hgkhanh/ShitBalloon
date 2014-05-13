//
//  SBScene.h
//  shitballoon_mvc
//
//  Created by Khanh Hoang Nguyen on 3/25/14.
//  Copyright __MyCompanyName__ 2014. All rights reserved.
//
#ifndef __SB_SCENE_2_H__
#define __SB_SCENE_2_H__
#include "cocos2d.h"
#include "SBBaseScene.h"
#include "Box2D.h"
#define PTM_RATIO 32.0
#define AIR_RESIST_SCALE 0.2
#define MAX_FORCE  150
using namespace cocos2d;
using namespace cocos2d::extension;
class SBScene2 : public SBBaseScene
{
public:
    SBScene2();
    ~SBScene2();
    static CCScene* scene();
    virtual bool init();
    virtual void ccTouchesEnded(CCSet* touches, CCEvent* event);
    void tick(float dt);
    void reset();
    void next();
    void showGameOverLayer(bool next);
    CREATE_FUNC(SBScene2);
};

#endif // __HELLO_WORLD_H__
