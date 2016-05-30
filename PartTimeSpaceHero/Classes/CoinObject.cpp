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
  pling->loadEffect("jet_pack_hum.aif", 0, 1, false);
  addChild(pling);
  objectSprite = cocos2d::Sprite::create();
  spriteFrameCache = spriteFrameCache->getInstance();
  animationCache = animationCache->getInstance();
  spriteFrameCache->addSpriteFramesWithFile("coin_sheet.plist");
  addAnimation("coin", "Coin1", 1, 4, 0.2f);
  setAnimation("Coin1");
  objectSprite->setPosition(19/2, 17/2);// Aling sprite in Hitbox
  addChild(objectSprite);
  const float xVel = cocos2d::random(-50, 50);
  setVelocityX(0);
  return true;
}

void CoinObject::interActWithPlayer(GameObject* player){
  remove_object = true;
  //pling->play(0.2f);
}

void CoinObject::update(const float delta) {

}