//
//  TurfelObject.cpp
//  PartTimeSpaceHero
//
//  Created by Anders Svensson on 27/05/16.
//
//

#include "TurfelObject.hpp"
#include "BabyTurfelObject.hpp"

bool TurfelObject::init() {
  //////////////////////////////
  // 1. super init first
  if (!GameObject::init())
  {
    return false;
  }
  
  
  this->schedule(schedule_selector(TurfelObject::AIUpdate),1.2);
  addGravityToObject(false);
  setElastic(1.f);
  // SETUP ANIMATIONS
  if(cocos2d::random(0, 100)>50){
    objectSprite = cocos2d::Sprite::create("turfel.png");

  }
  else{
    objectSprite = cocos2d::Sprite::create("turfel_b.png");
  }
    objectSprite->getTexture()->setAliasTexParameters();
  objectSprite->setPosition(16, 16);// Aling sprite in Hitbox
  objectSprite->setScale(2);
  addChild(objectSprite);
  const float xVel = -50;
  setVelocityX(xVel);
  return true;
}

void TurfelObject::colideWith(GameObject* oterhObj,const uint32_t otherType){
  if(otherType & (int)PhysicsCategory::Player){
    oterhObj->hurt(1,Vec2(getVelocityX(), 150));
  }
}

void TurfelObject::AIUpdate(const float delta) {
  stupidWalk(delta);
  walkInZone(delta);
  
}

bool TurfelObject::setupAnimation() {
  return true;
}
