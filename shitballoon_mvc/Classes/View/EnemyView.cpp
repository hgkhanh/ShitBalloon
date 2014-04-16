//
//  EnemyView.cpp
//  ShitBalloon
//
//  Created by Khanh Hoang Nguyen on 3/25/14.
//
//

#include "EnemyView.h"
EnemyView::EnemyView()
{
    
}

EnemyView::~EnemyView()
{
    
}

bool EnemyView::initWithModel(Enemy* anEnemy, CCLayer* aLayer, b2World* aWorld)
{
    if(!anEnemy){
        return false;
    }
    this->setModel(anEnemy);
    this->setWorld(aWorld);
    this->setLayer(aLayer);
    // Set Enemy Model Delegate to This View
    anEnemy->setViewDelegate(this);
    
    // Create  sprite
        // sprite frame
    CCSprite* enemySprite = CCSprite::createWithSpriteFrameName("LA_idle.png");
        // animation
    initAnimation();
    enemySprite->runAction(_upAction);
    
    enemySprite->setPosition(this->_model->getPosition());
    enemySprite->setTag(kEnemyTag);
    // Add HP Label
    CCString* enemyLabelStr = CCString::createWithFormat("%i HP",this->_model->getCurrentHP() );
    CCLabelTTF* enemyLabel = CCLabelTTF::create(enemyLabelStr->getCString(), "Helvetica", 18,
                                               CCSizeMake(245, 32), kCCTextAlignmentCenter);
    enemyLabel->setColor(ccBLUE);
    enemyLabel->setPosition(ccp(enemySprite->getContentSize().width,enemySprite->getContentSize().height));
    enemySprite->addChild(enemyLabel);
    
    //Set Sprite
    this->setSprite(enemySprite);
    
    // init Physics
    initPhysics(_world);
    return true;
}

void EnemyView::animateDown()
{
    _sprite->stopAllActions();
    _sprite->runAction(_downAction);
    CCLog("animateDown");
}

void EnemyView::animateUp()
{
    _sprite->stopAllActions();
    _sprite->runAction(_upAction);
    CCLog("animateUp");
}

void EnemyView::animateLeft()
{
    _sprite->stopAllActions();
    _sprite->runAction(_moveAction);
    _sprite->setFlipX(true);
    CCLog("animateLeft");
}

void EnemyView::animateRight()
{
    _sprite->stopAllActions();
    _sprite->runAction(_moveAction);
    _sprite->setFlipX(false);
    CCLog("animateRight");
}

void EnemyView::initAnimation()
{
    // up animation
    CCAnimation *anim = CCAnimation::create();
    CCSpriteFrameCache* spriteFrameCache =  CCSpriteFrameCache::sharedSpriteFrameCache();
    
    CCSpriteFrame *frame1 = spriteFrameCache->spriteFrameByName("LA_idle.png");
    CCSpriteFrame *frame2 = spriteFrameCache->spriteFrameByName("LA_up_02.png");
    anim->addSpriteFrame(frame1);
    anim->addSpriteFrame(frame2);
    anim->setDelayPerUnit(0.3f);
    CCAnimate *enemyAnimate = CCAnimate::create(anim);
    this->setUpAction(CCRepeatForever::create(enemyAnimate));
    _upAction->retain();
    
    // down animation
    anim = CCAnimation::create();
    frame1 = spriteFrameCache->spriteFrameByName("LA_idle.png");
    frame2 = spriteFrameCache->spriteFrameByName("LA_down_02.png");
    anim->addSpriteFrame(frame1);
    anim->addSpriteFrame(frame2);
    anim->setDelayPerUnit(0.3f);
    enemyAnimate = CCAnimate::create(anim);
    this->setDownAction(CCRepeatForever::create(enemyAnimate));
    _downAction->retain();
    
    // move animation
    anim = CCAnimation::create();
    frame1 = spriteFrameCache->spriteFrameByName("LA_idle.png");
    frame2 = spriteFrameCache->spriteFrameByName("LA_move_02.png");
    anim->addSpriteFrame(frame1);
    anim->addSpriteFrame(frame2);
    anim->setDelayPerUnit(0.3f);
    enemyAnimate = CCAnimate::create(anim);
    this->setMoveAction(CCRepeatForever::create(enemyAnimate));
    _moveAction->retain();
    
    // hit animation
    anim = CCAnimation::create();
    frame1 = spriteFrameCache->spriteFrameByName("LA_hit_02.png");
    anim->addSpriteFrame(frame1);
    anim->setDelayPerUnit(0.1f);
    CCAnimate *hitAnimate = CCAnimate::create(anim);
    hitAnimate->setDuration(0.2f);
    
    anim = CCAnimation::create();
    frame1 = spriteFrameCache->spriteFrameByName("LA_idle.png");
    frame2 = spriteFrameCache->spriteFrameByName("LA_move_02.png");
    anim->addSpriteFrame(frame1);
    anim->addSpriteFrame(frame2);
    anim->setDelayPerUnit(0.3f);
    enemyAnimate = CCAnimate::create(anim);
    
    CCSequence *hitSeq = CCSequence::create(hitAnimate, enemyAnimate);
    this->setHitAction(hitSeq);
    _hitAction->retain();

}

