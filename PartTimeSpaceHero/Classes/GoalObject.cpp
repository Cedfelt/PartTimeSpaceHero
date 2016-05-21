//
//  GoalObject.cpp
//  PartTimeSpaceHero
//
//  Created by Anders Svensson on 21/05/16.
//
//

#include "GoalObject.hpp"


bool GoalObject::init() {
  //////////////////////////////
  // 1. super init first
  if (!GameObject::init())
  {
    return false;
  }
  
  this->schedule(schedule_selector(GoalObject::update));
  //addGravityToObject(false);
  setElastic(0.f);
  // SETUP ANIMATIONS
  objectSprite = cocos2d::Sprite::create("SpaceshipA.png");
  objectSprite->setPosition(32, 32);// Aling sprite in Hitbox
  addChild(objectSprite);
  return true;
}

void GoalObject::update(const float delta) {
  
}