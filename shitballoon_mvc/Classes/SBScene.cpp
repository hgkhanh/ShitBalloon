//
//  HelloWorldScene.cpp
//  shitballoon_mvc
//
//  Created by Khanh Hoang Nguyen on 3/25/14.
//  Copyright __MyCompanyName__ 2014. All rights reserved.
//
#include "SBScene.h"
#include "SimpleAudioEngine.h"
#include "CommonProtocols.h"

using namespace cocos2d;
using namespace CocosDenshion;


SBScene::SBScene()
{
    this->_spawnPointArray = new CCArray();
}

SBScene::~SBScene()
{
    CC_SAFE_DELETE(_world);
}

CCScene* SBScene::scene()
{

    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // add layer as a child to scene
    SBScene* layer = SBScene::create();
    scene->addChild(layer);
    return scene;
}

bool SBScene::init(){
    if ( !CCLayer::init() )
    {
        return false;
    }
    this->setTouchEnabled(true);
    _screenSize = CCDirector::sharedDirector()->getWinSize();
    //init Physics and Touch
    this->initPhysics();
    this->initTouch();
    
    // init object
    this->addBackground();
    this->addHero(ccp(_screenSize.width * 0.5, _screenSize.height * 0.9));
    this->addSpawnPoint(ccp(_screenSize.width * 0.2, _screenSize.height * 0.5));
    
    this->schedule(schedule_selector(SBScene::tick));
    
    return true;
}

void SBScene::addBackground(){
    CCSprite *background = CCSprite::create("background.png");
    background->setPosition(ccp( _screenSize.width * 0.5, _screenSize.height * 0.5));
    background->setOpacity(150);
    this->addChild(background);
}

void SBScene::initPhysics()
{
    // Define the gravity vector.
	b2Vec2 gravity;
	gravity.Set(0.0f, -10.0f);
    
	// Construct a world object
	this->_world = new b2World(gravity);
    
    /* Create EDGES around the entire screen
     */
	// Define the ground body.
	b2BodyDef groundBodyDef;
	groundBodyDef.position.Set(0, 0); // bottom-left corner
    
	// Call the body factory which allocates memory for the ground body
	// from a pool and creates the ground box shape (also from a pool).
	// The body is also added to the world.
	b2Body* _groundBody = this->_world->CreateBody(&groundBodyDef);
    
	// Define the ground box shape.
	b2EdgeShape groundBox;
    
	// bottom
	groundBox.Set(b2Vec2(0,0), b2Vec2(_screenSize.width/PTM_RATIO,0));
	_groundBody->CreateFixture(&groundBox, 0);
    
	// top
	groundBox.Set(b2Vec2(0,_screenSize.height/PTM_RATIO), b2Vec2(_screenSize.width/PTM_RATIO,_screenSize.height/PTM_RATIO));
	_groundBody->CreateFixture(&groundBox, 0);
    
	// left
	groundBox.Set(b2Vec2(0,_screenSize.height/PTM_RATIO), b2Vec2(0,0));
	_groundBody->CreateFixture(&groundBox, 0);
    
	// right
	groundBox.Set(b2Vec2(_screenSize.width/PTM_RATIO,_screenSize.height/PTM_RATIO), b2Vec2(_screenSize.width/PTM_RATIO,0));
	_groundBody->CreateFixture(&groundBox, 0);
}



void SBScene::addHero(CCPoint p)
{
    //Create  Hero MVC
    HeroController* heroController  = HeroController::createHeroWithPos(p);
    this->_heroView = heroController->getView();
    this->_heroView->initPhysics(_world);
    this->addChild(_heroView->getSprite());
    
    
    //Set Delegate
    this->setDelegate(heroController);
}

void SBScene::addSpawnPoint(CCPoint p)
{
    //Create  SP MVC
    SpawnPointController* spawnPointController  = SpawnPointController::createWithPos(p);
    this->_spawnPointArray->addObject(spawnPointController->getView());
}

void SBScene::initTouch()
{
    //tap
    CCTapGestureRecognizer * tap = CCTapGestureRecognizer::create();
    tap->setTarget(this, callfuncO_selector(SBScene::didTap));
    tap->setNumberOfTapsRequired(1);
    tap->setCancelsTouchesInView(true);
    this->addChild(tap);
    
    //swipe
    CCSwipeGestureRecognizer * swipe = CCSwipeGestureRecognizer::create();
    swipe->setTarget(this, callfuncO_selector(SBScene::didSwipe));
    swipe->setDirection(kSwipeGestureRecognizerDirectionRight | kSwipeGestureRecognizerDirectionLeft
                        | kSwipeGestureRecognizerDirectionUp | kSwipeGestureRecognizerDirectionDown);
    swipe->setCancelsTouchesInView(true);
    this->addChild(swipe);
    

}

void SBScene::ccTouchesBegan(cocos2d::CCSet* touches, cocos2d::CCEvent* event){
    //CCLog("ccTouchesBegan");
    //Iterate over the bodies in the physics world
    this->getDelegate()->touch();
}

void SBScene::didTap(CCObject * obj){
    //CCLog("didTap");
    this->getDelegate()->tap();
}

void SBScene::didSwipe(CCObject * obj)
{
    //CCLog("didSwipe");
    CCSwipe * swipe = (CCSwipe*)obj;
   
    if(swipe->direction == kSwipeGestureRecognizerDirectionRight)
    {
        this->getDelegate()->swipeRight();
    }
    else if(swipe->direction == kSwipeGestureRecognizerDirectionLeft)
    {
        this->getDelegate()->swipeLeft();
    }
    else if(swipe->direction == kSwipeGestureRecognizerDirectionUp)
    {
        this->getDelegate()->swipeUp();
    }
    else if(swipe->direction == kSwipeGestureRecognizerDirectionDown)
    {
        this->getDelegate()->swipeDown();
    }
}

void SBScene::tick(float dt)
{
    int velocityIterations = 8;
	int positionIterations = 1;
	_world->Step(dt, velocityIterations, positionIterations);

    
    //Iterate over the bodies in the physics world
    for (b2Body* b = _world->GetBodyList(); b; b = b->GetNext())
    {
        if (b->GetUserData() != NULL) {
            //Synchronize the AtlasSprites position and rotation with the corresponding body
            CCSprite* myActor = (CCSprite*)b->GetUserData();
            myActor->setPosition( ccp( b->GetPosition().x * PTM_RATIO, b->GetPosition().y * PTM_RATIO) );
            myActor->setRotation( -1 * CC_RADIANS_TO_DEGREES(b->GetAngle()) );
            // air resistance
			b2Vec2 vel = b->GetLinearVelocity();
			float speed = vel.Normalize(); //normalizes vector and returns length
			b->ApplyForce( AIR_RESIST_SCALE * speed * speed * -vel, b->GetWorldCenter() );
        }    
    }
    
}




