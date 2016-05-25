//
//  Player.cpp
//  PartTimeSpaceHero
//
//  Created by Anders Svensson on 10/04/16.
//
//

#include "PlayerObject.hpp"

bool PlayerObject::init() {
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
  spriteFrameCache->addSpriteFramesWithFile("ptsh.plist");
  addAnimation("PTSH", "IdleR", 1, 4, 0.2f);
  addAnimation("PTSH", "IdleL", 1, 4, 0.2f);
  addAnimation("PTSH", "WalkR", 5, 8, 0.15f);
  addAnimation("PTSH", "WalkL", 5, 8, 0.15f);
  addAnimation("PTSH", "FlyR", 9, 12, 0.2f);
  addAnimation("PTSH", "FlyL", 9, 12, 0.2f);
  addAnimation("PTSH", "AscendR", 13, 13, 0.2f);
  addAnimation("PTSH", "AscendL", 13, 13, 0.2f);
  addAnimation("PTSH", "FallR", 14, 17, 0.2f);
  addAnimation("PTSH", "FallL", 14, 17, 0.2f);
  addAnimation("PTSH", "DashR", 18, 21, 0.15f);
  addAnimation("PTSH", "DashL", 18, 21, 0.15f);
  addAnimation("PTSH", "DieR", 22, 25, 0.15f);
  addAnimation("PTSH", "DieL", 22, 25, 0.15f);


  objectSprite = cocos2d::Sprite::create();
  objectSprite->setAnchorPoint(Point(0.5, 0));
  objectSprite->setPosition(8, -16);// Aling sprite in Hitbox
  setAnimation("WalkR");
  addChild(objectSprite);
  
  // soundfx
  jetpack1 = SoundFx::create();
  jetpack1->loadEffect("jet_pack_hum.aif", 0, 1, true);
  addChild(jetpack1);

  fuel = 1.0f;
  consumeRate = 0.01;

  return true;
}


const float ground_deacceleration = 0.85;
const float ground_acceleration = 5;
void PlayerObject::playerWalkUpdate(float delta) {
  if (getMovementStatus() != GO_ON_GROUND) {
    return;
  }
  if (playerInput->isLeft()) {
    objectSprite->setScaleX(-1);
    setAnimation("WalkL");
    addToVelocityX(-ground_acceleration);
    if (getVelocityX() < -getSpeed()) {
      setVelocityX(-getSpeed());
    }

  }
  else if (playerInput->isRight()) {
    objectSprite->setScaleX(1);
    setAnimation("WalkR");
    addToVelocityX(ground_acceleration);
    if (getVelocityX() > getSpeed()) {
      setVelocityX(getSpeed());
    }
  }
  else {
    setVelocityX(getVelocityX()*ground_deacceleration);

    if (getPrevDir() == GO_RIGHT) {
      objectSprite->setScaleX(1);
      setAnimation("IdleR");
    }
    else {
      objectSprite->setScaleX(-1);
      setAnimation("IdleL");
    }

  }
}

void PlayerObject::playerFallUpdate(float delta) {
  if (getMovementStatus() == GO_IN_AIR_DOWN) {
    const float playerFallSpeed = 0.1f;
    if (playerInput->isLeft()) {
      objectSprite->setScaleX(-1);
      setAnimation("FallL");
      addToVelocityX(-playerFallSpeed);

    }
    else if (playerInput->isRight()) {
      objectSprite->setScaleX(1);
      setAnimation("FallR");
      addToVelocityX(playerFallSpeed);
    }
    else {
      if (getPrevDir() == GO_RIGHT) {
        objectSprite->setScaleX(1);
        setAnimation("FallR");
      }
      else {
        objectSprite->setScaleX(-1);
        setAnimation("FallL");
      }
    }
  }
}

float PlayerObject::getFuel() {
  return fuel;
}

