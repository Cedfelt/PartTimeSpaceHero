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
  //this->schedule(schedule_selector(PlatformObject::update));
  staticBoody = true;
  platform = true;
  setVelocityX(-50);
  setPrevDir(GO_LEFT);
  objectSprite = Sprite::create("wagon1.png");
  objectSprite->getTexture()->setAliasTexParameters();
  objectSprite->setPosition(32,16);
  objectSprite->setScale(2);
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
  if(!bStarted){
    setVelocityX(0);
  }
  else if(!getVelocityX()){
    if(getPrevDir()==GO_LEFT){
      setVelocityX(50);
      setPrevDir(GO_RIGHT);
    }
    else{
      setVelocityX(-50);
      setPrevDir(GO_LEFT);
    }
  }
  setVelocityY(0*std::sin(cnt));
  cnt+=delta;
  auto h = getHitbox();
  Rect extRect;
  extRect.setRect(h->getMinX(),h->getMinY(),h->getMaxX()-h->getMinX(), h->getMaxY() - h->getMinY()+2);
  if (target->getHitbox()->intersectsRect(extRect)) {
    if(bObs){
      start(true);
    }
    target->moveX = (deltaX);
    target->moveY = (deltaY);
    /*target->addGravityToObject(false);*/
    target->platform = true;
  }
  else{
    target->addGravityToObject(true);
  }
  
  
  
}

void PlatformObject::setOnBoardStart(bool obs){
  bObs = obs;
}

void PlatformObject::start(bool start){
  bStarted = start;
}

bool PlatformObject::isBlocked(Rect* playerRect){
  auto platformRect = getHitbox();
  return playerRect->intersectsRect(*platformRect);
}

bool PlatformObject::setupAnimation() {
  return true;
}
