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

int Hero::takeDamage()
{
    CCLayer::onEnter(); // Must call this for Schedule to work
    this->setCurrentHP(_currentHP - 1);
    if (_currentHP == 0) {
        this->setState(kCharacterStateDying);
        this->getViewDelegate()->updateHPBar();
        this->getViewDelegate()->animateDead();
        this->scheduleOnce(schedule_selector(Hero::endDyingState), 3.0f);
    }
    else
    {
        // change state, update HP bar
        this->setState(kCharacterStateGotHit);
        this->getViewDelegate()->updateHPBar();
        this->scheduleOnce(schedule_selector(Hero::endGotHitState), 1.0f);
    }
    return _state;
}

void Hero::endGotHitState(float dt)
{
    this->setState(kCharacterStateAlive);
}

void Hero::endDyingState(float dt)
{
    this->setState(kCharacterStateDead);
}