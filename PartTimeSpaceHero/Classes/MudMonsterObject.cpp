//
//  MudMonsterObject.cpp
//  PartTimeSpaceHero
//
//  Created by Anders Svensson on 09/10/16.
//
//

#include "MudMonsterObject.hpp"
#include "BabyTurfelObject.hpp"
#include "CoinObject.hpp"


bool MudMonsterObject::init() {
  //////////////////////////////
  // 1. super init first
  if (!EnemyObject::init())
  {
    return false;
  }
  setScale(2);
  
  this->schedule(schedule_selector(MudMonsterObject::AIUpdate), 0.8);
  addGravityToObject(true);
  setElastic(0.f);
  plingSFX = SoundFx::create();
  plingSFX->loadEffect("small_explosion.aif", 0, 1, false);
  addChild(plingSFX);
  dmg = 1;
  
  // Start Speed
  setVelocityX(-speed);
  setPrevDir(GO_LEFT);
  objectSprite = cocos2d::Sprite::create();
  objectSprite->setPosition(8, 0);// Aling sprite in Hitbox
  objectSprite->setAnchorPoint(Point(0.5, 0));
  addChild(objectSprite);
  objectSprite->setScaleX(-1);
  return true;
}

void MudMonsterObject::colideWith(GameObject* oterhObj, const uint32_t otherType) {
  simpleWalkerHurt(oterhObj,otherType);
}

void MudMonsterObject::AIUpdate(const float delta) {
  if(isPlayerInZone()){
    // HUNT PLAYER
    approachPlayer(delta);
    setAnimation("mud_crawl");
  }
  else{
    // GO BACK TO START
    const float homeDistance = getObjectPositionX() - objectZone.getMidX();
    if(fabsf(homeDistance)<32){
      setVelocityX(0);
      setAnimation("mud_idle");
      const float player_dist = getObjectPositionX() - target->getObjectPositionX();
      if(player_dist>0){
        objectSprite->setScaleX(-1);
        setPrevDir(GO_LEFT);
      }
      else{
        objectSprite->setScaleX(1);
        setPrevDir(GO_RIGHT);
      }
    }
    else{
      if(homeDistance<0){
        walkAtDir(speed, GO_RIGHT);
      }
      else{
        walkAtDir(speed, GO_LEFT);
      }
    }
  }
}

void MudMonsterObject::deadState() {
  HP = 0;
  plingSFX->play(0.3f);
  setAnimation("mud_dead");
  this->bWallCollisions = false;
  setVelocityY(70);
  this->unschedule(schedule_selector(MudMonsterObject::AIUpdate));
  this->unschedule(schedule_selector(MudMonsterObject::update));
  removeWhenBelowZero();
  dropCoin(3);
}

bool MudMonsterObject::setupAnimation() {
  // SETUP ANIMATIONS
  
  SpriteFrameCache::getInstance()->addSpriteFramesWithFile("mud_monster.plist");
  addAnimation("mud_monster", "mud_idle", 1, 4, 0.3f);
  addAnimation("mud_monster", "mud_crawl", 6, 9, 0.3f);
  addAnimation("mud_monster", "mud_dead", 5, 5, 0.3f);
  
  return true;
}
