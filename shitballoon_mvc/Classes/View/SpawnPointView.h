//
//  SpawnPointView.h
//  shitballoon_mvc
//
//  Created by Khanh Hoang Nguyen on 3/26/14.
//
//

#ifndef __shitballoon_mvc__SpawnPointView__
#define __shitballoon_mvc__SpawnPointView__

#include "cocos2d.h"
#include "SpawnPointViewDelegate.h"
#include "SpawnPoint.h"

using namespace cocos2d;

class SpawnPointView: public CCLayer, public SpawnPointViewDelegate
{
private:
    CC_SYNTHESIZE(SpawnPoint*, _model, Model);
    CC_SYNTHESIZE(CCPoint, _position, Position)
    CC_SYNTHESIZE(CCScene*, _scene, Scene);
public:
    SpawnPointView* initWithModel(SpawnPoint* aSP);
    virtual Enemy* spawnNow();
};

#endif /* defined(__shitballoon_mvc__SpawnPointView__) */
