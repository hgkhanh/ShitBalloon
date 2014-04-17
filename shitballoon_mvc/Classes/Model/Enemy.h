//
//  Hero.h
//  ShitBalloon
//
//  Created by Minh Duc Tran on 3/13/14.
//
//

#ifndef __shitballoon_mvc__Enemy__
#define __shitballoon_mvc__Enemy__

#include <iostream>
#include "CommonProtocols.h"
#include "Box2D.h"
#include "EnemyViewDelegate.h"

using namespace cocos2d;

class Enemy : public CCLayer
{
private:
    CC_SYNTHESIZE(CCPoint, _posotion, Position);
    CC_SYNTHESIZE(int, _currentHP, CurrentHP);
    CC_SYNTHESIZE(CharacterStates, _state, State);
    //CC_SYNTHESIZE(CCSprite*, _sprite, Sprite);
    CC_SYNTHESIZE(EnemyViewDelegate*, _viewDelegate, ViewDelegate);
    static const int maxHP = 2;

    void endGotHitState(float dt);
    void endDyingState(float dt);
public:
    Enemy();
    ~Enemy();
    static Enemy* initWithPos(CCPoint aPos);
    int takeDamage();
};

#endif /* defined(__shitballoon_mvc__Enemy__) */
