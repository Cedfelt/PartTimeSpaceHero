//
//  Hero_Bullet.cpp
//  PartTimeSpaceHero
//
//  Created by Anders Svensson on 12/06/16.
//
//

#include "Simple_Bullet.hpp"
bool SimpleBullet::init() {
  //////////////////////////////
  // 1. super init first
  if (!GameObject::init())
  {
    return false;
  }
  
  this->schedule(schedule_selector(SimpleBullet::update));
  addGravityToObject(false);
  setElastic(0.f);
  // SETUP ANIMATIONS
  objectSprite = cocos2d::Sprite::create("turfel_baby.png");
  objectSprite->getTexture()->setAliasTexParameters();
  objectSprite->setPosition(8, 8);// Aling sprite in Hitbox
  objectSprite->setScale(2);
  addChild(objectSprite);
  dmg = 1;
  return true;
}

void SimpleBullet::colideWith(GameObject* oterhObj,const uint32_t otherType){
  oterhObj->hurt(dmg, Vec2(0.5f*getVelocityX(), 0.5f*getVelocityY()));
  remove_object = true;
}

void SimpleBullet::update(const float delta) {
  if(!getVelocityX()){
    remove_object = true;
  }
}