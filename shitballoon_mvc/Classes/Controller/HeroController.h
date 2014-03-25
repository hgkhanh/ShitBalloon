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
    static HeroController* createHeroWithPos(CCPoint aPos);
    virtual void touch(b2Body* aBody);
    virtual void tap(b2Body* aBody);
    virtual void swipeUp(b2Body* aBody);
    virtual void swipeDown(b2Body* aBody);
    virtual void swipeLeft(b2Body* aBody);
    virtual void swipeRight(b2Body* aBody);
};

#endif /* defined(__shitballoon_mvc__HeroController__) */
