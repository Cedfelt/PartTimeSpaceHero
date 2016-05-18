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


void PlayerObject::playerFlyUpdate(float delta){
  const float jetPackFlySpeed = 1.5f;
  const float maxSpeed = getSpeed();
  const float uppSpeed = 0.9f;
  const float maxRiseSpeed = 80;
  float upp_threshold;
  if(flying){
    upp_threshold = 0.1f;
  }
  else{
    upp_threshold = 2.1f;
  }
  const float movement_status = getMovementStatus();
  if(playerInput->isRight()){
    if(playerInput->getSwipeR()>upp_threshold){
      if(movement_status == GO_ON_GROUND && !flying){
        addToVelocityY(jumpStength);
        flying = true;
      }
      if(getVelocityY() < maxRiseSpeed)
        addToVelocityY(playerInput->getSwipeR()*uppSpeed);
      objectSprite->setScaleX(1);
      setAnimation("FlyR");
      if(getVelocityX()< maxSpeed){
        addToVelocityX(jetPackFlySpeed);
      }
      return;
    }
    else{
      if(movement_status == GO_ON_GROUND)
        flying = false;
    }
  }
  if(playerInput->isLeft()){
    if(playerInput->getSwipeL()>upp_threshold){
      if(movement_status == GO_ON_GROUND && !flying){
        addToVelocityY(jumpStength);
        flying = true;
      }
      if(getVelocityY() < maxRiseSpeed)
        addToVelocityY(playerInput->getSwipeL()*uppSpeed);
      objectSprite->setScaleX(-1);
      setAnimation("FlyL");
      if(getVelocityX()> -maxSpeed){
        addToVelocityX(-jetPackFlySpeed);
      }
      return;
    }
    else{
      
    }
  }
  if(movement_status == GO_ON_GROUND)
    flying = false;
}
bool dashingRight = false;
bool dashingLeft = false;
float dashLeftCnt = 0;
float dashRightCnt = 0;
float dashSpeed = 300;
const float dashTime = 2.0f;
bool PlayerObject::playerDashUpdate(float delta){
  if(playerInput->isDoubleRight() &&!dashingRight){
    objectSprite->setScaleX(1);
    dashRightCnt = dashTime;
    dashLeftCnt = 0;
  }
  if(playerInput->isDoubleLeft() && !dashingLeft){
    objectSprite->setScaleX(-1);
    dashLeftCnt = dashTime;
    dashRightCnt = 0;
  }
  if(dashRightCnt > 0){
    
    setVelocityY(0);
    if(dashRightCnt > 0.5*dashTime){
      setVelocityX(0);
      setAnimation("DashR");
    }
    else{
      setVelocityX(dashSpeed);
      setAnimation("DieR");
    }
    dashRightCnt -=delta;
    return true;
  }
  if(dashLeftCnt > 0){
    setVelocityY(0);
    if(dashLeftCnt > 0.5*dashTime){
      setVelocityX(0);
      setAnimation("DashL");
    }
    else{
      setVelocityX(-dashSpeed);
      setAnimation("DieL");
    }
    dashLeftCnt -=delta;
    return true;
  }
  return false;
}

void PlayerObject::playerUpdate(const float delta) {
  
  
  // Update priority
  if(playerDashUpdate(delta)){
    return;
  }
  playerFallUpdate(delta);
  playerFlyUpdate(delta);
  playerWalkUpdate(delta);
  if(std::abs(this->getVelocityX()) > getSpeed()){
    setVelocityX(getVelocityX()*0.98f);
  }
  
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