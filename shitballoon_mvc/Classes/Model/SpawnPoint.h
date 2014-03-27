//
//  SpawnPoint.h
//  shitballoon_mvc
//
//  Created by Khanh Hoang Nguyen on 3/26/14.
//
//

#ifndef __shitballoon_mvc__SpawnPoint__
#define __shitballoon_mvc__SpawnPoint__

#include "cocos2d.h"

using namespace cocos2d;

class SpawnPoint: public CCObject
{
private:
    CC_SYNTHESIZE(CCPoint, _position, Position);
    CC_SYNTHESIZE(int, _spawned, Spawned);
    static const int _capacity = 3;

public:
    static SpawnPoint* initWithPos(CCPoint aPos);
};
#endif /* defined(__shitballoon_mvc__SpawnPoint__) */
