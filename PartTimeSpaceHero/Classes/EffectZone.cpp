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

bool EffectZone::hideLayer(float delta){
  layerToHide->setVisible(false);
}

bool EffectZone::showLayer(float delta){
  layerToHide->setVisible(true);
}

void EffectZone::config(std::string type){
  if(type == "HideLayer"){
    playerEnter = &EffectZone::hideLayer;
    playerLeave = &EffectZone::showLayer;
  }
  else{
    assert(0);
  }
}

