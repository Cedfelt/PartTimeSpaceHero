//
//  UfoObject.cpp
//  PartTimeSpaceHero
//
//  Created by Anders Svensson on 29/05/16.
//
//

#include "BottyObject.hpp"
#include "BabyTurfelObject.hpp"
#include "CoinObject.hpp"


bool BottyObject::init() {
  //////////////////////////////
  // 1. super init first
  if (!EnemyObject::init())
  {
    return false;
  }

  
  this->schedule(schedule_selector(BottyObject::AIUpdate), 0.8);
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

void BottyObject::colideWith(GameObject* oterhObj, const uint32_t otherType) {
  simpleWalkerHurt(oterhObj,otherType);
}

void BottyObject::AIUpdate(const float delta) {
  genericWalkAi(delta);
}

void BottyObject::deadState() {
  HP = 0;
  plingSFX->play(0.3f);
  setAnimation("botty_dead");
  this->bWallCollisions = false;
  setVelocityY(70);
  this->unschedule(schedule_selector(BottyObject::AIUpdate));
  this->unschedule(schedule_selector(BottyObject::update));
  removeWhenBelowZero();
  dropCoin(3);
}

bool BottyObject::setupAnimation() {
  // SETUP ANIMATIONS
  
  spriteFrameCache = spriteFrameCache->getInstance();
  animationCache = animationCache->getInstance();
  spriteFrameCache->addSpriteFramesWithFile("botty.plist");
  addAnimation("Botty", "botty_idle", 1, 2, 0.2f);
  addAnimation("Botty", "botty_dead", 3, 3, 1.f);
  return true;
}
