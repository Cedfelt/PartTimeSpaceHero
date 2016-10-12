//
//  SuporterObject.cpp
//  PartTimeSpaceHero
//
//  Created by Anders Svensson on 27/07/16.
//
//

#include "SuporterObject.hpp"
#include "BabyTurfelObject.hpp"
#include "CoinObject.hpp"

float lastXX;
float lastYY;
bool SuporterObject::init() {
  //////////////////////////////
  // 1. super init first
  if (!GameObject::init())
  {
    return false;
  }
  
  
  this->schedule(schedule_selector(SuporterObject::update));
  addGravityToObject(true);
  setElastic(0.f);
  plingSFX = SoundFx::create();
  plingSFX->loadEffect("small_explosion.aif", 0, 1, false);
  addChild(plingSFX);
  dmg = 1;
  bWallCollisions = false;
  // Start Speed
  setVelocityX(-speed);
  setPrevDir(GO_LEFT);
  objectSprite = cocos2d::Sprite::create();
  objectSprite->setPosition(12, 0);// Aling sprite in Hitbox
  objectSprite->setAnchorPoint(Point(0.5, 0));
  addChild(objectSprite);
  
  setupAnimation();
  setAnimation("suport_idle");
  
  
  
  return true;
}

void SuporterObject::colideWith(GameObject* oterhObj, const uint32_t otherType) {

}

const float xBack = -45;
const float xFront = 25;
float xOffset = xBack;

void SuporterObject::update(const float delta) {
  if((target->getPrevDir()==GO_RIGHT) && xOffset>xBack){
    objectSprite->setScaleX(1);
    xOffset-= (delta*20);
  }
  else if((target->getPrevDir()==GO_LEFT) && xOffset<xFront){
    objectSprite->setScaleX(-1);
    xOffset+= (delta*20);
  }
  xtick+=delta * 0.75;
  ytick+=delta * 0.55;
  yVar = 10*std::sin(xtick);
  xVar = 10*std::sin(ytick);
  const float newX = (target->getObjectPositionX()  + xVar + xOffset);
  const float newY = (target->getObjectPositionY() + 60 + yVar);
  setObjectPositionX(newX);
  setObjectPositionY(newY);

}

void SuporterObject::deadState() {
  
}

bool SuporterObject::setupAnimation() {
  // SETUP ANIMATIONS
  SpriteFrameCache::getInstance()->addSpriteFramesWithFile("suport.plist");
  addAnimation("suport", "suport_idle", 1, 4, 0.065f);
  addAnimation("suport", "suport_dead", 1, 4, 1.f);
  return true;
}
