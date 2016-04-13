//
//  Player.cpp
//  PartTimeSpaceHero
//
//  Created by Anders Svensson on 10/04/16.
//
//

#include "PlayerObject.hpp"

bool PlayerObject::init(){
    //////////////////////////////
    // 1. super init first
    if (!GameObject::init())
    {
        return false;
    }
    return true;
}

void PlayerObject::setupPlayer(const float x,const float y){
    setPosition(x, y);
}