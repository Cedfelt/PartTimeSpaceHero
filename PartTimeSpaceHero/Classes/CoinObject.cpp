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
  addGravityToObject(false);
  // SETUP ANIMATIONS
  pling = SoundFx::create();
  pling->loadEffect("pling.aif", 0, 1, false);
  addChild(pling);
  objectSprite = cocos2d::Sprite::create();
  spriteFrameCache = spriteFrameCache->getInstance();
  animationCache = animationCache->getInstance();
  spriteFrameCache->addSpriteFramesWithFile("coin_sheet.plist");
  addAnimation("coin", "Coin1", 1, 4, 0.2f);
  setAnimation("Coin1");
  objectSprite->setPosition(19/2, 17/2);// Aling sprite in Hitbox
  addChild(objectSprite);
  return true;
}

void CoinObject::colideWith(GameObject* otherGo,const uint32_t otherType){
  if(otherType&(uint32_t)PhysicsCategory::Player){
    remove_object = true;
    pling->play(0.5f);
    otherGo->addCoins(1);
  }
  
}

void CoinObject::update(const float delta) {

}