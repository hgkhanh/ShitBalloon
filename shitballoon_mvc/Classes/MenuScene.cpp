//
//  MenuScene.cpp
//  shitballoon_mvc
//
//  Created by Minh Duc Tran on 4/10/14.
//
//

#include "MenuScene.h"
#include "SBScene.h"

MenuScene::~MenuScene(){}

MenuScene::MenuScene(){
}

CCScene* MenuScene::scene()
{
    CCScene *scene = CCScene::create();
    MenuScene* layer = MenuScene::create();
    scene->addChild(layer);
    
    return scene;
}

void MenuScene::showSBScene(){
    CCScene* newScene = CCTransitionFade::create(0.5f, SBScene::scene());
    CCDirector::sharedDirector()->replaceScene(newScene);
}

void MenuScene::showHelpScene(){
    CCScene* newScene = CCTransitionFade::create(0.5f, SBScene::scene());
    CCDirector::sharedDirector()->replaceScene(newScene);
}

bool MenuScene::init()
{
    if ( !CCLayer::init() )
    {
        return false;
    }
    this->setTouchEnabled(true);
    _screenSize = CCDirector::sharedDirector()->getWinSize();
    
    CCSprite* bg = CCSprite::create("background.png");
    bg->setPosition(ccp(_screenSize.width *0.5f, _screenSize.height * 0.5f));
    this->addChild(bg);
    
    //create menu
    CCSprite * menuItemOn;
    CCSprite * menuItemOff;
    menuItemOn = CCSprite::create("btn_play_on.png");
    menuItemOff = CCSprite::create("btn_play_off.png");
    CCMenuItemSprite * playItem = CCMenuItemSprite::create(menuItemOn, menuItemOff, this, menu_selector(MenuScene::showSBScene));
    
    menuItemOn = CCSprite::create("btn_help_on.png");
    menuItemOff = CCSprite::create("btn_help_off.png");
    CCMenuItemSprite * helpItem = CCMenuItemSprite::create(menuItemOn, menuItemOff, this, menu_selector(MenuScene::showHelpScene));
    _mainMenu = CCMenu::create(playItem, helpItem, NULL);
    _mainMenu->alignItemsVerticallyWithPadding(10);
    _mainMenu->setPosition(ccp(_screenSize.width * 0.5f, _screenSize.height * 0.5f));
    this->addChild(_mainMenu);
    return true;
}