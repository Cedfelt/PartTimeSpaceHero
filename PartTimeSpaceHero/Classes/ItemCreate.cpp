//
//  Player.cpp
//  PartTimeSpaceHero
//
//  Created by Anders Svensson on 10/04/16.
//
//

#include "ItemCreate.hpp"
#include "ItemObject.hpp"

bool ItemCreate::init() {
  //////////////////////////////
  // 1. super init first
  if (!GameObject::init())
  {
    return false;
  }
  bWallCollisions = false;
  landed = false;
  this->schedule(schedule_selector(ItemCreate::update));
  //addGravityToObject(false);
  setElastic(0.f);
  addGravityToObject(false);
  // SETUP ANIMATIONS
  pling = SoundFx::create();
  pling->loadEffect("small_explosion.aif", 0, 1, false);
  addChild(pling);
  
  //objectSprite->getTexture()->setAliasTexParameters();
  
  const float xVel = cocos2d::random(-50, 50);
  setVelocityX(0);
  setVelocityY(-25);
  
  // Animation
  objectSprite = cocos2d::Sprite::create();
  spriteFrameCache = spriteFrameCache->getInstance();
  animationCache = animationCache->getInstance();
  spriteFrameCache->addSpriteFramesWithFile("crate.plist");
  addAnimation("crate", "crate_fall", 1, 1, 5.0f);
  addAnimation("crate", "crate_land", 1, 5, 0.2f);
  setAnimation("crate_fall");
  objectSprite->setPosition(32/2, 32/2 + 32);// Aling sprite in Hitbox
  addChild(objectSprite);
  return true;
}

void ItemCreate::colideWith(GameObject* otherGo,const uint32_t otherType){
  if(otherType&(uint32_t)PhysicsCategory::Player || otherType&(uint32_t)PhysicsCategory::PlayerProjectile){
    otherGo->setVelocityY(otherGo->getVelocityY()*-1.0);
    otherGo->setVelocityX(otherGo->getVelocityX()*-1.0f);
    if(otherGo->getVelocityY()== 0.0f){
      otherGo->setVelocityY(50);
    }
    if(otherType&(uint32_t)PhysicsCategory::PlayerProjectile){
      otherGo->remove_object = true;
    }
    remove_object = true;
    pling->play(0.3f);
//    const uint32_t itemId = cocos2d::random(1, (int)(E_ITEM_CNT)-1);
//    otherGo->setItem((PlayerItem_ID)itemId);
    auto coin = ItemObject::create();
    coin->setupHitbox(0.1f, 1.0f, 16, 16, 16, 16, false);
    addToGameObjects.pushBack(coin);
    coin->setObjectPositionX(getObjectPositionX());
    coin->setObjectPositionY(getObjectPositionY()+4);
    coin->getPhysicsBody()->setCategoryBitmask((int)PhysicsCategory::PlayerPickups);
    coin->getPhysicsBody()->setCollisionBitmask((int)PhysicsCategory::None);
    coin->getPhysicsBody()->setContactTestBitmask((int)PhysicsCategory::Player | (int)PhysicsCategory::Hazard);
    
    
  }
  
}

void ItemCreate::update(const float delta) {
  if(getObjectPositionY()<goalY + 16.f){
    bWallCollisions = true;
  }
  else{
    bWallCollisions = false;
    return;
  }
  
  if(getVelocityY() == 0 && !landed){
    setAnimationOnce("crate_land");
    landed = true;
  }
}



bool ItemCreate::isBlocked(Rect* playerRect){
  auto platformRect = getHitbox();
  return playerRect->intersectsRect(*platformRect);
}