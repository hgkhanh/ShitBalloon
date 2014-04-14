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
    this->addBackground("background.png");
    this->addPlatforms("platform.png");
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