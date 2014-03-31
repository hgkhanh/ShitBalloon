//
//  SBContactListener.cpp
//  ShitBalloon
//
//  Created by Khanh Hoang Nguyen on 3/20/14.
//
//

#include "SBContactListener.h"
#include "cocos2d.h"

SBContactListener::SBContactListener() : _contacts(){

}

SBContactListener::~SBContactListener(){

}

void SBContactListener::BeginContact(b2Contact* aContact){
    // We need to copy out the data because the b2Contact passed in
    // is reused.
    SBContact sbContact = { aContact->GetFixtureA(), aContact->GetFixtureB() };
    _contacts.push_back(sbContact);
}

void SBContactListener::EndContact(b2Contact* aContact){
    SBContact sbContact = { aContact->GetFixtureA(), aContact->GetFixtureB() };
    std::vector<SBContact>::iterator pos;
    pos = std::find(_contacts.begin(), _contacts.end(), sbContact);
    if (pos != _contacts.end())
    {
        _contacts.erase(pos);
    }
}

void SBContactListener::PreSolve(b2Contact* contact, const b2Manifold* oldManifold) {

}

void SBContactListener::PostSolve(b2Contact* contact, const b2ContactImpulse* impulse) {

}
