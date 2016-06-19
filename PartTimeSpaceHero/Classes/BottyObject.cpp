//
//  UfoObject.cpp
//  PartTimeSpaceHero
//
//  Created by Anders Svensson on 29/05/16.
//
//

#include "BottyObject.hpp"
#include "BabyTurfelObject.hpp"
#include "CoinObject.hpp"


bool BottyObject::init() {
  //////////////////////////////
  // 1. super init first
  if (!GameObject::init())
  {
    return false;
  }
  
  
  this->schedule(schedule_selector(BottyObject::AIUpdate),1.2);
  addGravityToObject(true);
  setElastic(0.f);
  // SETUP ANIMATIONS
  objectSprite = cocos2d::Sprite::create();
  spriteFrameCache = spriteFrameCache->getInstance();
  animationCache = animationCache->getInstance();
  spriteFrameCache->addSpriteFramesWithFile("botty.plist");
  addAnimation("Botty", "botty_idle", 1, 2, 0.2f);
  setAnimation("botty_idle");
  objectSprite->setPosition(12, 0);// Aling sprite in Hitbox
  objectSprite->setAnchorPoint(Point(0.5, 0));
  objectSprite->setScale(1);
  addChild(objectSprite);
  
  
  // Start Speed
  const float xVel = -50;
  setVelocityX(xVel);
  setPrevDir(GO_LEFT);
  objectSprite->setScaleX(-1);
  return true;
}

const float forceX = 100;
const float forceY = 170;
void BottyObject::interActWithPlayer(GameObject* player){
  auto p = player->getHitbox();
  auto r = getHitbox();
  if(getPrevDir() == GO_RIGHT){
    setVelocityX(50);
    
    if(p->getMinY() +10 > r->getMaxY()){
      player->hurt(0, Vec2(player->getVelocityX(),player->getVelocityY()));
    }
    else{
      player->hurt(1, Vec2(forceX,forceY));
    }
    
  }
  else{
    if(p->getMinY() +10 > r->getMaxY()){
      player->hurt(0, Vec2(player->getVelocityX(),player->getVelocityY()));
    }
    else{
      player->hurt(1, Vec2(-forceX,forceY));
    }
  }
  
}

//const float xAttackDistance = 300;
//const float yAttackDistance = 500;
//const float throwSpeedY = 180;
//const float throwSpeedX = 60.f;

void BottyObject::AIUpdate(const float delta) {
  if(getVelocityX()== 0){
    if(getPrevDir() == GO_LEFT){
      setVelocityX(50);
      setPrevDir(GO_RIGHT);
      objectSprite->setScaleX(1);
    }
    else{
      setVelocityX(-50);
      setPrevDir(GO_LEFT);
      objectSprite->setScaleX(-1);
    }
  }
  // Close To Gap
  
  const float lookAhead = 1.50f*getVelocityX() / delta;
  if (!isBlocked((uint32_t)((getPositionX() + lookAhead)/16.0), (uint32_t)(getPositionY() - 1.0)/16.0)){
    if (getPrevDir() == GO_LEFT) {
      setVelocityX(50);
      setPrevDir(GO_RIGHT);
      objectSprite->setScaleX(1);
    }
    else {
      setVelocityX(-50);
      setPrevDir(GO_LEFT);
      objectSprite->setScaleX(-1);
    }
  }
}

void BottyObject::deadState(){
  HP = 0;
  this->remove_object = true;
  auto coin = CoinObject::create();
  coin->setupHitbox(0.1f, 1.0f, 16, 16, 16, 16, false);
  coin->setObjectPositionX(getPositionX());
  coin->setObjectPositionY(getPositionY() + 5);
  coin->getPhysicsBody()->setCategoryBitmask((int)PhysicsCategory::PlayerPickups);
  coin->getPhysicsBody()->setCollisionBitmask((int)PhysicsCategory::None);
  coin->getPhysicsBody()->setContactTestBitmask((int)PhysicsCategory::Player|(int)PhysicsCategory::PlayerPickups|(int)PhysicsCategory::Hazard);
  coin->setVelocityX(cocos2d::random(-25, 25));
  coin->setVelocityY(cocos2d::random(10,50));
  coin->addGravityToObject(true);
  coin->setElastic(1);
  addToGameObjects.pushBack(coin);
}

