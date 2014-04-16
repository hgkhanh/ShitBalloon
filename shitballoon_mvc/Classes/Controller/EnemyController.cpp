//
//  EnemyController.cpp
//  shitballoon_mvc
//
//  Created by Khanh Hoang Nguyen on 3/25/14.
//
//

#include "EnemyController.h"

EnemyController::EnemyController()
{
    
}

EnemyController::~EnemyController()
{
    
}

EnemyController* EnemyController::createEnemyWithPos(CCPoint aPos, CCLayer* aLayer, b2World* aWorld)
{
    //Model
    Enemy* anEnemy = Enemy::initWithPos(ccp(aPos.x/PTM_RATIO,aPos.y/PTM_RATIO));
    this->setModel(anEnemy);
    //View
    EnemyView* aView = new EnemyView();
    aView->initWithModel(anEnemy, aLayer, aWorld);
    this->setView(aView);
    
    return this;
}

int EnemyController::gotHit()
{
    if (_model->getState() == kCharacterStateAlive) {
        return _model->takeDamage();
    }
    return _model->getState();
}

void EnemyController::hitting()
{
    if (_model->getState() == kCharacterStateAlive) {
        _view->animateHit();
    }
}

void EnemyController::moveUp(){
    if (_model->getState() != kCharacterStateDying
        && _model->getState() != kCharacterStateDead)
    {
        _view->animateUp();
    }
}

void EnemyController::moveDown(){
    if (_model->getState() != kCharacterStateDying
        && _model->getState() != kCharacterStateDead)
    {
        _view->animateDown();
    }
}

void EnemyController::moveLeft(){
    if (_model->getState() != kCharacterStateDying
        && _model->getState() != kCharacterStateDead)
    {
        _view->animateLeft();
    }
}

void EnemyController::moveRight(){
    if (_model->getState() != kCharacterStateDying
        && _model->getState() != kCharacterStateDead)
    {   
        _view->animateRight();
    }
}