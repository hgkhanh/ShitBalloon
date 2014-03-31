//
//  Hero.cpp
//  ShitBalloon
//
//  Created by Minh Duc Tran on 3/13/14.
//
//

#include "Hero.h"

Hero::Hero(){
    
}

Hero::~Hero(){
    
}

Hero* Hero::initWithPos(CCPoint aPos){
    this->setCurrentHP(this->_maxHP);
    this->setState(kCharacterStateAlive);
    this->setPosition(aPos);
    return this;
}

void Hero::takeDamage()
{
    CCLayer::onEnter(); // Must call this for Schedule to work
    this->setCurrentHP(this->getCurrentHP() - 1);
    this->setState(kCharacterStateHit);
    this->scheduleOnce(schedule_selector(Hero::endHitState), 1.0f);
    this->getDelegate()->updateHPBar();
}

void Hero::endHitState(float dt)
{
    this->setState(kCharacterStateAlive);
}