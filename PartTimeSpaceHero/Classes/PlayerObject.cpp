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
    setSpeed(150.f);
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
    addAnimation("PTSHR", "FlyR", 9, 12, 0.2f);
    addAnimation("PTSHR", "FlyL", 9, 12, 0.2f);
    addAnimation("PTSHR", "FallR", 13, 16, 0.2f);
    addAnimation("PTSHR", "FallL", 13, 16, 0.2f);
    addAnimation("PTSHR", "DashR", 17, 20, 0.15f);
    addAnimation("PTSHR", "DashL", 17, 20, 0.15f);
    addAnimation("PTSHR", "DieR", 21, 24, 0.15f);
    addAnimation("PTSHR", "DieL", 21, 24, 0.15f);
    
    
    objectSprite = cocos2d::Sprite::create();
  objectSprite->setAnchorPoint(Point(0.5,0));
  objectSprite->setPosition(8,-1);// Aling sprite in Hitbox
  setAnimation("WalkR");
    addChild(objectSprite);
    return true;
}


const float ground_deacceleration = 0.75;
const float ground_acceleration = 5;
void PlayerObject::playerWalkUpdate(float delta){
  if(getMovementStatus()!=GO_ON_GROUND){
    return;
  }
  
  if (playerInput->isLeft()) {
    objectSprite->setScaleX(-1);
    setAnimation("WalkL");
    addToVelocityX(-ground_acceleration);
    if(getVelocityX()<-getSpeed()){
      setVelocityX(-getSpeed());
    }
    
  }
  else if (playerInput->isRight()) {
    objectSprite->setScaleX(1);
    setAnimation("WalkR");
    addToVelocityX(ground_acceleration);
    if(getVelocityX()>getSpeed()){
      setVelocityX(getSpeed());
    }
  }
  else{
    setVelocityX(getVelocityX()*ground_deacceleration);
    
    if(getPrevDir()==GO_RIGHT){
      objectSprite->setScaleX(1);
      setAnimation("IdleR");
    }
    else{
      objectSprite->setScaleX(-1);
      setAnimation("IdleL");
    }
    
  }
}

void PlayerObject::playerFallUpdate(float delta){
  if(getMovementStatus() == GO_IN_AIR_DOWN){
    const float playerFallSpeed = 0.1f;
    if(playerInput->isLeft()){
      objectSprite->setScaleX(-1);
      setAnimation("FallL");
      addToVelocityX(-playerFallSpeed);
      
    }
    else if(playerInput->isRight()){
      objectSprite->setScaleX(1);
      setAnimation("FallR");
      addToVelocityX(playerFallSpeed);
    }
    else{
      if(getPrevDir()==GO_RIGHT){
        objectSprite->setScaleX(1);
        setAnimation("FallR");
      }
      else{
        objectSprite->setScaleX(-1);
        setAnimation("FallL");
      }
    }
  }
}

const float jumpStength = 60;
void PlayerObject::playerFlyUpdate(float delta){
  const float jetPackFlySpeed = 1.5f;
  const float maxSpeed = getSpeed();
  const float uppSpeed = 0.75f;
  const float upp_threshold = 2.1f;
  if(playerInput->getSwipeR()>upp_threshold){
    if(getMovementStatus() == GO_ON_GROUND){
      addToVelocityY(jumpStength);
    }
    addToVelocityY(playerInput->getSwipeR()*uppSpeed);
    objectSprite->setScaleX(1);
    setAnimation("FlyR");
    addToVelocityX(jetPackFlySpeed);
    if(getVelocityX()>maxSpeed){
      setVelocityX(maxSpeed);
    }
    return;
  }
  if(playerInput->getSwipeL()>upp_threshold){
    if(getMovementStatus() == GO_ON_GROUND){
      addToVelocityY(jumpStength);
    }
    addToVelocityY(playerInput->getSwipeL()*uppSpeed);
    objectSprite->setScaleX(-1);
    setAnimation("FlyL");
    addToVelocityX(-jetPackFlySpeed);
    if(getVelocityX()< -maxSpeed){
      setVelocityX(-maxSpeed);
    }
    return;
  }
}
void PlayerObject::playerDashUpdate(float delta){
  
}

void PlayerObject::playerUpdate(const float delta) {
  // Update priority
  playerDashUpdate(delta);
  playerFallUpdate(delta);
  playerFlyUpdate(delta);
  playerWalkUpdate(delta);
  
  
  if(playerInput->isLeft()){
    setPrevDir(GO_LEFT);
  }
  else if(playerInput->isRight()){
    setPrevDir(GO_RIGHT);
  }
  
}

void PlayerObject::setupPlayer(const float x,const float y){
  setObjectPositionX(x);
  setObjectPositionY(y);
}