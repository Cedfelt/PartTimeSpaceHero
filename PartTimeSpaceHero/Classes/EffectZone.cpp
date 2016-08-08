//
//  EffectZone.cpp
//  PartTimeSpaceHero
//
//  Created by Anders Svensson on 06/08/16.
//
//

#include "EffectZone.hpp"

bool EffectZone::init() {
  //////////////////////////////
  // 1. super init first
  if (!GameObject::init())
  {
    return false;
  }
  addGravityToObject(false);
  bWallCollisions = false;
  setVelocityX(0);
  setVelocityY(0);
  return true;
}

void EffectZone::colideWith(GameObject* otherGo,const uint32_t otherType){
  this->schedule(schedule_selector(EffectZone::isPlayerInEffectZone));
  if(otherType == (int)PhysicsCategory::Player){
    (*this.*playerEnter)(0);
  }
}

void EffectZone::isPlayerInEffectZone(float delta){
  if(!isPlayerInZone()){
    this->unschedule(schedule_selector(EffectZone::isPlayerInEffectZone));
    (*this.*playerLeave)(0);

  }
}



void EffectZone::config(std::string type){
  if(type == "HideLayer"){
    playerEnter = &EffectZone::hideLayer;
    playerLeave = &EffectZone::showLayer;
  }
  else if(type=="Hurl"){
    playerEnter = & EffectZone::hurlPlayer;
    playerLeave = & EffectZone::doNothing;
  }
  else{
    assert(0);
  }
}

bool EffectZone::doNothing(float delta){
  return true;
}

enum ZONE_EFFECT_STATUS{
  ZONE_EFFECT_NONE,
  ZONE_EFFECT_NORMAL,
  ZONE_EFFECT_REVERSE,
};

// HURL
const float hurlSpeed = 200.0;


bool EffectZone::hurlPlayer(float delta){
  step = 0;
  realHurl(delta);
  this->schedule(schedule_selector(EffectZone::realHurl),0,10, 0);
  stepSizeX = (getHitbox()->getMidX() - target->getObjectPositionX()) / 10.0f;
  stepSizeY = (getHitbox()->getMidY() - target->getObjectPositionY()) / 10.0f;
  return true;
}

void EffectZone::stepTowards(float delta){
//  target->setObjectPositionX(target->getObjectPositionX() + stepSizeX);
//  target->setObjectPositionY(target->getObjectPositionY() + stepSizeY);
//  step++;
//  if(step == 10){
//    schedule(schedule_selector(EffectZone::realHurl));
//  }
}

void EffectZone::addHurlSpeed(GameObject* obj,uint32_t hurlDir){
  if(hurlDir & GO_UP){
    target->setVelocityY(hurlSpeed);
    return;
  }
  else if(hurlDir & GO_DOWN){
    target->setVelocityY(-hurlSpeed);
    return;
  }
  else if(hurlDir & GO_LEFT){
    target->setVelocityX(-hurlSpeed);
    return;
  }
  else if(hurlDir & GO_RIGHT){
    target->setVelocityX(hurlSpeed);
    return;
  }
}

void EffectZone::realHurl(float delta){
  step++;
  if(step<=10){
    target->setVelocityX(0);
    target->setVelocityY(0);
    target->moveX = stepSizeX;
    target->moveY = stepSizeY;
    
    return;
  }
  if(hurlType == HURL_TYPE_START){
    if(!target->dissconeted){
      target->zoneEffectStatus = ZONE_EFFECT_NORMAL;
//      target->setObjectPositionX(getHitbox()->getMidX());
//      target->setObjectPositionY(getHitbox()->getMidY());
      target->addGravityToObject(false);
      target->setVelocityX(0);
      target->setVelocityY(0);
      target->dissconect();
      addHurlSpeed(target, hurlDirection);
    }
    else {
      // REVERSE STOP
      target->zoneEffectStatus = ZONE_EFFECT_NONE;
      target->addGravityToObject(true);
      target->reconect();
      addHurlSpeed(target, hurlDirectionReverse);
    }
    
  }
  else if(hurlType == HURL_TYPE_STOP){
    if(target->dissconeted){
      // NORMAL STOP
      target->zoneEffectStatus = ZONE_EFFECT_NONE;
      target->addGravityToObject(true);
      target->reconect();
      addHurlSpeed(target, hurlDirection);
      
    }
    else{
      // A REVERSE START
      target->zoneEffectStatus = ZONE_EFFECT_REVERSE;
//      target->setObjectPositionX(getHitbox()->getMidX());
//      target->setObjectPositionY(getHitbox()->getMidY());
      target->addGravityToObject(false);
      target->setVelocityX(0);
      target->setVelocityY(0);
      target->dissconect();
      addHurlSpeed(target, hurlDirectionReverse);
    }
  }
  else if(hurlType == HURL_TYPE_TRANSFER){
    if(target->zoneEffectStatus == ZONE_EFFECT_NORMAL){
      target->setVelocityX(0);
      target->setVelocityY(0);
//      target->setObjectPositionX(getHitbox()->getMidX());
//      target->setObjectPositionY(getHitbox()->getMidY());
      addHurlSpeed(target, hurlDirection);
    }
    else if(target->zoneEffectStatus == ZONE_EFFECT_REVERSE){
      target->setVelocityX(0);
      target->setVelocityY(0);
//      target->setObjectPositionX(getHitbox()->getMidX());
//      target->setObjectPositionY(getHitbox()->getMidY());
      addHurlSpeed(target, hurlDirectionReverse);
    }
    
  }
  unschedule(schedule_selector(EffectZone::realHurl));
}

// Hide Show Layer
bool EffectZone::hideLayer(float delta){
  layerToHide->setVisible(false);
  return true;
}

bool EffectZone::showLayer(float delta){
  layerToHide->setVisible(true);
  return true;
}

bool EffectZone::hurt(const int dmg, const Vec2 force){
  return false;
}