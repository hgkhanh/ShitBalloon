//
//  PauseLayer.cpp
//  shitballoon_mvc
//
//  Created by Minh Duc Tran on 4/16/14.
//
//

#include "PauseLayer.h"

PauseLayer::~PauseLayer(){
    
}

PauseLayer::PauseLayer(){
    
}

PauseLayer* PauseLayer::create(const ccColor4B &color, GLfloat width, GLfloat height, CCSize screenSize) {
    PauseLayer* pLayer = (PauseLayer*) CCLayerColor::create(color, width, height);
    pLayer->_paused = CCLabelTTF::create("PAUSED", "VisitorTT1BRK", 50);
    pLayer->_paused->setPosition(ccp(screenSize.width * 0.5, screenSize.height * 0.7));
    pLayer->addChild(pLayer->_paused);
    return pLayer;
}