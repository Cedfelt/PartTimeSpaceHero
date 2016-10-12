//
//  MechObject.cpp
//  PartTimeSpaceHero
//
//  Created by Anders Svensson on 06/07/16.
//
//

#include "MechObject.hpp"
#include "CoinObject.hpp"


bool MechObject::init() {
  //////////////////////////////
  // 1. super init first
  if (!EnemyObject::init())
  {
    return false;
  }
  
  
  this->schedule(schedule_selector(MechObject::AIUpdate), 0.350);
  addGravityToObject(true);
  setElastic(0.f);
  plingSFX = SoundFx::create();
  plingSFX->loadEffect("small_explosion.aif", 0, 1, false);
  setScale(2);
  addChild(plingSFX);
  dmg = 1;
  speed = 25;
  // Start Speed
  setVelocityX(-speed);
  setPrevDir(GO_LEFT);
  objectSprite = cocos2d::Sprite::create();
  objectSprite->setPosition(12, 0);// Aling sprite in Hitbox
  objectSprite->setAnchorPoint(Point(0.5, 0));
  addChild(objectSprite);
  objectSprite->setScaleX(-1);
  return true;
}

void MechObject::colideWith(GameObject* oterhObj, const uint32_t otherType) {
  simpleWalkerHurt(oterhObj,otherType);
}


void MechObject::AIUpdate(const float delta) {
  if(test){
    setSpeed(45);
    test = false;
    
  }
  else{
    setSpeed(0.001);
    test = true;
  }
  if(getMovementStatus() == GO_RIGHT){
    goMovementStatus = GO_RIGHT;
    setVelocityX(speed);
  }
  else{
    goMovementStatus = GO_RIGHT;
    setVelocityX(-speed);
  }
}

void MechObject::deadState() {
  HP = 0;
  plingSFX->play(0.3f);
  setAnimation("mech_dead");
  this->bWallCollisions = false;
  setVelocityY(70);
  this->unschedule(schedule_selector(MechObject::AIUpdate));
  this->unschedule(schedule_selector(MechObject::update));
  removeWhenBelowZero();
  dropCoin(3);
}

bool MechObject::setupAnimation() {
  // SETUP ANIMATIONS
  
  SpriteFrameCache::getInstance()->addSpriteFramesWithFile("e_mech.plist");
  addAnimation("mech", "mech_idle", 1, 4, 0.350f);
  addAnimation("mech", "mech_dead", 1, 1, 1.f);
  return true;
}
