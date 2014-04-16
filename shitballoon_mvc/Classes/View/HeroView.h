//
//  HeroView.h
//  ShitBalloon
//
//  Created by Khanh Hoang Nguyen on 3/25/14.
//
//

#ifndef __shitballoon_mvc__HeroView__
#define __shitballoon_mvc__HeroView__

#include "cocos2d.h"
#include "Box2D.h"
#include "CommonProtocols.h"
#include "Hero.h"


#define PTM_RATIO 32.0
using namespace cocos2d;

class HeroView : public CCLayer, public HeroViewDelegate {
private:
    CC_SYNTHESIZE(Hero*, _model, Model);
    CC_SYNTHESIZE(b2Body*, _body, Body);
    CC_SYNTHESIZE(CCSprite*, _sprite, Sprite);
    CC_SYNTHESIZE(CCLayer*, _layer, Layer);
    CC_SYNTHESIZE(b2World*, _world, World);
    CC_SYNTHESIZE(CCAction*, _downAction, DownAction);
    CC_SYNTHESIZE(CCAction*, _upAction, UpAction);
    CC_SYNTHESIZE(CCAction*, _moveAction, MoveAction);
    CC_SYNTHESIZE(CCAction*, _hitAction, HitAction);
public:
    HeroView();
    ~HeroView();
    bool initWithModel(Hero* aHero, CCLayer* aLayer, b2World* aWorld);
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
#endif /* defined(__shitballoon_mvc__HeroView__) */
