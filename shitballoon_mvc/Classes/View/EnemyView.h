
#ifndef __ShitBalloon__EnemyView__
#define __ShitBalloon__EnemyView__

#include "cocos2d.h"
#include "Box2D.h"
#include "CommonProtocols.h"
#include "EnemyViewDelegate.h"
#include "Enemy.h"

#define PTM_RATIO 32.0
using namespace cocos2d;
class EnemyView : public CCLayer, public EnemyViewDelegate {
private:
    CC_SYNTHESIZE(Enemy*, _model, Model);
    CC_SYNTHESIZE(b2Body*, _body, Body);
    CC_SYNTHESIZE(CCSprite*, _sprite, Sprite);
public:
    EnemyView();
    ~EnemyView();
    bool initWithModel(Enemy* anEnemy);
    void initPhysics(b2World* aWorld);
    virtual void updateHPBar();
};
#endif /* defined(__ShitBalloon__HeroView__) */
