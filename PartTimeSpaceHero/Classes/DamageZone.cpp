//
//  DamageZone.cpp
//  PartTimeSpaceHero
//
//  Created by Anders Svensson on 04/06/16.
//
//

#include "DamageZone.hpp"


bool DamageZone::init() {
  //////////////////////////////
  // 1. super init first
  if (!GameObject::init())
  {
    return false;
  }
  addGravityToObject(false);
  bWallCollisions = false;
  return true;
}

void DamageZone::colideWith(GameObject* otherGo,const uint32_t otherType){
  otherGo->hurt(dmg, Vec2(xForce,yForce));
}
bool DamageZone::hurt(const int dmg, const Vec2 force){
  return false;
}

bool DamageZone::setupAnimation() {
  return true;
}
