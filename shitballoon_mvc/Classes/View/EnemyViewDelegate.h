//
//  EnemyViewDelegate.h
//  ShitBalloon
//
//  Created by Minh Duc Tran on 3/17/14.
//
//

#ifndef shitballoon_mvc_EnemyControllerDelegate_h
#define shitballoon_mvc_EnemyControllerDelegate_h

class EnemyViewDelegate
{
public:
    virtual void updateHPBar() = 0;
    virtual void animateDead() = 0;
};

#endif /* defined(__shitballoon_mvc__EnemyViewDelegate__) */
