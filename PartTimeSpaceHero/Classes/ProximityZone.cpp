//
//  ProximityZone.cpp
//  PartTimeSpaceHero
//
//  Created by Anders Svensson on 07/11/16.
//
//

#include "ProximityZone.hpp"

bool ProximityZone::init() {
  //////////////////////////////
  // 1. super init first
  if (!GameObject::init())
  {
    return false;
  }
  this->bWallCollisions = false;
  addGravityToObject(false);
  setupHitbox(1.0f, 1.0f, 96, 96, 96, 96, true);
  getPhysicsBody()->setCategoryBitmask((int)PhysicsCategory::Player);
  getPhysicsBody()->setCollisionBitmask((int)PhysicsCategory::None);
  getPhysicsBody()->setContactTestBitmask((int)PhysicsCategory::Enemy);
  return true;
}

void ProximityZone::colideWith(GameObject* otherGo,const uint32_t otherType){
  if(otherType&(uint32_t)PhysicsCategory::Enemy){
    
  }
  
}

void ProximityZone::update(const float delta) {
  
}

bool ProximityZone::setupAnimation() {
  return true;
}
