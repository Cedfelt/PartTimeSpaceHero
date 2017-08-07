//
//  Collectables.cpp
//  PartTimeSpaceHero
//
//  Created by Anders Svensson on 05/08/17.
//
//

#include "Collectables.hpp"

bool Collectables::init() {
  //////////////////////////////
  // 1. super init first
  if (!GameObject::init())
  {
    return false;
  }
  
  this->schedule(schedule_selector(Collectables::update));
  //addGravityToObject(false);
  setElastic(1.f);
  addGravityToObject(false);
  // SETUP ANIMATIONS
  pling = SoundFx::create();
  pling->loadEffect("pling.aif", 0, 1, false);
  addChild(pling);
  objectSprite = cocos2d::Sprite::create();
  SpriteFrameCache::getInstance()->addSpriteFramesWithFile("coin_sheet.plist");
  addAnimation("coin", "Coin1", 1, 4, 0.2f);
  //setAnimation("Coin1");
  if(cocos2d::random(0, 1)){
    objectSprite = cocos2d::Sprite::create("collectables.png");
  }
  else {
    objectSprite = cocos2d::Sprite::create("collectables.png");
  }
  
  objectSprite->getTexture()->setAliasTexParameters();
  objectSprite->setPosition(19/2, 17/2);// Aling sprite in Hitbox
  addChild(objectSprite);
  return true;
}

void Collectables::colideWith(GameObject* otherGo,const uint32_t otherType){
  if(otherType&(uint32_t)PhysicsCategory::Player){
    remove_object = true;
    pling->play(0.5f);
    otherGo->addCollectables(1);
  }
  
}

void Collectables::update(const float delta) {
  
}

bool Collectables::setupAnimation() {
  return true;
}
