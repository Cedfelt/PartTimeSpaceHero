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
  return true;
}

void DamageZone::colideWith(GameObject *otherGo){
  otherGo->hurt(dmg, Vec2(0,0));
}

