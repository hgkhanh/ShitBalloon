//
//  SBContactListener.h
//  ShitBalloon
//
//  Created by Khanh Hoang Nguyen on 3/20/14.
//
//

#ifndef __ShitBalloon__SBContactListener__
#define __ShitBalloon__SBContactListener__

#include <iostream>
#include "Box2D.h"
#include <vector>

struct SBContact {
    b2Fixture *fixtureA;
    b2Fixture *fixtureB;
    bool operator==(const SBContact& other) const
    {
        return (fixtureA == other.fixtureA) && (fixtureB == other.fixtureB);
    }
};

class SBContactListener : public b2ContactListener {
public:
    std::vector<SBContact> _contacts;
    SBContactListener();
    ~SBContactListener();
    virtual void BeginContact(b2Contact* aContact);
    virtual void EndContact(b2Contact* aContact);
    virtual void PreSolve(b2Contact* contact, const b2Manifold* oldManifold);
    virtual void PostSolve(b2Contact* contact, const b2ContactImpulse* impulse);
};

#endif /* defined(__ShitBalloon__SBContactListener__) */
