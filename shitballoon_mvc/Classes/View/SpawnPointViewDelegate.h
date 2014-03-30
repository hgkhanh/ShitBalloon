//
//  SpawnPointViewDelegate.h
//  shitballoon_mvc
//
//  Created by Khanh Hoang Nguyen on 3/28/14.
//
//

#ifndef shitballoon_mvc_SpawnPointViewDelegate_h
#define shitballoon_mvc_SpawnPointViewDelegate_h


#include "Enemy.h"

class SpawnPointViewDelegate
{
public:
    virtual Enemy* spawnNow() = 0;
};

#endif
