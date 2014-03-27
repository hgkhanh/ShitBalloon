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

void Enemy::takeDamage(){
    this->setCurrentHP(this->getCurrentHP() - 1);
    this->getDelegate()->updateHPBar();
}