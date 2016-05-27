//
//  TurfelObject.cpp
//  PartTimeSpaceHero
//
//  Created by Anders Svensson on 27/05/16.
//
//

#include "TurfelObject.hpp"

bool TurfelObject::init() {
  //////////////////////////////
  // 1. super init first
  if (!GameObject::init())
  {
    return false;
  }
  
  this->schedule(schedule_selector(TurfelObject::update));
  addGravityToObject(false);
  setElastic(1.f);
  // SETUP ANIMATIONS
  objectSprite = cocos2d::Sprite::create("turfel.png");
  objectSprite->getTexture()->setAliasTexParameters();
  objectSprite->setPosition(16, 16);// Aling sprite in Hitbox
  objectSprite->setScale(2);
  addChild(objectSprite);
  const float xVel = -50;
  setVelocityX(xVel);
  return true;
}

void TurfelObject::interActWithPlayer(GameObject* player){
  player->hurt(1, Vec2(0,0));
}

void TurfelObject::update(const float delta) {
  
}