//
//  SpawnPointView.cpp
//  shitballoon_mvc
//
//  Created by Khanh Hoang Nguyen on 3/26/14.
//
//

#include "SpawnPointView.h"
#include "EnemyController.h"

SpawnPointView::SpawnPointView()
{
    
}

SpawnPointView::~SpawnPointView()
{
    
}

SpawnPointView* SpawnPointView::initWithModel(SpawnPoint* aSP, CCLayer* aLayer, b2World* aWorld)
{
    SpawnPointView* aSPView = new SpawnPointView();
    aSPView->setModel(aSP);
    aSPView->setLayer(aLayer);
    aSPView->setWorld(aWorld);
    return aSPView;
}

