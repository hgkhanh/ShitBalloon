//
//  HeroController.h
//  shitballoon_mvc
//
//  Created by Khanh Hoang Nguyen on 3/25/14.
//
//

#ifndef __shitballoon_mvc__EnemyController__
#define __shitballoon_mvc__EnemyController__

#include "cocos2d.h"
#include "Enemy.h"
#include "EnemyView.h"

using namespace cocos2d;

class EnemyController : public CCObject
{
private:
    CC_SYNTHESIZE(Enemy*, _model, Model);
    CC_SYNTHESIZE(EnemyView*, _view, View);
public:
    EnemyController();
    ~EnemyController();
    EnemyController* createEnemyWithPos(CCPoint aPos);
};

#endif /* defined(__shitballoon_mvc__HeroController__) */
