//
//  Player.cpp
//  PartTimeSpaceHero
//
//  Created by Anders Svensson on 10/04/16.
//
//

#include "EnemyObject.hpp"

bool EnemyObject::init() {
  //////////////////////////////
  // 1. super init first
  if (!GameObject::init())
  {
    return false;
  }
  fSimpleHurtForce = 170;
}

void EnemyObject::stupidWalk(const float delta) {
  if (getVelocityX() == 0) {
    if (getPrevDir() == GO_LEFT) {
      setVelocityX(50);
      setPrevDir(GO_RIGHT);
      objectSprite->setScaleX(1);
    }
    else {
      setVelocityX(-50);
      setPrevDir(GO_LEFT);
      objectSprite->setScaleX(-1);
    }
  }
}

void EnemyObject::turnAtEdge(const float delta) {

  const float lookAhead = 0.5f*getVelocityX() / delta;
  if (!isBlocked((uint32_t)((getPositionX() + lookAhead - 24) / 16.0), (uint32_t)(getPositionY() - 64.0) / 16.0)) {
    if (getPrevDir() == GO_LEFT) {
      setVelocityX(50);
      setPrevDir(GO_RIGHT);
      objectSprite->setScaleX(1);
    }
    else {
      setVelocityX(-50);
      setPrevDir(GO_LEFT);
      objectSprite->setScaleX(-1);
    }
  }
}

void EnemyObject::simpleWalkerHurt(GameObject* pPlayer, const uint32_t otherType) {
  if (otherType&(uint32_t)PhysicsCategory::Player) {
    auto player = pPlayer->getHitbox();
    auto rThis = getHitbox();
    if (rThis->getMidY() > player->getMinY()) {
      pPlayer->hurt(1, Vec2(getVelocityX(), fSimpleHurtForce));
    }
  }
}