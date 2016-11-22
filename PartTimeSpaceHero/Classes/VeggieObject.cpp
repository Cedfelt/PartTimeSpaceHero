//
//  VeggieObject.cpp
//  PartTimeSpaceHero
//
//  Created by Anders Svensson on 01/11/16.
//
//

#include "VeggieObject.hpp"


bool VeggieObject::init() {
  //////////////////////////////
  // 1. super init first
  if (!EnemyObject::init())
  {
    return false;
  }
  
  //setScale(3.0);
  this->schedule(schedule_selector(VeggieObject::AIUpdate), 0.8);
  addGravityToObject(true);
  setElastic(0.f);
  plingSFX = SoundFx::create();
  plingSFX->loadEffect("small_explosion.aif", 0, 1, false);
  addChild(plingSFX);
  dmg = 1;
  
  // Start Speed
  setVelocityX(-speed);
  setPrevDir(GO_LEFT);
  objectSprite = cocos2d::Sprite::create();
  objectSprite->setPosition(28, 0);// Aling sprite in Hitbox
  objectSprite->setAnchorPoint(Point(0.5, 0));
  addChild(objectSprite);
  objectSprite->setScaleX(-1);
  return true;
}

void VeggieObject::colideWith(GameObject* oterhObj, const uint32_t otherType) {
  simpleWalkerHurt(oterhObj,otherType);
}

void VeggieObject::AIUpdate(const float delta) {
  if(getVelocityY()<0){
    setAnimation("veggie_dead");
  }
  else{
    setAnimation("veggie_idle");
  }
  genericWalkAi(delta);
}

void VeggieObject::deadState() {
  HP = 0;
  plingSFX->play(0.3f);
  setAnimation("veggie_dead");
  this->bWallCollisions = false;
  setVelocityY(70);
  this->unschedule(schedule_selector(VeggieObject::AIUpdate));
  this->unschedule(schedule_selector(VeggieObject::update));
  removeWhenBelowZero();
  dropCoin(3);
}

bool VeggieObject::setupAnimation() {
  // SETUP ANIMATIONS
  
  SpriteFrameCache::getInstance()->addSpriteFramesWithFile("veggie.plist");
  addAnimation("veggie", "veggie_idle", 3, 6, 0.2f);
  addAnimation("veggie", "veggie_dead", 1, 2, 0.18f);
  return true;
}
