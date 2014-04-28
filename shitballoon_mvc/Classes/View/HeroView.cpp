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

bool HeroView::initWithModel(Hero* aHero, CCLayer* aLayer, b2World* aWorld)
{
    if(!aHero){
        return false;
    }
    this->setModel(aHero);
    this->setWorld(aWorld);
    this->setLayer(aLayer);
    // Set Hero Model Delegate to This View
    aHero->setViewDelegate(this);

    // Create  sprite
        // sprite frame
    CCSprite* heroSprite = CCSprite::createWithSpriteFrameName("hero_idle_01.png");
    heroSprite->setScale(0.8f);
    // animation
    initAnimation();
    heroSprite->runAction(_upAction);
    
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
    
    // init Physics
    initPhysics(_world);
    return true;
}

void HeroView::animateIdle()
{
    _sprite->stopAllActions();
    _sprite->runAction(_idleAction);
}

void HeroView::animateDown()
{
    _sprite->stopAllActions();
    _sprite->runAction(_downAction);
}

void HeroView::animateUp()
{
    _sprite->stopAllActions();
    _sprite->runAction(_upAction);
}

void HeroView::animateLeft()
{
    _sprite->stopAllActions();
    _sprite->runAction(_moveAction);
    _sprite->setFlipX(true);
}

void HeroView::animateRight()
{
    _sprite->stopAllActions();
   
    _sprite->runAction(_moveAction);
    _sprite->setFlipX(false);
}

void HeroView::initAnimation()
{
    // up animation
    CCAnimation *anim = CCAnimation::create();
    CCSpriteFrameCache* spriteFrameCache =  CCSpriteFrameCache::sharedSpriteFrameCache();
    
    CCSpriteFrame *frame1 = spriteFrameCache->spriteFrameByName("hero_up_02.png");
    CCSpriteFrame *frame2 = spriteFrameCache->spriteFrameByName("hero_idle_01.png");
    anim->addSpriteFrame(frame1);
    anim->addSpriteFrame(frame2);
    anim->setDelayPerUnit(0.3f);
    CCAnimate *heroAnimate = CCAnimate::create(anim);
    this->setUpAction(CCRepeatForever::create(heroAnimate));
    _upAction->retain();
    
    // down animation
    anim = CCAnimation::create();
    frame1 = spriteFrameCache->spriteFrameByName("hero_down_02.png");
    frame2 = spriteFrameCache->spriteFrameByName("hero_idle_01.png");
    anim->addSpriteFrame(frame1);
    anim->setDelayPerUnit(0.3f);
    heroAnimate = CCAnimate::create(anim);
    this->setDownAction(CCRepeatForever::create(heroAnimate));
    _downAction->retain();
    
    // move animation
    anim = CCAnimation::create();
    frame1 = spriteFrameCache->spriteFrameByName("hero_idle_01.png");
    frame2 = spriteFrameCache->spriteFrameByName("hero_move_02.png");
    anim->addSpriteFrame(frame1);
    anim->addSpriteFrame(frame2);
    anim->setDelayPerUnit(0.3f);
    heroAnimate = CCAnimate::create(anim);
    this->setMoveAction(CCRepeatForever::create(heroAnimate));
    _moveAction->retain();
    
    // hit animation
    anim = CCAnimation::create();
    frame1 = spriteFrameCache->spriteFrameByName("hero_hit_02.png");
    anim->addSpriteFrame(frame1);
    anim->setDelayPerUnit(0.1f);
    CCAnimate *hitAnimate = CCAnimate::create(anim);
    hitAnimate->setDuration(0.2f);
    
    anim = CCAnimation::create();
    frame1 = spriteFrameCache->spriteFrameByName("hero_idle_01.png");
    frame2 = spriteFrameCache->spriteFrameByName("hero_move_02.png");
    anim->addSpriteFrame(frame1);
    anim->addSpriteFrame(frame2);
    anim->setDelayPerUnit(0.3f);
    heroAnimate = CCAnimate::create(anim);
    
    CCSequence *hitSeq = CCSequence::create(hitAnimate, heroAnimate);
    this->setHitAction(hitSeq);
    _hitAction->retain();
    
    // idle animation
    anim = CCAnimation::create();
    frame1 = spriteFrameCache->spriteFrameByName("hero_idle_01.png");
    anim->addSpriteFrame(frame1);
    anim->setDelayPerUnit(0.3f);
    heroAnimate = CCAnimate::create(anim);
    this->setIdleAction(CCRepeatForever::create(heroAnimate));
    _idleAction->retain();

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
    heroBodyShape.m_radius = this->_sprite->getContentSize().width*0.14/PTM_RATIO;
    heroBodyShape.m_p   = b2Vec2(0,-this->_sprite->getContentSize().height*0.15/PTM_RATIO);
    // Create shape definition and add body
    b2FixtureDef heroBodyFixDef;
    heroBodyFixDef.shape = &heroBodyShape;
    heroBodyFixDef.userData = (void *) kHeroBodyTag;
    heroBodyFixDef.density = 0.8f;
    heroBodyFixDef.friction = 0.2f;
    heroBodyFixDef.restitution = 0.5f;
    
    this->_body->CreateFixture(&heroBodyFixDef);
    //Balloon part
    // Create  shape
    b2CircleShape heroBalloonShape;
    heroBalloonShape.m_radius = this->_sprite->getContentSize().width*0.12/PTM_RATIO;
    heroBalloonShape.m_p   = b2Vec2(0,this->_sprite->getContentSize().height*0.15/PTM_RATIO);
    
    // Create shape definition and add body
    b2FixtureDef heroBalloonFixDef;
    heroBalloonFixDef.shape = &heroBalloonShape;
    heroBalloonFixDef.userData = (void *) kHeroBalloonTag;
    heroBalloonFixDef.density = 0.4f;
    heroBalloonFixDef.friction = 0.f;
    heroBalloonFixDef.restitution = 0.5f;
    
    this->_body->CreateFixture(&heroBalloonFixDef);

}

void HeroView::updateHPBar()
{
    if (_model->getCurrentHP() == 0)
    {
        this->_sprite->removeAllChildrenWithCleanup(true);
    }
    else
    {
        CCString* labelStr = CCString::createWithFormat("%i HP",this->_model->getCurrentHP());
        CCObject* child = this->_sprite->getChildren()->objectAtIndex(0);
        if(dynamic_cast<CCLabelTTF*>(child) != NULL)
        {
            ((CCLabelTTF*) child)->setString(labelStr->getCString());
        }
    }
}

void HeroView::animateHit()
{
    _sprite->stopAllActions();
    
    _sprite->runAction(_hitAction);
}

void HeroView::animateDead()
{
    _sprite->stopAllActions();
    CCSpriteFrameCache* spriteFrameCache =  CCSpriteFrameCache::sharedSpriteFrameCache();

    CCSpriteFrame *spriteFrame = spriteFrameCache->spriteFrameByName("hero_die_02.png");

    _sprite->setDisplayFrame(spriteFrame);
    
    // add final blow remove collision, let sprite fall out of screen
    for (b2Fixture* fixture = _body->GetFixtureList(); fixture; fixture = fixture->GetNext())
    {
        fixture->SetSensor(true);
    }
    b2Vec2 force = b2Vec2(0,300/PTM_RATIO);
    _body->ApplyLinearImpulse(force,_body->GetWorldCenter());
    CCLog("animateDead");
}