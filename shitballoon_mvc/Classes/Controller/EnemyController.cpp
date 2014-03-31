//
//  HeroController.cpp
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

EnemyController* EnemyController::createEnemyWithPos(CCPoint aPos)
{
    //Model
    Enemy* anEnemy = Enemy::initWithPos(ccp(aPos.x/PTM_RATIO,aPos.y/PTM_RATIO));
    this->setModel(anEnemy);
    //View
    EnemyView* aView = new EnemyView();
    aView->initWithModel(anEnemy);
    this->setView(aView);
    
    return this;
}
