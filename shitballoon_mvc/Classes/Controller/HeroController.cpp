//
//  HeroController.cpp
//  shitballoon_mvc
//
//  Created by Khanh Hoang Nguyen on 3/25/14.
//
//

#include "HeroController.h"

HeroController::HeroController()
{
    
}

HeroController::~HeroController()
{
    
}

HeroController* HeroController::createHeroWithPos(CCPoint aPos, CCLayer* aLayer, b2World* aWorld)
{
    //Model
    Hero* aHero = new Hero();
    aHero->initWithPos(ccp(aPos.x/PTM_RATIO,aPos.y/PTM_RATIO));
    this->setModel(aHero);
    //View
    HeroView* aView = new HeroView();
    aView->initWithModel(aHero, aLayer, aWorld);
    this->setView(aView);
    return this;
}

int HeroController::gotHit()
{
    if (_model->getState() == kCharacterStateAlive) {
        return _model->takeDamage();
    }
    return _model->getState();
}

void HeroController::touch(){
    b2Vec2 force = b2Vec2(0,150/PTM_RATIO);
    b2Body* heroBody = this->_view->getBody();
    heroBody->ApplyLinearImpulse(force,heroBody->GetLocalCenter());
}

void HeroController::tap(){
    b2Vec2 force = b2Vec2(0,250/PTM_RATIO);
    b2Body* heroBody = this->_view->getBody();
    heroBody->ApplyLinearImpulse(force,heroBody->GetWorldCenter());
}

void HeroController::swipeUp(){
    b2Vec2 force = b2Vec2(0,300/PTM_RATIO);
    b2Body* heroBody = this->_view->getBody();
    heroBody->ApplyLinearImpulse(force,heroBody->GetWorldCenter());
}

void HeroController::swipeDown(){
    b2Vec2 force = b2Vec2(0,-450/PTM_RATIO);
    b2Body* heroBody = this->_view->getBody();
    heroBody->ApplyLinearImpulse(force,heroBody->GetWorldCenter());
}

void HeroController::swipeLeft(){
    b2Vec2 force = b2Vec2(-300/PTM_RATIO,0);
    b2Body* heroBody = this->_view->getBody();
    heroBody->ApplyLinearImpulse(force,heroBody->GetWorldCenter());
}

void HeroController::swipeRight(){
    b2Vec2 force = b2Vec2(300/PTM_RATIO,0);
    b2Body* heroBody = this->_view->getBody();
    heroBody->ApplyLinearImpulse(force,heroBody->GetWorldCenter());
}

