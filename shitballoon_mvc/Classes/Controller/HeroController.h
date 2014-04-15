//
//  HeroController.h
//  shitballoon_mvc
//
//  Created by Khanh Hoang Nguyen on 3/25/14.
//
//

#ifndef __shitballoon_mvc__HeroController__
#define __shitballoon_mvc__HeroController__

#include "cocos2d.h"
#include "Hero.h"
#include "HeroView.h"
#include "HeroControllerDelegate.h"

using namespace cocos2d;

class HeroController : public CCObject, public HeroControllerDelegate {
private:
    CC_SYNTHESIZE(Hero*, _model, Model);
    CC_SYNTHESIZE(HeroView*, _view, View);
public:
    HeroController();
    ~HeroController();
    HeroController* createHeroWithPos(CCPoint aPos, CCLayer* aLayer, b2World* aWorld);
    
    int gotHit();
    void hitting();
    
    virtual void touch();
    virtual void swipeUp();
    virtual void swipeDown();
    virtual void swipeLeft();
    virtual void swipeRight();
};

#endif /* defined(__shitballoon_mvc__HeroController__) */
