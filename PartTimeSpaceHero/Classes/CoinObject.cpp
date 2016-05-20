//
//  Player.cpp
//  PartTimeSpaceHero
//
//  Created by Anders Svensson on 10/04/16.
//
//

#include "CoinObject.hpp"

bool CoinObject::init() {
  //////////////////////////////
  // 1. super init first
  if (!GameObject::init())
  {
    return false;
  }
  
  this->schedule(schedule_selector(CoinObject::update));
  //addGravityToObject(false);
  setElastic(1.f);
  // SETUP ANIMATIONS
  objectSprite = cocos2d::Sprite::create("space_pig1.png");
  objectSprite->setPosition(8, 8);// Aling sprite in Hitbox
  addChild(objectSprite);
  return true;
}


void CoinObject::update(const float delta) {

}