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
        this->setState(kCharacterStateDead);
    }
    else
    {
        // change state, update HP bar
        this->setState(kCharacterStateHit);
        this->scheduleOnce(schedule_selector(Hero::endHitState), 1.0f);
        this->getViewDelegate()->updateHPBar();
    }
    return _state;
}

void Hero::endHitState(float dt)
{
    this->setState(kCharacterStateAlive);
}
