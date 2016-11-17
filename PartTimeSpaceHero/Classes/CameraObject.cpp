//
//  CameraObject.cpp
//  PartTimeSpaceHero
//
//  Created by Anders Svensson on 17/11/16.
//
//

#include "CameraObject.hpp"

bool CameraObject::init() {
  //////////////////////////////
  // 1. super init first
  if (!GameObject::init())
  {
    return false;
  }
  this->bWallCollisions = false;
  addGravityToObject(false);
  return true;
}

void CameraObject::colideWith(GameObject* otherGo,const uint32_t otherType){
  if(otherType&(uint32_t)PhysicsCategory::Enemy){
    
  }
  
}

void CameraObject::update(const float delta) {
  
}

bool CameraObject::setupAnimation() {
  return true;
}
