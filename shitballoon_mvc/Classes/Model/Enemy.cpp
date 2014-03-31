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

void Enemy::takeDamage()
{
    CCLayer::onEnter(); // Must call this for Schedule to work
    this->setCurrentHP(this->getCurrentHP() - 1);
    this->setState(kCharacterStateHit);
    this->scheduleOnce(schedule_selector(Enemy::endHitState), 1.0f);
    this->getDelegate()->updateHPBar();
}

void Enemy::endHitState(float dt)
{
    this->setState(kCharacterStateAlive);
}