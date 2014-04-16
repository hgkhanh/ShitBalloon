//
//  HelloWorldScene.cpp
//  shitballoon_mvc
//
//  Created by Khanh Hoang Nguyen on 3/25/14.
//  Copyright __MyCompanyName__ 2014. All rights reserved.
//
#include "SBBaseScene.h"

SBBaseScene::SBBaseScene()
{
    this->_spawnPointControllerArray = new CCArray();
}

SBBaseScene::~SBBaseScene()
{
    CC_SAFE_DELETE(_world);
    delete _contactListener;
}

bool SBBaseScene::init(){
    if ( !CCLayer::init() )
    {
        return false;
    }
    this->setTouchEnabled(true);
    _screenSize = CCDirector::sharedDirector()->getWinSize();
    
    //Sprite Sheet
    this->initSprite();
    
    //init Physics and Touch
    this->initPhysics();
    this->initTouch();
    
    _running = true;
    
    // Create Contact Listener
    _contactListener = new SBContactListener();
    this->_world->SetContactListener(_contactListener);
    
    return true;
}

void SBBaseScene::addBackground(const char *pszFileName){
    CCSprite *background = CCSprite::create(pszFileName);
    background->setPosition(ccp( _screenSize.width * 0.5, _screenSize.height * 0.5));
    background->setOpacity(150);
    this->addChild(background);
    
    _btnPause = CCSprite::create("btn_pause_off.png");
    _btnPause->setAnchorPoint(ccp(1, 1));
    _btnPause->setPosition(ccp(_screenSize.width, _screenSize.height));
    this->addChild(_btnPause);
}

void SBBaseScene::addPlatforms(const char *pszFileName, CCPoint pos, int type){
    CCScale9Sprite *platform = CCScale9Sprite::create(pszFileName);
    platform->setCapInsets(CCRect(15,15,120,45));
    switch (type) {
        case kSmallPlatform:
            platform->setContentSize(CCSize(150,45));
            break;
        case kMediumPlatform:
            platform->setContentSize(CCSize(300,45));
            break;
        case kLargePlatform:
            platform->setContentSize(CCSize(450,45));
            break;
    }
    platform->setPosition(pos);
    this->addChild(platform);
    
    b2BodyDef platformBodyDef;
    platformBodyDef.type = b2_dynamicBody;
    platformBodyDef.position.Set(pos.x/PTM_RATIO, pos.y/PTM_RATIO);
    platformBodyDef.userData = platform;
    b2Body* platformBody = this->_world->CreateBody(&platformBodyDef);
    platformBody->SetGravityScale(0);
    
    b2PolygonShape platformShape;
    platformShape.SetAsBox(platform->getContentSize().width/PTM_RATIO/2, platform->getContentSize().height/PTM_RATIO/2);
    
    b2FixtureDef platformShapeDef;
    platformShapeDef.shape = &platformShape;
    platformShapeDef.density = 10000.0f;
    platformShapeDef.friction = 0.2f;
    platformShapeDef.restitution = 0.1f;
    b2Fixture* platformFixture = platformBody->CreateFixture(&platformShapeDef);
    
}

void SBBaseScene::initSprite()
{
    CCSpriteFrameCache* spriteFrameCache = CCSpriteFrameCache::sharedSpriteFrameCache();
    
    //  load the spritesheet file.
    spriteFrameCache->addSpriteFramesWithFile("AnimShit.plist");

    // create sprite batch node
    CCSpriteBatchNode* spriteBatchNode = CCSpriteBatchNode::create("AnimShit.png");
        // add _spriteBatchNode to scene
    this->addChild(spriteBatchNode);
}

void SBBaseScene::initPhysics()
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
    groundBodyDef.type = b2_staticBody;
	groundBodyDef.position.Set(0, 0); // bottom-left corner
    
	// Call the body factory which allocates memory for the ground body
	// from a pool and creates the ground box shape (also from a pool).
	// The body is also added to the world.
	_groundBody = this->_world->CreateBody(&groundBodyDef);
    
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



void SBBaseScene::addHero(CCPoint p)
{
    //Create  Hero MVC
    HeroController* heroController  = new HeroController();
    heroController->createHeroWithPos(p,this,_world);
    this->_heroController = heroController;
    this->addChild(_heroController->getView()->getSprite());
    
    //Set Delegate
    this->setDelegate(heroController);
}

