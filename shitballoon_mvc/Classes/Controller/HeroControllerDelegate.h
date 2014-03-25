//
//  HeroControllerDelegate.h
//  shitballoon_mvc
//
//  Created by Khanh Hoang Nguyen on 3/25/14.
//
//

#ifndef shitballoon_mvc_HeroControllerDelegate_h
#define shitballoon_mvc_HeroControllerDelegate_h

class HeroControllerDelegate {
public:
    virtual void touch(b2Body* aBody) = 0;
    virtual void tap(b2Body* aBody) = 0;
    virtual void swipeUp(b2Body* aBody) = 0;
    virtual void swipeDown(b2Body* aBody) = 0;
    virtual void swipeLeft(b2Body* aBody) = 0;
    virtual void swipeRight(b2Body* aBody) = 0;
};

#endif
