//
//  SmallWildLife.cpp
//  PartTimeSpaceHero
//
//  Created by Anders Svensson on 20/10/16.
//
//

#include "SmallWildLife.hpp"

bool SmallWildLife::init() {
  //////////////////////////////
  // 1. super init first
  if (!GameObject::init())
  {
    return false;
  }
  
  
  this->schedule(schedule_selector(SmallWildLife::AIUpdate),1.2);
  addGravityToObject(false);
  setElastic(0.f);
  SpriteFrameCache::getInstance()->addSpriteFramesWithFile("parrot.plist");
  objectSprite = Sprite::create();
  addAnimation("parrot", "parrot_fly", 1, 4, 0.2f);
  setAnimation("parrot_fly");
  objectSprite->getTexture()->setAliasTexParameters();
  objectSprite->setPosition(16, 16);// Aling sprite in Hitbox
  objectSprite->setScale(2);
  addChild(objectSprite);
  const float xVel = 60;
  objectSprite->setScaleX(2);
  setPrevDir(GO_RIGHT);
  setVelocityX(xVel);
  return true;
}

void SmallWildLife::colideWith(GameObject* oterhObj,const uint32_t otherType){
  if(otherType & (int)PhysicsCategory::Player){
    oterhObj->hurt(1,Vec2(getVelocityX(), 150));
  }
}

void SmallWildLife::AIUpdate(const float delta) {
  stupidWalk(delta);
  //walkInZone(delta);
  
}

bool SmallWildLife::setupAnimation() {
  return true;
}
