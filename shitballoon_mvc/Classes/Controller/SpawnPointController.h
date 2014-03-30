//
//  SpawnPointController.h
//  shitballoon_mvc
//
//  Created by Khanh Hoang Nguyen on 3/27/14.
//
//

#ifndef __shitballoon_mvc__SpawnPointController__
#define __shitballoon_mvc__SpawnPointController__

#include "cocos2d.h"
#include "SpawnPoint.h"
#include "SpawnPointView.h"

#define PTM_RATIO 32.0
using namespace cocos2d;
class SpawnPointController: public CCLayer
{
private:
    CC_SYNTHESIZE(SpawnPoint*, _model, Model);
    CC_SYNTHESIZE(SpawnPointView*, _view, View);
public:
    SpawnPointController* createWithPos(CCPoint aPos);
    void startSpawn();
};
#endif /* defined(__shitballoon_mvc__SpawnPointController__) */
