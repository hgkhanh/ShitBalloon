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
public:
    HeroView();
    ~HeroView();
    bool initWithModel(Hero* aHero);
    void initPhysics(b2World* aWorld);
    virtual void updateHPBar();
};
#endif /* defined(__shitballoon_mvc__HeroView__) */
