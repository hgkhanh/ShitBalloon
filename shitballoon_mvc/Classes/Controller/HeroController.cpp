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

void HeroController::hitting()
{
    if (_model->getState() == kCharacterStateAlive) {
        _view->animateHit();
    }
}

void HeroController::touch(){
    if (_model->getState() != kCharacterStateDying
        && _model->getState() != kCharacterStateDead)
    {
        b2Vec2 force = b2Vec2(0,400/PTM_RATIO);
        b2Body* heroBody = this->_view->getBody();
        heroBody->ApplyLinearImpulse(force,heroBody->GetLocalCenter());
        _view->animateUp();
    }
}

void HeroController::swipeUp(){
    if (_model->getState() != kCharacterStateDying
        && _model->getState() != kCharacterStateDead)
    {
        b2Vec2 force = b2Vec2(0,300/PTM_RATIO);
        b2Body* heroBody = this->_view->getBody();
        heroBody->ApplyLinearImpulse(force,heroBody->GetWorldCenter());
        _view->animateUp();
    }
}

void HeroController::swipeDown(){
    if (_model->getState() != kCharacterStateDying
        && _model->getState() != kCharacterStateDead)
    {
        b2Vec2 force = b2Vec2(0,-450/PTM_RATIO);
        b2Body* heroBody = this->_view->getBody();
        heroBody->ApplyLinearImpulse(force,heroBody->GetWorldCenter());
        _view->animateDown();
    }
}

void HeroController::swipeLeft(){
    if (_model->getState() != kCharacterStateDying
        && _model->getState() != kCharacterStateDead)
    {
        b2Vec2 force = b2Vec2(-300/PTM_RATIO,0);
        b2Body* heroBody = this->_view->getBody();
        heroBody->ApplyLinearImpulse(force,heroBody->GetWorldCenter());
        _view->animateLeft();
    }
}

void HeroController::swipeRight(){
    if (_model->getState() != kCharacterStateDying
        && _model->getState() != kCharacterStateDead)
    {
        b2Vec2 force = b2Vec2(300/PTM_RATIO,0);
        b2Body* heroBody = this->_view->getBody();
        heroBody->ApplyLinearImpulse(force,heroBody->GetWorldCenter());
        _view->animateRight();
    }
}

