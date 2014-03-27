//
//  Hero.h
//  ShitBalloon
//
//  Created by Minh Duc Tran on 3/13/14.
//
//

#ifndef __ShitBalloon__Hero__
#define __ShitBalloon__Hero__

#include <iostream>
#include "CommonProtocols.h"
#include "Box2D.h"
#include "HeroViewDelegate.h"

using namespace cocos2d;

class Hero : public CCObject {
private:
    CC_SYNTHESIZE(CCPoint, _position, Position);
    CC_SYNTHESIZE(int, _currentHP, CurrentHP);
    CC_SYNTHESIZE(CharacterStates, _state, State);
    //CC_SYNTHESIZE(CCSprite*, _sprite, Sprite);
    CC_SYNTHESIZE(HeroViewDelegate*, _delegate, Delegate);
    static const int _maxHP = 5;
public:
    Hero();
    ~Hero();
    static Hero* initWithPos(CCPoint aPos);
    void takeDamage();
};

#endif /* defined(__ShitBalloon__Hero__) */
