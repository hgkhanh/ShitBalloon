//
//  GameOverLayer.cpp
//  shitballoon_mvc
//
//  Created by Minh Duc Tran on 4/23/14.
//
//

#include "GameOverLayer.h"

GameOverLayer::~GameOverLayer(){
    
}

GameOverLayer::GameOverLayer(){
    
}

GameOverLayer* GameOverLayer::create(const ccColor4B &color, GLfloat width, GLfloat height, CCSize screenSize) {
    GameOverLayer* GOLayer = (GameOverLayer*) CCLayerColor::create(color, width, height);
    GOLayer->_gameOver = CCLabelTTF::create("GAME OVER", "VisitorTT1BRK", 50);
    GOLayer->_gameOver->setPosition(ccp(screenSize.width * 0.5, screenSize.height * 0.7));
    GOLayer->addChild(GOLayer->_gameOver);
    return GOLayer;
}