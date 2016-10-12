//
//  UfoObject.cpp
//  PartTimeSpaceHero
//
//  Created by Anders Svensson on 29/05/16.
//
//

#include "UfoObject.hpp"
#include "BabyTurfelObject.hpp"

bool UfoObject::init() {
  //////////////////////////////
  // 1. super init first
  if (!GameObject::init())
  {
    return false;
  }
  
  
  this->schedule(schedule_selector(UfoObject::AIUpdate),1.2);
  addGravityToObject(false);
  setElastic(1.f);
  // SETUP ANIMATIONS
  objectSprite = cocos2d::Sprite::create();
  SpriteFrameCache::getInstance()->addSpriteFramesWithFile("patrol_ufo.plist");
  addAnimation("patrol_ufo ", "ufo_idle", 1, 2, 0.2f);
  setAnimation("ufo_idle");
  objectSprite->setPosition(32, 32);// Aling sprite in Hitbox
  objectSprite->setScale(2);
  addChild(objectSprite);
  
  // Start Speed
  const float xVel = -50;
  setVelocityX(xVel);
  
  plingSFX = SoundFx::create();
  plingSFX->loadEffect("small_explosion.aif", 0, 1, false);
  addChild(plingSFX);
  
  return true;
}

void UfoObject::colideWith(GameObject* oterhObj,const uint32_t otherType){
  simpleWalkerHurt(oterhObj, otherType);
}

const float xAttackDistance = 300;
const float yAttackDistance = 500;
const float throwSpeedY = 180;
const float throwSpeedX = 60.f;

void UfoObject::AIUpdate(const float delta) {
  
  
  if((std::abs(target->getPositionX() - getPositionX() )< xAttackDistance)){
    const float yDist = getPositionY() - target->getPositionY();
    if(yDist<yAttackDistance && yDist > -100 && HP>0){
      auto babyTurf = BabyTurfelObject::create();
      babyTurf->setupHitbox(0.1f, 1.0f, 16, 16, 16, 16, false);
      babyTurf->setObjectPositionX(getPositionX() + objectSprite->getTexture()->getPixelsWide()/2);
      babyTurf->setObjectPositionY(getPositionY() + objectSprite->getTexture()->getPixelsWide());
      babyTurf->getPhysicsBody()->setCategoryBitmask((int)PhysicsCategory::Enemy);
      babyTurf->getPhysicsBody()->setCollisionBitmask((int)PhysicsCategory::None);
      babyTurf->getPhysicsBody()->setContactTestBitmask((int)PhysicsCategory::Player|(int)PhysicsCategory::Hazard);
      const float xPow = (float)100.0f/cocos2d::random(1000, 2000) + (target->getPositionX() - getPositionX())/xAttackDistance;
      babyTurf->setVelocityX(xPow * throwSpeedX);
      babyTurf->setVelocityY(throwSpeedY);
      addToGameObjects.pushBack(babyTurf);
    }
  }
}

void UfoObject::deadState(){
  HP = 0;
  plingSFX->play(0.3f);
  addGravityToObject(true);
  this->bWallCollisions = false;
  setVelocityY(70);
  this->unschedule(schedule_selector(UfoObject::AIUpdate));
  this->unschedule(schedule_selector(UfoObject::update));
  removeWhenBelowZero();
  setVelocityX(getVelocityX()*0.1);
  setVelocityY(getVelocityY()*0.1);
  objectSprite->setRotation(25);
  dropCoin(3);
}

bool UfoObject::setupAnimation() {
  return true;
}
