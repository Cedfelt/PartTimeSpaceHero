//
//  Tank.cpp
//  PartTimeSpaceHero
//
//  Created by Anders Svensson on 31/10/16.
//
//

#include "Tank.hpp"


bool TankObject::init() {
  //////////////////////////////
  // 1. super init first
  if (!EnemyObject::init())
  {
    return false;
  }
  
  
  this->schedule(schedule_selector(TankObject::AIUpdate), 0.8);
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
  objectSprite->setPosition(12, 0);// Aling sprite in Hitbox
  objectSprite->setAnchorPoint(Point(0.5, 0));
  addChild(objectSprite);
  objectSprite->setScaleX(-1);
  return true;
}

void TankObject::colideWith(GameObject* oterhObj, const uint32_t otherType) {
  simpleWalkerHurt(oterhObj,otherType);
}

void TankObject::AIUpdate(const float delta) {
  genericWalkAi(delta);
}

void TankObject::deadState() {
  HP = 0;
  plingSFX->play(0.3f);
  setAnimation("tank_dead");
  this->bWallCollisions = false;
  setVelocityY(70);
  this->unschedule(schedule_selector(TankObject::AIUpdate));
  this->unschedule(schedule_selector(TankObject::update));
  removeWhenBelowZero();
  dropCoin(3);
}

bool TankObject::setupAnimation() {
  // SETUP ANIMATIONS
  
  SpriteFrameCache::getInstance()->addSpriteFramesWithFile("tank.plist");
  addAnimation("tank", "tank_idle", 1, 4, 0.18f);
  addAnimation("tank", "tank_dead", 1, 4, 0.07f);
  return true;
}
