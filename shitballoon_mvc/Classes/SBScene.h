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
#include "Box2D.h"
#include "CommonProtocols.h"
#include "HeroController.h"
#include "CCTapGestureRecognizer.h"
#include "CCSwipeGestureRecognizer.h"
#include "HeroControllerDelegate.h"

#define PTM_RATIO 32.0
using namespace cocos2d;

class SBScene : public CCLayer  {
private:
    CC_SYNTHESIZE(HeroView*, _heroView, HeroView);
    CC_SYNTHESIZE(CCArray*, _enemyViewArray, EnemyViewArray);
    CC_SYNTHESIZE(HeroControllerDelegate*, _delegate, Delegate);
    b2World* _world;
    //SBContactListener* _contactListener;
    CCSize _screenSize;
public:
    SBScene();
    ~SBScene();
    static CCScene* scene();
    void addBackground();
    void addHero(CCPoint p);
    void initPhysics();
    void initTouch();
    virtual bool init();
    
    virtual void ccTouchesBegan(cocos2d::CCSet* touches, cocos2d::CCEvent* event);
    virtual void didSwipe(CCObject * obj);
    virtual void didTap(CCObject * obj);
    void tick(float dt);
    CREATE_FUNC(SBScene);
};

#endif // __HELLO_WORLD_H__
