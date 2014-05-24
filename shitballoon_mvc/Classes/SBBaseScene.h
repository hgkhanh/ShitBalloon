//
//  SBScene.h
//  shitballoon_mvc
//
//  Created by Khanh Hoang Nguyen on 3/25/14.
//  Copyright __MyCompanyName__ 2014. All rights reserved.
//
#ifndef __SB_BASE_SCENE_H__
#define __SB_BASE_SCENE_H__
#include "cocos2d.h"
#include "Box2D.h"
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
#include "PauseLayer.h"
#include "GameOverLayer.h"
#include "MenuScene.h"
#include "B2DebugDrawLayer.h"

#define PTM_RATIO 32.0
#define AIR_RESIST_SCALE 0.2
#define MAX_FORCE  150
using namespace cocos2d;
using namespace cocos2d::extension;
class SBBaseScene : public CCLayer
{
private:
    CC_SYNTHESIZE(HeroController*, _heroController, HeroController);
    CC_SYNTHESIZE(CCArray*, _spawnPointControllerArray, SpawnPointControllerArray);
    CC_SYNTHESIZE(HeroControllerDelegate*, _delegate, Delegate);
    CC_SYNTHESIZE(b2World*, _world, World);
    CC_SYNTHESIZE(PauseLayer*, _pauseLayer, PauseLayer);
    CC_SYNTHESIZE(GameOverLayer*, _gameOverLayer, GameOverLayer);
    CC_SYNTHESIZE(int, _enemyCount, EnemyCount);
    SBContactListener* _contactListener;
    CCSize _screenSize;
    CCArray* _platformArray;
    b2Body* _groundBody;
    bool _running;
    bool _isHeroDie;
    CCSprite* _btnPause;
    CCSprite* _btnReset;
    CCMenu* _pauseMenu;
    CCMenu* _gameOverMenu;
    CCMenu* _nextMenu;
    CC_SYNTHESIZE(int, _playerPoints, PlayerPoints);
public:
    SBBaseScene();
    ~SBBaseScene();
    void addBackground(const char *pszFileName);
    void addPlatforms(char *Filename, CCPoint pos, int type);
    void addHero(CCPoint p);
    void addSpawnPoint(CCPoint p, float spawnInterval, int capacity);
    
    void initSprite();
    void initPhysics();
    void initTouch();
    virtual bool init();
    void resume();
    void showMenuScene();
    void showPopBalloon(int charTag,CCPoint aPos);
    void spriteMoveFinished(CCObject *sender);
    void setHeroDie();
    EnemyController* getEnemybyBody(b2Body* aBody);
    
    virtual void ccTouchesBegan(CCSet* touches, CCEvent* event);
    virtual void didSwipe(CCObject * obj);
    void tick(float dt);
    CREATE_FUNC(SBBaseScene);
};
#endif

