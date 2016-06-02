//
//  UfoObject.cpp
//  PartTimeSpaceHero
//
//  Created by Anders Svensson on 29/05/16.
//
//

#include "BottyObject.hpp"
#include "BabyTurfelObject.hpp"

bool BottyObject::init() {
  //////////////////////////////
  // 1. super init first
  if (!GameObject::init())
  {
    return false;
  }
  
  
  this->schedule(schedule_selector(BottyObject::AIUpdate),1.2);
  addGravityToObject(true);
  setElastic(0.f);
  // SETUP ANIMATIONS
  objectSprite = cocos2d::Sprite::create();
  spriteFrameCache = spriteFrameCache->getInstance();
  animationCache = animationCache->getInstance();
  spriteFrameCache->addSpriteFramesWithFile("botty.plist");
  addAnimation("Botty", "botty_idle", 1, 2, 0.2f);
  setAnimation("botty_idle");
  objectSprite->setPosition(12, 0);// Aling sprite in Hitbox
  objectSprite->setAnchorPoint(Point(0.5, 0));
  objectSprite->setScale(1);
  addChild(objectSprite);
  
  // Start Speed
  const float xVel = -50;
  setVelocityX(xVel);
  setPrevDir(GO_LEFT);
  objectSprite->setScaleX(-1);
  return true;
}

const float forceX = 100;
const float forceY = 100;
void BottyObject::interActWithPlayer(GameObject* player){
  if(getPrevDir() == GO_RIGHT){
    setVelocityX(50);
    player->hurt(0, Vec2(forceX,forceY));
  }
  else{
    setVelocityX(-50);
    player->hurt(0, Vec2(-forceX,forceY));
  }
  
}

//const float xAttackDistance = 300;
//const float yAttackDistance = 500;
//const float throwSpeedY = 180;
//const float throwSpeedX = 60.f;

void BottyObject::AIUpdate(const float delta) {
  if(getVelocityX()== 0){
    if(getPrevDir() == GO_LEFT){
      setVelocityX(50);
      setPrevDir(GO_RIGHT);
      objectSprite->setScaleX(1);
    }
    else{
      setVelocityX(-50);
      setPrevDir(GO_LEFT);
      objectSprite->setScaleX(-1);
    }
  }
}