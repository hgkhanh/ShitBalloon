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
    CCMenuItemImage * playItem = CCMenuItemImage::create("button_normal.png", "button_pressed.png", this, menu_selector(MenuScene::showSBScene));
    playItem->setAnchorPoint(ccp(0.5, 0.5));
    CCLabelTTF* playLabel = CCLabelTTF::create("PLAY", "VisitorTT1BRK", 34);
    playLabel->setColor(ccc3(0, 0, 0));
    playLabel->setPosition(ccp(playItem->getPosition().x + playItem->getContentSize().width / 2, playItem->getPosition().y + playItem->getContentSize().height / 2));
    
    playItem->addChild(playLabel);
    
    CCMenuItemImage * helpItem = CCMenuItemImage::create("button_normal.png", "button_pressed.png", this, menu_selector(MenuScene::showSBScene));
    helpItem->setAnchorPoint(ccp(0.5, 0.5));
    CCLabelTTF* helpLabel = CCLabelTTF::create("HELP", "VisitorTT1BRK", 34);
    helpLabel->setColor(ccc3(0, 0, 0));
    helpLabel->setPosition(ccp(helpItem->getPosition().x + helpItem->getContentSize().width / 2, helpItem->getPosition().y + helpItem->getContentSize().height / 2));
    helpItem->addChild(helpLabel);
    
    _mainMenu = CCMenu::create(playItem, helpItem, NULL);
    _mainMenu->alignItemsVerticallyWithPadding(10);
    _mainMenu->setPosition(ccp(_screenSize.width * 0.5f, _screenSize.height * 0.5f));
    this->addChild(_mainMenu);
    return true;
}