//
//  HeroView.cpp
//  ShitBalloon
//
//  Created by Khanh Hoang Nguyen on 3/25/14.
//
//

#include "HeroView.h"
HeroView::HeroView()
{
    
}

HeroView::~HeroView()
{
    
}

bool HeroView::initWithModel(Hero* aHero)
{
    if(!aHero){
        return false;
    }
    this->setModel(aHero);
    // Set Hero Model Delegate to This View
    aHero->setDelegate(this);

    // Create  sprite
    CCSprite* heroSprite = CCSprite::create("hero.png");
    heroSprite->setPosition(this->_model->getPosition());
    heroSprite->setTag(kHeroTag);
        // Add HP Label
    CCString* heroLabelStr = CCString::createWithFormat("%i HP",this->_model->getCurrentHP() );
    CCLabelTTF* heroLabel = CCLabelTTF::create(heroLabelStr->getCString(), "Helvetica", 18,
                                               CCSizeMake(245, 32), kCCTextAlignmentCenter);
    heroLabel->setColor(ccBLUE);
    heroLabel->setPosition(ccp(heroSprite->getContentSize().width,heroSprite->getContentSize().height));
    heroSprite->addChild(heroLabel);
    
    //Set Sprite
    this->setSprite(heroSprite);
    return true;
}

void HeroView::initPhysics(b2World* aWorld){
    // Create hero body
    b2BodyDef heroBodyDef;
    heroBodyDef.type = b2_dynamicBody;
    heroBodyDef.position.Set(this->_model->getPosition().x,this->_model->getPosition().y);
    heroBodyDef.userData = this->_sprite;
    heroBodyDef.fixedRotation = true;
    
    this->_body = aWorld->CreateBody(&heroBodyDef);
    
    //Body part
    // Create  shape
    b2CircleShape heroBodyShape;
    heroBodyShape.m_radius = this->_sprite->getContentSize().width*0.25/PTM_RATIO;
    heroBodyShape.m_p   = b2Vec2(0,-this->_sprite->getContentSize().height*0.25/PTM_RATIO);
    // Create shape definition and add body
    b2FixtureDef heroBodyFixDef;
    heroBodyFixDef.shape = &heroBodyShape;
    heroBodyFixDef.userData = (void *) kHeroBodyTag;
    heroBodyFixDef.density = 0.4f;
    heroBodyFixDef.friction = 0.f;
    heroBodyFixDef.restitution = 0.5f;
    
    this->_body->CreateFixture(&heroBodyFixDef);
    //Balloon part
    // Create  shape
    b2CircleShape heroBalloonShape;
    heroBalloonShape.m_radius = this->_sprite->getContentSize().width*0.15/PTM_RATIO;
    heroBalloonShape.m_p   = b2Vec2(0,this->_sprite->getContentSize().height*0.3/PTM_RATIO);
    
    // Create shape definition and add body
    b2FixtureDef heroBalloonFixDef;
    heroBalloonFixDef.shape = &heroBalloonShape;
    heroBalloonFixDef.userData = (void *) kHeroBalloonTag;
    heroBalloonFixDef.density = 0.4f;
    heroBalloonFixDef.friction = 0.f;
    heroBalloonFixDef.restitution = 0.5f;
    
    this->_body->CreateFixture(&heroBalloonFixDef);

}

void HeroView::updateHPBar(){
    CCString* labelStr = CCString::createWithFormat("%i HP",this->_model->getCurrentHP());
    CCObject* child = this->_sprite->getChildren();
    if(dynamic_cast<CCLabelTTF*>(child) != NULL){
        ((CCLabelTTF*) child)->setString(labelStr->getCString());
    }
}
