//
//  SpawnPointView.cpp
//  shitballoon_mvc
//
//  Created by Khanh Hoang Nguyen on 3/26/14.
//
//

#include "SpawnPointView.h"
#include "EnemyController.h"

SpawnPointView* SpawnPointView::initWithModel(SpawnPoint* aSP)
{
    SpawnPointView* aSPView = new SpawnPointView();
    aSPView->setModel(aSP);
    return aSPView;
}

Enemy* SpawnPointView::spawnNow()
{
    EnemyController* enemyController = EnemyController::createEnemyWithPos(this->getPosition());
    return NULL;
}