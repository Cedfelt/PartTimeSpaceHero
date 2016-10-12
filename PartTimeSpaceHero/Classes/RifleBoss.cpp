//
//  RifleBoss.cpp
//  PartTimeSpaceHero
//
//  Created by Anders Svensson on 18/07/16.
//
//

#include "RifleBoss.hpp"
#include "Simple_Bullet.hpp"
#include "CoinObject.hpp"



bool RifleBoos::init() {
  //////////////////////////////
  // 1. super init first
  if (!EnemyObject::init())
  {
    return false;
  }
  
  
  this->schedule(schedule_selector(RifleBoos::AIUpdate), 0.8);
  addGravityToObject(true);
  setElastic(0.f);
  plingSFX = SoundFx::create();
  plingSFX->loadEffect("small_explosion.aif", 0, 1, false);
  addChild(plingSFX);
  dmg = 1;
  HP = 5;
  lastHP = HP;
  shotFired = false;
  // Start Speed
  setVelocityX(0);
  setPrevDir(GO_LEFT);
  objectSprite = cocos2d::Sprite::create();
  objectSprite->setPosition(12, 0);// Aling sprite in Hitbox
  objectSprite->setAnchorPoint(Point(0.5, 0));
  addChild(objectSprite);
  objectSprite->setScaleX(-1);
  return true;
}

void RifleBoos::colideWith(GameObject* oterhObj, const uint32_t otherType) {
  simpleWalkerHurt(oterhObj,otherType);
}

bool RifleBoos::isPlayerInBossArea(){
  auto playRect = target->getHitbox();
  return playRect->intersectsRect(bossArea);
}

void RifleBoos::walkAtDir(float speed, int dir){
  if(dir == GO_LEFT){
    objectSprite->setScaleX(-1);
    setAnimation("rifle_walk");
    setPrevDir(GO_LEFT);
    setVelocityX(-speed);
  }
  else if(dir == GO_RIGHT){
    objectSprite->setScaleX(1);
    setAnimation("rifle_walk");
    setPrevDir(GO_RIGHT);
    setVelocityX(speed);
  }
  
}

void RifleBoos::approachPlayer(const float delta){
  const float distX = getObjectPositionX() - target->getObjectPositionX();
  if(distX>0){
    walkAtDir(speed, GO_LEFT);
  }
  else{
    walkAtDir(speed, GO_RIGHT);
  }
}

void RifleBoos::escapeFromPlayer(const float delta){
  const float distX = getObjectPositionX() - target->getObjectPositionX();
  if(distX>0){
    walkAtDir(speed, GO_RIGHT);
  }
  else{
    walkAtDir(speed, GO_LEFT);
  }
}

bool RifleBoos::isFacingPlayer(){
  const float distX = getObjectPositionX() - target->getObjectPositionX();
  const int dir = getPrevDir();
  if(distX>0&&dir == GO_LEFT){
    return true;;
  }
  else if(distX<0&&dir == GO_RIGHT){
    return true;
  }
  return false;
}
void RifleBoos::shootAtPlayer(){
  if(isFacingPlayer()){
    auto babyTurf = SimpleBullet::create();
    const int dir = getPrevDir();
    babyTurf->setupHitbox(0.1f, 1.0f, 16, 16, 16, 16, false);
    babyTurf->setObjectPositionX(getPositionX() + 10);
    babyTurf->setObjectPositionY(getPositionY() + 8);
    babyTurf->getPhysicsBody()->setCategoryBitmask((int)PhysicsCategory::Enemy);
    babyTurf->getPhysicsBody()->setCollisionBitmask((int)PhysicsCategory::None);
    babyTurf->getPhysicsBody()->setContactTestBitmask((int)PhysicsCategory::Player|(int)PhysicsCategory::Hazard|(int)PhysicsCategory::PlayerProjectile);
    addToGameObjects.pushBack(babyTurf);
    if(dir == GO_RIGHT){
      babyTurf->setVelocityX(200);
    }
    else if(dir == GO_LEFT){
      babyTurf->setVelocityX(-200);
    }
  }
}

void RifleBoos::AIUpdate(const float delta) {
  
  if(isPlayerInBossArea()){
    if(getVelocityX() == 0.0f){
      speed = 85;
      approachPlayer(delta);
      if(cocos2d::random()%2){
        setVelocityY(185);
      }
      shotFired = false;
      shootCnt = 0;
      return;
    }
    //objectSprite->setColor(Color3B::RED);
    const int rng = cocos2d::random()%2;
    speed = 50;
    if(target->HP!=playerHp || HP!=lastHP){
      speed = 85;
      escapeFromPlayer(delta);
    }
    else{
    
      if((rng==0 && shotFired )&&shootCnt>=3){
        speed = 85;
        escapeFromPlayer(delta);
        if(cocos2d::random()%2){
          setVelocityY(170);
        }
        shotFired = false;
        shootCnt = 0;
      }
      else if(shootCnt<3){
        if(cocos2d::random()%2 && getVelocityY()==0){
          setVelocityY(170);
        }
        approachPlayer(delta);
        shootAtPlayer();
        shotFired = true;
        shootCnt++;
      }
    }
  }
  else{
    objectSprite->setColor(Color3B::WHITE);
    setVelocityX(0);
  }
  playerHp = target->HP;
  lastHP = HP;
}

void RifleBoos::deadState() {
  HP = 0;
  plingSFX->play(0.3f);
  setAnimation("rifle_dead");
  this->bWallCollisions = false;
  setVelocityY(70);
  this->unschedule(schedule_selector(RifleBoos::AIUpdate));
  this->unschedule(schedule_selector(RifleBoos::update));
  removeWhenBelowZero();
  dropCoin(3);
}

bool RifleBoos::setupAnimation() {
  // SETUP ANIMATIONS
  
  SpriteFrameCache::getInstance()->addSpriteFramesWithFile("RifeBoss.plist");
  addAnimation("GunMan", "rifle_walk", 1, 4, 0.2f);
  addAnimation("GunMan", "rifle_dead", 1, 1, 3.f);
  return true;
}
