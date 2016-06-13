//
//  Hero_Bullet.cpp
//  PartTimeSpaceHero
//
//  Created by Anders Svensson on 12/06/16.
//
//

#include "Hero_Bullet.hpp"
bool HeroBullet::init() {
  //////////////////////////////
  // 1. super init first
  if (!GameObject::init())
  {
    return false;
  }
  
  this->schedule(schedule_selector(HeroBullet::update));
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

void HeroBullet::colideWith(GameObject *otherGo){
  otherGo->hurt(dmg, Vec2(0,0));
  remove_object = true;
}

void HeroBullet::update(const float delta) {
  if(!getVelocityX()){
    remove_object = true;
  }
}