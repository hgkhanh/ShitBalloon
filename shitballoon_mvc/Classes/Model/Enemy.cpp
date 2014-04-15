//
//  Hero.cpp
//  ShitBalloon
//
//  Created by Minh Duc Tran on 3/13/14.
//
//

#include "Enemy.h"

Enemy::Enemy(){
    
}

Enemy::~Enemy(){
    
}

Enemy* Enemy::initWithPos(CCPoint aPos){
    Enemy* enemy = new Enemy();
    enemy->setCurrentHP(enemy->maxHP);
    enemy->setState(kCharacterStateAlive);
    enemy->setPosition(aPos);
    return enemy;
}

int Enemy::takeDamage()
{
    CCLayer::onEnter(); // Must call this for Schedule to work
    this->setCurrentHP(_currentHP - 1);
    if (_currentHP == 0) {
        this->setState(kCharacterStateDead);
    }
    else
    {
        // change state, update HP bar
        this->setState(kCharacterStateGotHit);
        this->scheduleOnce(schedule_selector(Enemy::endHitState), 1.0f);
        this->getViewDelegate()->updateHPBar();
    }
    return _state;
}

void Enemy::endHitState(float dt)
{
    this->setState(kCharacterStateAlive);
}