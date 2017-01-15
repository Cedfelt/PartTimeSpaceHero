//
//  SpecialFX.cpp
//  PartTimeSpaceHero
//
//  Created by Anders Svensson on 15/01/17.
//
//

#include "SpecialFX.hpp"
#include "BabyTurfelObject.hpp"
#include "CoinObject.hpp"
#include "Simple_Bullet.hpp"

bool SpecialFX::init() {
  //////////////////////////////
  // 1. super init first
  if (!GameObject::init())
  {
    return false;
  }
  addGravityToObject(false);
  bWallCollisions = false;
  setElastic(0.f);
  plingSFX = SoundFx::create();
  plingSFX->loadEffect("small_explosion.aif", 0, 1, false);
  addChild(plingSFX);
  dmg = 1;
  HP = 3;
  
  this->schedule(schedule_selector(SpecialFX::update));
  
  
  return true;
}

void SpecialFX::update(const float delta){
  const bool animation_complete = setAnimationOnce(prevAnimation);
  if(animation_complete){
    remove_object = true;
  }
}

void SpecialFX::setupFXType(FX_ID id){
  
  // Start Speed
  setVelocityX(0);
  setVelocityY(0);
  setupAnimation(id);
  objectSprite = cocos2d::Sprite::create();
  fx_id = id;
  
  if(id == BIG_EXPLOSION_FX){
    setAnimationOnce("poof");
    objectSprite->setPosition(0, 0);// Aling sprite in Hitbox
    objectSprite->setAnchorPoint(Point(0.5f, 0.25f));
  }
  else if(id == POOF_FX){
    setAnimationOnce("poof");
    objectSprite->setPosition(0, 0);// Aling sprite in Hitbox
    objectSprite->setAnchorPoint(Point(0.5f, 0.25f));
    speed = speed * 0.5f;
  }
  
  addChild(objectSprite);
  objectSprite->setScaleX(-1);
  
}

bool SpecialFX::setupAnimation(int monster_type) {
  // SETUP ANIMATIONS
  SpriteFrameCache::getInstance()->addSpriteFramesWithFile("poof.plist");
  
  if(fx_id == BIG_EXPLOSION_FX){
    addAnimation("poof", "poof", 1, 5, 0.075f);
  }
  else if(fx_id == POOF_FX){
    addAnimation("poof", "poof", 1, 5, 0.075f);
  }
  
  return true;
}
