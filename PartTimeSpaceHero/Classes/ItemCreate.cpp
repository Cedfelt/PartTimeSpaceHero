//
//  Player.cpp
//  PartTimeSpaceHero
//
//  Created by Anders Svensson on 10/04/16.
//
//

#include "ItemCreate.hpp"

bool ItemCreate::init() {
  //////////////////////////////
  // 1. super init first
  if (!GameObject::init())
  {
    return false;
  }
  
  this->schedule(schedule_selector(ItemCreate::update));
  //addGravityToObject(false);
  setElastic(0.f);
  addGravityToObject(false);
  // SETUP ANIMATIONS
  pling = SoundFx::create();
  pling->loadEffect("pickup.aif", 0, 1, false);
  addChild(pling);
  objectSprite = cocos2d::Sprite::create("item_create.png");
  objectSprite->getTexture()->setAliasTexParameters();
  objectSprite->setPosition(32/2, 32/2 + 32);// Aling sprite in Hitbox
  addChild(objectSprite);
  const float xVel = cocos2d::random(-50, 50);
  setVelocityX(0);
  setVelocityY(-25);
  return true;
}

void ItemCreate::colideWith(GameObject* otherGo,const uint32_t otherType){
  if(otherType&(uint32_t)PhysicsCategory::Player){
    remove_object = true;
    pling->play(0.18f);
    const uint32_t itemId = cocos2d::random(1, (int)(E_ITEM_CNT)-1);
    otherGo->setItem((PlayerItem_ID)itemId);
  }
  
}

void ItemCreate::update(const float delta) {
  
}