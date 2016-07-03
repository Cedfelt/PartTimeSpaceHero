//
//  TurfelObject.cpp
//  PartTimeSpaceHero
//
//  Created by Anders Svensson on 27/05/16.
//
//

#include "BabyTurfelObject.hpp"

bool BabyTurfelObject::init() {
  //////////////////////////////
  // 1. super init first
  if (!GameObject::init())
  {
    return false;
  }
  
  this->schedule(schedule_selector(BabyTurfelObject::update));
  addGravityToObject(true);
  setElastic(0.f);
  // SETUP ANIMATIONS
  objectSprite = cocos2d::Sprite::create("turfel_baby.png");
  objectSprite->getTexture()->setAliasTexParameters();
  objectSprite->setPosition(8, 8);// Aling sprite in Hitbox
  objectSprite->setScale(2);
  addChild(objectSprite);
  const float xVel = 0;
  setVelocityY(-0.1);
  return true;
}

void BabyTurfelObject::colideWith(GameObject* otherObj,const uint32_t otherType){
  otherObj->hurt(1, Vec2(0,0));
}

void BabyTurfelObject::update(const float delta) {
  if(!getVelocityY()){
    remove_object = true;
  }
}