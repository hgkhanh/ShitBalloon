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
    this->setEnemyCount(0);
    
    //Sprite Sheet
    this->initSprite();
    
    //init Physics and Touch
    this->initPhysics();
    this->initTouch();
    
    _running = true;
    _isHeroDie = false;
    
    // Create Contact Listener
    _contactListener = new SBContactListener();
    this->_world->SetContactListener(_contactListener);
    
    return true;
}

void SBBaseScene::addBackground(const char *pszFileName){
    CCSprite *background = CCSprite::create(pszFileName);
    background->setPosition(ccp( _screenSize.width * 0.5, _screenSize.height * 0.5));
    this->addChild(background);
    
    _btnPause = CCSprite::create("pause_button.png");
    _btnPause->setAnchorPoint(ccp(1, 1));
    _btnPause->setPosition(ccp(_screenSize.width, _screenSize.height));
    this->addChild(_btnPause);
    
    _btnReset = CCSprite::create("pause_button.png");
    _btnReset->setAnchorPoint(ccp(1, 1));
    _btnReset->setPosition(ccp(_screenSize.width - _btnPause->getContentSize().width, _screenSize.height));
    this->addChild(_btnReset);
    
    CCSprite * menuItemOn;
    CCSprite * menuItemOff;
    menuItemOn = CCSprite::create("btn_play_on.png");
    menuItemOff = CCSprite::create("btn_play_off.png");
    CCMenuItemSprite * playItem = CCMenuItemSprite::create(menuItemOn, menuItemOff, this, menu_selector(SBBaseScene::resume));
    
    menuItemOn = CCSprite::create("btn_help_on.png");
    menuItemOff = CCSprite::create("btn_help_off.png");
    CCMenuItemSprite * helpItem = CCMenuItemSprite::create(menuItemOn, menuItemOff, this, menu_selector(SBBaseScene::showMenuScene));
    _pauseMenu = CCMenu::create(playItem, helpItem, NULL);
    _pauseMenu->alignItemsVerticallyWithPadding(10);
    _pauseMenu->setPosition(ccp(_screenSize.width * 0.5f, _screenSize.height * 0.5f));
    _pauseMenu->setVisible(false);
    this->addChild(_pauseMenu, 9);
}

void SBBaseScene::addPlatforms(char *fileName, CCPoint pos, int type){
    char * newChar = new char[strlen(fileName) + 12];
    strcpy(newChar, fileName);
    switch (type) {
        case kSmallPlatform:
            strcat(newChar, "_short.gif");
            break;
        case kMediumPlatform:
            strcat(newChar, "_medium.png");
            break;
        case kLargePlatform:
            strcat(newChar, "_long.gif");
            break;
        default:
            break;
    }
    CCSprite *platform = CCSprite::create(newChar);

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
    platformBody->CreateFixture(&platformShapeDef);
}

void SBBaseScene::resume() {
    if (_running) return;
    _running = !_running;
    this->removeChildByTag(1000);
    this->_pauseMenu->setVisible(false);
    this->_btnReset->setVisible(true);
    this->_btnPause->setVisible(true);
}

