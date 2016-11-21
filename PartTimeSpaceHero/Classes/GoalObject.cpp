//
//  GoalObject.cpp
//  PartTimeSpaceHero
//
//  Created by Anders Svensson on 21/05/16.
//
//

#include "GoalObject.hpp"


bool GoalObject::init() {
  //////////////////////////////
  // 1. super init first
  if (!GameObject::init())
  {
    return false;
  }
  
  this->schedule(schedule_selector(GoalObject::update));
  setScale(1);
  //addGravityToObject(false);
  setElastic(0);
  // SETUP ANIMATIONS
  objectSprite = cocos2d::Sprite::create(/*"SpaceshipA.png"*/);
  objectSprite->setPosition(32, 64);// Aling sprite in Hitbox
  objectSprite->getTexture()->setAliasTexParameters();
  addChild(objectSprite);
  setAnchorPoint(Point(0.5,0));
  return true;
}

void GoalObject::update(const float delta) {
  if(ai_state == SHUTDOWN_AI){
    if(setAnimationOnce("ai_of")){
      ai_state = DRAIN_AI;
    }
  }
  else if (ai_state == DRAIN_AI){
    setAnimationOnce("ai_drain");
    ai_state = NO_AI_STATE;
  }
}

void GoalObject::colideWith(GameObject* oterhObj, const uint32_t otherType){
  colided = true;
  if(ai_state == AI_ENABLE)
    ai_state = SHUTDOWN_AI;
}

bool GoalObject::setupAnimation() {
  return true;
}

void GoalObject::ai_setup(){
  SpriteFrameCache::getInstance()->addSpriteFramesWithFile("ai.plist");
  addAnimation("ai", "ai_idle", 1, 4, 0.18f);
  addAnimation("ai", "ai_of", 5, 10, 0.18f);
  addAnimation("ai", "ai_drain", 11, 17, 0.18f);
  setAnimation("ai_idle");
  ai_state = AI_ENABLE;
}
