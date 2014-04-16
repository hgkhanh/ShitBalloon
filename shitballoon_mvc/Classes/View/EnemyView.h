
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
    CC_SYNTHESIZE(CCAction*, _downAction, DownAction);
    CC_SYNTHESIZE(CCAction*, _upAction, UpAction);
    CC_SYNTHESIZE(CCAction*, _moveAction, MoveAction);
    CC_SYNTHESIZE(CCAction*, _hitAction, HitAction);
public:
    EnemyView();
    ~EnemyView();
    bool initWithModel(Enemy* anEnemy, CCLayer* aLayer, b2World* aWorld);
    void initAnimation();
    void initPhysics(b2World* aWorld);
    void animateLeft();
    void animateDown();
    void animateUp();
    void animateRight();
    void animateHit();
    
    virtual void animateDead();
    virtual void updateHPBar();
};
#endif /* defined(__shitballoon_mvc__EnemyView__) */