void SBBaseScene::showMenuScene() {
    if (_running) return;
    _running = !_running;
    CCScene* newScene = CCTransitionFade::create(0.5f, MenuScene::scene());
    MenuScene* newLayer= (MenuScene*) newScene;
    newLayer->retain();
    CCDirector::sharedDirector()->replaceScene(newScene);
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
    
    if (kDebug==1) {
        this->addChild(B2DebugDrawLayer::create(_world, PTM_RATIO), 9999);
    }
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
        CCRect boundaryPause;
        CCRect boundaryReset;
        //handle button touches
        
        boundaryPause = _btnPause->boundingBox();
        boundaryReset = _btnReset->boundingBox();
        
        if (!boundaryPause.containsPoint(tap) && !boundaryReset.containsPoint(tap) && _running) {
            this->getDelegate()->touch();
        }
        if (boundaryPause.containsPoint(tap) && _running) {
            CCTexture2D* tex = CCTextureCache::sharedTextureCache()->addImage("pause_button_active.png");
            _btnPause->setTexture(tex);
        }
        if (boundaryReset.containsPoint(tap) && _running) {
            CCTexture2D* tex = CCTextureCache::sharedTextureCache()->addImage("pause_button_active.png");
            _btnPause->setTexture(tex);
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
                    setHeroDie();
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
            
            if (curCharState == kCharacterStateDying)
            { // make dying char fall faster
                b2Vec2 flapForce = b2Vec2(0,-50/PTM_RATIO);
                b->ApplyLinearImpulse(flapForce,b->GetPosition());
            }
            else
            { // create balloon-like movement
                b->ApplyForce( AIR_RESIST_SCALE * speed * speed * -vel, b->GetWorldCenter() );
            }
            // check hero idle
            if (curSprite->getTag() == kHeroTag && speed < 1.0f) {
                _heroController->getView()->animateIdle();
            }
            //random enemy movement
            if(curSprite->getTag() == kEnemyTag && curCharState != kCharacterStateDying){
                if(rand() % 2 == 0 ){ // 50% of time , apply force
                    b->SetLinearVelocity(b2Vec2(0, 0));
                    int x = rand() % (2*MAX_FORCE) - MAX_FORCE;
                    int y = rand() % (2*MAX_FORCE) - MAX_FORCE;
                    if(y>0){
                        b2Vec2 flapForce = b2Vec2(0,380/PTM_RATIO);
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
                if  (curEnemy && curEnemy->getModel()->getState() == kCharacterStateAlive && _heroController->getModel()->getState() == kCharacterStateAlive)
                {
                    int result = curEnemy->gotHit();
                    if (result == kCharacterStateDying) {
                        CCPoint popPos = ccp(curEnemy->getView()->getSprite()->getPosition().x,curEnemy->getView()->getSprite()->getPosition().y + curEnemy->getView()->getSprite()->getContentSize().height*0.25);
                        this->showPopBalloon(kEnemyTag,popPos);
                        this->setEnemyCount(this->getEnemyCount() - 1);
                    }
                    _heroController->hitting();
                    SimpleAudioEngine::sharedEngine()->playEffect("balloon_pop.wav");
                }
            }
            // (B : Enemy) Hit (A:Hero)
            else if ((int)contact.fixtureA->GetUserData() == kHeroBalloonTag
                     && (int)contact.fixtureB->GetUserData() == kEnemyBodyTag)
            {
                EnemyController* curEnemy = getEnemybyBody(contact.fixtureB->GetBody());
                if  (curEnemy && curEnemy->getModel()->getState() == kCharacterStateAlive && _heroController->getModel()->getState() == kCharacterStateAlive)
                {
                    int result = _heroController->gotHit();
                    if (result == kCharacterStateDying) {
                        CCPoint popPos = ccp(_heroController->getView()->getSprite()->getPosition().x,_heroController->getView()->getSprite()->getPosition().y + _heroController->getView()->getSprite()->getContentSize().height*0.25);
                        this->showPopBalloon(kHeroTag,popPos);
                        this->setTouchEnabled(false);
                    }
                    curEnemy->hitting();
                    SimpleAudioEngine::sharedEngine()->playEffect("balloon_pop.wav");
                }
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

void SBBaseScene::setHeroDie() {
    _isHeroDie = true;
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

void SBBaseScene::showPopBalloon(int charTag, CCPoint aPos)
{
    //balloon pop
        //particles
    CCParticleSmoke* balloonPop = new CCParticleSmoke();
    balloonPop->initWithTotalParticles(10);
    balloonPop->setAutoRemoveOnFinish(true);
    balloonPop->setStartSize(50.0f);
    balloonPop->setEndSize(1.0f);
    balloonPop->setEmitterMode(kCCParticleModeGravity);
    balloonPop->setSpeed(100.0f);
    balloonPop->setAnchorPoint(ccp(0.5f,0.5f));
    balloonPop->setPosition(aPos);
    balloonPop->setDuration(0.3f);
    this->addChild(balloonPop);
    balloonPop->release();
        // animation
    // up animation
    CCAnimation *anim = CCAnimation::create();
    CCSpriteFrameCache* spriteFrameCache =  CCSpriteFrameCache::sharedSpriteFrameCache();
    CCSpriteFrame *frame1 = spriteFrameCache->spriteFrameByName("balloon_02.png");
    CCSpriteFrame *frame2 = spriteFrameCache->spriteFrameByName("balloon_03.png");
    if (charTag == kEnemyTag) {
        frame1 = spriteFrameCache->spriteFrameByName("red_balloon_02.png");
        frame2 = spriteFrameCache->spriteFrameByName("red_balloon_03.png");
    }
    anim->addSpriteFrame(frame1);
    anim->addSpriteFrame(frame2);
    anim->setDelayPerUnit(0.1f);
    
    CCAnimate *balloonAnimate = CCAnimate::create(anim);
    balloonAnimate->setDuration(0.5f);
    
    CCCallFuncND *actionMoveDone = CCCallFuncND::create(this, callfuncND_selector(SBBaseScene::spriteMoveFinished), (CCObject *) this );
    CCSequence *popSequence = CCSequence::create(balloonAnimate,actionMoveDone);
    
    CCSprite* balloonSprite = CCSprite::create();
    balloonSprite->setPosition(aPos);
    this->addChild(balloonSprite);
    balloonSprite->runAction(popSequence);
    CCLog("ANimate POP");
}

void SBBaseScene::spriteMoveFinished(CCObject *sender)
{
    CCSprite *sprite = (CCSprite *)sender;
    sprite->stopAllActions();
    sprite->removeFromParent();
}
