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
#include "Enemy.h"
#include "EnemyView.h"
#include "EnemyController.h"

using namespace cocos2d;

class EnemyController : public CCObject
{
private:
    CC_SYNTHESIZE(Enemy*, _model, Model);
    CC_SYNTHESIZE(EnemyView*, _view, View);
public:
    EnemyController();
    ~EnemyController();
    static EnemyController* createEnemyWithPos(CCPoint aPos);
};

#endif /* defined(__shitballoon_mvc__HeroController__) */