void SBBaseScene::addSpawnPoint(CCPoint p, float spawnInterval, int capacity)
{
    //Create  SP MVC
    SpawnPointController* spawnPointController = new SpawnPointController();
    spawnPointController->create(p, this , this->getWorld(), spawnInterval, capacity);
    
    this->_spawnPointControllerArray->addObject(spawnPointController);
}

void SBBaseScene::initTouch()
{
    //swipe
    CCSwipeGestureRecognizer * swipe = CCSwipeGestureRecognizer::create();
    swipe->setTarget(this, callfuncO_selector(SBBaseScene::didSwipe));
    swipe->setDirection(kSwipeGestureRecognizerDirectionRight | kSwipeGestureRecognizerDirectionLeft
                        | kSwipeGestureRecognizerDirectionUp | kSwipeGestureRecognizerDirectionDown);
    swipe->setCancelsTouchesInView(true);
    this->addChild(swipe);
    
    
}

void SBBaseScene::ccTouchesBegan(cocos2d::CCSet* touches, cocos2d::CCEvent* event){
    CCTouch *touch = (CCTouch *)touches->anyObject();
    if (touch) {
        CCPoint tap = touch->getLocation();
        CCRect boundary;
        //handle button touches
        CCSprite * button;
        
        button = _btnPause;
        boundary = button->boundingBox();
        
        if (!boundary.containsPoint(tap)) {
            this->getDelegate()->touch();
        }
    }
}

void SBBaseScene::ccTouchesEnded(cocos2d::CCSet *touches, cocos2d::CCEvent *event){
    CCTouch *touch = (CCTouch *)touches->anyObject();
    if (touch) {
        CCPoint tap = touch->getLocation();
        CCRect boundary;
        CCSprite * button;
        
        button = _btnPause;
        boundary = button->boundingBox();
        
        if (boundary.containsPoint(tap)) {
            _running = !_running;
        }
    }
}

void SBBaseScene::didSwipe(CCObject * obj)
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

