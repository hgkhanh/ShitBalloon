//
//  SpawnPoint.cpp
//  shitballoon_mvc
//
//  Created by Khanh Hoang Nguyen on 3/26/14.
//
//

#include "SpawnPoint.h"

SpawnPoint* SpawnPoint::initWithPos(CCPoint aPos){
    this->setPosition(aPos);
    this->setSpawned(_capacity);
    return this;
}

void SpawnPoint::onTimeUp()
{
    // spawn next enemy
    this->_delegate->spawnNow();
}