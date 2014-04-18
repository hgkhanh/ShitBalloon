//
//  PauseLayer.h
//  shitballoon_mvc
//
//  Created by Minh Duc Tran on 4/16/14.
//
//

#ifndef __shitballoon_mvc__PauseLayer__
#define __shitballoon_mvc__PauseLayer__

#include <iostream>
#include "cocos2d.h"

using namespace cocos2d;

class PauseLayer : public CCLayerColor {
    CCSize _screenSize;    
public:
    CCLabelTTF* _paused;
    ~PauseLayer();
    PauseLayer();
    
    static PauseLayer* create(const ccColor4B &color, GLfloat width, GLfloat height, CCSize screenSize);
    CREATE_FUNC(PauseLayer);
};

#endif /* defined(__shitballoon_mvc__PauseLayer__) */
