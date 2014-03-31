//
//  SpawnPoint.h
//  shitballoon_mvc
//
//  Created by Khanh Hoang Nguyen on 3/26/14.
//
//

#ifndef __shitballoon_mvc__SpawnPoint__
#define __shitballoon_mvc__SpawnPoint__

#include <iostream>
#include "cocos2d.h"
#include "SpawnPointControllerDelegate.h"

using namespace cocos2d;

class SpawnPoint: public CCObject
{
private:
    CC_SYNTHESIZE(CCPoint, _position, Position);
    CC_SYNTHESIZE(int, _spawned, Spawned);
    CC_SYNTHESIZE(SpawnPointControllerDelegate*, _delegate, Delegate);
    static const int _capacity = 3;
public:
    SpawnPoint();
    ~SpawnPoint();
    SpawnPoint* initWithPos(CCPoint aPos);
    void onTimeUp();
};
#endif /* defined(__shitballoon_mvc__SpawnPoint__) */
