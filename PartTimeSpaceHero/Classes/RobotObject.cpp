//
//  RobotObject.cpp
//  PartTimeSpaceHero
//
//  Created by Anders Svensson on 22/12/16.
//
//

#include "RobotObject.hpp"
#include "BabyTurfelObject.hpp"
#include "CoinObject.hpp"


bool RobotObject::init() {
  //////////////////////////////
  // 1. super init first
  if (!EnemyObject::init())
  {
    return false;
  }
  
  
  this->schedule(schedule_selector(RobotObject::AIUpdate), 0.8);
  addGravityToObject(true);
  setElastic(0.f);
  plingSFX = SoundFx::create();
  plingSFX->loadEffect("small_explosion.aif", 0, 1, false);
  addChild(plingSFX);
  dmg = 1;
  
  // Start Speed
  setVelocityX(-speed);
  setPrevDir(GO_LEFT);
  setupAnimation();
  objectSprite = cocos2d::Sprite::create();
  setAnimation("robot_idle");
  objectSprite->setPosition(12, 0);// Aling sprite in Hitbox
  objectSprite->setAnchorPoint(Point(0.5, 0));
  addChild(objectSprite);
  objectSprite->setScaleX(-1);
  //objectSprite->setScaleY(2);

  return true;
}

void RobotObject::colideWith(GameObject* oterhObj, const uint32_t otherType) {
  simpleWalkerHurt(oterhObj,otherType);
}

void RobotObject::AIUpdate(const float delta) {
  genericWalkAi(delta);
}

void RobotObject::deadState() {
  HP = 0;
  plingSFX->play(0.3f);
  setAnimation("robot_dead");
  this->bWallCollisions = false;
  setVelocityY(70);
  this->unschedule(schedule_selector(RobotObject::AIUpdate));
  this->unschedule(schedule_selector(RobotObject::update));
  removeWhenBelowZero();
  dropCoin(3);
}

bool RobotObject::setupAnimation() {
  // SETUP ANIMATIONS
  
  SpriteFrameCache::getInstance()->addSpriteFramesWithFile("robothunter.plist");
  addAnimation("robothunter", "robot_idle", 1, 4, 0.2f);
  addAnimation("robothunter", "robot_dead", 5, 7, 0.2f);
  return true;
}
