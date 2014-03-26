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
    virtual void touch() = 0;
    virtual void tap() = 0;
    virtual void swipeUp() = 0;
    virtual void swipeDown() = 0;
    virtual void swipeLeft() = 0;
    virtual void swipeRight() = 0;
};

#endif
