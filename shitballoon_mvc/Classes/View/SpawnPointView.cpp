//
//  SpawnPointView.cpp
//  shitballoon_mvc
//
//  Created by Khanh Hoang Nguyen on 3/26/14.
//
//

#include "SpawnPointView.h"

SpawnPointView* SpawnPointView::initWithModel(SpawnPoint* aSP)
{
    SpawnPointView* aSPView = new SpawnPointView();
    aSPView->setModel(aSP);
    return aSPView;
}