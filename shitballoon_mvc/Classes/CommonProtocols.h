//
//  Header.h
//  ShitBalloon
//
//  Created by Minh Duc Tran on 3/13/14.
//
//

#ifndef ShitBalloon_Common_Protocols_h
#define ShitBalloon_Common_Protocols_h

#include "cocos2d.h"

using namespace cocos2d;

typedef enum {
    kCharacterStateAlive,
    kCharacterStateHitting,
    kCharacterStateGotHit,
    kCharacterStateDying,
    kCharacterStateDead,
} CharacterStates;

typedef enum {
    kObjectTypeNone,
    kObjectTypeHero,
    kObjectTypeEnemy,
    kObjectTypePlatform,
} GameObjectType;

typedef enum {
    kHeroTag = 1,
    kEnemyTag = 2,
    kHeroBodyTag = 11,
    kHeroBalloonTag = 12,
    kEnemyBodyTag = 21,
    kEnemyBalloonTag = 21,
    kEnemyCount = 5,
} GameSpriteTag;

typedef enum {
    kHitCooldown = 3,
} GameConfig;
#endif
