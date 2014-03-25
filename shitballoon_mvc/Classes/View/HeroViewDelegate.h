//
//  SBViewDelegate.h
//  ShitBalloon
//
//  Created by Minh Duc Tran on 3/17/14.
//
//

#ifndef __ShitBalloon__SBViewDelegate__
#define __ShitBalloon__SBViewDelegate__

#include <iostream>
#include "cocos2d.h"

class HeroViewDelegate
{
public:
    virtual void updateHPBar() = 0;
};

#endif /* defined(__ShitBalloon__SBViewDelegate__) */