void SBBaseScene::tick(float dt)
{
    if (!_running) return;
    int velocityIterations = 8;
	int positionIterations = 1;
	_world->Step(dt, velocityIterations, positionIterations);
    
    std::vector<b2Body *>toDestroy; // list of Char is Dead
    srand ( time(NULL) );

    //Iterate over the bodies in the physics world
    for (b2Body* b = _world->GetBodyList(); b; b = b->GetNext())
    {
        if (b->GetUserData() != NULL) {

            //Synchronize the AtlasSprites position and rotation with the corresponding body
            CCSprite* curSprite = (CCSprite*)b->GetUserData();
            curSprite->setPosition( ccp( b->GetPosition().x * PTM_RATIO, b->GetPosition().y * PTM_RATIO) );
            curSprite->setRotation( -1 * CC_RADIANS_TO_DEGREES(b->GetAngle()) );
            
            // check dead Char
            if (curSprite->getTag() == kHeroTag)
            {
                if  (_heroController->getModel()->getState() == kCharacterStateDead )
                {
                    toDestroy.push_back(b);
                }
            }
            else if (curSprite->getTag() == kEnemyTag)
            {
                EnemyController* curEnemy = getEnemybyBody(b);
                if  (curEnemy->getModel()->getState() == kCharacterStateDead )
                {
                    toDestroy.push_back(b);
                }
            }
            // air resistance
            b2Vec2 vel = b->GetLinearVelocity();
            float speed = vel.Normalize();
            int curCharState = 0;
            //normalizes vector and returns length
            if(curSprite->getTag() == kHeroTag  )
            {
                curCharState = _heroController->getModel()->getState();
            }
            else if (curSprite->getTag() == kEnemyTag)
            {
                curCharState =  this->getEnemybyBody(b)->getModel()->getState();
            }
            
            if (curCharState != kCharacterStateDying)
            {
                b->ApplyForce( AIR_RESIST_SCALE * speed * speed * -vel, b->GetWorldCenter() );
            }
            //random enemy movement
            if(curSprite->getTag() == kEnemyTag){
                if(rand() % 2 == 0 ){ // 50% of time , apply force
                    b->SetLinearVelocity(b2Vec2(0, 0));
                    int x = rand() % (2*MAX_FORCE) - MAX_FORCE;
                    int y = rand() % (2*MAX_FORCE) - MAX_FORCE;
                    if(y>0){
                        b2Vec2 flapForce = b2Vec2(0,150/PTM_RATIO);
                        b->ApplyLinearImpulse(flapForce,b->GetPosition());
                    }
                    b2Vec2 enemyForce = b2Vec2(x/PTM_RATIO,y/PTM_RATIO);
                    b->ApplyLinearImpulse(enemyForce,b->GetPosition());
                    
                    if (x>0 && y >0)
                    {
                        if (x>y)
                        {
                            this->getEnemybyBody(b)->moveUp();
                        }
                        else
                        {
                            this->getEnemybyBody(b)->moveRight();
                        }
                    }
                    else if (x<0 && y >0)
                    {
                        if (-x>y)
                        {
                            this->getEnemybyBody(b)->moveDown();
                        }
                        else
                        {
                            this->getEnemybyBody(b)->moveRight();
                        }
                    }
                    else if (x>0 && y <0)
                    {
                        if (x>-y)
                        {
                            this->getEnemybyBody(b)->moveUp();
                        }
                        else
                        {
                            this->getEnemybyBody(b)->moveLeft();
                        }
                    }
                    else if (x<0 && y <0)
                    {
                        if (-x>y)
                        {
                            this->getEnemybyBody(b)->moveDown();
                        }
                        else
                        {
                            this->getEnemybyBody(b)->moveLeft();
                        }
                    }
                    
                }
                
            }
            
        }
    }
    
    // Check Contact
    std::vector<SBContact>::iterator pos;
    for (pos = _contactListener->_contacts.begin();
         pos!= _contactListener->_contacts.end();
         ++pos)
    {
        
        SBContact contact = *pos;
        
        if (contact.fixtureA->GetBody() != NULL && contact.fixtureB->GetBody() != NULL)
        {
            // (A : Hero) Hit (B : Enemy)
            if ((int)contact.fixtureA->GetUserData() == kHeroBodyTag
                && (int)contact.fixtureB->GetUserData() == kEnemyBalloonTag)
            {
                EnemyController* curEnemy = getEnemybyBody(contact.fixtureB->GetBody());
                if  (curEnemy)
                {
                    int hitResult = curEnemy->gotHit();
                    _heroController->hitting();
                    /*
                    if (hitResult == kCharacterStateDead
                        && std::find(toDestroy.begin(), toDestroy.end(), contact.fixtureB->GetBody() )
                        == toDestroy.end()) //check if Char was set to Destroy already (==last means not found)
                    {
                        toDestroy.push_back(contact.fixtureB->GetBody());
                    }
                     */
                }
            }
            // (B : Enemy) Hit (A:Hero)
            else if ((int)contact.fixtureA->GetUserData() == kHeroBalloonTag
                     && (int)contact.fixtureB->GetUserData() == kEnemyBodyTag)
            {
                int hitResult = _heroController->gotHit();
                
                /*
                if (hitResult == kCharacterStateDead
                    && std::find(toDestroy.begin(), toDestroy.end(), contact.fixtureB->GetBody() )
                    == toDestroy.end()) //check if Char was set to Destroy already (==last means not found)
                {
                    toDestroy.push_back(contact.fixtureA->GetBody());
                }
                */
            }
        }
    }
    
    // Process toDestroy
    std::vector<b2Body *>::iterator pos2;
    for(pos2 = toDestroy.begin(); pos2 != toDestroy.end(); ++pos2)
    {
        b2Body *bodyToDestroy = *pos2;
        if (bodyToDestroy->GetUserData() != NULL)
        {
            CCSprite *spriteToDestroy = (CCSprite *) bodyToDestroy->GetUserData();
            this->removeChild(spriteToDestroy, true);
        }
        _world->DestroyBody(bodyToDestroy);
    }
    
}



EnemyController* SBBaseScene::getEnemybyBody(b2Body *aBody)
{
    CCObject* curSPController;
    CCARRAY_FOREACH(_spawnPointControllerArray, curSPController)
    {
        CCObject* curEnemyController;
        CCARRAY_FOREACH(((SpawnPointController*)curSPController)->getEnemyList(), curEnemyController)
        {
            if (((EnemyController*)curEnemyController)->getView()->getBody() == aBody)
            {
                return ((EnemyController*)curEnemyController);
            }
        }
    }
    return NULL;
}
