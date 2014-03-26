//
//  EnemyViewDelegate.h
//  ShitBalloon
//
//  Created by Minh Duc Tran on 3/17/14.
//
//

#ifndef __ShitBalloon__EnemyViewDelegate__
#define __ShitBalloon__EnemyViewDelegate__

#include <iostream>
#include "cocos2d.h"

class EnemyViewDelegate
{
public:
    virtual void updateHPBar() = 0;
};

#endif /* defined(__ShitBalloon__EnemyViewDelegate__) */
