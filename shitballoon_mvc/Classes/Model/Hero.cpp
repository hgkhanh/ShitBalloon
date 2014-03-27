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
    Hero* hero = new Hero();
    hero->setCurrentHP(hero->_maxHP);
    hero->setState(kCharacterStateAlive);
    hero->setPosition(aPos);
    return hero;
}

void Hero::takeDamage()
{
    this->setCurrentHP(this->getCurrentHP() - 1);
    this->getDelegate()->updateHPBar();
}