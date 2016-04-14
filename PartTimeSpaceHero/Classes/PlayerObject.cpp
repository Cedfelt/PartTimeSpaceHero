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
    setSpeed(200.f);
    addChild(playerInput);
    this->schedule(schedule_selector(PlayerObject::playerUpdate));
    
    // SETUP ANIMATIONS
    spriteFrameCache = spriteFrameCache->getInstance();
    animationCache = animationCache->getInstance();
    spriteFrameCache->addSpriteFramesWithFile("PTSH_new_colors.plist");
    addAnimation("PTSHR", "IdleR", 1, 4, 0.2f);
    addAnimation("PTSHR", "IdleL", 1, 4, 0.2f);
    addAnimation("PTSHR", "WalkR", 5, 8, 0.15f);
    addAnimation("PTSHR", "WalkL", 5, 8, 0.15f);
    addAnimation("PTSHR", "flyR", 9, 12, 0.2f);
    addAnimation("PTSHR", "flyL", 9, 12, 0.2f);
    addAnimation("PTSHR", "fallR", 13, 16, 0.2f);
    addAnimation("PTSHR", "fallL", 13, 16, 0.2f);
    addAnimation("PTSHR", "dashR", 17, 20, 0.15f);
    addAnimation("PTSHR", "dashL", 17, 20, 0.15f);
    addAnimation("PTSHR", "dieR", 21, 24, 0.15f);
    addAnimation("PTSHR", "dieL", 21, 24, 0.15f);
    
    
    objectSprite = cocos2d::Sprite::create();
    objectSprite->runAction(RepeatForever::create(Animate::create(animationCache->getAnimation("WalkR"))));
    addChild(objectSprite);
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