//
//  GameOverLayer.h
//  shitballoon_mvc
//
//  Created by Minh Duc Tran on 4/23/14.
//
//

#ifndef __shitballoon_mvc__GameOverLayer__
#define __shitballoon_mvc__GameOverLayer__

#include <iostream>
#include "cocos2d.h"

using namespace cocos2d;

class GameOverLayer : public CCLayerColor {
    CCSize _screenSize;
public:
    CCLabelTTF* _gameOver;
    ~GameOverLayer();
    GameOverLayer();
    
    static GameOverLayer* create(const ccColor4B &color, GLfloat width, GLfloat height, CCSize screenSize);
    CREATE_FUNC(GameOverLayer);
};


#endif /* defined(__shitballoon_mvc__GameOverLayer__) */
