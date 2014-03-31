//
//  SpawnPoint.cpp
//  shitballoon_mvc
//
//  Created by Khanh Hoang Nguyen on 3/26/14.
//
//

#include "SpawnPoint.h"
int SpawnPoint::_enemyCount = 0;
SpawnPoint::SpawnPoint()
{
    
}

SpawnPoint::~SpawnPoint()
{
    
}

SpawnPoint* SpawnPoint::initWithPos(CCPoint aPos){
    this->setPosition(aPos);
    this->setSpawned(0);
    return this;
}

void SpawnPoint::startSpawnTimer()
{
    CCLayer::onEnter();
    this->schedule(schedule_selector(SpawnPoint::spawnTimeDue), _spawnInterval);
}

void SpawnPoint::spawnTimeDue()
{
    // spawn next enemy
    if ( _spawned < _capacity )
    {
        this->setSpawned(_spawned+1);
        SpawnPoint::_enemyCount++;
        this->getDelegate()->spawnNow();
    }
    else
    {
        this->unschedule(schedule_selector(SpawnPoint::spawnTimeDue));
    }
}
