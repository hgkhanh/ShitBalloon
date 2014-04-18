//
//  HelloWorldScene.cpp
//  shitballoon_mvc
//
//  Created by Khanh Hoang Nguyen on 3/25/14.
//  Copyright __MyCompanyName__ 2014. All rights reserved.
//
#include "SBScene.h"

SBScene::SBScene()
{
    
}

SBScene::~SBScene()
{
    
}

CCScene* SBScene::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // add layer as a child to scene
    SBScene* layer = SBScene::create();
    scene->addChild(layer);
    return scene;
}

void reset(){
    CCScene* newScene = CCTransitionFade::create(0.5f, SBScene::scene());
    CCDirector::sharedDirector()->replaceScene(newScene);
}

bool SBScene::init(){
    if ( !SBBaseScene::init() )
    {
        return false;
    }
    
    // init object
    this->addBackground("background.png");
    this->addPlatforms("platform.png", ccp(_screenSize.width * 0.5, _screenSize.height * 0.2), kSmallPlatform);
    this->addHero(ccp(_screenSize.width * 0.5, _screenSize.height * 0.9));
    this->addSpawnPoint(ccp(_screenSize.width * 0.2, _screenSize.height * 0.5), 1.0f, 3);
    this->addSpawnPoint(ccp(_screenSize.width * 0.6, _screenSize.height * 0.7), 1.5f, 4);
    
    CCObject* curSPController;
    CCARRAY_FOREACH(this->_spawnPointControllerArray, curSPController)
    {
        ((SpawnPointController*) curSPController)->startSpawn();
    }
    
    this->schedule(schedule_selector(SBBaseScene::tick));
    
    return true;
}

void SBScene::ccTouchesEnded(cocos2d::CCSet *touches, cocos2d::CCEvent *event){
    CCTouch *touch = (CCTouch *)touches->anyObject();
    if (touch) {
        CCPoint tap = touch->getLocation();
        CCRect boundaryPause;
        CCRect boundaryReset;
        
        boundaryPause = _btnPause->boundingBox();
        boundaryReset = _btnReset->boundingBox();
        
        if (boundaryPause.containsPoint(tap)) {
            if (_running) {
                _pauseLayer = PauseLayer::create(ccc4(150, 150, 150, 125), _screenSize.width, _screenSize.height, _screenSize);
                _pauseLayer->setPosition(CCPointZero);
                _pauseLayer->setTag(1000);
                this->addChild(_pauseLayer, 8);
                CCObject* child;
                CCARRAY_FOREACH(this->getChildren(), child) {
                    ((CCSprite*) child)->pauseSchedulerAndActions();
                }
                this->_pauseMenu->setVisible(true);
                this->_btnPause->setVisible(false);
                this->_btnReset->setVisible(false);
            } else {
                this->removeChildByTag(1000);
                CCObject* child;
                CCARRAY_FOREACH(this->getChildren(), child) {
                    ((CCSprite*) child)->resumeSchedulerAndActions();
                }
            }
            _running = !_running;
        } else if (boundaryReset.containsPoint(tap)) {
            if (_running) {
                _running = !_running;
                CCScene* newScene = CCTransitionFade::create(0.5f, SBScene::scene());
                SBScene* newLayer= (SBScene*) newScene;
                newLayer->retain();
                CCDirector::sharedDirector()->replaceScene(newScene);
            }
        }
    }
}