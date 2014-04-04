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
#include "extension.h"
#include "CCScale9Sprite.h"
#include "CommonProtocols.h"
#include "EnemyController.h"
#include "HeroController.h"
#include "CCTapGestureRecognizer.h"
#include "CCSwipeGestureRecognizer.h"
#include "HeroControllerDelegate.h"
#include "SpawnPointController.h"
#include "SBContactListener.h"
#include "Enemy.h"

#define PTM_RATIO 32.0
#define AIR_RESIST_SCALE 0.2
#define MAX_FORCE  150
using namespace cocos2d;
using namespace cocos2d::extension;
class SBScene : public CCLayer
{
private:
    CC_SYNTHESIZE(HeroController*, _heroController, HeroController);
    CC_SYNTHESIZE(CCArray*, _spawnPointControllerArray, SpawnPointControllerArray);
    CC_SYNTHESIZE(HeroControllerDelegate*, _delegate, Delegate);
    CC_SYNTHESIZE(b2World*, _world, World);
    SBContactListener* _contactListener;
    CCSize _screenSize;
    CCArray* _platformArray;
    b2Body* _groundBody;
public:
    SBScene();
    ~SBScene();
    static CCScene* scene();
    void addBackground();
    void addPlatforms();
    void addHero(CCPoint p);
    void addSpawnPoint(CCPoint p);

    void initPhysics();
    void initTouch();
    virtual bool init();
    
    EnemyController* getEnemybyBody(b2Body* aBody);
    
    virtual void ccTouchesBegan(CCSet* touches, CCEvent* event);
    virtual void didSwipe(CCObject * obj);
    virtual void didTap(CCObject * obj);
    void tick(float dt);
    CREATE_FUNC(SBScene);
};

#endif // __HELLO_WORLD_H__
