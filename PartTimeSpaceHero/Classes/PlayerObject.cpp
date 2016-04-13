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
    playerInput = PlayerInput::create();
    setSpeed(100.f);
    addChild(playerInput);
    this->schedule(schedule_selector(PlayerObject::playerUpdate));
    return true;
}

void PlayerObject::playerUpdate(const float delta) {
  if (playerInput->isLeft()) {
    setVelocityX(-getSpeed());
  }
  else if (playerInput->isRight()) {
    setVelocityX(getSpeed());
  }
  setPositionX(getPositionX() +getVelocityX()*delta);
}

void PlayerObject::setupPlayer(const float x,const float y){
    setPosition(x, y);
}