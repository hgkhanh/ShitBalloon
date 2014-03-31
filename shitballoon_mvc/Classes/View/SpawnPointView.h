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
#include "Box2d.h"

using namespace cocos2d;

class SpawnPointView: public CCLayer
{
private:
    CC_SYNTHESIZE(SpawnPoint*, _model, Model);
    CC_SYNTHESIZE(CCSprite*, _sprite, Sprite);
    CC_SYNTHESIZE(CCLayer*, _layer, Layer);
    CC_SYNTHESIZE(b2World*, _world, World);
public:
    SpawnPointView();
    ~SpawnPointView();
    static SpawnPointView* initWithModel(SpawnPoint* aSP, CCLayer* aLayer, b2World* aWorld);
};

#endif /* defined(__shitballoon_mvc__SpawnPointView__) */
