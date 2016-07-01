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
  bStayInZone = false;
  bStupidWalk = false;
  bTurnAtEdges = false;

}

// AI - BEHAVIOURS

void EnemyObject::genericAi(const float delta) {
  if (bStupidWalk) {
    stupidWalk(delta);
  }
  if (bStayInZone) {
    //stayInZone(delta);
  }
  if (bTurnAtEdges) {
    turnAtEdge(delta);
  }
}

//A stupid Walk algorithm. Change Direction When The Objects X-velocity is == 0
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

/*** Add this function to the objects update function to make it turn at edges. This Algorithm was not designed For slopes.
If the objects path includes slopes use a predefined zone instead***/
void EnemyObject::turnAtEdge(const float delta) {

  const float lookAhead = 0.5f*getVelocityX() / delta;
  auto const hitbox = getHitbox();
  if (!isBlocked((uint32_t)((hitbox->getMidX() + lookAhead - 24) / 16.0), (uint32_t)(hitbox->getMinY() - 1) / 16.0)) {
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

/*** This should be called when Objects colided. If 1/2 of the object height is > the other objects minY
it will hurt the other object with damage dmg.***/
void EnemyObject::simpleWalkerHurt(GameObject* pPlayer, const uint32_t otherType) {
    auto player = pPlayer->getHitbox();
    auto rThis = getHitbox();
    if (rThis->getMidY() > player->getMinY()) {
      pPlayer->hurt(dmg, Vec2(getVelocityX(), fSimpleHurtForce));
    }
}