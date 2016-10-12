//
//  SnailObject.cpp
//  PartTimeSpaceHero
//
//  Created by Anders Svensson on 19/07/16.
//
//

#include "SnailObject.hpp"
#include "BabyTurfelObject.hpp"
#include "CoinObject.hpp"


bool SnailObject::init() {
  //////////////////////////////
  // 1. super init first
  if (!EnemyObject::init())
  {
    return false;
  }
  setScale(2);
  
  this->schedule(schedule_selector(SnailObject::AIUpdate), 0.8);
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

void SnailObject::colideWith(GameObject* oterhObj, const uint32_t otherType) {
  simpleWalkerHurt(oterhObj,otherType);
}

void SnailObject::AIUpdate(const float delta) {
  if(isPlayerInZone()){
      // HUNT PLAYER
      approachPlayer(delta);
      setAnimation("snail_crawl");
  }
  else{
    // GO BACK TO START
    const float homeDistance = getObjectPositionX() - objectZone.getMidX();
    if(fabsf(homeDistance)<32){
      setVelocityX(0);
      setAnimation("snail_idle");
    }
    else{
      if(homeDistance<0){
        walkAtDir(speed, GO_RIGHT);
      }
      else{
        walkAtDir(speed, GO_LEFT);
      }
    }
  }
}

void SnailObject::deadState() {
  HP = 0;
  plingSFX->play(0.3f);
  setAnimation("snail_dead");
  this->bWallCollisions = false;
  setVelocityY(70);
  this->unschedule(schedule_selector(SnailObject::AIUpdate));
  this->unschedule(schedule_selector(SnailObject::update));
  removeWhenBelowZero();
  dropCoin(3);
}

bool SnailObject::setupAnimation() {
  // SETUP ANIMATIONS
  
  SpriteFrameCache::getInstance()->addSpriteFramesWithFile("zombie_and_snail.plist");
  addAnimation("snail", "snail_idle", 1, 1, 0.3f);
  addAnimation("snail", "snail_crawl", 2, 4, 0.3f);
  addAnimation("snail", "snail_dead", 3, 3, 0.3f);
  return true;
}
