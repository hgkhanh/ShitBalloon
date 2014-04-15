//
//  HeroViewDelegate.h
//  ShitBalloon
//
//  Created by Minh Duc Tran on 3/17/14.
//
//

#ifndef shitballoon_mvc_HeroViewDelegate_h
#define shitballoon_mvc_HeroViewDelegate_h

class HeroViewDelegate
{
public:
    virtual void updateHPBar() = 0;
    virtual void animateDead() = 0;
};

#endif /* defined(__shitballoon_mvc__HeroViewDelegate__) */
