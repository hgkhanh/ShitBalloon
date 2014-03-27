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
#include "SpawnPoint.h"

using namespace cocos2d;
class SpawnPointView: public CCLayer
{
private:
    CC_SYNTHESIZE(SpawnPoint*, _model, Model);
public:
    SpawnPointView* initWithModel(SpawnPoint* aSP);
};

#endif /* defined(__shitballoon_mvc__SpawnPointView__) */
