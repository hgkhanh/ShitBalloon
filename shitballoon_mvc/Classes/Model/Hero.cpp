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
    this->setCurrentHP(this->getCurrentHP() - 1);
    this->getDelegate()->updateHPBar();
}