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
#include "Simple_Bullet.hpp"

bool RobotObject::init() {
  //////////////////////////////
  // 1. super init first
  if (!EnemyObject::init())
  {
    return false;
  }
  
  
  this->schedule(schedule_selector(RobotObject::AIUpdate), 0.4);
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
  
  if(AI_STATE_VAR == PATROL){
    genericWalkAi(delta);
    setAnimation("robot_idle");
    if(isPlayerInZone() && target->HP > 0){
      AI_STATE_VAR = AIM;
      AI_TIMER = 1.f;
      return;
    }
  }
  else if(AI_STATE_VAR == AIM){
    setVelocityX(0);
    setAnimation("robot_aim");
    faceTarget(delta);
    if(AI_TIMER>0){
      AI_TIMER-= delta;
      return;
    }
    else{
      AI_STATE_VAR = SHOOT;
      return;
    }
  }
  else if(AI_STATE_VAR == SHOOT){
    ShootXDir(delta);
    AI_STATE_VAR = AIM_DOWN;
    AI_TIMER = 1.f;
    return;
  }
  else if(AI_STATE_VAR == AIM_DOWN){
    if(AI_TIMER>0){
      AI_TIMER-= delta;
      return;
    }
    else{
      AI_STATE_VAR = PATROL;
      return;
    }
  }
  
}

void RobotObject::ShootXDir(const float delta) {
  auto babyTurf = SimpleBullet::create();
  float bullet_x_offset;
  babyTurf->setup(E_SIMPLE_BULLET);
  babyTurf->setupHitbox(0.1f, 1.0f, 16, 16, 16, 16, false);
  babyTurf->getPhysicsBody()->setCategoryBitmask((int)PhysicsCategory::Enemy);
  babyTurf->getPhysicsBody()->setCollisionBitmask((int)PhysicsCategory::None);
  babyTurf->getPhysicsBody()->setContactTestBitmask( (int)PhysicsCategory::Player | (int)PhysicsCategory::Hazard);
  addToGameObjects.pushBack(babyTurf);
  if(getPrevDir() == GO_RIGHT){
    babyTurf->setVelocityX(200);
    bullet_x_offset = 22;
  }
  else {
    babyTurf->setVelocityX(-200);
    bullet_x_offset = -16;
  }
  babyTurf->setObjectPositionX(getPositionX() + bullet_x_offset);
  babyTurf->setObjectPositionY(getPositionY() + 16);
  //weaponSFX->play(0.4f);
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
  addAnimation("robothunter", "robot_aim", 8, 8, 0.2f);
  return true;
}
