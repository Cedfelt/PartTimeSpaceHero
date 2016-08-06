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
  return true;
}


void  ItemObject::generateItem(uint32_t itemType){
  itemId = itemType;
  if(itemType & E_RIFLE_ITEM){
    objectSprite = cocos2d::Sprite::create("rifle.png");
    objectSprite->getTexture()->setAliasTexParameters();
    objectSprite->setPosition(16/2, 16/2);// Aling sprite in Hitbox
    addChild(objectSprite);
  }
  else if(itemType & E_DASH_ITEM){
    objectSprite = cocos2d::Sprite::create("dash_icon.png");
    objectSprite->getTexture()->setAliasTexParameters();
    objectSprite->setPosition(16/2, 16/2);// Aling sprite in Hitbox
    addChild(objectSprite);
  }
  else if(itemType & E_SUPORT_ITEM){
    objectSprite = cocos2d::Sprite::create("blue_droid_icon.png");
    objectSprite->getTexture()->setAliasTexParameters();
    objectSprite->setPosition(16/2, 16/2);// Aling sprite in Hitbox
    addChild(objectSprite);
  }
  
}

void ItemObject::colideWith(GameObject* otherGo,const uint32_t otherType){
  random++;
  if(otherType&(uint32_t)PhysicsCategory::Player){
    remove_object = true;
    pling->play(0.18f);
    otherGo->setItem((PlayerItem_ID)(itemId ));
    dia->presentation = DialogObject::E_LINE_BY_LINE;
    if(otherGo->itemLevel<NUMBER_OF_ITEMS){
      dia->addLine("Use Red items by double tap", 3.5f);
    }
    dialogObjects->pushBack(dia);
    
  }
  
}

void ItemObject::update(const float delta) {
  
}

bool ItemObject::setupAnimation() {
  return true;
}