//
//  HeroViewDelegate.h
//  ShitBalloon
//
//  Created by Minh Duc Tran on 3/17/14.
//
//

#ifndef __ShitBalloon__HeroViewDelegate__
#define __ShitBalloon__HeroViewDelegate__

#include <iostream>
#include "cocos2d.h"

class HeroViewDelegate
{
public:
    virtual void updateHPBar() = 0;
};

#endif /* defined(__ShitBalloon__HeroViewDelegate__) */
