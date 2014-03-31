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
#include "SpawnPointControllerDelegate.h"
#include "EnemyController.h"

#define PTM_RATIO 32.0
using namespace cocos2d;
class SpawnPointController: public CCLayer, public  SpawnPointControllerDelegate
{
private:
    CC_SYNTHESIZE(SpawnPoint*, _model, Model);
    CC_SYNTHESIZE(SpawnPointView*, _view, View);
    CC_SYNTHESIZE(CCArray*, _enemyList, EnemyList);
    
public:
    SpawnPointController();
    ~SpawnPointController();
    SpawnPointController* createWithPos(CCPoint aPos, CCLayer* aLayer, b2World* aWorld);
    void startSpawn();
    virtual void spawnNow();
};
#endif /* defined(__shitballoon_mvc__SpawnPointController__) */
