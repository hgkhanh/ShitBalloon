
#ifndef __shitballoon_mvc__EnemyView__
#define __shitballoon_mvc__EnemyView__

#include "EnemyViewDelegate.h"
#include "Enemy.h"

#define PTM_RATIO 32.0
using namespace cocos2d;

class EnemyView : public CCLayer, public EnemyViewDelegate {
private:
    CC_SYNTHESIZE(Enemy*, _model, Model);
    CC_SYNTHESIZE(b2Body*, _body, Body);
    CC_SYNTHESIZE(CCSprite*, _sprite, Sprite);
    CC_SYNTHESIZE(CCLayer*, _layer, Layer);
    CC_SYNTHESIZE(b2World*, _world, World);
public:
    EnemyView();
    ~EnemyView();
    bool initWithModel(Enemy* anEnemy, CCLayer* aLayer, b2World* aWorld);
    void initPhysics(b2World* aWorld);
    virtual void updateHPBar();
};
#endif /* defined(__shitballoon_mvc__EnemyView__) */