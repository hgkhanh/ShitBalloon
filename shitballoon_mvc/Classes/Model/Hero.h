//
//  Hero.h
//  ShitBalloon
//
//  Created by Minh Duc Tran on 3/13/14.
//
//

#ifndef __shitballoon_mvc__Hero__
#define __shitballoon_mvc__Hero__

#include <iostream>
#include "CommonProtocols.h"
#include "Box2D.h"
#include "HeroViewDelegate.h"
#include "HeroControllerDelegate.h"

using namespace cocos2d;

class Hero : public CCLayer {
private:
    CC_SYNTHESIZE(CCPoint, _position, Position);
    CC_SYNTHESIZE(int, _currentHP, CurrentHP);
    CC_SYNTHESIZE(CharacterStates, _state, State);
    CC_SYNTHESIZE(HeroViewDelegate*, _viewDelegate, ViewDelegate);
    static const int _maxHP = 5;
    
    void endGotHitState(float dt);
    void endDyingState(float dt);
public:
    Hero();
    ~Hero();
    Hero* initWithPos(CCPoint aPos);
    int takeDamage();
};

#endif /* defined(__shitballoon_mvc__Hero__) */
