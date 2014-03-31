//
//  HeroView.cpp
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

bool EnemyView::initWithModel(Enemy* anEnemy)
{
    if(!anEnemy){
        return false;
    }
    this->setModel(anEnemy);
    // Set Enemy Model Delegate to This View
    anEnemy->setDelegate(this);
    
    // Create  sprite
    CCSprite* enemySprite = CCSprite::create("enemy.png");
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
    return true;
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
    enemyBodyFixDef.friction = 0.f;
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