void EnemyView::initPhysics(b2World* aWorld){
    // Create enemy body
    b2BodyDef enemyBodyDef;
    enemyBodyDef.type = b2_dynamicBody;
    enemyBodyDef.position.Set(this->_model->getPosition().x,this->_model->getPosition().y);
    enemyBodyDef.userData = this->_sprite;
    enemyBodyDef.fixedRotation = true;
    
    this->_body = aWorld->CreateBody(&enemyBodyDef);
    
    //Body part
    // Create  shape
    b2CircleShape enemyBodyShape;
    enemyBodyShape.m_radius = this->_sprite->getContentSize().width*0.25/PTM_RATIO;
    enemyBodyShape.m_p   = b2Vec2(0,-this->_sprite->getContentSize().height*0.25/PTM_RATIO);
    // Create shape definition and add body
    b2FixtureDef enemyBodyFixDef;
    enemyBodyFixDef.shape = &enemyBodyShape;
    enemyBodyFixDef.userData = (void *) kEnemyBodyTag;
    enemyBodyFixDef.density = 0.4f;
    enemyBodyFixDef.friction = 0.2f;
    enemyBodyFixDef.restitution = 0.5f;
    
    this->_body->CreateFixture(&enemyBodyFixDef);
    //Balloon part
    // Create  shape
    b2CircleShape enemyBalloonShape;
    enemyBalloonShape.m_radius = this->_sprite->getContentSize().width*0.15/PTM_RATIO;
    enemyBalloonShape.m_p   = b2Vec2(0,this->_sprite->getContentSize().height*0.3/PTM_RATIO);
    
    // Create shape definition and add body
    b2FixtureDef enemyBalloonFixDef;
    enemyBalloonFixDef.shape = &enemyBalloonShape;
    enemyBalloonFixDef.userData = (void *) kEnemyBalloonTag;
    enemyBalloonFixDef.density = 0.4f;
    enemyBalloonFixDef.friction = 0.f;
    enemyBalloonFixDef.restitution = 0.5f;
    
    this->_body->CreateFixture(&enemyBalloonFixDef);
    
}

void EnemyView::updateHPBar()
{
    CCString* labelStr = CCString::createWithFormat("%i HP",this->_model->getCurrentHP());
    CCObject* child = this->_sprite->getChildren()->objectAtIndex(0);
    if(dynamic_cast<CCLabelTTF*>(child) != NULL){
        ((CCLabelTTF*) child)->setString(labelStr->getCString());
    }
}

void EnemyView::animateHit()
{
    _sprite->stopAllActions();
    
    _sprite->runAction(_hitAction);
    
    CCLog("animateHit");
}

void EnemyView::animateDead()
{
    _sprite->stopAllActions();
    CCSpriteFrameCache* spriteFrameCache =  CCSpriteFrameCache::sharedSpriteFrameCache();
    
    CCSpriteFrame *spriteFrame = spriteFrameCache->spriteFrameByName("LA_die_02.png");
    
    _sprite->setDisplayFrame(spriteFrame);
    
    // add final blow remove collision, let sprite fall out of screen
    for (b2Fixture* fixture = _body->GetFixtureList(); fixture; fixture = fixture->GetNext())
    {
        fixture->SetDensity(20.0f);
        fixture->SetSensor(true);
        b2Vec2 force = b2Vec2(0,300/PTM_RATIO);
        _body->ApplyLinearImpulse(force,_body->GetWorldCenter());
    }
    CCLog("animateDead");
}