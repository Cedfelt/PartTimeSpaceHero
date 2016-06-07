//
//  PlatformObject.cpp
//  PartTimeSpaceHero
//
//  Created by Anders Svensson on 06/06/16.
//
//

#include "PlatformObject.hpp"

//
//  Player.cpp
//  PartTimeSpaceHero
//
//  Created by Anders Svensson on 10/04/16.
//
//

bool PlatformObject::init() {
  //////////////////////////////
  // 1. super init first
  if (!GameObject::init())
  {
    return false;
  }
  
  addGravityToObject(false);
  this->schedule(schedule_selector(PlatformObject::update));
  staticBoody = true;
  platform = true;
  setVelocityX(-50);
  setPrevDir(GO_LEFT);
  objectSprite = Sprite::create("stone_back.png");
  objectSprite->getTexture()->setAliasTexParameters();
  objectSprite->setPosition(32,16);
  objectSprite->setScaleX(2);
  addChild(objectSprite);
  setElastic(0);
  lastX = getObjectPositionX();
  lastY = getObjectPositionY();
  return true;
}

void PlatformObject::interActWithPlayer(GameObject* player){
  
}

static int dir_sign(const float num){
  if (num<0){
    return 1;
  }
  return -1;
}
float cnt = 0;
void PlatformObject::update(const float delta) {
  deltaX = getObjectPositionX() - lastX;
  deltaY = getObjectPositionY() - lastY;
  lastX = getObjectPositionX();
  lastY = getObjectPositionY();
  
  
  if(!getVelocityX()){
    if(getPrevDir()==GO_LEFT){
      setVelocityX(50);
      setPrevDir(GO_RIGHT);
    }
    else{
      setVelocityX(-50);
      setPrevDir(GO_LEFT);
    }
  }
}

bool PlatformObject::isBlocked(Rect* playerRect){
  auto platformRect = getHitbox();
  return playerRect->intersectsRect(*platformRect);
}