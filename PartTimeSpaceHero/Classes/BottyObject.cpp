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
  // SETUP ANIMATIONS
  objectSprite = cocos2d::Sprite::create();
  spriteFrameCache = spriteFrameCache->getInstance();
  animationCache = animationCache->getInstance();
  spriteFrameCache->addSpriteFramesWithFile("botty.plist");
  addAnimation("Botty", "botty_idle", 1, 2, 0.2f);
  addAnimation("Botty", "botty_dead", 3, 3, 1.f);
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

void BottyObject::colideWith(GameObject* oterhObj, const uint32_t otherType) {
  simpleWalkerHurt(oterhObj,otherType);
}

void BottyObject::AIUpdate(const float delta) {
  
  stupidWalk(delta);
  turnAtEdge(delta);
}

void BottyObject::deadState() {
  HP = 0;
  setAnimation("botty_dead");
  this->bWallCollisions = false;
  setVelocityY(70);
  this->unschedule(schedule_selector(BottyObject::AIUpdate));
  this->unschedule(schedule_selector(BottyObject::update));
  removeWhenBelowZero();
  dropCoin(3);
}

