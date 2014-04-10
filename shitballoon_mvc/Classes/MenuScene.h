//
//  MenuScene.h
//  shitballoon_mvc
//
//  Created by Minh Duc Tran on 4/10/14.
//
//

#ifndef __shitballoon_mvc__MenuScene__
#define __shitballoon_mvc__MenuScene__

#include <iostream>
#include "cocos2d.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;
using namespace CocosDenshion;

class MenuScene : public CCLayer {
public:
    MenuScene();
    ~MenuScene();
    
    static cocos2d::CCScene* scene();
    void showSBScene();
    void showHelpScene();
    virtual bool init();
    CREATE_FUNC(MenuScene);
    
private:
    CCSize _screenSize;
    CCMenu* _mainMenu;
};

#endif /* defined(__shitballoon_mvc__MenuScene__) */
