//
//  SpawnPointController.cpp
//  shitballoon_mvc
//
//  Created by Khanh Hoang Nguyen on 3/27/14.
//
//

#include "SpawnPointController.h"

SpawnPointController* SpawnPointController::createWithPos(CCPoint aPos)
{
    SpawnPointController* aSPController = new SpawnPointController();
    //create MOdel
    SpawnPoint* aModel = SpawnPoint::initWithPos(ccp(aPos.x/PTM_RATIO,aPos.y/PTM_RATIO));
    aSPController->setModel(aModel);
    // create View
    SpawnPointView* aView =  new SpawnPointView();
    aView->initWithModel(aModel);
    aSPController->setView(aView);
    return aSPController;
}

void SpawnPointController::spawnEnemy()
{
    
}