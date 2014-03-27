//
//  SpawnPoint.cpp
//  shitballoon_mvc
//
//  Created by Khanh Hoang Nguyen on 3/26/14.
//
//

#include "SpawnPoint.h"

SpawnPoint* SpawnPoint::initWithPos(CCPoint aPos){
    SpawnPoint* spawnPoint = new SpawnPoint();
    spawnPoint->setPosition(aPos);
    spawnPoint->setSpawned(_capacity);
    return spawnPoint;
}