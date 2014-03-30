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
    //create MOdel
    SpawnPoint* aModel = new SpawnPoint();
    aModel->initWithPos(ccp(aPos.x/PTM_RATIO,aPos.y/PTM_RATIO));
    this->setModel(aModel);
    // create View
    SpawnPointView* aView =  new SpawnPointView();
    aView->initWithModel(aModel);
    this->setView(aView);
    return this;
}

void SpawnPointController::startSpawn()
{
    // kick start timer in SP Model
}