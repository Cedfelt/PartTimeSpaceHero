//
//  Player.cpp
//  PartTimeSpaceHero
//
//  Created by Anders Svensson on 10/04/16.
//
//

#include "FlowerShootaObject.hpp"
#include "BabyTurfelObject.hpp"

bool FlowerShootaObject::init() {
  //////////////////////////////
  // 1. super init first
  if (!EnemyObject::init())
  {
    return false;
  }


  //addGravityToObject(false);
  setElastic(0.f);
  addGravityToObject(true);
  // SETUP ANIMATIONS
  objectSprite = cocos2d::Sprite::create();
  SpriteFrameCache::getInstance()->addSpriteFramesWithFile("flower_shoota.plist");
  addAnimation("flowe_shoota", "flower_shoot", 1, 7, 0.2f);
  addAnimation("flowe_shoota", "flower_idle", 1, 2, 0.2f);
  setAnimation("flower_idle");
  objectSprite->setPosition(32 / 2, 32 / 2);// Aling sprite in Hitbox
  addChild(objectSprite);
  const float xVel = cocos2d::random(0, 0);
  setVelocityX(0);
  shoot_timer = 0.2 * 6;
  return true;
}

void FlowerShootaObject::colideWith(GameObject* oterhObj, const uint32_t otherType) {
  simpleWalkerHurt(oterhObj,otherType);
}

const float yForce = 250;
const float rangeX = 200;
const float rangeY = -3;
void FlowerShootaObject::update(const float delta) {
  const float distanceX = target->getObjectPositionX() - getObjectPositionX();
  const float distanceY = target->getObjectPositionY() - getObjectPositionY();
  if (std::abs(distanceX) < rangeX && distanceY > rangeY) {
    setAnimation("flower_shoot");
    if (shoot_timer <= 0) {
      auto babyTurf = BabyTurfelObject::create();
      babyTurf->setupHitbox(0.1f, 1.0f, 16, 16, 16, 16, false);
      babyTurf->setObjectPositionX(getPositionX() + 12);
      babyTurf->setObjectPositionY(getPositionY() + 12);
      babyTurf->getPhysicsBody()->setCategoryBitmask((int)PhysicsCategory::Enemy);
      babyTurf->getPhysicsBody()->setCollisionBitmask((int)PhysicsCategory::None);
      babyTurf->getPhysicsBody()->setContactTestBitmask((int)PhysicsCategory::Player | (int)PhysicsCategory::PlayerPickups | (int)PhysicsCategory::Hazard);
      babyTurf->setVelocityX(distanceX/2 + cocos2d::random(-5, 5));
      babyTurf->setVelocityY(yForce);
      babyTurf->setGlobalZOrder(E_Z_LEVEL_ONE_BEHIND_PLAYER);
      addToGameObjects.pushBack(babyTurf);
      shoot_timer = 7 * 0.2;
    }
    shoot_timer -= delta;
  }
  else {
    setAnimation("flower_idle");
    shoot_timer = 6 * 0.2;
  }

}

bool FlowerShootaObject::setupAnimation() {
  return true;
}
