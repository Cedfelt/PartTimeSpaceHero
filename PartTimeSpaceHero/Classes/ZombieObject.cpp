//
//  ZombieObject.cpp
//  PartTimeSpaceHero
//
//  Created by Anders Svensson on 19/07/16.
//
//

#include "ZombieObject.hpp"
#include "BabyTurfelObject.hpp"
#include "CoinObject.hpp"


bool ZombieObject::init() {
  //////////////////////////////
  // 1. super init first
  if (!EnemyObject::init())
  {
    return false;
  }
  setScale(2);
  
  this->schedule(schedule_selector(ZombieObject::AIUpdate), 0.8);
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

void ZombieObject::colideWith(GameObject* oterhObj, const uint32_t otherType) {
  simpleWalkerHurt(oterhObj,otherType);
}

void ZombieObject::AIUpdate(const float delta) {
  if(isPlayerInZone()){
    speed = 50;
    approachPlayer(delta);
  }
  else{
    speed = 25;
    stupidWalk(delta);
  }
  
}

void ZombieObject::deadState() {
  HP = 0;
  plingSFX->play(0.3f);
  setAnimation("zombie_dead");
  this->bWallCollisions = false;
  setVelocityY(70);
  this->unschedule(schedule_selector(ZombieObject::AIUpdate));
  this->unschedule(schedule_selector(ZombieObject::update));
  removeWhenBelowZero();
  dropCoin(3);
}

bool ZombieObject::setupAnimation() {
  // SETUP ANIMATIONS
  
  SpriteFrameCache::getInstance()->addSpriteFramesWithFile("zombie_and_snail.plist");
  addAnimation("zombie", "zombie_idle", 1, 1, 0.3f);
  addAnimation("zombie", "zombie_walk", 1, 8, 0.2f);
  addAnimation("zombie", "zombie_dead", 3, 3, 0.3f);
  return true;
}
