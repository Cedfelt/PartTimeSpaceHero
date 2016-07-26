//
//  Player.cpp
//  PartTimeSpaceHero
//
//  Created by Anders Svensson on 10/04/16.
//
//

#include "ItemObject.hpp"

bool ItemObject::init() {
  //////////////////////////////
  // 1. super init first
  if (!GameObject::init())
  {
    return false;
  }
  
  
  this->schedule(schedule_selector(ItemObject::update));
  //addGravityToObject(false);
  setElastic(0.f);
  addGravityToObject(true);
  // SETUP ANIMATIONS
  pling = SoundFx::create();
  pling->loadEffect("pickup.aif", 0, 1, false);
  addChild(pling);
  objectSprite = cocos2d::Sprite::create("rifle.png");
  objectSprite->getTexture()->setAliasTexParameters();
  objectSprite->setPosition(16/2, 16/2);// Aling sprite in Hitbox
  addChild(objectSprite);
  const float xVel = cocos2d::random(-50, 50);
  return true;
}

void ItemObject::colideWith(GameObject* otherGo,const uint32_t otherType){
  if(otherType&(uint32_t)PhysicsCategory::Player){
    remove_object = true;
    pling->play(0.18f);
    const uint32_t itemId = cocos2d::random(1, (int)(E_ITEM_CNT)-1);
    otherGo->setItem((PlayerItem_ID)itemId);
    DialogObject* dia = DialogObject::create();
    dia->addLine(item_descriptions[itemId],2);
    dia->presentation = DialogObject::E_LINE_BY_LINE;
    dialogObjects->pushBack(dia);
    
  }
  
}

void ItemObject::update(const float delta) {
  
}

bool ItemObject::setupAnimation() {
  return true;
}