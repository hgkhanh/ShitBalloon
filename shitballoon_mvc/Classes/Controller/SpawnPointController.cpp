//
//  SpawnPointController.cpp
//  shitballoon_mvc
//
//  Created by Khanh Hoang Nguyen on 3/27/14.
//
//

#include "SpawnPointController.h"

SpawnPointController::SpawnPointController()
{
    this->_enemyList = new CCArray();
}

SpawnPointController::~SpawnPointController()
{
    
}

SpawnPointController* SpawnPointController::createWithPos(CCPoint aPos, CCLayer* aLayer, b2World* aWorld)
{
    //create MOdel
    SpawnPoint* aModel = new SpawnPoint();
    aModel->initWithPos(ccp(aPos.x,aPos.y));
    this->setModel(aModel);
    aModel->setDelegate(this);
    // create View
    SpawnPointView* aView =  SpawnPointView::initWithModel(aModel, aLayer, aWorld);
    this->setView(aView);
    return this;
}

void SpawnPointController::startSpawn()
{
    // kick start timer in SP Model
    _model->startSpawnTimer();
}

void SpawnPointController::spawnNow()
{
    //create Enemy MVC
    EnemyController* enemyController =  new EnemyController();
    enemyController->createEnemyWithPos(this->_model->getPosition(), this->_view->getLayer(), this->_view->getWorld());
    b2World* curWorld = this->getView()->getWorld();
    this->getEnemyList()->addObject(enemyController);
    // add to current Scene
    
    CCLayer* curLayer = this->getView()->getLayer();
    curLayer->addChild(enemyController->getView()->getSprite());
}