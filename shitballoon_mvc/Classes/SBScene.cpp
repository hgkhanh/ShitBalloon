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

bool SBScene::init(){
    if ( !SBBaseScene::init() )
    {
        return false;
    }
    
    // init object
    this->addBackground("shitballoon_bg.png");
    this->addPlatforms("platform_grass", ccp(_screenSize.width * 0.5, _screenSize.height * 0.5), kLargePlatform);
    this->addHero(ccp(_screenSize.width * 0.5, _screenSize.height * 0.9));
    this->addSpawnPoint(ccp(_screenSize.width * 0.2, _screenSize.height * 0.5), 1.0f, 3);
    this->addSpawnPoint(ccp(_screenSize.width * 0.6, _screenSize.height * 0.7), 1.5f, 4);
    
    this->setEnemyCount(7);
    
    CCSprite * menuItemOn;
    CCSprite * menuItemOff;
    
    menuItemOn = CCSprite::create("btn_play_on.png");
    menuItemOff = CCSprite::create("btn_play_off.png");
    CCMenuItemSprite * replayItem = CCMenuItemSprite::create(menuItemOn, menuItemOff, this, menu_selector(SBScene::reset));
    
    menuItemOn = CCSprite::create("btn_help_on.png");
    menuItemOff = CCSprite::create("btn_help_off.png");
    CCMenuItemSprite * quitItem = CCMenuItemSprite::create(menuItemOn, menuItemOff, this, menu_selector(SBBaseScene::showMenuScene));
    _gameOverMenu = CCMenu::create(replayItem, quitItem, NULL);
    _gameOverMenu->alignItemsVerticallyWithPadding(10);
    _gameOverMenu->setPosition(ccp(_screenSize.width * 0.5f, _screenSize.height * 0.5f));
    _gameOverMenu->setVisible(false);
    this->addChild(_gameOverMenu, 9);
    
    
    menuItemOn = CCSprite::create("btn_play_on.png");
    menuItemOff = CCSprite::create("btn_play_off.png");
    CCMenuItemSprite * nextItem = CCMenuItemSprite::create(menuItemOn, menuItemOff, this, menu_selector(SBScene::next));
    
    menuItemOn = CCSprite::create("btn_help_on.png");
    menuItemOff = CCSprite::create("btn_help_off.png");
    CCMenuItemSprite * quitItem2 = CCMenuItemSprite::create(menuItemOn, menuItemOff, this, menu_selector(SBBaseScene::showMenuScene));
    _nextMenu = CCMenu::create(nextItem, quitItem2, NULL);
    _nextMenu->alignItemsVerticallyWithPadding(10);
    _nextMenu->setPosition(ccp(_screenSize.width * 0.5f, _screenSize.height * 0.5f));
    _nextMenu->setVisible(false);
    this->addChild(_nextMenu, 9);

    
    CCObject* curSPController;
    CCARRAY_FOREACH(this->_spawnPointControllerArray, curSPController)
    {
        ((SpawnPointController*) curSPController)->startSpawn();
    }
    
    this->schedule(schedule_selector(SBScene::tick));
    
    return true;
}

void SBScene::reset(){
//    _running = !_running;
    CCScene* newScene = CCTransitionFade::create(0.1f, SBScene::scene());
    SBScene* newLayer= (SBScene*) newScene;
    newLayer->retain();
    CCDirector::sharedDirector()->replaceScene(newScene);
}

void SBScene::next(){
//    _running = !_running;
    CCScene* newScene = CCTransitionFade::create(0.1f, SBScene2::scene());
    CCDirector::sharedDirector()->replaceScene(newScene);
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
                CCDirector::sharedDirector()->pause();
                CCTexture2D* tex = CCTextureCache::sharedTextureCache()->addImage("pause_button.png");
                this->_btnPause->setTexture(tex);
                this->_pauseMenu->setVisible(true);
                this->_btnPause->setVisible(false);
                this->_btnReset->setVisible(false);
                _running = !_running;
            }
        } else if (boundaryReset.containsPoint(tap)) {
            if (_running) {
                CCTexture2D* tex = CCTextureCache::sharedTextureCache()->addImage("pause_button_active.png");
                this->_btnReset->setTexture(tex);
                _running = !_running;
                CCScene* newScene = CCTransitionFade::create(0.5f, SBScene::scene());
                SBScene* newLayer= (SBScene*) newScene;
                newLayer->retain();
                CCDirector::sharedDirector()->replaceScene(newScene);
            }
        }
    }
}

void SBScene::tick(float dt) {
    SBBaseScene::tick(dt);
    if (this->getEnemyCount() == 0 && _running) {
        CCUserDefault::sharedUserDefault()->setIntegerForKey("current point", this->getPlayerPoints());
        CCUserDefault::sharedUserDefault()->flush();
        showGameOverLayer(true);
    }
    if (_isHeroDie && _running) {
        CCLog("Pts: %i", this->getPlayerPoints());
        CCLog("HighScore: %i", CCUserDefault::sharedUserDefault()->getIntegerForKey("highscore"));
        if (this->getPlayerPoints() > CCUserDefault::sharedUserDefault()->getIntegerForKey("highscore")) {
            CCUserDefault::sharedUserDefault()->setIntegerForKey("highscore", this->getPlayerPoints());
            CCUserDefault::sharedUserDefault()->setIntegerForKey("current point", 0);
            CCUserDefault::sharedUserDefault()->flush();
            CCLog("Pts: %i", this->getPlayerPoints());
            CCLog("HighScore: %i", CCUserDefault::sharedUserDefault()->getIntegerForKey("highscore"));
        }
        showGameOverLayer(false);
    }
}

void SBScene::showGameOverLayer(bool next) {
    this->setTouchEnabled(true);
    CCObject* child;
    CCARRAY_FOREACH(this->getChildren(), child) {
        ((CCSprite*) child)->pauseSchedulerAndActions();
    }
    _running = !_running;
    _gameOverLayer = GameOverLayer::create(ccc4(150, 150, 150, 125), _screenSize.width, _screenSize.height, _screenSize);
    _gameOverLayer->setPosition(CCPointZero);
    _gameOverLayer->setTag(2000);
    this->addChild(_gameOverLayer, 8);
    if (!next) {
        this->_gameOverMenu->setVisible(true);
    } else {
        this->_nextMenu->setVisible(true);
    }
}