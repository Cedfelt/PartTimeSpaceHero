//
//  TurfelObject.cpp
//  PartTimeSpaceHero
//
//  Created by Anders Svensson on 27/05/16.
//
//

#include "TurfelObject.hpp"
#include "BabyTurfelObject.hpp"

bool TurfelObject::init() {
  //////////////////////////////
  // 1. super init first
  if (!GameObject::init())
  {
    return false;
  }
  
  
  this->schedule(schedule_selector(TurfelObject::AIUpdate),1.2);
  addGravityToObject(false);
  setElastic(1.f);
  // SETUP ANIMATIONS
  objectSprite = cocos2d::Sprite::create("turfel.png");
  objectSprite->getTexture()->setAliasTexParameters();
  objectSprite->setPosition(16, 16);// Aling sprite in Hitbox
  objectSprite->setScale(2);
  addChild(objectSprite);
  const float xVel = -50;
  setVelocityX(xVel);
  return true;
}

void TurfelObject::interActWithPlayer(GameObject* player){
  player->hurt(1, Vec2(0,0));
}

const float xAttackDistance = 100;
const float yAttackDistance = 500;
void TurfelObject::AIUpdate(const float delta) {
  
  
  if((std::abs(target->getPositionX() - getPositionX() )< xAttackDistance)){
    const float yDist = getPositionY() - target->getPositionY();
    if(yDist<yAttackDistance && yDist > 0){
      auto babyTurf = BabyTurfelObject::create();
      babyTurf->setupHitbox(0.1f, 1.0f, 16, 16, 16, 16, false);
      babyTurf->setObjectPositionX(getPositionX() + objectSprite->getTexture()->getPixelsWide()/2);
      babyTurf->setObjectPositionY(getPositionY());
      babyTurf->getPhysicsBody()->setCategoryBitmask((int)PhysicsCategory::Enemy);
      babyTurf->getPhysicsBody()->setCollisionBitmask((int)PhysicsCategory::None);
      babyTurf->getPhysicsBody()->setContactTestBitmask((int)PhysicsCategory::Player|(int)PhysicsCategory::PlayerPickups|(int)PhysicsCategory::Hazard);
      addToGameObjects.pushBack(babyTurf);
    }
  }
}

bool TurfelObject::setupAnimation() {
  return true;
}