bool PlayerObject::playerFlyUpdate(float delta) {
  const float jetPackFlySpeed = 1.5f;
  const float maxSpeed = getSpeed();
  const float uppSpeed = 0.9f;
  const float maxRiseSpeed = 80;
  float upp_threshold;
  int throtling = 0;
  bool module_active = false;
  if (flying) {
    upp_threshold = 0.0f;
    consumeRate = -0.01f;
  }
  else {
    upp_threshold = 2.1f;
    consumeRate = 0.00f;;
  }
  const float movement_status = getMovementStatus();
  if (playerInput->isRight()) {
    if (playerInput->getSwipeR() > upp_threshold &&fuel>0) {
      consumeRate = -0.01f;
      throtling++;
      module_active = true;
      if (movement_status == GO_ON_GROUND && !flying) {
        addToVelocityY(jumpStength);
        flying = true;
      }
      if (getVelocityY() < maxRiseSpeed)
        addToVelocityY(playerInput->getSwipeR()*uppSpeed);
      objectSprite->setScaleX(1);
      setAnimation("FlyR");
      if (getVelocityX() < maxSpeed) {
        addToVelocityX(jetPackFlySpeed);
      }
      module_active = true;
    }
    else {
      if (movement_status == GO_ON_GROUND){
        flying = false;
        consumeRate = 0.01;
      }
      
    }
  }
  if (playerInput->isLeft()) {
    if (playerInput->getSwipeL() > upp_threshold &&fuel>0) {
      throtling++;
      consumeRate = -0.01f;
      if (movement_status == GO_ON_GROUND && !flying) {
        addToVelocityY(jumpStength);
        flying = true;
      }
      if (getVelocityY() < maxRiseSpeed)
        addToVelocityY(playerInput->getSwipeL()*uppSpeed);
      objectSprite->setScaleX(-1);
      setAnimation("FlyL");
      if (getVelocityX() > -maxSpeed) {
        addToVelocityX(-jetPackFlySpeed);
      }
      module_active = true;
    }
    else {

    }
  }
  if (movement_status == GO_ON_GROUND){
    flying = false;
    consumeRate = 0.01;
  }
  if(throtling){
    jetpack1->play(0.2f);
  }
  else{
    jetpack1->stop();
    if(getVelocityY()>0)
    setAnimation("AscendR");
    
  }
  fuel += consumeRate;
  if (fuel > 1) {
    fuel = 1;
  }
  if (fuel < 0) {
    fuel = 0;
  }
  return module_active;
}
bool dashingRight = false;
bool dashingLeft = false;
float dashLeftCnt = 0;
float dashRightCnt = 0;
float dashSpeed = 300;
const float dashTime = 2.0f;
int dash_stage = 0;
bool PlayerObject::playerDashUpdate(float delta) {
  if (playerInput->isDoubleRight() && !dashingRight) {
    objectSprite->setScaleX(1);
    dashRightCnt = dashTime;
    dashLeftCnt = 0;
    jetpack1->play(0.2,1.7f);
  }
  if (playerInput->isDoubleLeft() && !dashingLeft) {
    objectSprite->setScaleX(-1);
    dashLeftCnt = dashTime;
    dashRightCnt = 0;
    jetpack1->play(0.2,1.7f);
  }
  if (dashRightCnt > 0) {

    setVelocityY(0);
    if (dashRightCnt > 0.5*dashTime) {
      setVelocityX(0);
      setAnimation("DashR");
    }
    else {
      dash_stage++;
      jetpack1->play(0.4,0.7f);
      setVelocityX(dashSpeed);
      setAnimation("DieR");
    }
    if(dash_stage== 1){
      jetpack1->stop();
    }
    dashRightCnt -= delta;
    return true;
  }
  if (dashLeftCnt > 0) {
    setVelocityY(0);
    if (dashLeftCnt > 0.5*dashTime) {
      setVelocityX(0);
      setAnimation("DashL");
    }
    else {
      dash_stage++;
      setVelocityX(-dashSpeed);
      setAnimation("DieL");
      jetpack1->play(0.4,0.7f);
    }
    if(dash_stage== 1){
      jetpack1->stop();
    }
    dashLeftCnt -= delta;
    return true;
  }
  if(dash_stage > 0){
    jetpack1->stop();
  }
  dash_stage = 0;
  return false;
}

void PlayerObject::playerUpdate(const float delta) {


  // Update priority
  if (playerDashUpdate(delta)) {
    return;
  }
  if(!playerFlyUpdate(delta)){
    playerFallUpdate(delta);
    playerWalkUpdate(delta);
  }
  
  if (std::abs(this->getVelocityX()) > getSpeed()) {
    setVelocityX(getVelocityX()*0.99f);
  }

  if (playerInput->isLeft()) {
    setPrevDir(GO_LEFT);
  }
  else if (playerInput->isRight()) {
    setPrevDir(GO_RIGHT);
  }
  auto pb = this->getPhysicsBody();
}

void PlayerObject::colideWith(GameObject* otherObj){
  otherObj->interActWithPlayer(this);
}

void PlayerObject::setupPlayer(const float x, const float y) {
  setObjectPositionX(x);
  setObjectPositionY(y);
}